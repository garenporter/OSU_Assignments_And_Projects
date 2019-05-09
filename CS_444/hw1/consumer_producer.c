#include <pthread.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "rand_handler.h"

pthread_mutex_t lock;
pthread_cond_t consumer_cond, producer_cond;

struct item{
    int ran_num;
    int sleep_time;
};

struct buffer {
    struct item* items;
    int size;
};

void* consume(void* arg){
    printf("Consumer |\tThread has started.\n");

    struct buffer* buffer = (struct buffer*) arg;

    while(1){
        printf("Consumer |\tLocking mutex\n");
        pthread_mutex_lock(&lock);

        while(buffer->size <= 0){
            printf("Consumer |\tBuffer empty!\n");
            pthread_cond_wait(&consumer_cond, &lock);
        }

        printf("Consumer |\tSleeping for %d seconds\n", buffer->items[buffer->size-1].sleep_time);
        sleep(buffer->items[buffer->size-1].sleep_time);

        printf("Consumer |\tPrinter ran_num: %d\n", buffer->items[buffer->size-1].ran_num);
        printf("Consumer |\tRemoving consumed item from buffer\n");
        // buffer->items[buffer->size] = NULL;
        buffer->size--;
        // printf("Printing buffer\n");
        // int i = 0;
        // for(i; i < buffer->size; i++){
        //     printf("%d, %d\n\n", buffer->items[i].ran_num, buffer->items[i].sleep_time);
        // }

        printf("Consumer |\tUnlocking mutex\n");
        pthread_cond_signal(&producer_cond);
        pthread_mutex_unlock(&lock);
        sleep(1);

    }
    printf("Consumer |\tThread has finished.\n");

    free(buffer);
    return NULL;

}

void* produce(void* arg){

    int alg = rand_choice();
    seed_rand(alg);
    printf("Producer |\tThread has started.\n");

    struct buffer* buffer = (struct buffer*) arg;

    while(1){
        printf("Producer |\tLocking mutex\n");
        pthread_mutex_lock(&lock);

        printf("Producer |\tCreating item\n");
        struct item item = {get_rand() % 50, get_rand() % (9-2) + 2};

        while(buffer->size >= 32){
            printf("Producer |\tbuffer full!\n");
            pthread_cond_wait(&producer_cond, &lock);
        }

        printf("Producer |\tSleeping before producing\n");
        sleep(get_rand() % (7-3)+3);

        printf("Producer |\tAdding item to buffer\n");
        buffer->items[buffer->size] = item;
        buffer->size++;

        // printf("Printing buffer\n");
        // int i = 0;
        // for(i; i < buffer->size; i++){
        //     printf("%d, %d\n\n", buffer->items[i].ran_num, buffer->items[i].sleep_time);
        // }

        printf("Producer |\tUnlocking mutex\n");
        pthread_cond_signal(&consumer_cond);
        pthread_mutex_unlock(&lock);
        sleep(1);
    }
    printf("Producer |\tThread has finished.\n");

    free(buffer);
    return NULL;

}

int main(){

    pthread_t consumer, producer;
    struct buffer buffer;

    buffer.items = (struct item*)calloc(32, sizeof(struct item));
    buffer.size = 0;

    //initialize the pthread conditions
    pthread_cond_init(&consumer_cond, NULL);
    pthread_cond_init(&producer_cond, NULL);

    //initialize mutex
    if(pthread_mutex_init(&lock, NULL) != 0){
        printf("Failed to initialize mutex 'lock'!\n");
        return 1;
    }

    //initialize the pthreads
    if(pthread_create(&producer, NULL, &produce, &buffer)){
        printf("Failed to initialize producer thread!\n");
        return 1;
    }

    if(pthread_create(&consumer, NULL, &consume, &buffer)){
        printf("Failed to initialize consumer thread!\n");
        return 1;
    }

    //join the pthreads
    pthread_join(consumer, NULL);
    pthread_join(producer, NULL);

    //clean up pointers
    pthread_mutex_destroy(&lock);
    pthread_cond_destroy(&consumer_cond);
    pthread_cond_destroy(&producer_cond);
    free(buffer.items);

    return 0;
}