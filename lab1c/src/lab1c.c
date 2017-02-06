/*
 ============================================================================
 Name        : Lab1c.c
 Author      : Cameron Tucker, Brent Schultz
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
	float first, second, result;
	char operator;
	printf("Enter the first operand \n");
	fflush(stdout);
	scanf("%f", &first);

	printf("Enter the second operand \n");
	fflush(stdout);
	scanf("%f", &second);
	printf("Enter the operator\n");
	fflush(stdout);
	operator = getchar(); //get rid of trailing \n from scanf
	operator = getchar();

	switch(operator){
	case '+':
		result = first + second;
		printf("%.1f %c %.1f = %.1f", first, operator, second, result);
		break;
	case '-':
		result = first - second;
		printf("%.1f %c %.1f = %.1f", first, operator, second, result);
		break;
	case '*':
		result = first * second;
		printf("%.1f %c %.1f = %.1f", first, operator, second, result);
		break;
	case '/':
		//if here
		result = first / second;
		if (second == 0){
			printf("nit by 0");

		}
		printf("%.1f %c %.1f = %.1f", first, operator, second, result);
		break;
	default:
		printf("Operator not recognized\n");
		break;
	}
	printf("\n");
	return 0;

}
