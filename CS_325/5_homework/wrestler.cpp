#include <iostream>
#include <cstring>
#include <string>
#include <stdlib.h>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <queue>

using namespace std;

//represents a wrestler
struct wrestler {
    string name;    //wrestler name
    int num;        //wrestler number
    int group;      //wrestler group (babyface/heel)
};

//represents a rivalry between two wrestleres
struct rivalry {
    wrestler w1;
    wrestler w2;
};

//indicates the number of wrestlers and rivalries
int num_wrestlers;
int num_rivalries;

//prints the created graph for testing purposes
void print_graph(vector<vector<wrestler> > graph){

    for(int i = 0; i < graph.size(); i++){
        printf("%s: ", graph[i][0].name.c_str());
        for(int j = 1; j < graph[i].size(); j++){
            printf("%s, ", graph[i][j].name.c_str());
        }
        printf("\n");
    }
}

//prints all wrestlers and rivalries for testing purposes
void print_file_info(vector<wrestler> wrestlers, vector<rivalry> rivalries){
    printf("num_wrestlers: %d, num_rivalries %d\n", num_wrestlers, num_rivalries);
    cout << "Wrestlers: " << endl;
    for(int i = 0; i < wrestlers.size(); i++){
        cout << wrestlers[i].name << endl;
        cout << wrestlers[i].num << endl;
        
    }

    cout << "Rivalries: " << endl;
    for(int j = 0; j < rivalries.size(); j++){
        cout << rivalries[j].w1.name << endl;
        cout << rivalries[j].w2.name << endl;
        printf("\n");
    }
}

//returns a wrestler from the list of wrestlers based on its name
wrestler get_wrestler(vector<wrestler> wrestlers, string name){
    for(int i = 0; i < wrestlers.size(); i++){          //for each wrestler
        if(wrestlers[i].name.compare(name) == 0)        //if the names match, return the wrestler
            return wrestlers[i];
    }
    printf("MAKE SURE dos2unix_script.sh HAS EXECUTE PERMISSION\n");
    exit(1);
}

//pulls the wrestler and rivalry data from the specified file
void get_file_info(vector<wrestler> &wrestlers, vector<rivalry> &rivalries, string filename){
    ifstream file;

    string script = "dos2unix_script.sh " + filename;
    system(script.c_str());
    //open the file and ensure that it opens successfully
    file.open(filename.c_str());
    if(!file){
        cerr << "Unable to open act.txt";
        exit(1);
    }

    string line;
    int i = 0;

    //get the number of wrestlers
    getline(file, line);
    istringstream iss1(line); 
    iss1 >> num_wrestlers;

    for(i = 0; i < num_wrestlers; i++){
        wrestler row;                   //add a wrestler row
        wrestlers.push_back(row);

        getline(file, line);        //get next wrestler from file
        wrestlers[i].name = line;   //set wrestler name
        wrestlers[i].num = i;       //set wrestler number
    }

    //get number of rivarlies
    getline(file, line);
    istringstream iss2(line); 
    iss2 >> num_rivalries;

    //for each rivalry...
    for(i = 0; i < num_rivalries; i++){
        rivalry riv;                                        //add new row
        rivalries.push_back(riv);

        getline(file, line, ' ');                           //get first wrestler in rivalry
        rivalries[i].w1 = get_wrestler(wrestlers, line);    //add wrestler to rivalries list
        getline(file, line);                                //get second wrestler in rivalry
        rivalries[i].w2 = get_wrestler(wrestlers, line);    //add second wrestler to rivalries list
    }

}

//creates the graph with wrestlers as vertices and rivalries as edges 
void create_graph(vector<vector<wrestler> > &graph, vector<wrestler> &wrestlers, vector<rivalry> &rivalries){
    int i = 0;
    //initialize the adjancency matrix, creating a row for each wrestler
    for(i; i < num_wrestlers; i++){
        vector<wrestler> row;
        graph.push_back(row);
        graph[i].push_back(wrestlers[i]);
    }

    //add the edges of the graph (rivalries)
    for(i = 0; i < num_rivalries; i++){
        graph[rivalries[i].w1.num].push_back(rivalries[i].w2);
        graph[rivalries[i].w2.num].push_back(rivalries[i].w1);
    }

}

//checks if the graph is bipartite in order to determine if wrestlers can be separated into two groups (uses BFS)
bool is_bipartite(vector<vector<wrestler> > &graph, int s, vector<wrestler> &wrestlers){

    vector<bool> visited(num_wrestlers);    //list of respective visited wrestlers
    vector<int> level(num_wrestlers);       //level of each respective wrestler
    vector<int> group(num_wrestlers);       //group of each respective wrestler
    
    visited[s] = true;      //make source node visited
    level[s] = 0;           //make source node level to be 0

    queue<int> queue;       //create a queue
    queue.push(s);          //push first node onto queue

    //initialize each item in group list to be -1 (indicates wrestler is not grouped)
    for(int &p : group){
        p = -1;
    }

    int j;
    while(!queue.empty()){              //while the queue is not empty...
        s = queue.front();              //make s hold the top of the queue
        queue.pop();                    //pop the top of the queue
        j = 0;                          //j is used to indicate the first iteration of the next for loop
        for(wrestler i : graph[s]){     //for each edge of vertex s
            if(!visited[i.num]){        //if vertex i has not been visited yet...
                visited[i.num] = true;  //set i to be visited

                level[i.num] = level[s] + 1;    //set i's level to be 1 above it's parent
                queue.push(i.num);              //push i onto the queue
            }
            else if(level[s] == level[i.num] && j != 0)     //if this is not the first iteration and the levels of the parent and child are equal, then the graph is not bipartite
                return false;
            j++;
        }
    }

    //this loop groups the wrestlers into groups based on rivalries
    for(int o = 0; o < graph.size(); o++){
        for(int p = 0; p < graph[o].size(); p++){
            if(p == 0 && group[graph[o][p].num] == -1){
                group[graph[o][p].num] = 1;
            }
            else if(group[graph[o][p].num] == -1){
                group[graph[o][p].num] = 1 - group[graph[o][0].num];
            }
        }
    }

    //this loops puts the wrestlers into groups based on the group list
    for(int k = 0; k < num_wrestlers; k++){
        if(group[wrestlers[k].num] == 1){
            wrestlers[k].group = true;
        }
        else
            wrestlers[k].group = false;
    }

    return true;
}

//prints the heels/babyfaces groups
void print_results(vector<wrestler> wrestlers){

    //create two lists to represent the two groups
    vector<wrestler> babyfaces;
    vector<wrestler> heels;

    //if a wrestler group is true, then babyface. Else the wrestler is a heel
    int i;
    for(i = 0; i < num_wrestlers; i++){
        if(wrestlers[i].group)
            babyfaces.push_back(wrestlers[i]);
        else
            heels.push_back(wrestlers[i]);
    }

    //print the babyfaces
    printf("Babyfaces: ");
    for(wrestler i : babyfaces){
        printf("%s ", i.name.c_str());
    }

    printf("\n");

    //print the heels
    printf("Heels: ");
    for(wrestler i : heels){
        printf("%s ", i.name.c_str());
    }
    printf("\n");
}

int main(int argc, char *argv[]){

    string filename(argv[1]);

    vector<wrestler> wrestlers;                     //array of all wrestlers
    vector<rivalry> rivarlies;                      //array of all rivarlies

    vector<vector<wrestler> > graph;                //adjacency list to represent graph

    get_file_info(wrestlers, rivarlies, filename);   //pulls data from file
    create_graph(graph, wrestlers, rivarlies);                            //creates graph

    //checks if the graph is bipartite, which determines if the wrestlers can be split into two groups
    if(!is_bipartite(graph, 0, wrestlers)){
        cout << "Not possible to seperate wrestlers into two groups." << endl;
        return 0;
    }

    cout << "Yes, the wrestlers can be separated into two groups." << endl;
    print_results(wrestlers);


    return 0;
}