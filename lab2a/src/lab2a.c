/*
 ============================================================================
 Name        : Brent Schultz
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Problem 1
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#define max(a,b) (a > b) ? a : b;

int main(void) {
	int i, numerator, denom;
	char choice;
	unsigned short input;
	unsigned long output;
	unsigned int year;
	float num1, num2, maximum, result;

	while(1){
	printf(" a:Factorial\n b:Leap Year?\n c:Maximum\n d:Division of two numbers\n e:Exit program.\nEnter your choice: (a,b,c,d,or e)\n");
	scanf(" %c", &choice);
	fflush(stdout);


	switch(choice){
	case 'a':
		printf("Enter a number: \n"); //Restrict to values that would fit in unsigned long (12)
		scanf("%hu", &input);
		output = 1;
		for(i = 1; i <= input; i++){
			output = output * i;
		}
		printf("%u! = %lu \n", input, output);
		break;
	case 'b':
		printf("Enter a year to check if its a leap year: \n");
		scanf("%u", &year);

		if(((year%4==0)&&(year%100!=0))||(year%400==0)){
			printf("%u is a leap year\n",year);
		} else{
			printf("%u is not a leap year\n",year);
		}
		break;
	case 'c':
		printf("Finding the max number\nEnter the first number to be compared:\n");
		scanf("%f", &num1);
		printf("Enter the second number to be compared:\n");
		scanf("%f", &num2);
		maximum = max(num1, num2);
		printf("The maximum is: %f \n", maximum);
		break;
	case 'd':
		printf("Enter the numerator:\n");
		scanf("%d", &numerator);
		printf("Enter the denominator:\n");
		scanf("%d", &denom);
		result = (float)numerator / (float)denom;
		printf("%d / %d = %f \n", numerator, denom, result);
		break;
	case 'e':
		printf("Exiting the program\n");
		return 0;
		break;
	}
	}
	return 0;
}
