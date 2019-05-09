#include <pthread.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#define THREAD_NUM 5

//Represents each philosopher
struct Person {
    const char* name; 
    int num;
};

void think(struct Person *);
void get_forks(struct Person *);
void eat(struct Person *);
void put_forks(struct Person *);
void *person_task(void *);
void print_info();
void eat_update(struct Person *);
void fork_update(int);

//thread of mutexts to represent the forks
pthread_mutex_t forks[THREAD_NUM];

//each fork/person gets its own resource
int fork0, fork1, fork2, fork3, fork4;
int p0, p1, p2, p3, p4;

int main(){
    pthread_t threads[THREAD_NUM];		//list of threads, 1 thread for each philosopher
    struct Person person_list[THREAD_NUM];	//list of philosophers

    srand(time(0));

    int i;
    //initialize mutexes
    for(i = 0; i < THREAD_NUM; i++) {
        if(pthread_mutex_init(&forks[i], NULL) != 0){
            printf("Failed to initialize mutex\n");
            return 1;
        }
    }

    printf("Starting threads\n");
    // Create threads
    for(i = 0; i < THREAD_NUM; i++) {
        person_list[i].num = i;
    	if(i==0)
    	    person_list[i].name = "George Takei";
    	else if(i==1)
    	    person_list[i].name = "Kanye West";
    	else if(i==2)
    	    person_list[i].name = "Nicholas Cage";
    	else if(i==3)
    	    person_list[i].name = "Donald Trump";
    	else
    	    person_list[i].name = "Mark Hamill";

        pthread_create(&threads[i], NULL, &person_task, &person_list[i]);
    }

    // Wait for threads to end. This won't execute
    for(i = 0; i < THREAD_NUM; i++) {
        pthread_join(threads[i], NULL);
        printf("Thread %d joined\n", i);
    }

    return 0;
}

//updates times eaten
void eat_update(struct Person *person){
    if(person->num == 0)
        p0++;

    if(person->num == 1)
        p1++;
    
    if(person->num == 2)
        p2++;
    
    if(person->num == 3)
        p3++;
    
    if(person->num == 4)
        p4++;
}

//toggles forks
void fork_update(int fork){
    if(fork == 0){
    	if(fork0 == 0)
            fork0++;
    	else
    	    fork0--;
    }
    if(fork == 1){
        if(fork1 == 0)
            fork1++;
        else
            fork1--;
    }
    if(fork == 2){
    	if(fork2 == 0)
            fork2++;
    	else
    	    fork2--;
    }
    if(fork == 3){
    	if(fork3 == 0)
            fork3++;
    	else   
    	    fork3--;
    }
    if(fork == 4){
    	if(fork4 == 0)
            fork4++;
    	else
    	    fork4--;
    }
}

//prints the status of forks and how many times each person has eaten
void print_info(){  
    printf("\nForks that are currently picked up(1 means it's picked up, 0 means it's down): %d %d %d %d %d\n", fork0, fork1, fork2, fork3, fork4);
    printf("Times each philospher has eaten: George Takei(%d), Kanye West(%d), Nicholas Cage(%d), Donald Trump(%d), Mark Hamill(%d)\n\n", p0, p1, p2, p3, p4); 
}

//the endless loop of the philosophers
void *person_task(void *arg) {
    struct Person *person = (struct Person *) arg;
    while(1){
        think(person);
        get_forks(person);
        eat(person);
        put_forks(person);
        print_info();
    }
}

//think for a random amount of time
void think(struct Person *person) {
    int wait_time = (rand() % 20) + 1;
    printf("Person %s\t| Thinking for %d seconds\n", person->name, wait_time);
    sleep(wait_time);
}

//try to pick up both forks
void get_forks(struct Person *person) {  
    if(person->num != 4){
        pthread_mutex_lock(&forks[person->num+1]);	//person tries to pick up fork
        printf("Person %s\t| Getting fork %d\n", person->name, person->num+1);
        fork_update(person->num+1);
    }
    else{
        pthread_mutex_lock(&forks[0]);			//person 4 tries to pick up fork 0 to simulate loop
    	printf("Person %s\t| Getting fork %d\n", person->name, 0);
    	fork_update(0);
    }
    pthread_mutex_lock(&forks[person->num]);		//person tries to pick up the second fork
    printf("Person %s\t| Getting fork %d\n", person->name, person->num);
    fork_update(person->num);
}

//eat for a random amount of time
void eat(struct Person *person) {
    int wait_time = (rand() % 8) + 2;
    printf("Person %s\t| Eating for %d seconds\n", person->name, wait_time);
    sleep(wait_time);   
}

//put down both forks
void put_forks(struct Person *person) {
    eat_update(person);	

    if(person->num != 4){
    	pthread_mutex_unlock(&forks[person->num+1]);	//put down the first fork
    	printf("Person %s\t| Putting down fork %d\n", person->name, person->num+1);
    	fork_update(person->num+1);
    }
    else{
    	pthread_mutex_unlock(&forks[0]);			//person 4 puts down fork 0
        printf("Person %s\t| Putting down fork %d\n", person->name, 0);
    	fork_update(0);
    }

    pthread_mutex_unlock(&forks[person->num]);		//put down the second fork
    printf("Person %s\t| Putting down fork %d\n", person->name, person->num);
    fork_update(person->num);
}
