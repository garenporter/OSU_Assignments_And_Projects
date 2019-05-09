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

  //variables for network use
  int socketFD, portNumber, charsWritten, charsRead;
  struct sockaddr_in serverAddress;
  struct hostent* serverHostInfo;
  char plaintext[1000]; //variable to hold data to send to server
  char key[256]; //variable to hold the key file name
  char name[256]; //variable to hold the name of the executing program
  char cipher_text[1000]; //variable to hold the data received by the server

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

  // Clear out the various variable arrays
  memset(plaintext, '\0', sizeof(plaintext));
  memset(key, '\0', sizeof(key));
  memset(name, '\0', sizeof(name));
  //assign each variable its appropriate command line arg
  strcpy(name, argv[0]);
  strcpy(plaintext, argv[1]);
  strcpy(key, argv[2]);

  //concatinate the command line args together to make the form plaintext$key$name$
  strcat(plaintext, "$");
  strcat(plaintext, key);
  strcat(plaintext, "$");
  strcat(plaintext, name);
  strcat(plaintext, "$");

  // Send message to server
  charsWritten = send(socketFD, plaintext, strlen(plaintext), 0); // Write to the server
  if (charsWritten < 0) perror("CLIENT: ERROR writing to socket");

  if (charsWritten < strlen(plaintext)) printf("CLIENT: WARNING: Not all data written to socket!\n");

  // Get return message from server
  memset(cipher_text, '\0', sizeof(cipher_text)); // Clear out the buffer again for reuse

  charsRead = recv(socketFD, cipher_text, sizeof(cipher_text) - 1, 0); // Read data from the socket, leaving \0 at end
  if (charsRead < 0) perror("CLIENT: ERROR reading from socket");

  printf("%s\n", cipher_text); //send the cipher text to stdout

  close(socketFD); // Close the socket

  return 0;
}
