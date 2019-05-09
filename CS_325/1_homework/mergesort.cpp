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

void out_sorted(vector<vector<int> > &vectors){
    ofstream mergeOut("merge.out");                 //create the file to hold the sorted data

    for(int i = 0; i<vectors.size(); i++){          //loop through every sorted vector
        for(int j = 0; j<vectors[i].size(); j++){   //write each value to file
            mergeOut << vectors[i][j] << " ";
        }
        mergeOut << "\n";
    }
    mergeOut.close();                               //close file
}

int main(){

    vector<vector<int> > vectors;               //create a 2D vector (is not initialized yet)

    get_file_info(vectors);                     //fills the vector with the data from data.txt

    for(int i = 0; i < vectors.size(); i++){    //for each vector, perform merge sort
        sort_merge(vectors[i], 0, vectors[i].size()-1);
    }
    
    out_sorted(vectors);                        //write the sorted vectors to a file

    return 0;
}