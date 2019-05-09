#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <time.h>

//This is the struct that each file wil be parsed into
struct Room {
    int id;
    char name[64]; //holds the name of the Room
    int num_outbound_connections; //holds the number of connections of the room
    char outbound_connections[6][32]; //this array holds 6 strings, each being the name of a connection
    int start_room; //determines if room is a start room
    int end_room; //determines if room is an end room
};

char dir[256]; // this holds the name of the directory containing the 7 room files

struct Room play_rooms[7]; //this is the array that holds each room struct

//this function prints out each outgoing connection for testing purposes
void print_connections(struct Room x){
    int i;
    printf("POSSIBLE CONNECTIONS: ");
    for(i=0; i<x.num_outbound_connections; i++){
        if(x.num_outbound_connections == (i+1)){
          printf("%s.", x.outbound_connections[i]);
          break;
        }
        printf("%s, ", x.outbound_connections[i]);
    }
    printf("\n");
}

//this functions prints out the contents of each room struct in play_rooms for testing purposes
void print_room(){
    int i;
    printf("Printing each room struct...\n");
    for(i=0; i<7; i++){
        printf("Struct %d: ID: %d | Name: %s | Num_Conns: %d | Start_room: %d | End_room: %d\n", i, play_rooms[i].id, play_rooms[i].name, play_rooms[i].num_outbound_connections, play_rooms[i].start_room, play_rooms[i].end_room);
        print_connections(play_rooms[i]);
    }

}

//returns the start room
struct Room get_start(){

  int i;
  for(i=0; i<7; i++){
    if(play_rooms[i].start_room == 1) //checks if play_rooms[i] is true, return if it is
      return play_rooms[i];
  }
}

//returns the end_room
struct Room get_end(){

  int i;
  for(i=0; i<7; i++){
    if(play_rooms[i].end_room == 1) ///checks if play_rooms[i] is true, return if it is
      return play_rooms[i];
  }
}

//compares user input against outbound_connections of current room (the passed in room parameter)
int compare_input(char* x, struct Room y){

  int i;
  for(i=0; i<y.num_outbound_connections; i++){
    if(strcmp(x, y.outbound_connections[i]) == 0) //compares the user input with each outbound_connection of y, return true if it matches one
      return 1;
  }
  return 0;
}

//returns the room with the given name
struct Room find_room(char *x){

  int i;
  for(i=0; i<7; i++){
    if(strcmp(x, play_rooms[i].name) == 0) //compares input string against all names in play_rooms, return the matching room
      return play_rooms[i];
  }
}
//gets the most recent rooms directory
void get_dir(){

  int newestDirTime = -1; // Modified timestamp of newest subdir examined
  char targetDirPrefix[32] = "porterga.rooms."; // Prefix we're looking for
  char newestDirName[256]; // Holds the name of the newest dir that contains prefix
  memset(newestDirName, '\0', sizeof(newestDirName));

  DIR* dirToCheck; // Holds the directory we're starting in
  struct dirent *fileInDir; // Holds the current subdir of the starting dir
  struct stat dirAttributes; // Holds information we've gained about subdir

  dirToCheck = opendir("."); // Open up the directory this program was run in

  if (dirToCheck > 0) // Make sure the current directory could be opened
  {
    while ((fileInDir = readdir(dirToCheck)) != NULL) // Check each entry in dir
    {
      if (strstr(fileInDir->d_name, targetDirPrefix) != NULL) // If entry has prefix
      {
        //printf("Found the prefex: %s\n", fileInDir->d_name);
        stat(fileInDir->d_name, &dirAttributes); // Get attributes of the entry

        if ((int)dirAttributes.st_mtime > newestDirTime) // If this time is bigger
        {
          newestDirTime = (int)dirAttributes.st_mtime;
          memset(newestDirName, '\0', sizeof(newestDirName));
          strcpy(newestDirName, fileInDir->d_name);
        }
      }
    }
  }
strcpy(dir, newestDirName); //make dir have the contents of newestDirName
closedir(dirToCheck); // Close the directory we opened

}

void print_time(){
   time_t rawtime;
   struct tm *info; //create tm struct so we can access time elements
   char buffer[256]; //array to hold time/date
   FILE* time_file = fopen("./currentTime.txt", "w"); //open or create currentTime.txt for writing

   time( &rawtime );

   info = localtime( &rawtime );
   strftime(buffer, 40, "%I:%M%p, %A, %B %d, %Y", info); //format the time into the specified format
   printf("%s\n\n", buffer); //print the time
   fprintf(time_file, "%s", buffer); //write the time to the time file

//following lines were for finding seg fault
   //if(time_file == NULL)
    //printf("NULL bruh\n");
    //time_file = NULL;
   fclose(time_file); //close the time file, for some reason this causes a seg fault
   //printf("Here\n");
}

//this functions turns the contents of a room file into a struct
void file_to_struct(int x){ //0,1,2,... is passed in for the file names

    struct Room y; //temporary room struct that will be fille up with the contents of a file
    y.start_room = 0; //initialize start_room to false
    y.end_room = 0; //initialize end_room to false
    y.id = x; //set the id of the room to the value x

    memset(y.name, '\0', sizeof(y.name)); //initialize y.name to NULL
    memset(y.outbound_connections, '\0', sizeof(y.outbound_connections)); //initialize y.outbound_connections to NULL
    char rooms_dir[256]; //This variable will contain the filepath to be opened
    memset(rooms_dir, '\0', sizeof(rooms_dir)); //initialize rooms_dir to NULL
    strcpy(rooms_dir, dir); //makes rooms_dir contain the value stored in dir, which is the directory holding the room files
    char slash[256] = "/"; //simply a slash, to be concatinated with rooms_dir
    strcat(rooms_dir, slash); //cats rooms_dir and slash, making rooms_dir have a / at the end

    char ns[32]; //
    sprintf(ns, "%d", x); //convert x to a strings so it can be concatinated
    strcat(rooms_dir, ns); //concatinate rooms_dir and x, so now we have the complete file path to be opened and read
    char name[64]; //this variable will contain the name of the room
    FILE* file = fopen(rooms_dir, "r"); //open the file for reading

    fscanf(file, "%*s %*s %s", y.name); //stores the third string of file into name, so now y.name has its proper name
    char temp[32]; //this will hold the first string of each line in the file
    char con[32] = "CONNECTION"; //assign con the string CONNECTION, this will be compared with temp to tell if the current line being read is an outbound connection
    fscanf(file, "%s", temp); //Temp gets the next string in the file, which is garunteed to be CONNECTION
    int i = 0; //i is a counter that will help determine the number of outbound connections per room

    while(strcmp(temp, con) == 0){ //this while loop runs while there are still connections to be added to the struct

        char temp2[32]; //this temp variable holds the name of the outbound connection
        fscanf(file, "%*s %s", temp2); //this stores the string that is the name of the connection in the temp2 variable
        strcpy(y.outbound_connections[i], temp2); //this copies the temp2 variable into the array of outbound connections for y
        fscanf(file, "%s", temp); //temp gets the next string, which is either CONNECTION or ROOM
        i++; //increment i
    }
    y.num_outbound_connections = i; //assign the number of outbound connections to y

    char type[32]; //this will hold the start_room/end_room/middle_room string
    char start[32] = "START_ROOM"; //string to compare against
    char end[32] = "END_ROOM"; //string to compare against
    fscanf(file, "%*s %s", type); //This gets the last string in the file, which determines the room type

    if(strcmp(type, start) == 0){ //if last string in file is START_ROOM, then declare y as the start room
      y.start_room = 1;
    }
    if(strcmp(type, end) == 0){ //if last string in file is END_ROOM, then declare y as the end room
      y.end_room = 1;
    }

    fclose(file); //close the file

    play_rooms[x] = y; //assign y to its appropriate place in the play_rooms array
}

//this is the functions that contains the game logic and actually runs the game
void play_game(){

  struct Room start; //contains the start_room
  struct Room end; //contains the end room
  struct Room current; //contains the room the player is currently in
  char path_list [256][64]; //this is the path the player has taken to reach the end
  int path_num; //this is the number of rooms the player has been in

  start = get_start(); //start is assigned the start room
  end = get_end(); //end is assigned the end room
  current = start; //the current room is assigned the start room
  memset(path_list, '\0', sizeof(path_list)); //initialize the elements in path_list to NULL
  path_num = 0; //initialize path_num to 0

  //main game loop, runs while the room the player is in is not the end room
  while(current.end_room == 0){

      printf("CURRENT LOCATION: %s\n", current.name); //print the current location of the player
      print_connections(current); //prints the possible connections for current
      printf("WHERE TO? >"); //prompts the player for input
      char* input; //this is the variable that will hold the user input
      scanf("%s", input); //puts the user input in the input variable

      if(compare_input(input, current) == 0){ //if the input does not match a connection...
        while(compare_input(input, current) == 0){ //keep prompting the user for input until the input matches a connection from current
          printf("\n");
		  if(strcmp(input, "time") != 0) //if the input is not a connected room and does not equal time...
          	printf("HUH? I DON’T UNDERSTAND THAT ROOM. TRY AGAIN.\n\n"); //let the player know their input was invalid
          else //input must equal time, so....
		  	     print_time(); //print the time
		  print_connections(current); //print the connections for the player to see
          printf("WHERE TO? >"); //prompt player for input
          scanf("%s", input); //store input in input variable
        }
      }
      printf("\n");
      current = find_room(input); //current changes to the room specified by the player
      strcpy(path_list[path_num], current.name); //store the name of the current room in the path_list array
      path_num++; //increment path_num
      if(current.end_room == 1){ //if the current room is the end_room, then...
          //print VICTORY text and tell the player how many moves they made
          printf("YOU HAVE FOUND THE END ROOM. CONGRATULATIONS!\nYOU TOOK %d STEPS. YOUR PATH TO VICTORY WAS:\n", path_num);
          int j;
          for(j=0; j<path_num; j++){ //print each room that was visited
            printf("%s\n", path_list[j]);
          }
      }
  }

}
int main() {


  get_dir(); //assigns the dir variable its proper value, which is the newest rooms directory


  //the following for loop calls file_to_struct on each file, which builds up play_rooms
  int k;
  for(k=0; k<7; k++){
    file_to_struct(k);
  }
  play_game();
  //print_room();

  exit(0); //exit with status 0
  return 0;

}
