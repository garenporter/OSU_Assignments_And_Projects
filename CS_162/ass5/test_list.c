/*Program: test_list.c
 * Author: Garen Porter
 * Date 6/5/16
 * Description: Reads ints from a file anc created a doubley linked list out of them. Then various operations are performed on the linked list.
 * Input: File of ints as well as some user input for added and deleted elements.
 * Output: The values of the linked list after various operations are performed on them.
 */

#include "./list.h"
#include <stdio.h>
#include <stdlib.h>

int main(){
	char filename[20];
	struct list l;
	struct node *temp = NULL;
	FILE *fileptr;
	char num[3];
	printf("Enter a filename: ");
	scanf("%s", filename);
	fileptr = fopen (filename, "r");

	l.head = NULL;
	l.tail = NULL;
	
	while(fscanf(fileptr, "%s", num) != EOF){
		temp = (struct node*) malloc(sizeof(struct node));
		temp->val=atoi(num);
		if(l.head == NULL){
			temp->prev = NULL;
			l.tail = temp;
		}
		else{
			
			l.head->prev = temp;
		}
		temp->next = l.head;
		l.head = temp;			
		printf("number is: %d \n", atoi(num));

	}

	printf("The length of the list is %d \n\n", length(l));
	print(l);

	printf("Here is the list in ascending order - \n");
	sort_ascending(&l);
	print(l);

	printf("Here is the list in descending order - \n");
	sort_descending(&l);
	print(l);
	
	int v;
	printf("Enter a value to be removed: ");
	scanf("%d", &v);		
	remove_val(&l, v);
	print(l);

	int v2, i;
	printf("Enter a value to be added: ");
	scanf("%d", &v2);
	printf("Enter the location of the value (0 is the beginning, 1 minus the total length is the end): ");
	scanf("%d", &i);
	insert(&l, i, v2);
	print(l);

	int v3;
	printf("Enter a value to be pushed to the front: ");
	scanf("%d", &v3);
	push_front(&l, v3);
	print(l);

	int v4;
	printf("Enter a value to be pushed to the back: ");
	scanf("%d", &v4);
	push_back(&l, v4);
	print(l);

	clear(&l);		
	fclose(fileptr);

	return 0;
}


















