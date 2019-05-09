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

    for(int i = 0; i<50; i++){                              //outer loop runs 10 times, which fills up 10 vectors
        vector<int> row;                                    //create a new vector
        vectors.push_back(row);                             //add the vector to the 2D vector
        for(int j = 0; j<n; j++){                           //add n number of random numbers to the vector
            int randNum = rand()%(10000-0 + 1) + 0;
            vectors[i].push_back(randNum);
        }
        n+=10000;                                            //increase n by 5000 for the next vector
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

//merges two halves of a vector, vector[left to middle] and vector[middle+1 to right]
void merge(vector<int> &vector, int left, int middle, int right){
    //create the size of each sub-vector
    int sub1 = middle-left+1;   //size of left sub-vector
    int sub2 = right-middle;    //size of right sub-vector

    //create two temp arrays, one for each sub-vector
    std::vector<int> temp_left;
    std::vector<int> temp_right;

    //fill the two arrays with the appropriate values
    for(int i = 0; i < sub1; i++){
        temp_left.push_back(vector[left+i]);    //starting at the left index, add values up to the size
    }
    for(int i = 0; i < sub2; i++){
        temp_right.push_back(vector[middle+1+i]);   //starting at the middle index, add values up to the size
    }

    int i = 0;      //index of left vector
    int j = 0;      //inded of right vector
    int k = left;   //index of merged vector

    //this loops for the length of the largest sub-vector
    //the merged vector (passed in vector) gets filled from left to right in ascending order
    while(i < sub1 && j < sub2){            
        if(temp_left[i] <= temp_right[j]){  
            vector[k] = temp_left[i];       
            i++;
        }
        else{
            vector[k] = temp_right[j];
            j++;
        }
        k++;
    }

    //if there are any values left in temp_left, append them to vector
    while(i<sub1){
        vector[k] = temp_left[i];
        i++;
        k++;
    }

    //if there are any values left in temp_right, append them to vector
    while(j<sub2){
        vector[k] = temp_right[j];
        j++;
        k++;
    }


}

//this coninuously splits the vector in half until it can't be split anymore, then begins merging
//the last call to merge will merge the two full halves of the vector together
void sort_merge(vector<int> &vector, int left, int right){
    //if right index is greater than left index, basically if there is anything to split
    if(left < right){
        int middle = (left+right)/2;            //find middle to divide vector in half
        sort_merge(vector, left, middle);       //recursively call sort_merge on the left half of the vector
        sort_merge(vector, middle+1, right);    //recursively call sort_merge on the right half of the vector
        merge(vector, left, middle, right);     //merge the two halves created in the previous 2 lines of code
    }

}

int main(){

    vector<vector<int> > vectors;                           //create a 2D vector (is not initialized yet)

    get_random_vectors(vectors);                            //fills the vector with the data from data.txt

    for(int i = 0; i < vectors.size(); i++){                //for each random vector, time how long insertion sort takes
        clock_t time = clock();                             //start the clock
        sort_merge(vectors[i], 0, vectors[i].size()-1);     //sort vector using merge sort
        time = clock()-time;                                //get how many clock cycles merge sort took
        printf("Input of size %d took %f seconds to sort with merge sort.\n", vectors[i].size(), ((float)time)/CLOCKS_PER_SEC);
    }

    return 0;
}