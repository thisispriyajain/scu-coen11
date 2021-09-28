//Priya Jain
//COEN 11
//Lab 2
//Tuesday 5:15pm

#include <stdio.h>
#include <string.h>

#define SIZE 10
#define LENGTH 20

int count = 0;
int size[SIZE];

char names[SIZE][LENGTH];
char customer[20];

void insert(void);
void delete(void);
void list(void);

int main() {
	int input;
	printf("Welcome to the Surf Lesson Scheduling System! \n\n");
	printf("1: Schedule an appointment. \n");
	printf("2: Remove an appointment. \n");
	printf("3: List the schedule. \n");
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
			default:
				printf("That command is not valid.\n");
				break;
		}
	}
	return 1;
}

void insert() {
	char customer[20];
	int group;
	int i;

	if(count >= 5) {
		printf("Sorry, the instructor is all booked up. Please try again tomorrow.\n"); 
        }
	else {
		printf("Name: \n");
		scanf("%s", &customer);
		
		printf("Group size: \n");
		scanf("%d", &group);
		
		for(i=0; i<5; i++) {
			if(names[i][0] == '\0') {
				strcpy(names[i], customer);
				size[i] = group;
				count++;
				printf("A lesson for %s for a party of %d has been scheduled.\n", customer, group);
				break;
			}
		}
	}
}	

void delete() {
	int i;
	int j;
	int group;
	int foundGroup = 0;
	
	if(count == 0) {
		printf("All lessons are available. \n");
        }
        else {
                printf("Enter the number that corresponds with the group size you would like to cancel.\n");
        	scanf("%d", &group);
                for(i=0; i<count; i++) {
			if(group > 0) {
				if(size[i] <= group) {
					group -= size[i];
					foundGroup = 1;
					printf("%s's lesson for a party of %d has been cancelled.\n", names[i], size[i]);
                        		
					for(j=i; j<count; j++) {
						strcpy(names[j], names[j+1]);            
						size[j] = size[j+1];
					}
					count--;
					i--;
				}
			}
		}
		if(foundGroup == 0) {
			printf("There is no group size of that number.\n");
		}
	}
	return;
}

void list() {
	int i;
	if(count == 0) {
		printf("All appointments are available. \n");
        }
	else {
		for(i=0; i<count; i++) {
			printf("%s, Party of %d\n", names[i], size[i]);
                }
          	
	}
}
