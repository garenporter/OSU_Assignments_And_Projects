#include <iostream>
#include <cstring>
#include <string>
#include <stdlib.h>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

//function that extracts the numbers from each line in data.txt and places them in vectors
void get_file_info(vector<vector<int> > &vectors){
    ifstream file;

    //open the file and ensure that it opens successfully
    file.open("data.txt");
    if(!file){
        cerr << "Unable to open data.txt";
        exit(1);
    }

    string line;
    int vec_num = 0;

    //loops through each line in the file, and for each line puts each number into its respective vector
    //the goal is to create a vector for each line in the file, and fill the vector with the contents of the line
    while(getline(file, line)){
        vector<int> row;            //create a new vector row
        vectors.push_back(row);     //insert row into vector

        istringstream iss(line);    //turn line into a string stream
        int x;
        iss >> x;                   //We don't care about the first number in the line, so move past it before looping
        while(iss >> x){            //while there are numbers on the line, continue pushing them into the vector
            vectors[vec_num].push_back(x);
        }
        vec_num++;
    }
}

//prints out the contents of each vector within the 2D vector
void print_vectors(vector<vector<int> > vectors){
    for(int i = 0; i < vectors.size(); i++){
        for(int j = 0; j < vectors[i].size(); j++){
            printf("%d ", vectors[i][j]);
        }
        printf("\n");
    }
}

void out_sorted(vector<vector<int> > &vectors){
    ofstream stoogeOut("stooge.out");                 //create the file to hold the sorted data

    for(int i = 0; i<vectors.size(); i++){          //loop through every sorted vector
        for(int j = 0; j<vectors[i].size(); j++){   //write each value to file
            stoogeOut << vectors[i][j] << " ";
        }
        stoogeOut << "\n";
    }
    stoogeOut.close();                               //close file
}

void sort_stooge(vector<int> &vector, int start, int end){
    //if there is less than 2 elements in the vector, return
    if(end-start+1 < 2)
        return;

    //if the first value in the vector is larger than the last value, swap them
    if(vector[start] > vector[end]){
        int temp = vector[start];
        vector[start] = vector[end];
        vector[end] = temp;
    }

    //if there are more than two values in the vector...
    if(end-start+1 > 2){
        int ceiling = (end-start+1)/3;              //break the vector into thirds
        sort_stooge(vector, start, end-ceiling);    //sort the first 2 thirds of the vector
        sort_stooge(vector, start+ceiling, end);    //sort the last 2 thirds of the vector 
        sort_stooge(vector, start, end-ceiling);    //confirm the first 2 thirds are sorted by sorting them again
    }
    
}

int main(){

    vector<vector<int> > vectors;   //create a 2D vector (is not initialized yet)

    get_file_info(vectors);         //fills the vector with the data from data.txt
    for(int i = 0; i < vectors.size(); i++){                 //for each random vector, time how long insertion sort takes       
        sort_stooge(vectors[i], 0, vectors[i].size()-1);     //sort vector using merge sort
        
    }

    out_sorted(vectors);            //write the sorted vectors to a file

    return 0;
}