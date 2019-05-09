#include <iostream>
#include <cstring>
#include <string>
#include <stdlib.h>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <queue>
#include <time.h>

using namespace std;

//represents a wrestler
struct test_case {
    int num_items;      //number of items to pack
    int bin;            //size of the bins
    vector<int> items;  //all the items to be packed
};

//results of the 3 greedy algorithms
struct results {
    int first_fit;              //how many bins first-fit approach used
    int first_fit_decreasing;   //how many bins first-fit-decreasing approach used
    int best_fit;               //how many bins best-fit approach used
};

//pulls bin packing data from a given file
void get_file_info(vector<test_case> &test_cases, vector<results> &results, string filename){
    ifstream file;

    //open the file and ensure that it opens successfully
    file.open(filename.c_str());
    if(!file){
        cerr << "Unable to open bin.txt";
        exit(1);
    }

    string line;
    int i, num_cases;

    //get the number of test cases
    getline(file, line);
    istringstream iss1(line); 
    iss1 >> num_cases;

    //for each test case...
    for(i = 0; i < num_cases; i++){
        test_case row;
        test_cases.push_back(row);   //add a new test_case

        struct results r;
        results.push_back(r);        //add new results;

        //get the bin size
        getline(file, line);
        istringstream iss2(line);
        iss2 >> test_cases[i].bin;

        //get the number of items
        getline(file, line);
        istringstream iss3(line);
        iss3 >> test_cases[i].num_items;

        //get all of the items
        for(int j = 0; j < test_cases[i].num_items; j++){
            int item;
            //if this is the last item, do not use a delimeter with getline
            if(j == test_cases[i].num_items - 1){
                getline(file, line);
                istringstream iss4(line);
                iss4 >> item;
                test_cases[i].items.push_back(item);
                break;
            }

            //get the next item using a space as a delimeter
            getline(file, line, ' ');
            istringstream iss4(line);
            iss4 >> item;
            test_cases[i].items.push_back(item);
        }
    }
}

//prints the test cases for testing purposes
void print_file_info(vector<test_case> test_cases){
    //printf("%d\n", test_cases.size());
    for(int i = 0; i < test_cases.size(); i++){
        printf("Num items: %d, Bin size: %d\n", test_cases[i].num_items, test_cases[i].bin);
        for(int j = 0; j < test_cases[i].items.size(); j++){
            printf("%d ", test_cases[i].items[j]);
        }
        printf("\n");
    }
}

void first_fit(vector<test_case> test_cases, vector<results> &results){
    //perform first-fit on each test case
    for(int i = 0; i < test_cases.size(); i++){
        vector<int> bins;
        bins.push_back(test_cases[i].bin);  //add a bin to the list bins
        //for each item...
        for(int j = 0; j < test_cases[i].items.size(); j++){
            int found = 0;
            //for each bin
            for(int k = 0; k < bins.size(); k++){
                if(test_cases[i].items[j] <= bins[k]){
                    bins[k] = bins[k] - test_cases[i].items[j]; //if the item fits, add it to the bin
                    found = 1;
                }
            }
            //if item does not fit in a bin, add it to a new bin
            if(found == 0){
                bins.push_back(test_cases[i].bin - test_cases[i].items[j]);
            }
        }
       // printf("BINS: %d\n", bins.size());
        results[i].first_fit = bins.size();
    }
}

void first_fit_decreasing(vector<test_case> test_cases, vector<results> &results){
    //sort items in descending order
    for(int i = 0; i < test_cases.size(); i++){
        for(int j = 0; j < test_cases[i].items.size(); j++){
            for(int k = 0; k < test_cases[i].items.size()-1; k++){
                if(test_cases[i].items[k] < test_cases[i].items[k+1]){
                    int temp = test_cases[i].items[k];
                    test_cases[i].items[k] = test_cases[i].items[k+1];
                    test_cases[i].items[k+1] = temp;
                }
            }
        }
    }

    //perform first-fit on each test case
    for(int i = 0; i < test_cases.size(); i++){
        vector<int> bins;
        bins.push_back(test_cases[i].bin);  //add a bin to the list bins
        //for each item...
        for(int j = 0; j < test_cases[i].items.size(); j++){
            int found = 0;
            //for each bin
            for(int k = 0; k < bins.size(); k++){
                if(test_cases[i].items[j] <= bins[k]){
                    bins[k] = bins[k] - test_cases[i].items[j]; //if the item fits, add it to the bin
                    found = 1;
                    break;
                }
            }
            //if item does not fit in a bin, add it to a new bin
            if(found == 0){
                bins.push_back(test_cases[i].bin - test_cases[i].items[j]);
            }
        }
        results[i].first_fit_decreasing = bins.size();
    }
}

void best_fit(vector<test_case> test_cases, vector<results> &results){
    //perform best-fit on each test case
    for(int i = 0; i < test_cases.size(); i++){
        vector<int> bins;
        bins.push_back(test_cases[i].bin);  //add a bin to the list bins
        //for each item...
        for(int j = 0; j < test_cases[i].items.size(); j++){
            int found = 0;
            int room = 0;
            int first_to_fit = 0;
            int room_loc = 0;
            //for each bin
            for(int k = 0; k < bins.size(); k++){
                if(test_cases[i].items[j] <= bins[k]){  //if the item fits
                    if(first_to_fit == 0){     //if this is the first bin, initialize room and continue
                        room = bins[k] - test_cases[i].items[j];
                        room_loc = k;
                        first_to_fit = 1;
                        found = 1;
                        continue;
                    }
                    if((bins[k] - test_cases[i].items[j]) < room){
                        room = bins[k] - test_cases[i].items[j];
                        room_loc = k;
                    }
                }
            }
            if(found == 1){
                bins[room_loc] = bins[room_loc] - test_cases[i].items[j]; //add item to the bin that leaves the least room
            }
            //if item does not fit in a bin, add it to a new bin
            if(found == 0){
                bins.push_back(test_cases[i].bin - test_cases[i].items[j]);
            }
        }
       // printf("BINS: %d\n", bins.size());
        results[i].best_fit = bins.size();
    }
}

void generate_random_cases(vector<test_case> &test_cases, vector<results> &results){
    srand(static_cast <unsigned int> (time(0))); 

    //generate 20 random test cases
    for(int i = 0; i < 20; i++){
        //add new test case row
        test_case row;
        test_cases.push_back(row);

        //add new result row
        struct results r;
        results.push_back(r);
        
        //get random bin capacity between 1 and 20
        test_cases[i].bin = rand()%(20-0 + 1) + 1;

        //get random number of items between 1 and 20
        test_cases[i].num_items = rand()%(20-0 + 1) + 1;

        //generate random items
        for(int j = 0; j < test_cases[i].num_items; j++){
            test_cases[i].items.push_back(rand()%(test_cases[i].bin-0 + 1) + 1);
        }
    }

}

void print_results(vector<results> results){
    for(int i = 0; i < results.size(); i++){
        printf("Case %d:\nFirst-Fit: %d\nFirst-Fit-Decreasing: %d\nBest-Fit: %d\n\n", i+1, results[i].first_fit, results[i].first_fit_decreasing, results[i].best_fit);        
    }
}

int main(int argc, char *argv[]){

    string filename(argv[1]);

    vector<test_case> test_cases;
    vector<test_case> random_test_cases;

    vector<results> random_results;
    vector<results> results;

    get_file_info(test_cases, results, filename);   //pulls data from file
    //print_file_info(test_cases);
    first_fit(test_cases, results);
    first_fit_decreasing(test_cases, results);
    best_fit(test_cases, results);
    print_results(results);

//uncomment for randomness
  /*
    generate_random_cases(random_test_cases, random_results);
    first_fit(random_test_cases, random_results);
    first_fit_decreasing(random_test_cases, random_results);
    best_fit(random_test_cases, random_results);
    print_results(random_results);
*/


    return 0;
}