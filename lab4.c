//Priya Jain
//COEN 11
//Lab 4
//Tuesday 5:15pm

#include <stdio.h>
#include <string.h>

#define SIZE 10
#define LENGTH 20

void insert(void);
void delete(void);
void list(void);
void search_size(void);
int check_duplicate(char*);

int count = 0;

union extra_info {
	char phone[10];
	int min_age;
	float avg_age;
};

struct waitlist {
	char name[20];
	int size;
	int max_age;
	union extra_info info;
};

struct waitlist array[SIZE];

int main() {
	int input;
	printf("Welcome to the Surf School Waiting List! \n\n");
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
		scanf("%s", array[count].name);

		if(check_duplicate(array[count].name)) {
			printf("There is already an appointment under this name.\n");
			return;
		}
		
		printf("Group size: \n");
		scanf("%d", &array[count].size);

		printf("Maximum age: \n");
		scanf("%d", &array[count].max_age);
			if(array[count].max_age < 18) {
				printf("Parent/Guardian's phone number: \n");
				scanf("%s", &array[count].info.phone);	
			}
			else if(array[count].max_age > 65) {
				printf("Age of youngest in group: \n");
				scanf("%d", &array[count].info.min_age);
			}
			else {
				printf("Average age: \n");
				scanf("%f", &array[count].info.avg_age);
			}

		count++;
		//printf("A group has been added at %d\n", count);
		return;
	}
}	

void delete() {
	int i, j, group;
	struct waitlist *p;	
	p = array;
	
	if(count == 0) {
		printf("All lessons are available. \n");
        }
        else {
                printf("Enter the number that corresponds with the group size you would like to cancel.\n");
        	scanf("%d", &group);
                for(i=0; i<count; i++, p++) {
			if(group > 0) {
				if(array[i].size <= group) {
					group -= array[i].size;
					printf("%s's lesson for a party of %d has been cancelled.\n", p->name, p->size);
					for(j=i; j<count-1; j++) {
						//strcpy(array[j].name,array[j+1].name);            
						//array[j].size = array[j+1].size;
						//array[j].max_age = array[j+1].max_age;
						array[j] = array[j+1];
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
	p = array;
	
	if(count == 0) {
		printf("All appointments are available. \n");
        }
	else {
		for(i=0; i<count; i++, p++) {
			if(p->max_age < 18) {
				printf("Name: %s, Party of: %d, Maximum age: %d, Guardian Phone Number: %s \n", p->name, p->size, p->max_age, p->info.phone);
			}
			else if(p->max_age > 65) {
				printf("Name: %s, Party of: %d, Maximum age: %d, Minimum age: %d \n", p->name, p->size, p->max_age, p->info.min_age);
			}
			else {
				printf("Name: %s, Party of: %d, Maximum age: %d, Average age: %f \n", p->name, p->size, p->max_age, p->info.avg_age);       
			}
		//printf("This is the count: %d", count);
		}
	}
}

void search_size() {
	int i, search;
	struct waitlist *p;
	p = array;
	printf("Enter a group size: \n");
	scanf("%d", &search);
	for(i=0; i<count; i++, p++) {
		if(p->size <= search) {
			if(p->max_age < 18) {
				printf("Name: %s, Party of: %d, Maximum age: %d, Guardian Phone Number: %s \n", p->name, p->size, p->max_age, p->info.phone);
			}
			else if(p->max_age > 65) {
				printf("Name: %s, Party of: %d, Maximum age: %d, Minimum age: %d \n", p->name, p->size, p->max_age, p->info.min_age);
			}
			else {
				printf("Name: %s, Party of: %d, Maximum age: %d, Average age: %f \n", p->name, p->size, p->max_age, p->info.avg_age);
			}
			//printf("Name: %s, Party of: %d\n", p->name, p->size);
		}	
	}
}


int check_duplicate(char *p) {
	int i;
	for(i=0; i<count; i++) {
		if(strcmp(p, array[i].name) == 0) {
			return 1;
		}
		else {
			return 0;
		}
	}
}
