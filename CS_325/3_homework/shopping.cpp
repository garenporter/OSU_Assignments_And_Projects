#include <iostream>
#include <cstring>
#include <string>
#include <stdlib.h>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;


//struct to hold each test case
struct test_case{
    int num_items;
    vector<vector<int> > items;     //2-D vector that looks like [value][weight] for each item
    int num_family;
    vector<int> family_weight;      //weight each family member can carry
};

//struct to hold the result of shopping spree on each test case
struct result{
    int test_case;
    int total_price;                    //total value the family made
    vector<vector<int> > member_items;  //the items each family member grabbed
};

//function creates a vector of test cases
void get_file_info(vector<test_case> &vector){
    ifstream file;

    //open the file and ensure that it opens successfully
    file.open("shopping.txt");
    if(!file){
        cerr << "Unable to open shopping.txt";
        exit(1);
    }

    string line;
    int vec_num = 0;

    getline(file, line);                //get number of test cases
    int num_test_cases = line[0] - 48;
    for(int i = 0; i < num_test_cases; i++){   //initialise test cases
        struct test_case test_case;
        vector.push_back(test_case);
    }
    for(int i = 0; i < num_test_cases; i++){    //for each test case
        getline(file, line);                    //get number of items in test case
        istringstream iss1(line);            //convert string to stream
        int num_items;
        iss1 >> num_items;
        vector[i].num_items = num_items;        //set num_items in test_case struct
        for(int j = 0; j<num_items; j++){       //for each item
            std::vector<int> new_row;           //add new row in items vector
            vector[i].items.push_back(new_row);

            getline(file, line);                //retreive item
            istringstream iss2(line);            //convert string to stream
            int x;
            iss2 >> x;                           //get item price
            vector[i].items[j].push_back(x);
            iss2 >> x;                           //get item weight
            vector[i].items[j].push_back(x);
        }

        getline(file, line);                    //get number of family members
        istringstream iss3(line);            //convert string to stream
        int num_family;
        iss3 >> num_family;
        vector[i].num_family = num_family;      //set num_family in test_case struct
        for(int j = 0; j < num_family; j++){    //for each family member
            getline(file, line);                //get weight family member can carry
            istringstream iss4(line);            //convert string to stream
            int weight;
            iss4 >> weight;
            vector[i].family_weight.push_back(weight);  //add weight value to vector
        }

    }
}

//prints out the test cases for testing purposes
void print_test_cases(vector<test_case> test_cases){
    for(int i = 0; i < test_cases.size(); i++){
        printf("Vector %d\n", i);
        printf("Num items %d\n", test_cases[i].num_items);
        printf("Num family %d\n", test_cases[i].num_family);
        printf("Items[Price, Weight]:\n");
        for(int j = 0; j < test_cases[i].items.size(); j++){
            printf("%d %d\n", test_cases[i].items[j][0], test_cases[i].items[j][1]);
        }
        cout << "Family Weight:" << endl;
        for(int j = 0; j < test_cases[i].family_weight.size(); j++){
            printf("%d\n", test_cases[i].family_weight[j]);
        }
        printf("\n\n");
    }
}

//returns the max of two numbers
int max(int x, int y){
    if(x > y)
        return x;
    return y;
}

//implements a solution to the shopping spree problem
void shopping_spree(test_case test_case, int test_case_num){
    vector<vector<int> > table;
    
    //find the family member who can carry the largest amount of weight
    int largest_weight = 0;
    for(int i = 0; i < test_case.num_family; i++){
        if(test_case.family_weight[i] > largest_weight)
            largest_weight = test_case.family_weight[i];
    }

    //fill the memo table for the family member who can carry the most weight
    //if the table is filled to find the highest value for the most weight,
    //then the table can be used to quickly look up the highest value for smaller weights
    //there is no need to re-compute the table per family member 
    for(int i = 0; i <= test_case.num_items; i++){      //for each item
        vector<int> row;
        table.push_back(row);                           //create a new row for the table
        for(int j = 0; j <= largest_weight; j++){       //for each weight up to the max weight
            if(i == 0 || j == 0){                       //if first element in the row, make zero
                table[i].push_back(0);
            }
            else if(test_case.items[i-1][1] <= j){      //if weight of item is <= to current iteration weight....
                //add the max of the following two values to the table
                table[i].push_back(max(test_case.items[i-1][0] + table[i-1][j-test_case.items[i-1][1]], table[i-1][j]));
            }
            else{    
                table[i].push_back(table[i-1][j]);      //if weight of item is > current iteration weight, add diagnal of previous row to table
            }
        }
    }

    //use the table to find the max value that can be carried with each weight
    //use the bottom row, and the column equal to the weight to find the max value that can be carried
    int total_value = 0;
    for(int i = 0; i < test_case.num_family; i++){
        total_value += table[test_case.num_items][test_case.family_weight[i]];
    }

    //create a result struct to hold data to put into shopping.out
    result result;
    result.test_case = test_case_num;
    result.total_price = total_value;

    //find the items each member gathered
    for(int i = 0; i < test_case.num_family; i++){                          //for each family member in the test case
        int val = table[test_case.num_items][test_case.family_weight[i]];   //get max value family member can hold
        int weight = test_case.family_weight[i];                            //get weight of that family member
        vector<int> row;
        result.member_items.push_back(row);                                 //add new row to member_items 2-D vector
        for(int j = test_case.num_items; j > 0 && val > 0; j--){            //for each item and while total value is > 0. The loop goes until value reaches 0, meaning all held items have been accounted for
            if(val == table[j-1][weight])                                   //if value of items member is carrying equals diagnal of previous row, that item is not being carried
                continue;
            else{
                result.member_items[i].push_back(j);                        //item is being carried, so add that item to member_items vector
                val = val-test_case.items[j-1][0];                          //subtract the value of added item from the total value being carried
                weight = weight-test_case.items[j-1][1];                    //same as above, but for weight
            }
        }
    }

    ofstream shopping("shopping.out", ios::app);                            //open shopping.out file in such a way that data is always appended to end of file
    shopping << "Test case: " << result.test_case << "\n";                  //write the test case number
    shopping << "Total Price: " << result.total_price << "\n";              //write the total value carried by the family
    shopping << "Member Items:\n";
    for(int i = 0; i < test_case.num_family; i++){                          //for each family member, write the items they carried
        shopping << i+1 << ": ";
        for(int j = 0; j < result.member_items[i].size(); j++){
            shopping << result.member_items[i][j] << " ";
        }
        shopping << "\n";
    }
    shopping << "\n";
    shopping.close();
}

int main(){
    ofstream shopping("shopping.out");      //create file to hold output data
    shopping.close();
    vector<test_case> vector;               //create a 2D vector (is not initialized yet)

    get_file_info(vector);                  //fills the vector with the data from shopping.txt

    for(int i = 0; i < vector.size(); i++){ //for each test case, run the shopping_spree algorithm      
        shopping_spree(vector[i], i+1);
    }

    //print_test_cases(vector);

    return 0;
}