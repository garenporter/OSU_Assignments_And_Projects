#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/stat.h>

//this is the struct that represents each room
struct Room {
    int id; //id of the room, 0-10
    char const* name; //name of the room
    int num_outbound_connections; //number of connections
    const char* outbound_connections[6]; //array of connection names
    int start_room; //determines if start_room
    int end_room; //determines if end_room
};


//declare each room
struct Room alpha;
struct Room beta;
struct Room charlie;
struct Room delta;
struct Room echo;
struct Room foxtraut;
struct Room gammaa;
struct Room hotel;
struct Room india;
struct Room juliett;

//create array of all rooms
struct Room all_rooms[9];
//create array of the 7 rooms that are played with
struct Room play_rooms[6];

//prints the outbound connections of a room for testing purposes
void print_connections(struct Room x){
    int i;
    for(i=0; i<x.num_outbound_connections; i++){
        printf("Connection %d: %s\n", i, x.outbound_connections[i]);
    }
}

//prints all of the elements of a room struct for testing purposes
void print_room(){
    int i;
    printf("Printing each room struct...\n");
    for(i=0; i<7; i++){
        printf("Struct %d: ID: %d | Name: %s | Num_Conns: %d | Start_room: %d | End_room: %d\n", i, play_rooms[i].id, play_rooms[i].name, play_rooms[i].num_outbound_connections, play_rooms[i].start_room, play_rooms[i].end_room);
        print_connections(play_rooms[i]);
    }

}

// Returns true if all rooms have 3 to 6 outbound connections, false otherwise
int is_graph_full() {
    int i;
    //this runs through each room in play_rooms and determines if they have more than 3 outbound connections
    for(i = 0;i<7;i++){
        if(play_rooms[i].num_outbound_connections < 3){
            return 0;
        }
    }

    return 1; //return true if all outbound_connections are greater than 3
}

// Returns a random Room, does NOT validate if connection can be added
struct Room get_random_room(int r){ //the value r is a randomly generated number
    return play_rooms[r];
}

// Returns true if a connection can be added from Room x, false otherwise
int can_add_connection_from(struct Room* x) {
    if(x->num_outbound_connections < 6){ //checks if a room has less than 6 outbound connections
        return 1;
    }
    return 0;
}

// Connects Rooms x and y together, does not check if this connection is valid
void connect_room(struct Room* x, struct Room* y) {

    x->outbound_connections[x->num_outbound_connections] =  y->name; //adds the name of y to the outbound_connections array for x
    int z = x->num_outbound_connections; //assign z the number of outbound_connections for x
    z++; //increment z
    x->num_outbound_connections = z; //assign x's num_outbound_connections z

}

// Returns true if Rooms x and y are the same Room, false otherwise
int is_same_room(struct Room x, struct Room y) {

    if(strcmp(x.name, y.name) == 0){ //compares the names of 2 rooms, returns 2 if they are equal
        return 1;
    }
    return 0;
}

//checks if a connections between two rooms already exists
int connection_already_exists(struct Room x, struct Room y){
    int i;
    //this loop checks x's name to each outbound_connection in y, returns true if any match, false otherwise
    for(i=0; i<y.num_outbound_connections; i++){
        if(strcmp(x.name, y.outbound_connections[i]) == 0){
            return 1;
        }
    }
    return 0;
}

// Adds a random, valid outbound connection from a Room to another Room
void add_random_connection() {

    struct Room A; //Maybe a struct, maybe global arrays of ints
    struct Room B;
    int q, u; //these will hold the two random numbers

    //this loop finds a suitable random room A
    while(1) {
        int r = rand() % 7; //get a random number between 0-6
        q = r; //have q remember the random number r
        A = get_random_room(r); //assign A a random room
        if(can_add_connection_from(&A) == 1) //checks if A can have anymore connections, if it can then break, otherwise loop again
            break;
    }
    //the following do/while loop finds a suitable random room B such that B and A are able to have a connection
    do {
        int n = rand() % 7;
        u = n; //have u remember the random number n;
        B = get_random_room(n); //give B a random room
    }
    //B will continue to receive random rooms while A and B are the name, while they already have a connection, and while B cannot receive any more connections
    while(can_add_connection_from(&B) == 0 || is_same_room(A, B) == 1 || connection_already_exists(A, B) == 1);


    //connect A and B together
    connect_room(&A, &B);
   // increment_num_connections(&A);
    connect_room(&B, &A);

    //put the random rooms back into play_rooms
    play_rooms[q] = A;
    play_rooms[u] = B;

}

//this function creates a file for a given Room
void create_room_file(struct Room x, int y){ //directory name passed

    //the following block gets the name of directory that the Room file will be placed in
    int id = getpid(); //gets the Process ID
    char ids[10]; //will hold the strings version of id
    sprintf(ids, "%d", id); //turns id into a string
    char dir_name[] = "./porterga.rooms."; //dir_name is assigned the first part of the directory name
    strcat(dir_name, ids); //cats together the directory name and the PID to get the full directory name

    //the following block creates the name of the file path to be opened
    char file[30] = "/"; //string containing /
    char ny[32]; //will hold y, passed in value
    sprintf(ny, "%d", y); //turns y into a string
    strcat(file, ny); //cats the / and y together
    strcat(dir_name, file); //cats the directory name with file to get the full filepath

    FILE* fp = fopen(dir_name, "w"); //creates/opens the room file for writing

    fprintf(fp, "ROOM NAME: %s\n", x.name); //write the Room name to the file

    int i;
    //this for loop adds CONNECTION information the file, it loops until there are no more connections to be added for the room
    for(i=0;i<x.num_outbound_connections;i++){
        fprintf(fp, "CONNECTION %d: %s\n", i+1, x.outbound_connections[i]);
    }
    //this if statement determines if a room is a middle room
    if(x.start_room == 0 && x.end_room == 0){
        fprintf(fp, "ROOM TYPE: MID_ROOM\n");
    }
    //this if statement determines if a room is the start_room
    if(x.start_room == 1){
        fprintf(fp, "ROOM TYPE: START_ROOM\n");
    }
    //this if statement determines if the room is the end_room
    if(x.end_room == 1){
        fprintf(fp, "ROOM TYPE: END_ROOM\n");
    }

    fclose(fp); //close the file

}

//determines the start and end Room
void determine_start_end(){

    //get two random numbers
    int r = rand() % 7;
    int r2 = rand() %7;

    //this while loop makes sure r and r2 are different
    while(r == r2){
        r2 = rand() % 7;
    }

    play_rooms[r].start_room = 1; //make play_rooms[r] the start room
    play_rooms[r2].end_room = 1; //makes play_rooms[r2] the end room
}
int main() {

    //seeds random
    srand(time(NULL));

    //add an ID to each room
    alpha.id = 0;
    beta.id = 1;
    charlie.id = 2;
    delta.id = 3;
    echo.id = 4;
    foxtraut.id = 5;
    gammaa.id = 6;
    hotel.id = 7;
    india.id = 8;
    juliett.id = 9;

    //add a name to each room
    alpha.name = "Nap";
    beta.name = "Cherek";
    charlie.name = "Eat";
    delta.name = "Ulgo";
    echo.name = "Nyissa";
    foxtraut.name = "Drasnia";
    gammaa.name = "Melcena";
    hotel.name = "Kell";
    india.name = "Sleep";
    juliett.name = "Sit";

    //initialize each num_outbound_connections to 0
    alpha.num_outbound_connections = 0;
    beta.num_outbound_connections = 0;
    charlie.num_outbound_connections = 0;
    delta.num_outbound_connections = 0;
    echo.num_outbound_connections = 0;
    foxtraut.num_outbound_connections = 0;
    gammaa.num_outbound_connections = 0;
    hotel.num_outbound_connections = 0;
    india.num_outbound_connections = 0;
    juliett.num_outbound_connections = 0;

    //add each room to the array of rooms
    all_rooms[0] = alpha;
    all_rooms[1] = beta;
    all_rooms[2] = charlie;
    all_rooms[3] = delta;
    all_rooms[4] = echo;
    all_rooms[5] = foxtraut;
    all_rooms[6] = gammaa;
    all_rooms[7] = hotel;
    all_rooms[8] = india;
    all_rooms[9] = juliett;

    //shuffle all_rooms
    int s;
    for(s=0; s<100; s++){
        int r1 = rand() % 10;
        int r2 = rand() % 10;
        struct Room temp1 = all_rooms[r1];
        struct Room temp2 = all_rooms[r2];
        all_rooms[r1] = temp2;
        all_rooms[r2] = temp1;
    }

    //set start/end room status to false for all rooms
    int g;
    for(g=0; g<10; g++){
        all_rooms[g].start_room = 0;
        all_rooms[g].end_room = 0;
    }

    //initializes outbound_connections to NULL
    int k,l;
    for(k=0; k<9; k++){
        for(l=0; l<7; l++){
            all_rooms[k].outbound_connections[l] = NULL;
        }
    }
    //fill play rooms with first 7 of all_rooms
    int p;
    for(p=0; p<7; p++){
        play_rooms[p] = all_rooms[p];
    }



    //fills the graph, everything is ready to be put into files after this is ran
    while (is_graph_full() == 0) {
        add_random_connection();
    }

    determine_start_end(); //makes one room a start room and one room an end room

    //making the directory to put files in, see create_room_file() for more details
    int id = getpid();
    char ids[10];
    sprintf(ids,"%d", id);
    char dir_name[] = "./porterga.rooms.";
    strcat(dir_name, ids);
    mkdir(dir_name, 0755); //actually makes the directory and set the permissions to the appropriate level

    int e;
    //calls create_room_file() on each Room struct, which makes all room files in the appropriate directory
    for(e=0; e<7; e++){
        create_room_file(play_rooms[e], e);
    }

    return 0;

}
