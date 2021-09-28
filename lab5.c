//Priya Jain
//COEN 11
//Lab 5
//Tuesday 5:15pm

#define NODE struct node
#define SIZE 10
#define LENGTH 20

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
	char name[LENGTH];
	int size;
	NODE *next;
};

NODE *head = (NODE *)NULL;
NODE *tail = (NODE *)NULL;

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
				return 1;
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

void insert() {
	char name[LENGTH];
	int size;
	NODE *temp;

	printf("Name: \n");
	scanf("%s", name);

	if(check_duplicate(name)) {
		printf("There is already an appointment under this name.\n");
		return;
	}

	printf("Group size: \n");
	scanf("%d", &size);
	
	if((temp = (NODE *)malloc (sizeof (NODE))) == NULL) {
		printf("Malloc error \n");
		return;
	}
	strcpy(temp->name, name);
	temp->size = size;

	if (head == NULL) {
		head = tail = temp;
		temp->next = NULL;
	}
	else {
		tail->next = temp;
		temp->next = NULL;
		tail = temp;
	}
	return;
}	

void delete() {
	NODE *p;
	NODE *q;
	int group;	
	int result;
		
	if(head == NULL) {
		printf("All lessons are available. \n.");
	}

	printf("Enter the number that corresponds with the group size you would like to delete.\n");
	scanf("%d", &group);

	result = 0;
	q = p = head;
	while (p != NULL && group > 0) {
		if(p->size > group) {
			q = p;
			p = p->next;
		}
		else {
			printf("%s's lesson for a party of %d has been cancelled.\n", p->name, p->size);
			group -= p->size;

			if(head == tail) {
				head = tail = NULL;
				free(p);
				return;
			}
			else if(p == tail) {
				tail = q;
				q->next = NULL;
				free(p);
				return;
			}
			else if(p == head) {
				head = p->next;
				free(p);
				q = p = head;
				result++;
			}
			else {
				q->next = p->next;
				free(p);
				p = q->next;
				result++;
			} 	     
		
		}
	}
}

void show() {
	NODE *p;
	p = head;
	if(head == NULL) {
		printf("All appointments are available. \n");
        	return;
	}
	while (p != NULL) {
		printf("%s, Party of %d\n", p->name, p->size);
		p = p->next;       	
	}
	return;
}

void search_size() {
	int i, search;
	NODE *p;
	p = head;
	
	printf("Enter a group size: \n");
	scanf("%d", &search);
	
	while(p != NULL) {
		if(p->size <= search) {
			printf("%s, Party of %d\n", p->name, p->size);
		}
		p = p->next;
	}
}

int check_duplicate(char *name) {
	int i;
	NODE *p;
	p = head;
	while (p != NULL) {
		if(strcmp(name, p->name) == 0) {
			return 1;
		}
		p = p->next;
	}
	return 0;
}
