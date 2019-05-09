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
    int n = 50000;                                          //set the starting number of vector elements at 5000

    for(int i = 0; i<10; i++){                              //outer loop runs 10 times, which fills up 10 vectors
        vector<int> row;                                    //create a new vector
        vectors.push_back(row);                             //add the vector to the 2D vector
        for(int j = 0; j<n; j++){                           //add n number of random numbers to the vector
            int randNum = rand()%(10000-0 + 1) + 0;
            vectors[i].push_back(randNum);
        }
        n+=10000;                                            //increase n by 5000 for the next vector
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
    int temp, k, key;

    //outer loop is not part of the sort algorithm, it simply keeps track of which vector we are sorting
    //there can be 0 to many vectors, so we sort every vector within the 2D vector.
    for(int i = 0; i < vectors.size(); i++){
        clock_t time = clock();                         //Get the clock time before starting the sort
        for(int j = 1; j < vectors[i].size(); j++){     //Outer loop of the algorithm. Loops through each element in the vector
            key = vectors[i][j];                        //Set key equal to the second element in the vector
            k = j-1;                                    //Set k equal to the value left of the key      
            while(k >= 0 && vectors[i][k] > key){       //loops while k is greater than -1 and the key is greater than the value on its left
                vectors[i][k+1] = vectors[i][k];        //set the key value to be the value on it's left
                k--;
            }
            vectors[i][k+1] = key;                      //set the value to the left of the key position to be the key, thus completing the swap
        }
        time = clock()-time;                            //get the number of clock cycles that passed during the sort
        printf("Input of size %d took %f seconds to sort with insertion sort.\n", vectors[i].size(), ((float)time)/CLOCKS_PER_SEC);     //print out the size of the vector and the number of seconds it took to complete the sort
    }
}

int main(){

    vector<vector<int> > vectors;   //create a 2D vector (is not initialized yet)

    get_random_vectors(vectors);    //fills the vector with the data from data.txt

    sort_insertion(vectors);        //sorts each vector using insertion sort

    //print_vectors(vectors);


    return 0;
}