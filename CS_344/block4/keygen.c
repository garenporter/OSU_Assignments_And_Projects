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

	//the following if statement checks for correct number of args
	if(argc != 2){
		write(2, "Incorrect number of arguments", 29);
		printf("\n");
		exit(1);
	}
	//following array holds all of the allowed characters
	char alphabet[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', ' '};

	const char* keylength_string = argv[1]; //store specified keylength in var
	int keylength = atoi(keylength_string); // stores length of the key

	char key[keylength+1]; //this array will store the key and the prepending newline
	memset(key, '\0', sizeof(key)); //clear out the key array

	srand(time(NULL)); //seed time

	int i;
	// the following for loop puts a random symbol from the alphabet array into the key array
	for(i=0; i<keylength; i++){
		int position = rand() % 27;
		key[i] = alphabet[position];
	}
	key[keylength] = '\n'; //put a newline at the end of key array
	key[keylength+1] = '\0'; //null terminate key array
	printf("%s", key); //send key array to stdout

	return 0;
}
