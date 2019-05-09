#include <stdio.h>
#include<stdlib.h>

struct node {
	int val;
	struct node *next;
	struct node *prev;
};

struct list {
	struct node *head;
	struct node *tail;
};

int length(struct list);
void print(struct list);
void push_front(struct list*, int);
void push_back(struct list*, int);
void clear(struct list *);
void remove_val(struct list*, int);
void sort_ascending(struct list *);
void sort_descending(struct list *);

void insert(struct list *, int, int);
