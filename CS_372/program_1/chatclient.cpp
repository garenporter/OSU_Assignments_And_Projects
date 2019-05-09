//Name: Garen Porter
//Program name: chatclient
//Program description: Creates a TCP socket using a port specified as a command line argument.
//                     Waits for a client to connect to the port. Once connection is established,
//                     both clients may take turns sending messages back and forth.
//Course name: CS 372 Intro to Computer Networks
//Program can run on any flip server
//Last modified: 2/6/2019
/*Citations:
    Beej's guide was used to assist with the socket related functions: https://beej.us/guide/bgnet/html/single/bgnet.html#simpleclient
    C++ reference guide was used to assist with some functions (such as sprintf and fgets): http://www.cplusplus.com/
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>

//Function description: Sets up the addrinfo struct with correct socket info
//Preconditions: Correct hostname and port were inputted at command line
//Postconditions: A socket is ready to be made from returned struct addrinfo
//Cites used: https://beej.us/guide/bgnet/html/single/bgnet.html#simpleclient
struct addrinfo* initiate_structs(char *hostname, char *port){

    //declare variables
    int status;
    struct addrinfo hints;
    struct addrinfo* res;

    // Set up the server address struct
    memset(&hints, 0, sizeof(hints));       //initialize struct hints to 0
    hints.ai_family = AF_INET;              //set hints to use IPv4
    hints.ai_socktype = SOCK_STREAM;        //set hints to use TCP

    //getaddrinfo sets up res with all of the socket info
    status = getaddrinfo(hostname, port, &hints, &res);

    //if getaddrinfo errored, exit and print the error message
    if(status != 0){
        perror("CLIENT: ERROR initiating addrinfo structs");
        exit(1);
    }

    return res;     //return res struct, which helps set up and connect the socket
}

//Function description: Creates socket for the client
//Preconditions: Struct addrinfo was setup correctly
//Postconditions: Socket has been successfully created
//Cites used: https://beej.us/guide/bgnet/html/single/bgnet.html#simpleclient
int create_socket(struct addrinfo *res){

    //declare socket file descriptor
    int socketFD;

    //create a TCP/IP socket
    socketFD = socket(res->ai_family, res->ai_socktype, res->ai_protocol); 

    //if socket creation errored, exit and print the error message
    if (socketFD < 0){
        perror("CLIENT: ERROR opening socket");
        exit(1);
    }

    return socketFD;    //return the socket
}

//Function description: Establishes a connection between the server and the client
//Preconditions: Socket was created successfully
//Postconditions: Server and client are now successfully connected
//Cites used: https://beej.us/guide/bgnet/html/single/bgnet.html#simpleclient
void connect_socket(struct addrinfo *res, int socketFD){

    //declare status variable
    int status;

    // Connect to the server using the TCP socket previously created
    status = connect(socketFD, res->ai_addr, res->ai_addrlen);

    //if connect errored, exit and pring the error message
    if (status < 0){ // Connect socket to address
        perror("CLIENT: ERROR connecting");
        exit(1);
    }
}

//Function description: Sends a message to the server over the socket connection
//Preconditions: Connection between client and server is established
//Postconditions: Message was successfully sent to server
//Cites used: https://beej.us/guide/bgnet/html/single/bgnet.html#simpleclient
void send_message(char *message, int socketFD) {

    //declare charsWritten variable
    int charsWritten;

    // Send message to server over TCP connection
    charsWritten = send(socketFD, message, strlen(message), 0); // Write to the server

    //if unable to send, send error message to stderr
    if (charsWritten < 0) perror("CLIENT: ERROR writing to socket");

}

//Function description: Blocks and recieves a message from the server
//Preconditions: Connection is established between client and server
//Postconditions: Message has been successfully recieved from server
//Cites used: https://beej.us/guide/bgnet/html/single/bgnet.html#simpleclient
char* rec_message(int socketFD) {

    //allocate heap space for server's message
    char* message = (char *)malloc(500*sizeof(char));
    int charsRead;

    //Clear out message
    memset(message, '\0', sizeof(message)); 

    //Read data from the socket, leaving \0 at end
    charsRead = recv(socketFD, message, 500, 0); 

    //if recv failed, send error message to stderr
    if (charsRead < 0) perror("CLIENT: ERROR reading from socket");

    //return the server's message
    return message;
}

//Function description: Chat loop between client and server
//Preconditions: Connection between client and server is has been established
//Postconditions: Client or server has quit and server is now waiting for another connection
//Cites used: http://www.cplusplus.com/
void p2p_chat(char *handle, int socketFD){

    //allocate heap space for the client and server messages
    char *message_rec = (char *)malloc(500*sizeof(char));
    char *user_message = (char *)malloc(500*sizeof(char));
    char *message_sent = (char *)malloc(510*sizeof(char));

    //this loop runs until either client or server quit
    while(1){

        //clear out message_rec
        memset(message_rec, '\0', sizeof(message_rec));

        //receive the server's message
        message_rec = rec_message(socketFD);
        
        //print server's message with the Server handle
        printf("Server> %s\n", message_rec);

        //close connection if server sends quit
        if(strcmp(message_rec, "quit") == 0){
            return;
        }

        //print the client handle
        printf("%s> ", handle);
        
        //clear out message_sent and user_message
        memset(message_sent, '\0', sizeof(message_sent));
        memset(user_message, '\0', sizeof(user_message));

        //get client's input
        fgets(user_message, 500, stdin);

        //chop off the trailing newline character
        strtok(user_message, "\n");

        //if client wants to quit, close socket
        if(strcmp(user_message, "quit") == 0){
            return;
        }

        //prepend the message with the handle
        //first copy the handle into message_sent
        strcpy(message_sent, handle);
        //next, concat > to the end of the handle
        strcat(message_sent, "> ");
        //finally, append the client's message to message_sent
        strcat(message_sent, user_message);

        //send the message to the server
        send_message(message_sent, socketFD);
        
    }
}


//Function description: sends server client's port number and waits to receive server's port number
//Preconditions: Socket connection between client and server has been successfully established
//Postconditions: Client and server are now ready to send messages to each other back and forth
//Cites used: http://www.cplusplus.com/
void initiate_contact(int socketFD, int client_port){

    //allocate heap space for port# and confirmation port#
    char *confirmation = (char *)malloc(16*sizeof(char));
    char *port = (char *)malloc(16*sizeof(char));
    int charsWritten, charsRead;

    //clear out port
    memset(port, '\0', sizeof(port));

    //cast client_port to a cstring
    sprintf(port, "%d", client_port);

    // Send PORTNUM to server
    printf("Sending PORTNUM to server.\n");
    send_message(port, socketFD);

    //receive server's port number
    printf("Waiting for server's PORTNUM...\n");
    confirmation = rec_message(socketFD);
    
    printf("CONNECTION ESTABLISHED, server's portnum response: %s\n", confirmation);
}

//Function description: Returns client's port number
//Preconditions: Socket connection between server and client has been established
//Postconditions: None
//Cites used: https://beej.us/guide/bgnet/html/single/bgnet.html#simpleclient
in_port_t get_client_port(struct sockaddr *res)
{
    //return client port number
    return (((struct sockaddr_in*)res)->sin_port);
}

int main (int argc, char *argv[]) {

    //allocate heap space for user's handle
    char *handle = (char *)malloc(10*sizeof(char)); 

    //store the port number
    char *port = argv[2];

    //check for corect number of cmd args. If wrong amount, exit and print usage message
    if (argc < 3) { fprintf(stderr,"USAGE: %s hostname port\n", argv[0]); exit(1); }

    //get user handle
    printf("Enter a username no longer than 10 characters: ");
    fgets(handle, 10, stdin);

    //remove trailing newline character from user handle
    strtok(handle, "\n");

    //initiate addrinfo struct, which helps setup the socket and establish the socket connection
    struct addrinfo* res = initiate_structs(argv[1], port);

    //create the socket
    int socketFD = create_socket(res);

    //connect to the server
    connect_socket(res, socketFD);

    //get the client's port number to send to the server
    int client_port = ntohs(get_client_port((struct sockaddr *)res->ai_addr));

    //initiate contact with server and finalize connection. Pass in client's port number.
    initiate_contact(socketFD, client_port);

    //chat with the server until either the server or client quit
    p2p_chat(handle, socketFD);

    //close the socket connection
    close(socketFD); // Close the socket
   
    //free the heap memory allocated in the addrinfo struct
    freeaddrinfo(res);
    
    return 0;

}