#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

void error(const char *msg) { perror(msg); exit(1); } // Error function used for reporting issue

int main(int argc, char *argv[]){

  int listenSocketFD, establishedConnectionFD, portNumber, charsRead, client_address_len, pid;
  socklen_t sizeOfClientInfo;
  char plain_key[1000];
  char self_name[256];
  memset(self_name, '\0', sizeof(self_name));
  strcpy(self_name, argv[0]);
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
    char plaintext[256];
    memset(plaintext, '\0', sizeof(plaintext));
    while(plain_key[count] != '$'){
      plaintext[count] = plain_key[count];
      count++;
    }
    plaintext[count] = '\0';

    //following block grabs the key file from the client
    char key[256];
    memset(key, '\0', sizeof(key));
    count++;
    int i = 0;
    while(plain_key[count] != '$'){
      key[i] = plain_key[count];
      i++;
      count++;
    }

    char name[256];
    memset(name, '\0', sizeof(name));
    count++;
    int g = 0;
    while(plain_key[count] != '$'){
      name[g] = plain_key[count];
      g++;
      count++;
    }
    key[count] = '\0';
    //printf("plaintext: %s\nkey: %s\n", plaintext, key);

    FILE* fp1 = fopen(plaintext, "r+");
    FILE* fp2 = fopen(key, "r");

    //check to see if keygen file is long enough
    fseek(fp1, 0, SEEK_END);
    int byteCount1 = ftell(fp1);

    fseek(fp2, 0, SEEK_END);
    int byteCount2 = ftell(fp2);



    rewind(fp1);
    rewind(fp2);
    char cipher_char;
    char cipher_str[1000];
    //memset(cipher, '\0', sizeof(cipher));
    int j = 0;
    int k = 0;
    int p_char = fgetc(fp1);
    int k_char = fgetc(fp2);

    //fseek(fp1, -1, SEEK_CUR);
    //fseek(fp2, -1, SEEK_CUR);
    //encrypt the plaintext
    while(p_char != EOF){

      if(strcmp(name, "otp_enc") != 0){
        perror("Only opt_enc can connect to opt_enc_d");
        exit(1);
        break;
      }
      if(byteCount2 < byteCount1){
        perror("Key too small");
        exit(1);
      }

      if(p_char == '\n')
        break;

      if(((int)p_char < 65 || (int)p_char > 91) && p_char != ' ' && p_char){
        perror("Invalid character encountered\n");
        break;
      }

      if(p_char == ' ')
        p_char = '[';
      if(k_char == ' ')
        k_char = '[';

      //printf("p_char: %c\nk_char: %c\n", p_char, k_char);
      cipher_char = (p_char+k_char-130)%27+65;
      //  printf("cipher: %c\n", cipher_char);

      //printf("pos before: %ld\n", ftell(fp1));
      if(cipher_char == '['){
        cipher_str[k] = ' ';
        //fputc(' ', fp1);
      }
      else{
        cipher_str[k] = cipher_char;
      }
      //fputc(cipher, fp1);
      //printf("pos after: %ld\n", ftell(fp1));
      //fseek(fp1, -1, SEEK_CUR);
      p_char = fgetc(fp1);
      k_char = fgetc(fp2);
      //fseek(fp1, -1, SEEK_CUR);
      k++;
      //  fseek(fp2, -1, SEEK_CUR);
    }
    cipher_str[k] = '\0';
    fclose(fp2);
    fclose(fp1);
    //  printf("cipher: %s\n", cipher_str);

    if (charsRead < 0) perror("ERROR reading from socket");

    //  printf("SERVER: I received this from the client: \"%s\"\n", plain_key);

    // Send a Success message back to the client
    charsRead = send(establishedConnectionFD, cipher_str, sizeof(cipher_str), 0); // Send success back
    if (charsRead < 0) perror("ERROR writing to socket");

    exit(0);
    }
  else
  close(establishedConnectionFD); // Close the existing socket which is connected to the client
  }
  close(listenSocketFD); // Close the listening socket

  return 0;
}
