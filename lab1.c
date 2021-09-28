//Priya Jain
//COEN 11
//Lab 1
//Tuesday 5:15pm

#include <time.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
	printf("Division Test.\n");
	int i;
	int userQuo = 0;
	int counter = 0;
	int divisor;
	int quotient;
	int dividend;
	srand((int)time(NULL));
	
	for(i=0; i<10; i++) {
		divisor = rand() % 12 + 1;
		quotient = rand() % 13;
		dividend = divisor * quotient;
		printf("What is %d / %d \n", dividend, divisor);
		scanf("%d", &userQuo);
		
		int check = division(userQuo, quotient);

		if(check == 1) {
       			printf("That is correct.\n");
			counter++;
		}
		else {
			printf("That is incorrect. The correct answer is %d.\n", quotient);
		}
	}

	printf("You got %d%%.\n", counter*10); 
}

int division(int userQuo, int quotient) {
	if(quotient == userQuo){
		return 1;
	}
	else {
		return 0;
	}
}
