#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

void error(const char *msg) { perror(msg); exit(1); } // Error function used for reporting issue

int main(int argc, char *argv[]){

  int listenSocketFD, establishedConnectionFD, portNumber, charsRead, pid;
  socklen_t sizeOfClientInfo;
  char plain_key[1000]; // this will hold the stuff sent by the client
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
  if (listenSocketFD < 0) error("ERROR opening socket");

  // Enable the socket to begin listening
  if (bind(listenSocketFD, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0) // Connect socket to port
    perror("ERROR on binding");

  listen(listenSocketFD, 5); // Flip the socket on - it can now receive up to 5 connections
  while(1) {
  // Accept a connection, blocking if one is not available until one connects
  sizeOfClientInfo = sizeof(clientAddress); // Get the size of the address for the client that will connect
  establishedConnectionFD = accept(listenSocketFD, (struct sockaddr *)&clientAddress, &sizeOfClientInfo); // Accept
  if (establishedConnectionFD < 0) perror("ERROR on accept");

  pid = fork();
  if(pid == 0){
    // Get the message from the client and display it
    memset(plain_key, '\0', sizeof(plain_key));

    charsRead = recv(establishedConnectionFD, plain_key, 999, 0); // Read the client's message from the socket

    //following block grabs the plaintext file from the client
    int count = 0;
    char plaintext[256]; // this will hold the plaintext file to be opened
    memset(plaintext, '\0', sizeof(plaintext));
    while(plain_key[count] != '$'){ //add all of the characters before $ to plaintext
      plaintext[count] = plain_key[count];
      count++;
    }
    plaintext[count] = '\0'; //set NULL terminator

    //following block grabs the key file from the client
    char key[256]; //This will hold the key file to be opened
    memset(key, '\0', sizeof(key));
    count++;
    int i = 0;
    while(plain_key[count] != '$'){ //add all of the characters before $ to key
      key[i] = plain_key[count];
      i++;
      count++;
    }
    key[count] = '\0';

    //open both the plaintext and key file for read/write
    FILE* fp1 = fopen(plaintext, "r+");
    FILE* fp2 = fopen(key, "r");

    //check to see if keygen file is long enough
    fseek(fp1, 0, SEEK_END); // set file pointer to the end of plaintext
    int byteCount1 = ftell(fp1); // grab the position of the pointer

    fseek(fp2, 0, SEEK_END); // set the file pointer to the end of key
    int byteCount2 = ftell(fp2); // grab the postion of the pointer

    rewind(fp1); // reset plaintext file pointer
    rewind(fp2); // reset key file pointer
    char cipher_char; // this will hold the current decoded character
    char cipher_str[1000]; // this will hold the string of decoded characters
    //memset(cipher, '\0', sizeof(cipher));
    int temp = 0;
    int k = 0;
    int p_char = fgetc(fp1); //grab first character in plaintext
    int k_char = fgetc(fp2); //grab first character in key

    //decrypt the plaintext
    while(p_char != EOF){
      if(byteCount2 < byteCount1){ // check if length of key is less than plaintext
        perror("Key too small, exiting\n"); //error
        break;
      }

      if(p_char == '\n') // if a newline is encounterd, break the loop
        break;

      if(((int)p_char < 65 || (int)p_char > 91) && p_char != ' ' && p_char){ //if an invalid character is encountered, break the loop
        perror("Invalid character encountered\n");
        break;
      }

      //[ is the ascii character after Z, so we can treat it as a space
      if(p_char == ' ') //if p_char is a space, turn it into a [
        p_char = '[';
      if(k_char == ' ') //if k_char is a space, turn it into a [
        k_char = '[';

      //if char less than 0, adjust so modulo works.
      temp = p_char - k_char;
      if(temp < 0) // if temp is negative, add 27 to it
        temp += 27;

      cipher_char = temp%27+65; // this is the decrypted character

      if(cipher_char == '[') // if the character is a [, turn it into a space
          cipher_str[k] = ' ';
      else
        cipher_str[k] = cipher_char; // add the decrypted characte to cipher_string

      //get the next character in the plaintext and key files
      p_char = fgetc(fp1);
      k_char = fgetc(fp2);

      k++;
    }

    //close the files
    fclose(fp2);
    fclose(fp1);

    if (charsRead < 0) error("ERROR reading from socket");

    // Send a Success message back to the client
    charsRead = send(establishedConnectionFD, cipher_str, sizeof(cipher_str), 0); // Send success back
    if (charsRead < 0) error("ERROR writing to socket");

    exit(0); //exit the forked process
  }
  else
  close(establishedConnectionFD); // Close the existing socket which is connected to the client
  }
  close(listenSocketFD); // Close the listening socket

  return 0;
}
