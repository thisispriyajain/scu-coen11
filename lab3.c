//Priya Jain
//COEN 11
//Lab 3
//Tuesday 5:15pm

#include <stdio.h>
#include <string.h>

#define SIZE 10
#define LENGTH 20

int count = 0;

void insert(void);
void delete(void);
void list(void);
void search_size(void);
int check_duplicate(char*);

struct waitlist {
	char name[20];
	int size;
};

struct waitlist info[SIZE];

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
				list();
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
	if(count == SIZE) {
		printf("Sorry, the instructor is all booked up. Please try again tomorrow.\n"); 
      		return;
	}
	else {
		printf("Name: \n");
		scanf("%s", info[count].name);

		if(check_duplicate(info[count].name)) {
			printf("There is already an appointment under this name.\n");
			return;
		}
		
		printf("Group size: \n");
		scanf("%d", &info[count].size);
		count++;
		printf("A group has been added at %d\n", count);
		return;
	}
}	

void delete() {
	int i, j, group;
	struct waitlist *p;	
	p = info;
	
	if(count == 0) {
		printf("All lessons are available. \n");
        }
        else {
                printf("Enter the number that corresponds with the group size you would like to cancel.\n");
        	scanf("%d", &group);
                for(i=0; i<count; i++, p++) {
			if(group > 0) {
				if(info[i].size <= group) {
					group -= info[i].size;
					printf("%s's lesson for a party of %d has been cancelled.\n", p->name, p->size);
					for(j=i; j<count-1; j++) {
						strcpy(info[j].name,info[j+1].name);            
						info[j].size = info[j+1].size;
					}
					count--;
					i--;
					p--;
				}
			}
		}
	}
	return;
}

void list() {
	int i;
	struct waitlist *p;
	p = info;
	
	if(count == 0) {
		printf("All appointments are available. \n");
        }
	else {
		for(i=0; i<count; i++, p++) {
			printf("%s, Party of %d\n", p->name, p->size);       
		}
		printf("This is the count: %d", count);
	}
}

void search_size() {
	int i, search;
	struct waitlist *p;
	p = info;
	printf("Enter a group size: \n");
	scanf("%d", &search);
	for(i=0; i<count; i++, p++) {
		if(p->size <= search) {
			printf("%s, Party of %d\n", p->name, p->size);
		}	
	}
}


int check_duplicate(char *p) {
	int i;
	for(i=0; i<count; i++) {
		if(strcmp(p, info[i].name) == 0) {
			return 1;
		}
		else {
			return 0;
		}
	}
}
