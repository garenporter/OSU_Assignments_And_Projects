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

//sorts each vector using insertion sort. Modifys vector directly, so nothing is returned
void sort_insertion(vector<vector<int> > &vectors){
    int k, key;

    //outer loop is not part of the sort algorithm, it simply keeps track of which vector we are sorting
    //there can be 0 to many vectors, so we sort every vector within the 2D vector.
    for(int i = 0; i < vectors.size(); i++){
        for(int j = 1; j < vectors[i].size(); j++){     //Outer loop of the algorithm. Loops through each element in the vector
            key = vectors[i][j];                        //Set key equal to the second element in the vector
            k = j-1;                                    //Set k equal to the value left of the key
            while(k >= 0 && vectors[i][k] > key){       //loops while k is greater than -1 and the key is greater than the value on its left
                vectors[i][k+1] = vectors[i][k];        //set the key value to be the value on it's left
                k--;
            }
            vectors[i][k+1] = key;                      //set the value to the left of the key position to be the key, thus completing the swap
        }
    }
}

void out_sorted(vector<vector<int> > &vectors){
    ofstream insertOut("insert.out");                 //create the file to hold the sorted data

    for(int i = 0; i<vectors.size(); i++){          //loop through every sorted vector
        for(int j = 0; j<vectors[i].size(); j++){   //write each value to file
            insertOut << vectors[i][j] << " ";
        }
        insertOut << "\n";
    }
    insertOut.close();                               //close file
}

int main(){

    vector<vector<int> > vectors;   //create a 2D vector (is not initialized yet)

    get_file_info(vectors);         //fills the vector with the data from data.txt

    sort_insertion(vectors);        //sorts each vector using insertion sort

    out_sorted(vectors);            //write the sorted vectors to a file

    return 0;
}