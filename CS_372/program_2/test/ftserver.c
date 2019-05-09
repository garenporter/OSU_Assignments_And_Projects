//Name: Garen Porter
//Program name: ftserver
//Program description: Waits on a control socket and accepts incoming clients. Sends either a directory listing or file over a separate data connection.
                       //Data connection is closed after requested action has been completed and a new client may connect.
//Course name: CS 372 Intro to Computer Networks
//Program can be ran on any flip server
//Last modified: 3/2/2019
/*Citations:
    Beej's guide was used to assist with the socket related functions: https://beej.us/guide/bgnet/html/single/bgnet.html#simpleclient
    C++ reference guide was used to assist with some functions (such as sprintf and fgets): http://www.cplusplus.com/
    Help with sleep functions: https://linux.die.net/man/3/sleep
    Help with getting directory listing: https://stackoverflow.com/questions/4204666/how-to-list-files-in-a-directory-in-a-c-program
    Help with finding file size - https://stackoverflow.com/questions/238603/how-can-i-get-a-files-size-in-c
    Help with sending file - https://stackoverflow.com/questions/11952898/c-send-and-receive-file
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
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <fcntl.h>

//Function description: Sets up the addrinfo struct with correct socket info
//Preconditions: Valid port was inputted at command line
//Postconditions: A socket is ready to be made from returned struct addrinfo
//Cites used: https://beej.us/guide/bgnet/html/single/bgnet.html#simpleclient
struct addrinfo* initiate_structs(char *port){

    //declare variables
    int status;
    struct addrinfo hints;
    struct addrinfo* res;

    // Set up the server address struct
    memset(&hints, 0, sizeof(hints));       //initialize struct hints to 0
    hints.ai_family = AF_INET;              //set hints to use IPv4
    hints.ai_socktype = SOCK_STREAM;        //set hints to use TCP
    hints.ai_flags = AI_PASSIVE;

    //getaddrinfo sets up res with all of the socket info
    status = getaddrinfo(NULL, port, &hints, &res);

    //if getaddrinfo errored, exit and print the error message
    if(status != 0){
        perror("SERVER: ERROR initiating addrinfo structs");
        exit(1);
    }

    return res;     //return res struct, which helps set up and connect the socket
}

//Function description: Sets up addrinfo struct for the data connection using client port number and hostname
//Preconditions: Client inputed the correct arguments at command line
//Postconditions: A socket is ready to made using the returned addrinfo struct
//Cites used: https://beej.us/guide/bgnet/html/single/bgnet.html#simpleclient
struct addrinfo* initiate_structs_client(char *port, char *hostname){

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
        perror("SERVER: ERROR initiating addrinfo structs for client");
        exit(1);
    }

    return res;     //return res struct, which helps set up and connect the socket
}

//Function description: Creates a socket using an addrinfo struct
//Preconditions: addrinfo was successfully created with correct info
//Postconditions: Socket has been successfully created and is ready to connect
//Cites used: https://beej.us/guide/bgnet/html/single/bgnet.html#simpleclient
int create_socket(struct addrinfo *res){

    //declare socket file descriptor
    int socketFD;

    //create a TCP/IP socket
    socketFD = socket(res->ai_family, res->ai_socktype, res->ai_protocol); 

    //if socket creation errored, exit and print the error message
    if (socketFD < 0){
        perror("SERVER: ERROR opening socket");
        exit(1);
    }

    return socketFD;    //return the socket
}

//Function description: Connects to a socket
//Preconditions: Socket and addrinfo struct was successfully created
//Postconditions: Socket represented by socketFD has been successfully connected to
//Cites used: https://beej.us/guide/bgnet/html/single/bgnet.html#simpleclient
void connect_socket(struct addrinfo *res, int socketFD){

    //declare status variable
    int status;

    // Connect to the TCP socket previously created
    status = connect(socketFD, res->ai_addr, res->ai_addrlen);

    //if connect errored, exit and pring the error message
    if (status < 0){ // Connect socket to address
        perror("SERVER: ERROR connecting");
        exit(1);
    }
}

//Function description: Binds a socket
//Preconditions: Socket has been successfully connected to
//Postconditions: Socket is ready to listen on
//Cites used: https://beej.us/guide/bgnet/html/single/bgnet.html#simpleclient
void bind_socket(struct addrinfo *res, int socketFD){
    //declare status variable
    int status;

    //bind the TCP socket using an initiated addrinfo struct
    status = bind(socketFD, res->ai_addr, res->ai_addrlen);

    //if bind failed, exit and print an error message
    if(status < 0){
        close(socketFD);
        perror("SERVER: ERROR binding socket");
        exit(1);
    }
}

//Function description: Begins listening to a socket, allowing incoming connections to be accepted
//Preconditions: Socket has been created and bound
//Postconditions: Socket is ready to receive incoming connections
//Cites used: https://beej.us/guide/bgnet/html/single/bgnet.html#simpleclient
void listen_socket(int socketFD){
    //declare status variable
    int status;

    //begin listening to socket and accept up to 5 connections
    status = listen(socketFD, 5);

    //if list fails, exit and print an error message
    if(status < 0){
        close(socketFD);
        perror("SERVER: ERROR listening");
        exit(1);
    }
}

//Function description: Sends the current directory to the client over the data connection
//Preconditions: Client send the -l command
//Postconditions: Client has been sent the current directory and the data connection has been closed
//Cites used: 
//https://linux.die.net/man/3/sleep
//https://stackoverflow.com/questions/4204666/how-to-list-files-in-a-directory-in-a-c-program
void send_directory_listing(char *hostname, char *port){
    //declare variables
    struct addrinfo *res;
    DIR *directory;
    struct dirent *dir;
    int socketFD;

    //sleep for 1 second to allow time for client to setup data socket
    sleep(1);

    //connet to data socket
    res = initiate_structs_client(port, hostname);      //use client's hostname and the data port to initiate an addrinfo struct
    socketFD = create_socket(res);                      //create the socket using the addrinfo struct created in the previous line
    connect_socket(res, socketFD);                      //connect to the socket created in the previous line

    //allocate memory to hold the various filenames in the directory
    char *file = (char *)malloc(500*sizeof(char));

    //open the current directory and parse through its contents
    directory = opendir("./");
    if(directory){
        printf("Sending directory listing...\n");
        while((dir = readdir(directory)) != NULL){      //while there are still directory contents to read
            memset(file, '\0', sizeof(file));           //set all contents of file to NULL
            strcpy(file, dir->d_name);                  //copy file or directory name into file
            send(socketFD, file, strlen(file), 0);      //send file to the client
            usleep(5*1000);                             //sleep for 0.5 seconds, without this things get weird on the client side
        }
        closedir(directory);                            //close the directory
    }
    //sleep for 0.5 seconds before sending done message
    usleep(5*1000);                         

    //let client know we are done sending directory contents
    char *done = "_done_!";
    send(socketFD, done, strlen(done), 0);

    printf("Directory listing sent.\n");

    //close socket and free allocated memory
    close(socketFD);
    freeaddrinfo(res);
}

//Function description: Sends a file to the client over a separata data connection
//Preconditions: Client sent the -g command
//Postconditions: Client has been sent the requested file and the data connection has been closed
//Cites used: 
//https://stackoverflow.com/questions/238603/how-can-i-get-a-files-size-in-c
//https://stackoverflow.com/questions/11952898/c-send-and-receive-file
int send_file(char *filename, char *hostname, char *port){
    //declare variables
    struct addrinfo *res;
    struct stat fileStats;
    int socketFD;
    int file_size, fileFD;
    int character;
    FILE *file;

    //sleep for 1 second to allow time for client to setup data socket
    sleep(1);

    //connet to data socket
    res = initiate_structs_client(port, hostname);      //use client's hostname and the data port to initiate an addrinfo struct
    socketFD = create_socket(res);                      //create the socket using the addrinfo struct created in the previous line
    connect_socket(res, socketFD);                      //connect to the socket created in the previous line

    //open file in read-only mode and error if file fails to open
    fileFD = open(filename, O_RDONLY);
    if(fileFD < 0){
        printf("FAILED TO OPEN file: %s\n", filename);
        return -1;
    }

    //get the statss of the file and store it in fileStats
    if(fstat(fileFD, &fileStats) < 0){
        printf("FAILED fstat(): %s", filename);
        return -1;
    }

    //get the file size from fileStats and close the file
    file_size = fileStats.st_size;
    close(fileFD);

    //open the file in read-only mode
    file = fopen(filename, "r");
    
    //allocate enough memory to hold the contents of the file
    char *fileText = (char *)malloc(file_size*sizeof(char));
    memset(fileText, '\0', sizeof(fileText));

    //store the contents of the file in fileText and close the file
    int buffer = fread(fileText, 1, file_size, file);
    fclose(file);

    //flush both stdout and stdin to ensure a clean file-sending process
    fflush(stdout);
    fflush(stdin);

    //send the file to the client
    void *location = fileText;
    while(buffer > 0){
        int written_bytes = send(socketFD, location, strlen(location), 0);  //send as many bytes as possible and record the number of bytes sent

        if(written_bytes < 0){                                              //if the amount of bytes sent is less than 0, error and return
            printf("SERVER: ERROR SENDING FILE\n");
            return -1;
        }

        buffer -= written_bytes;                                            //subtract the amount of sent bytes from total bytes in file being sent
        location += written_bytes;                                          //add written bytes to location so that location knows where to begin sending from next iteration
        usleep(5*1000);                                                     //sleep for 0.5 seconds to give client time to perform its duties
    }
    
    //sleep for 1 second before sending done
    sleep(1);

    //let client know we are done sending the file
    char *done = "_done_!";
    send(socketFD, done, strlen(done), 0);

    printf("TRANSFER COMPLETE\n");

    //close socket and free allocated memory
    close(socketFD);
    freeaddrinfo(res);
    
    return 0;
    
}

//Function description: Checks whether or not a file exists in the current directory
//Preconditions: Client has requested a file to be transferred
//Postconditions: File is determined whether or not it exists
//Cites used: //https://stackoverflow.com/questions/4204666/how-to-list-files-in-a-directory-in-a-c-program
int file_exists(char *filename){
    //declare variables
    DIR *directory;
    struct dirent *dir;

    //allocate memory to hold file and directory names
    char *file_temp = (char *)malloc(500*sizeof(char));

    //open the directory and compare each file or directory with the client's requested filename
    directory = opendir("./");
    if(directory){
        while((dir = readdir(directory)) != NULL){          //while there are still directory contents to read
            memset(file_temp, '\0', sizeof(file_temp));     //set each element in file_temp to NULL
            strcpy(file_temp, dir->d_name);                 //copy directory or file into file_temp
            if(strcmp(filename, file_temp) == 0){           //compare filename to file_temp, if they are the same, close directory and return true
                closedir(directory);
                return 1;
            }
        }
        closedir(directory);                                //close the directory
    }
    //return false
    return -1;
}

//Function description: Gets the client command line info and hostname, determines which actions to take by parsing the client's command.
                      //Will either send the client a directoy listing, a file, or an error.
//Preconditions: Client has successfully connected to the control socket
//Postconditions: Client has been serviced appropriately by either receiving an error, a file, or a directory listing
//Cites used:
//http://www.cplusplus.com/
//https://beej.us/guide/bgnet/html/single/bgnet.html#simpleclient
void handle_connection(int socketFD){
    //declare messages that may be sent to the client
    char *no_file = "SERVER: FILE NOT FOUND";
    char *ready = "name?";
    char *invalid = "SERVER: INVALID COMMAND";
    char *good_file = "_good_!";

    //declare structures to hold client arguments
    char *port = (char *)malloc(500*sizeof(char));
    char *hostname = (char *)malloc(500*sizeof(char));
    char *command = (char *)malloc(500*sizeof(char));
    char *filename = (char *)malloc(500*sizeof(char));

    //recieve client port number
    memset(port, '\0', sizeof(port));
    recv(socketFD, port, 500, 0);
    printf("\nData port: %s\n", port);

    //receive client hostname
    memset(hostname, '\0', sizeof(hostname));
    recv(socketFD, hostname, 500, 0);
    printf("Client hostname: %s\n", hostname);

    //receive client command
    memset(command, '\0', sizeof(command));
    recv(socketFD, command, 500, 0);
    printf("Command: %s\n\n", command);

    //if command is -l, send directory
    if(strcmp(command, "-l") == 0){
        send_directory_listing(hostname, port);
    }

    //if command is -g, get file, check file exists, then send file
    else if(strcmp(command, "-g") == 0){
        //ask for filename     
        send(socketFD, ready, strlen(ready), 0);

        //get filename
        memset(filename, '\0', sizeof(filename));
        recv(socketFD, filename, 500, 0);

        //check if file exists
        if(file_exists(filename) < 0){
            printf("File does not exist!\n");          
            send(socketFD, no_file, strlen(no_file), 0);
            return;
        }

        //let client know the file exists
        printf("Requested file: %s\n\n", filename);
        send(socketFD, good_file, strlen(good_file), 0);

        //send file to client
        if(send_file(filename, hostname, port) < 0){
            printf("ERROR SENDING FILE\n");
            return;
        }

    }

    //else the command is invalid, so sent invlalid command error to client
    else {
        printf("Command invalid, closing connection with client.\n");
        send(socketFD, invalid, strlen(invalid), 0);
        return;
    }

    return;
}

//Function description: Endless loop that continuously accepts clients and handles their requests. After client is accepted, its request is handled.
                      //After client's request has been handled, the connection is disconnected and a new connection is waited for.
//Preconditions: Socket has been successfully setup and is listening.
//Postconditions: Client sockets have been cleaned up.
//Cites used: https://beej.us/guide/bgnet/html/single/bgnet.html#simpleclient
void accept_connections(int socketFD){
    //loop until SIGINT is received
    while(1){
        //declare variables for new control connections
        struct sockaddr_storage client_addr;
        socklen_t size;
        int socketFD_new;

        //get size of client socket struct
        size = sizeof(client_addr);

        //accept the incoming connection
        printf("\nWaiting for incoming connection...\n");
        socketFD_new = accept(socketFD, (struct sockaddr *)&client_addr, &size);
        printf("Accepted incoming connection!\n");

        //if socket accept fails, wait for a new connection
        if(socketFD_new < 0){
            printf("Failed to accept socket\n");
            continue;
        }
        
        //handle the client's request
        handle_connection(socketFD_new);

        //close the control connection and wait for a new connection
        printf("Closing control connection with client.\n");
        close(socketFD_new);
    }
}

//main function sets up the main server socket (control socket) and starts the accept_connections loop.
int main(int argc, char **argv){

    //declare server socket variables for control connection
    struct addrinfo *res;
    int socketFD;

    //check for correct number of commandline arguments
    if(argc != 2){
        perror("INVALID ARGS: ./fserver <SERVER_PORT>\n");
        freeaddrinfo(res);
        exit(1);
    }

    printf("Server open on %s\n", argv[1]);

    res = initiate_structs(argv[1]);        //initiate the server's addrinfo struct
    socketFD = create_socket(res);          //create the server control socket
    bind_socket(res, socketFD);             //bind the server control socket
    listen_socket(socketFD);                //start listening on the socket
    accept_connections(socketFD);           //start the endless loop that continually services client requests

    //close socket and free allocated data
    close(socketFD);
    freeaddrinfo(res);

    return 1;
}