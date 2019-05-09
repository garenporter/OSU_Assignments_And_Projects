#include <iostream>
#include <cstring>
#include <string>
#include <stdlib.h>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

//represents each set of activities
struct test_case{
    int num_activities;
    vector<int> activity_nums;
    vector<int> finish_times;
    vector<int> start_times;
};

//represents the results of the activity-selection algorithm on a set of activities
struct result{
    int set_num;
    int num_activities;
    vector<int> chosen_activites;
};

//prints the activity sets for testing purposes
void print_test_cases(vector<test_case> vector){
    for(int i = 0; i < vector.size(); i++){
        printf("Test Case: %d\n", i+1);
        printf("Number of activities: %d\n", vector[i].num_activities);
        for(int j = 0; j < vector[i].activity_nums.size(); j++){
            printf("Activity: %d\n%d %d\n", vector[i].activity_nums[j], vector[i].start_times[j], vector[i].finish_times[j]);
        }
    }
}

//prints the results of each set of activities
void print_results(vector<result> results){
    for(int i = 0; i < results.size(); i++){
        printf("Set %d\n", results[i].set_num);         //print set number
        printf("Number of activities selected = %d\n", results[i].num_activities);  //print number compatible activities in set
        printf("Activities: ");
        //print compatible activities
        for(int j = 0; j < results[i].chosen_activites.size(); j++){
            printf("%d ", results[i].chosen_activites[j]);
        }
        printf("\n\n");
    }
}

//parses the act.txt file and stores the activity set info in an array of test_cases
void get_file_info(vector<test_case> &cases){
    ifstream file;

    //open the file and ensure that it opens successfully
    file.open("act.txt");
    if(!file){
        cerr << "Unable to open act.txt";
        exit(1);
    }

    string line;

    int i = 0;      //test set counter
    while(1){
        //get number of activities if it is not the end of the file
        if(!getline(file, line))                    
            break;
        
        test_case row;
        cases.push_back(row);           //add blank test case to vector

        istringstream iss1(line);       //convert number of activities to a stream
        int num_activities;
        iss1 >> num_activities;         //convert the stream into an int

        cases[i].num_activities = num_activities;   //set the number of activities for the current test_case

        //for each activity, put its data in the current test case
        for(int j = 0; j < num_activities; j++){
            getline(file, line);                    //get activity info
            istringstream iss2(line); 

            int x;
            iss2 >> x;
            cases[i].activity_nums.push_back(x);    //save the activity number

            iss2 >> x;
            cases[i].start_times.push_back(x);      //save the activity start time

            iss2 >> x;
            cases[i].finish_times.push_back(x);     //save the activity end time
        }
        i++;
    }
}

//sorts the activities in each test_case by descending start times
void sort_activities(vector<test_case> &cases){

    for(int i = 0; i < cases.size(); i++){                  //for each test_case
        //perform bubble-sort
        for(int j = 0; j < cases[i].num_activities; j++){
            for(int k = 0; k < cases[i].num_activities-1; k++){
                if(cases[i].start_times[k] < cases[i].start_times[k+1]){
                    //swap the two activities:
                    //first swap activity numbers
                    int temp = cases[i].activity_nums[k];
                    cases[i].activity_nums[k] = cases[i].activity_nums[k+1];
                    cases[i].activity_nums[k+1] = temp;

                    //swap start times
                    temp = cases[i].start_times[k];
                    cases[i].start_times[k] = cases[i].start_times[k+1];
                    cases[i].start_times[k+1] = temp;

                    //swap finish times
                    temp = cases[i].finish_times[k];
                    cases[i].finish_times[k] = cases[i].finish_times[k+1];
                    cases[i].finish_times[k+1] = temp;
                }
            }
        }
    }
}

void activity_selection(vector<test_case> cases, vector<result> &results){

    //for each set of activities...
    for(int i = 0; i < cases.size(); i++){
        //initialize new result:
        result row;
        results.push_back(row);
        results[i].set_num = i+1;       //set numbers start at 1 and increment from there
        results[i].num_activities = 1;  //number of activities starts at 1, because we always last activity to start

        //add last activity to start
        results[i].chosen_activites.push_back(cases[i].activity_nums[0]);

        int k = 0;  //k points to last activity added
        //for each activity in the current set...
        for(int j = 1; j < cases[i].num_activities; j++){
            //if the start time at k is greater than or equal to the finish time at j, then activity j is compatible
            if(cases[i].start_times[k] >= cases[i].finish_times[j]){
                results[i].chosen_activites.push_back(cases[i].activity_nums[j]);   //add activity j to results
                results[i].num_activities++;    //increment number of compatible activities in current set
                k = j;                          //set k equal to last activity added
            }
        }
    }
}

int main(){

    vector<test_case> test_cases;               //vector of sets of activities
    vector<result> results;                     //vector of results of activity sets that have gone through the activity_selection algorithm

    get_file_info(test_cases);                  //fills test_cases with data from the act.txt file

    sort_activities(test_cases);                //sorts the test_cases in descending order by start time

    activity_selection(test_cases, results);    //performs the activity selection item on each test_case

    print_results(results);                     //print the results
    //print_test_cases(test_cases);


    return 0;
}