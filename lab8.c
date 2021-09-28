//Priya Jain
//COEN 11
//Lab 8
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
void insert(char *name, int size);
void delete(void);
void show(void);
void search_size(void);
int check_duplicate(char *name);

void read_all(char *fileName);
void save_all(char *fileName);

void back_lists(void);
void back_names(void);
void backward_list(NODE *head);
void backward_name(char *name);
void delete_list(NODE *head);

int main(int argc, char *argv[]) {
	
	int input;
	char name[LENGTH];
	int size;

	if(argc == 1) {
		printf("The name of the file is missing!\n");
		return 1;
	}
	
	read_all(argv[1]);

	printf("Welcome to the Surf Lesson Scheduling System! \n\n");
	printf("0. Quit. \n");
	printf("1: Schedule an appointment. \n");
	printf("2: Remove an appointment. \n");
	printf("3: List the schedule. \n");
	printf("4: Search size. \n");
	printf("5: Print the schedule backwards. \n");
	printf("6: Print all names backwards. \n");

	while(1) {
		scanf("%d", &input);
		switch(input) {
			case 0:
 				save_all(argv[1]);
				quit();
				return;
			case 1:
				printf("Name: \n");
				scanf("%s", name);

				if(check_duplicate(name)) {
					printf("There is already an appointment under this name.\n");
					break;
				}
			
				printf("Group size: \n");
				scanf("%d", &size);

				insert(name, size);
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
			case 5:
				back_lists();
				break;
			case 6:
				back_names();
				break;
			default:
				printf("That command is not valid.\n");
				break;
		}
	}
	return 1;
}

//Reads data and inserts it in list
void read_all(char *file_name) {
	FILE *file;
	char fileName[LENGTH];
	int fileSize;

	//Opens file
	file = fopen(file_name, "r");
	
	//If file is empty
	while (file == NULL) {
		return;
	}
	
	//If file is not empty
	while(fscanf(file, "%s%d", fileName, &fileSize) == 2) {
		insert(fileName, fileSize);
	}
	fclose(file);
}

//Stores data in text file
void save_all(char *file_name) {
	FILE *file;
	NODE *temp;
	int i;

	//Opens file
	file = fopen(file_name, "w");

	//If data was not saved to file
	while(file == NULL) {
		printf("Error. Cannot open file.\n");
		return;
	}

	//fprintf(file, "Name,\tGroup Size\n");
	//fprintf(file, "------------------\n");

	//Saves name and group size to file
	for(i=0; i<SIZE; i++) {
		temp = array[i].head;
		while (temp != NULL) {
			fprintf(file, "%s\t%d\n", temp->name, temp->size);
			temp = temp->next;
		}
	}
	fclose(file);
}


//Free all nodes before quitting
void quit() {
	int i;
	NODE *p, *q;
	for(i=0; i<SIZE; i++) {
		p = q = array[i].head;
		delete_list(p);
	}
	return;
}

//Insert names
void insert(char *name, int size) {
	NODE *temp;
	temp = (NODE*)malloc(sizeof(NODE));
	int i;
	
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
			printf("List %d is available.\n", i);
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


//Recursive function that prints the schedule backwards
void backward_list(NODE *head) {
	if(head == NULL) {
		return;
	}
	backward_list(head->next);
	printf("Name: %s, Party of: %d\n", head->name, head->size);
	return;
}

//Recursive function that prints names backwards
void backward_name(char *name){
	if(*name == '\0') {
		return;
	}
	else {
		backward_name(name+1);
	}
	printf("%c", *name);
}

//Deletes list and frees nodes
void delete_list(NODE *head) {
	if(head == NULL) {
		return;
	}
	delete_list(head->next);
	free(head);
	return;
}

//Calls recursive function backward_list()
void back_lists() {	
	NODE *temp;
	int i;
	int count;
	for (i=0; i<SIZE; i++) {
		temp = array[i].head;
		if(temp == NULL) {
			printf("List %d is available.\n", i);
			return;
		}
		else {
			printf("Range: %d\n", i);
			backward_list(temp);
		}
	}
}

//Calls recursive function backward_name()
void back_names() {
	NODE *temp;
	int i;
	
	for(i=0; i<SIZE; i++) {
		temp = array[i].head;
		if(temp == NULL) {
			printf("List %d is available.\n", i);
			return;
		}
		else {
			printf("Range %d\n", i);
			while (temp != NULL) {
				backward_name(temp->name);
				printf("\n");
				temp = temp->next;
			}
		}
	}	
}
