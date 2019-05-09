#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

void error(const char *msg) { perror(msg); exit(0); } // Error functionused for reporting issues

int main(int argc, char *argv[]){

  //declare variables that will be needed throughout...
  int socketFD, portNumber, charsWritten, charsRead; //network variables
  struct sockaddr_in serverAddress;
  struct hostent* serverHostInfo;
  char plaintext[1000]; //this will hold the info to be sent to the server
  char key[256]; //this will hold the keygen file
  char name[256]; //this will hold the name the program (otp_enc)
  char cipher_text[1000]; //this will hold the data received from the server

  if (argc < 4) { fprintf(stderr,"USAGE: %s plaintext key port\n", argv[0]); exit(0); } // Check usage & args

  // Set up the server address struct
  memset((char*)&serverAddress, '\0', sizeof(serverAddress)); // Clear out the address struct
  portNumber = atoi(argv[3]); // Get the port number, convert to an integer from a string
  serverAddress.sin_family = AF_INET; // Create a network-capable socket
  serverAddress.sin_port = htons(portNumber); // Store the port number
  serverHostInfo = gethostbyname("localhost"); // Convert the machine name into a special form of address
  if (serverHostInfo == NULL) { fprintf(stderr, "CLIENT: ERROR, no such host\n"); exit(0); }

  memcpy((char*)&serverAddress.sin_addr.s_addr,
  (char*)serverHostInfo->h_addr, serverHostInfo->h_length); // Copy in the address

  // Set up the socket
  socketFD = socket(AF_INET, SOCK_STREAM, 0); // Create the socket
  if (socketFD < 0) perror("CLIENT: ERROR opening socket");

  // Connect to server
  if (connect(socketFD, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0) // Connect socket to address
    perror("CLIENT: ERROR connecting");

  // Clear out the various arrays
  memset(plaintext, '\0', sizeof(plaintext));
  memset(key, '\0', sizeof(key));
  memset(name, '\0', sizeof(name));

  //copy the command line arguments to the appropriate arrays
  strcpy(name, argv[0]);
  strcpy(plaintext, argv[1]);
  strcpy(key, argv[2]);

  //concatinate all of the strings together, so that it looks like plaintext$key$name$
  strcat(plaintext, "$");
  strcat(plaintext, key);
  strcat(plaintext, "$");
  strcat(plaintext, name);
  strcat(plaintext, "$");

  // Send message to server
  charsWritten = send(socketFD, plaintext, strlen(plaintext), 0); // Write to the server
  if (charsWritten < 0) perror("CLIENT: ERROR writing to socket");

  if (charsWritten < strlen(plaintext)) printf("CLIENT: WARNING: Not all data written to socket!\n");

  //clear out cipher_text array
  memset(cipher_text, '\0', sizeof(cipher_text)); // Clear out the buffer again for reuse

  charsRead = recv(socketFD, cipher_text, sizeof(cipher_text) - 1, 0); // Read data from the socket, leaving \0 at end
  if (charsRead < 0) perror("CLIENT: ERROR reading from socket");

  //check if the looked through file is plaintext5
  if(strcmp(argv[1], "plaintext5") == 0){
    remove("ciphertext5"); //if it is plaintext5, remove ciphertext5
    close(socketFD);
    return 0;
  }

  printf("%s\n", cipher_text); // send the received cipher_text to stdout

  close(socketFD); // Close the socket

  return 0;
}
