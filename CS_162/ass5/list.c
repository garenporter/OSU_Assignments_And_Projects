#include "./list.h"

/*Function: length
 * Description: returns the length of a linked list
 * Parameters: A linked list
 * Pre-conditions: none
 * Post-conditions: none
 */
int length(struct list l){
	int t;
	t=0;
	while(l.head != NULL){
		l.head = l.head->next;
		t++;
	}
	return t;
}

/*Function: print
 * Description: prints the values of a linked list
 * Parameters: a linked list
 * Pre-conditions: none
 * Post-conditions: none
 */
void print(struct list l){
	while(l.head != NULL){
		printf("number is: %d\n", l.head->val);
		l.head = l.head->next;
	}
}

/*Function: push_front
 * Description: adds a value to the front of the list
 * Parameters: address of a linked list and value 
 * Pre-conditions: none
 * Post-conditions: new head value
 */
void push_front(struct list *l, int v){
	struct node* temp = malloc(sizeof(struct node));
	
	temp->val = v;
	temp->next = l->head;
	temp->prev = NULL;
	l->head->prev = temp;
	l->head = temp;
}

/*Function: push_back
 * Description: pushes a value to the back of a list
 * Parameters: address of a linked list and value
 * Pre-conditions: none
 * Post-conditions: new tail value
 */
void push_back(struct list *l, int v){
	struct node* temp = malloc(sizeof(struct node));
	
	temp->val = v;
	temp->next = NULL;
	temp->prev = l->tail;
	l->tail->next = temp;
	l->tail = temp;
}

/*Function: clear
 * Description: frees all the allocated memory in a linked list
 * Parameters: address of a linked list
 * Pre-conditions: none
 * Post-conditions: memory is freed
 */
void clear(struct list *l){
	struct node* temp;
	while(l->head != NULL){
		if(l->head->prev == NULL)
			free(l->head->prev);
		temp = l->head;
		l->head = l->head->next;
		free(temp);
	}
}

/*Function: remove_val
 * Description: removes all instances of a value in a linked list
 * Parameters: address of a linked list and a value to be removed
 * Pre-conditions: none
 * Post-conditions: values are removed from list
 */
void remove_val(struct list *l, int v){
	struct node* temp;
	struct node* temp2;
	temp2 = l->head;
	while(l->head != NULL){
		if(l->head->val == v){
			if(l->head->prev == NULL){
				temp = l->head;
				l->head->next->prev = NULL;
				free(temp);
				temp2 = l->head->next;
			}
			else if(l->head == l->tail){
				temp = l->head;
				l->head->prev->next = NULL;
				l->tail = l->head->prev;
				free(temp);
			}
			else{
			temp = l->head;
			l->head->next->prev = l->head->prev;
			l->head->prev->next = l->head->next;
			free(temp);
			}
		}
		l->head = l->head->next;
	}
	l->head = temp2;
}			


/*Function: sort_ascending
 * Description: sorts the values of a linked list in ascending order
 * Parameters: address of a linked list
 * Pre-conditions: none
 * Post-conditions: list values are sorted
 */
void sort_ascending(struct list *l){
	int temp;
	struct node* temp2;
	struct node *temp3;
	temp3 = l->head;
	temp2= l->head;
	while(temp3 != NULL){
	//	printf("here \n");
		while(l->head != NULL){
		//	printf("second while \n");
			if(l->head->next == NULL)
				break; 
			if(l->head->val > l->head->next->val){
			//	printf("if \n");
				temp = l->head->val;		
				l->head->val = l->head->next->val;
				l->head->next->val = temp;
				
				
			}
			
			l->head = l->head->next;
			
		}
		l->head = temp2;
		temp3 = temp3->next;
		if(temp3 == NULL)
			break;
	}
	l->head = temp2;
}	 

/*Function: sort_descending
 * Description: sorts the values of a linked list in descending order
 * Parameters: address of a linked list
 * Pre-conditions: none
 * Post-conditions: values in list are sorted
 */
void sort_descending(struct list *l){
	
	int temp;
	struct node* temp2;
	struct node *temp3;
	temp3 = l->head;
	temp2= l->head;
	while(temp3 != NULL){
	//	printf("here \n");
		while(l->head != NULL){
		//	printf("second while \n");
			if(l->head->next == NULL)
				break; 
			if(l->head->val < l->head->next->val){
			//	printf("if \n");
				temp = l->head->val;		
				l->head->val = l->head->next->val;
				l->head->next->val = temp;
				
				
			}
			
			l->head = l->head->next;
			
		}
		l->head = temp2;
		temp3 = temp3->next;
		if(temp3 == NULL)
			break;
	}
	l->head = temp2;
}	 

/*Function: insert
 * Description: inserts a node at a specific location in a linked list
 * Parameters: address of a linked list, an index value and a node value
 * Pre-conditions: none
 * Post-conditions: linked list has a new node somewhere
 */
void insert(struct list *l, int i, int v){
	int x = 0;
	struct node *temp1;
	struct node *temp2;
	temp1 = l->head;
	while(l->head != NULL){
		if(x == i){
			struct node *temp = malloc(sizeof(struct node));
			if(l->head->prev == NULL){
				temp->val = v;
				temp->prev = NULL;
				temp->next = l->head;
				l->head->prev = temp;
				l->head = temp;
				temp1 = l->head;
			}
			else if(l->head->next == NULL){
				temp->val = v;
				temp->next = NULL;
				temp->prev = l->head;
				l->head->next = temp;
				l->tail = temp;
			}
			else{
				temp2 = l->head;
				temp->val = v;
				temp->next = temp2;
				temp->prev = temp2->prev;
				temp2->prev = temp;
				temp->prev->next = temp;
				break;
			}
		}
		x++;
		l->head = l->head->next;
	}
	l->head = temp1;
}













