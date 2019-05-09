#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <time.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/fcntl.h>

int main(int argc, char* argv[]){

	//following if checks for correct number of args
	if(argc != 2){
		write(2, "Incorrect number of arguments", 29);
		printf("\n");
		exit(1);
	}
	//following array holds all of the allowed characters
	char alphabet[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', ' '};

	const char* keylength_string = argv[1]; //store specified keylength in var
	int keylength = atoi(keylength_string);

	char key[keylength+1]; //this array will store the key and the prepending newline
	memset(key, '\0', sizeof(key));
	//printf("argv: %s, keylength: %d\n", argv[1], keylength);
	srand(time(NULL));

	int i;
	for(i=0; i<keylength; i++){
		int position = rand() % 27;
		key[i] = alphabet[position];
	}
	key[keylength] = '\n';
	key[keylength+1] = '\0';
	printf("%s", key);

	return 0;
}
