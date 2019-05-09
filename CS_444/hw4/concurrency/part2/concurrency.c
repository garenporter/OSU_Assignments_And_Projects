#include <pthread.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_NUM 20
#define THREAD_NUM 3

pthread_mutex_t insert_mutex, delete_mutex, search_mutex[THREAD_NUM];
pthread_t search_t[THREAD_NUM], insert_t[THREAD_NUM], delete_t[THREAD_NUM];

struct node {
	struct node *next;
	int data;
};

void llist_print(struct node *head) {
	int i = 0;
	struct node *cur_item = head;
	printf("== List contents ==\n");
	while(cur_item != NULL) {
		printf("[%02d] - %d\n", i, cur_item->data);
		cur_item = cur_item->next;
		i++;
	}
	printf("===================\n");
}

struct node *create_node(int data) {
	struct node *item = (struct node *) calloc(1, sizeof(struct node));
	item->data = data;
	item->next = NULL;
	return item;
}

void insert(struct node *head, int data) {
	struct node *new_item = create_node(data);
	struct node *cur_item = head;
	while(cur_item->next != NULL) {
		cur_item = cur_item->next;
	}
	cur_item->next = new_item;
	return;
}

// Returns value at index
int search(struct node *head, int index) {
	struct node *cur_item = head;
	int i, len = head->data;
	for(i = 0; i < index; i++) {
		if(cur_item == NULL) {
			return -1;
		} 
		cur_item = cur_item->next;
	}
	if(cur_item == NULL) {
		return -1;
	} 
	return cur_item->data;
}

// Returns 0 if task succeeded, 1 if it did not
int delete(struct node **head, int index) {
	struct node *cur_item = *head, *parent = NULL;
	int i;

	if(index == 0) {
		*head = cur_item->next;
	} else if((*head)->next == NULL) {
		//Don't allow deletion of the head if there is only one item
		return 1;
	} else {
		for(i = 0; i < index; i++) {
			if(cur_item == NULL) {
				return 1;
			} 
			parent = cur_item;
			cur_item = cur_item->next;
		}
		if(cur_item == NULL) {
			return 1;
		}
		parent->next = cur_item->next;
	}
	free(cur_item);
	return 0;
}

void *search_task(void *arg) {
	struct node *head = ((struct node *) arg)->next;
	int thread_name = ((struct node *) arg)->data;
	
	int i, idx, result;
	for(i = 0; i < 10; i++) {
		idx = rand() % MAX_NUM + 1;

    	pthread_mutex_lock(&search_mutex[thread_name - 1]);
		printf("== Search %d ==  Searching at index [%d]\n", thread_name, idx);
		result = search(head, idx);
		if(result == -1) {
			printf("== Search %d ==  Invalid index [%d]\n", thread_name, idx);
		} else {
			printf("== Search %d ==  Found %d at [%d]\n", thread_name, result, idx);
		}

		fflush(stdout);
		pthread_mutex_unlock(&search_mutex[thread_name - 1]);

		sleep(rand() % 5); 

	}
}


void *insert_task(void *arg) {
	//sort out arguments
	struct node *head = ((struct node *) arg)->next;
	int thread_name = ((struct node *) arg)->data;

	int i, num;
	for(i = 0; i < 10; i++) {
		num = rand() % MAX_NUM + 1;
		printf("== Insert %d ==  Waiting on lock\n", thread_name);

		pthread_mutex_lock(&insert_mutex);
		printf("== Insert %d ==  Locked\n", thread_name);
		printf("== Insert %d ==  Inserting %d\n", thread_name, num);
		insert(head, num);
		printf("== Insert %d ==  Unlocking\n", thread_name);
		fflush(stdout);
		pthread_mutex_unlock(&insert_mutex);
		sleep(rand() % 5); //Sleep random amount of time to allow other threads to catch the mutex
	}
}

void *delete_task(void *arg) {
	struct node *head = ((struct node *) arg)->next;
	int thread_name = ((struct node *) arg)->data;

	int i, j, idx, result;
	for(i = 0; i < 10; i++) {
		idx = rand() % MAX_NUM + 1;
    
		printf("== Delete %d ==  Waiting on locks\n", thread_name);
		pthread_mutex_lock(&delete_mutex);
		pthread_mutex_lock(&insert_mutex);
		for(j = 0; j < THREAD_NUM; j++) {
			pthread_mutex_lock(&search_mutex[j]);
		}
		printf("== Delete %d ==  Locked\n", thread_name);
		
		printf("== Delete %d ==  Deleting index [%d]\n", thread_name, idx);
		result = delete(&head, idx);
		if(result == 1) {
			printf("== Delete %d ==  Invalid index [%d]\n", thread_name, idx);
		} else {
			printf("== Delete %d ==  Deleted [%d]\n", thread_name, idx);
		}

		printf("== Delete %d ==  Unlocking\n", thread_name);
		fflush(stdout);
		pthread_mutex_unlock(&delete_mutex);
		pthread_mutex_unlock(&insert_mutex);
		for(j = 0; j < THREAD_NUM; j++) {
			pthread_mutex_unlock(&search_mutex[j]);
		}

		sleep(rand() % 5); //Sleep random amount of time to allow other threads to catch the mutex
	}
}

int main(){
	int i;
	srand(time(NULL));
    pthread_mutex_init(&insert_mutex, NULL);
    pthread_mutex_init(&delete_mutex, NULL);
	for(i = 0; i < THREAD_NUM; i++) {
		pthread_mutex_init(&search_mutex[i], NULL);
	}

    //initialize list with one item
	//head cannot be deleted. The data located in head is the length of the list
    struct node *head = create_node(1);

    //cheating by using node struct to contain pointer to head of list and thread number for logging
    //passed into each thread handler
    struct node args[THREAD_NUM];

    printf("Creating Threads\n");
    for(i = 0; i < THREAD_NUM; i++) {
    	args[i].next = head;
    	args[i].data = i + 1;
    	pthread_create(&search_t[i], NULL, search_task, &args[i]);
	    pthread_create(&insert_t[i], NULL, insert_task, &args[i]);
	    pthread_create(&delete_t[i], NULL, delete_task, &args[i]);
    }

    for(i = 0; i < THREAD_NUM; i++) {
    	pthread_join(search_t[i], NULL);
	    pthread_join(insert_t[i], NULL);
	    pthread_join(delete_t[i], NULL);
    }
    printf("Threads joined\n");

    llist_print(head);

    return 0;
}
