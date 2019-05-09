#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

void error(const char *msg) { perror(msg); exit(1); } // Error function used for reporting issue

int main(int argc, char *argv[]){

  //declare variables for network and fork use
  int listenSocketFD, establishedConnectionFD, portNumber, charsRead, client_address_len, pid;
  socklen_t sizeOfClientInfo;
  char plain_key[1000]; //variable to hold the data sent by client
  char self_name[256]; //variable to hold the name of the executed program
  memset(self_name, '\0', sizeof(self_name)); //clear out self name array
  strcpy(self_name, argv[0]); //fill self name array with first cmd line arg
  struct sockaddr_in serverAddress, clientAddress;

  if (argc < 2) { fprintf(stderr,"USAGE: %s port\n", argv[0]); exit(1); } // Check usage & args

  // Set up the address struct for this process (the server)
  memset((char *)&serverAddress, '\0', sizeof(serverAddress)); // Clear out the address struct
  portNumber = atoi(argv[1]); // Get the port number, convert to an integer from a string
  serverAddress.sin_family = AF_INET; // Create a network-capable socket
  serverAddress.sin_port = htons(portNumber); // Store the port number
  serverAddress.sin_addr.s_addr = INADDR_ANY; // Any address is allowed for connection to this process

  // Set up the socket
  listenSocketFD = socket(AF_INET, SOCK_STREAM, 0); // Create the socket
  if (listenSocketFD < 0) perror("ERROR opening socket");

  // Enable the socket to begin listening
  if (bind(listenSocketFD, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0) // Connect socket to port
    perror("ERROR on binding");

  listen(listenSocketFD, 5); // Flip the socket on - it can now receive up to 5 connections

  //this is the main while loop, acts like a multiserver that forks each new connection
  while(1) {
  // Accept a connection, blocking if one is not available until one connects
  sizeOfClientInfo = sizeof(clientAddress); // Get the size of the address for the client that will connect
  establishedConnectionFD = accept(listenSocketFD, (struct sockaddr *)&clientAddress, &sizeOfClientInfo); // Accept
  if (establishedConnectionFD < 0) perror("ERROR on accept");

  pid = fork(); //create new forked process
  if(pid == 0){ //if child, do all of the following

    //clear plain_key array
    memset(plain_key, '\0', sizeof(plain_key));

    charsRead = recv(establishedConnectionFD, plain_key, 999, 0); // Read the client's message from the socket

    //following block grabs the plaintext file from the client
    int count = 0;
    char plaintext[256]; //this variable will hold plaintext file name
    memset(plaintext, '\0', sizeof(plaintext)); //clear out the array
    while(plain_key[count] != '$'){ //keep adding characters until $ is hit
      plaintext[count] = plain_key[count];
      count++;
    }
    plaintext[count] = '\0'; //null terminate the array

    //following block grabs the key file from the client
    char key[256]; //this will hold the name of the key file
    memset(key, '\0', sizeof(key)); //clear out the array
    count++;
    int i = 0;
    while(plain_key[count] != '$'){ //kepp adding characters until & is hit
      key[i] = plain_key[count];
      i++;
      count++;
    }

    //following block grabs the name of the connecting client
    char name[256]; //this will hold the name
    memset(name, '\0', sizeof(name)); //clear out the array
    count++;
    int g = 0;
    while(plain_key[count] != '$'){ //keep adding characters until $ is hit
      name[g] = plain_key[count];
      g++;
      count++;
    }
    key[count] = '\0'; //null terminate key

    //open both the key and plaintext files for read only
    FILE* fp1 = fopen(plaintext, "r");
    FILE* fp2 = fopen(key, "r");

    //check to see if keygen file is long enough
    fseek(fp1, 0, SEEK_END);
    int byteCount1 = ftell(fp1); //length of plaintext file

    fseek(fp2, 0, SEEK_END);
    int byteCount2 = ftell(fp2); //length of key file

    if(byteCount2 < byteCount1){ //if the key is smaller than the plaintext, refuse
      perror("Key too small");
      exit(1);
    }

    //rewind the filepoints back to the beginning of the files
    rewind(fp1);
    rewind(fp2);
    char cipher_char; //this will hold the current cipher character
    char cipher_str[1000]; //this will hold the complete cipher string

    int j = 0;
    int k = 0;

    //grab the first characters of each file
    int p_char = fgetc(fp1);
    int k_char = fgetc(fp2);

    //encrypt the plaintext, keep going until end of plaintext file
    while(p_char != EOF){

      if(strcmp(name, "otp_enc") != 0){ //if something other than otp_enc is trying to connect, refuse
        perror("Only opt_enc can connect to opt_enc_d");
        exit(1);
        break;
      }

      if(p_char == '\n') // if a newline is encounterd, break the loop
        break;

      if(((int)p_char < 65 || (int)p_char > 91) && p_char != ' ' && p_char){ //if an invalid character is encountered, break the loop
        perror("Invalid character encountered\n");
        break;
      }

      //if a space is encounterd, turn it into a [, which the ascii char after Z
      if(p_char == ' ')
        p_char = '[';
      if(k_char == ' ')
        k_char = '[';

      //calculate the value of the cipher character
      cipher_char = (p_char+k_char-130)%27+65;

      //if the cipher character is a [, add a space to the cipher string
      if(cipher_char == '['){
        cipher_str[k] = ' ';
      }
      else{ //otherwise just add the cipher character to the cipher string
        cipher_str[k] = cipher_char;
      }

      //get the next characters from the files
      p_char = fgetc(fp1);
      k_char = fgetc(fp2);

      k++;
    }

    cipher_str[k] = '\0'; //null terminate the cipher string

    //close the files
    fclose(fp2);
    fclose(fp1);

    if (charsRead < 0) perror("ERROR reading from socket");

    charsRead = send(establishedConnectionFD, cipher_str, sizeof(cipher_str), 0); // Send cipher string to client
    if (charsRead < 0) perror("ERROR writing to socket");

    exit(0); // exit the forked process
    }
  else
  close(establishedConnectionFD); // Close the existing socket which is connected to the client
  }
  close(listenSocketFD); // Close the listening socket

  return 0;
}
