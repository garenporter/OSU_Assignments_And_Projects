/* To compile: gcc -pthread part1.c */

/* Header files */
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <semaphore.h>
#include <stdlib.h>

/* Prototypes */
void *use(void*);
void use_resource(void*);

/* Global variables */
sem_t check_resource; //used to cheack resorces
int stop_resource = 0; //boolean to allow/dont allow users to use resorces
int num_threads = 6; //number of threads (users)
sem_t avail_resource; //used to state number of available resorces

/* Main */
int main() { 
  pthread_t user[num_threads]; //create num_threads number of threads
  int i;
  int id[num_threads];
  for(i = 0; i<num_threads; i++) {
    id[i]= i; //creates an id for each thread
  }
  sem_init(&avail_resource, 0, 3); //init the semaphore for available resorces (3 max)
  sem_init(&check_resource, 0, 1); //init the semaphore to check resorces (checks 1)
  srand(time(NULL)); //generates a psudo-random number - time(NULL) gets current system time
  for(i = 0; i < num_threads; i++) {
    pthread_create(&user[i], NULL, use, &id[i]); //creates pthread by passing in the user, use function, and the users id
  }
  for(i = 0; i < num_threads; i++) {
    pthread_join(user[i], NULL); //suspends execution of the current user, NULL prevents the value being passed to pthread_exit()
  }
  return 0;
}

/* Lets a thread use a resorce for 2 seconds */
void use_resource(void *id) {
  int *user_id = (int *)id;
  printf("%d: is using resorce.\n", *user_id); //use the resorce
  fflush(stdout);
  sleep(2); //wait 2 seconds
  printf("%d: is finished.\n", *user_id); //finish using the resorce
  fflush(stdout);
}

/* Checks what is being used and makes any threads not being used, wait */
void *use(void *id) {
  int *user_id = (int *)id;
  int free_resource;
  while(1) {
    if(stop_resource == 1) { //if stop_resource == 1, do not let any other threads use any resorce
      printf("%d: is waiting.\n", *user_id);
      fflush(stdout);
      sem_wait(&check_resource); //locks check_resource unitl sem_post unlocks it
      sem_post(&check_resource); //unlocks check_resource that was locked my sem_wait
    }
    sem_getvalue(&avail_resource, &free_resource); //updates the location referenced by free_resource to have the value of the semaphore referenced by avail_resource without affecting the state of the semaphore
    if (free_resource == 1) {
      sem_wait(&check_resource); //if only 1 resorce is available, lock check_resource
      stop_resource = 1; //dont let any thread use a resorce
    }
    sem_wait(&avail_resource); //lock avail_resource
    use_resource(id); //use the resorce
    
    sem_getvalue(&avail_resource, &free_resource); //see 8 lines up for details
    if(free_resource == 2) {
      sem_post(&check_resource); //if there are 2 available resorces, unlcok check_resource
      stop_resource = 0; //let threads use resorces
    }
    
    sem_post(&avail_resource); //unlock avail_resource
    
  }
}
