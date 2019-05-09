#include <iostream>
#include <cstring>
#include <string>
#include <stdlib.h>
#include <vector>
#include <fstream>
#include <sstream>
#include <time.h>

using namespace std;

//function that fills up 10 vectors with a number of random number between 0 and 10000
void get_random_vectors(vector<vector<int> > &vectors){
    srand(static_cast <unsigned int> (time(0)));            //seed the random number generator with time(0)
    int n = 500;                                          //set the starting number of vector elements at 300

    for(int i = 0; i<10; i++){                              //outer loop runs 10 times, which fills up 10 vectors
        vector<int> row;                                    //create a new vector
        vectors.push_back(row);                             //add the vector to the 2D vector
        for(int j = 0; j<n; j++){                           //add n number of random numbers to the vector
            int randNum = rand()%(10000-0 + 1) + 0;
            vectors[i].push_back(randNum);
        }
        n+=500;                                            //increase n by 300 for the next vector
    }
}

//prints the vector of vectors
void print_vectors(vector<vector<int> > vectors){
    for(int i = 0; i < vectors.size(); i++){
        for(int j = 0; j < vectors[i].size(); j++){
            printf("%d ", vectors[i][j]);
        }
        printf("\n");
    }
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

    vector<vector<int> > vectors;                           //create a 2D vector (is not initialized yet)

    get_random_vectors(vectors);                            //fills the vector with the data from data.txt

    for(int i = 0; i < vectors.size(); i++){                 //for each random vector, time how long insertion sort takes   
        clock_t time = clock();                              //start the clock    
        sort_stooge(vectors[i], 0, vectors[i].size()-1);     //sort vector using merge sort
        time = clock()-time;                                 //get how many clock cycles merge sort took
        printf("Input of size %d took %f seconds to sort with stooge sort.\n", vectors[i].size(), ((float)time)/CLOCKS_PER_SEC);
    }

    return 0;
}