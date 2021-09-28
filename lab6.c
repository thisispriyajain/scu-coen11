//Priya Jain
//COEN 11
//Lab 6
//Tuesday 5:15pm

#define NODE struct node
#define SIZE 4
#define LENGTH 20

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
	char name[LENGTH];
	int size;
	NODE *next;
};

struct list {
	NODE *head;
	NODE *tail;
};

struct list array[SIZE] = {{NULL, NULL}, {NULL, NULL}, {NULL, NULL}, {NULL, NULL}};

void quit(void);
void insert(void);
void delete(void);
void show(void);
void search_size(void);
int check_duplicate(char*);

int main() {
	int input;
	printf("Welcome to the Surf Lesson Scheduling System! \n\n");
	printf("1: Schedule an appointment. \n");
	printf("2: Remove an appointment. \n");
	printf("3: List the schedule. \n");
	printf("4: Search size. \n");
	printf("0. Quit. \n");

	while(1) {
		scanf("%d", &input);
		switch(input) {
			case 0:
				quit();
				break;
			case 1:
				insert();
				break;
			case 2:
				delete();
				break;
			case 3:
				show();
				break;
			case 4:
				search_size();
				break;
			default:
				printf("That command is not valid.\n");
				break;
		}
	}
	return 1;
}

//Free all nodes before quitting
void quit() {
	int i;
	NODE *p, *q;
	for(i=0; i<SIZE; i++) {
		p = q = array[i].head;
		while(p != NULL) {
			q = q->next;
			free(p);
			p = q;
		} 
	}
	return;
}

//Insert names
void insert() {
	char name[LENGTH];
	int size;
	NODE *temp;
	temp = (NODE*)malloc(sizeof(NODE));
	int i;

	printf("Name: \n");
	scanf("%s", name);

	if(check_duplicate(name)) {
		printf("There is already an appointment under this name.\n");
		return;
	}

	printf("Group size: \n");
	scanf("%d", &size);
	
	strcpy(temp->name, name);
	temp->size = size;

	switch(size) {
		case 1:
		case 2:
			i = 0;
			break;
		case 3:
		case 4:
			i = 1;
			break;
		case 5:
		case 6:
			i = 2;
			break;
		default:
			i = 3;
			//break;
	
	}

	//If first element is empty
	if (array[i].head == NULL) {
		array[i].head = array[i].tail = temp;
		temp->next = NULL;
	}
	//If not
	else {
		array[i].tail->next = temp;
		array[i].tail = temp; 
		temp->next = NULL;
	}
	return;
}	

//Delete function
void delete() {
	NODE *p, *q;
	int i, group;
	int index;	

	printf("Enter the number that corresponds with the group size you would like to delete.\n");
	scanf("%d", &group);

	switch(group) {
		case 1:
		case 2:
			index = 0;
			break;
		case 3:
		case 4:
			index = 1;
			break;
		case 5:
		case 6:
			index = 2;
			break;
		default:
			index = 3;
	}	

	for(i=0; i<=index&& group>0; i++) {
		p = q = array[i].head;
		while (p != NULL && group > 0) {
			if(p->size > group) {
				//printf("%s's lesson for a party of %d has been cancelled.\n", p->name, p->size);	
				q = p;
				p = p->next;	
				//group -= p->size;
			}
			else{
				printf("%s's lesson for a party of %d has been cancelled.\n", p->name, p->size);
				group -= p->size;
				
				//Only one node
				if(array[i].head == array[i].tail) {
					array[i].head = NULL;
					array[i].tail = NULL;
					free(p);
					printf("Debug 1\n");
					break;
				}

				//Head node
				else if(p == array[i].head) {
					array[i].head = p->next;
					free(p);
					q = array[i].head;
					p = array[i].head;
					printf("Debug 2\n");
				}

				//Tail node	
				else if(p == array[i].tail) {
					array[i].tail = q;
					q->next = NULL;
					free(p);
					printf("Debug 3\n");
					break;
				}
				//Middle node
				else {
					q->next = p->next;
					free(p);
					p = q->next;
					printf("Debug 4\n");
				}
			}		
		}
	}
}

//Print list
void show() {
	NODE *temp;
	int i;
	
	for(i=0; i<SIZE; i++) {
		temp = array[i].head;
		
		if(temp == NULL) {
			printf("All appointments are available. \n");
		} else{
			printf("Range: %d\n", i);
			while (temp != NULL) {
				printf("Name: %s, Party of %d\n", temp->name, temp->size);
				temp = temp->next;       	
			}
		}
	}
	return;
}

//Search for size <= entered group size
void search_size() {
	int i, search;
	NODE *temp;
	
	printf("Enter a group size: \n");
	scanf("%d", &search);
	
	for(i=0; i<SIZE; i++) {
		temp = array[i].head;
		while(temp != NULL) {
			if(temp->size <= search) {
				printf("%s, Party of %d\n", temp->name, temp->size);
			}
			temp = temp->next;
		}
	}
}

//Check for duplicate name
int check_duplicate(char *name) {
	int i;
	NODE *temp;
	for(i=0; i<SIZE; i++) {
		temp = array[i].head;
		while (temp != NULL) {
			if(strcmp(name, temp->name) == 0) {
				return 1;
			}
			temp = temp->next;
		}
	}
	return 0;
}
