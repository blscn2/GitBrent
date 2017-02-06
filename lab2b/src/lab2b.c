/*
 ============================================================================
 Name        : lab2b.c
 Author      : Brent Schultz
 Version     :
 Copyright   : Your copyright notice
 Description : Problem2
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>


int bitwise(unsigned short x);

int main(void) {
	unsigned short number;
	int choice, binary[8], quotient, i = 0, j = 8;
	for(j=0;j<10;j++){
		binary[j] = 0;
	}
	printf("Enter a number to see its binary representation. (0-255)\n");
	scanf("%hu", &number);
	if(number < 0 || number >255 ){
		printf("outside the limits \n");
		return 0;
	}
	printf("Type 1 for arithmetic.\nType 2 for bitwise.\n");
	scanf("%d", &choice);
	if(choice == 1){
		quotient = number;
		while(quotient != 0){
			binary[i++] = quotient % 2;
			quotient = quotient / 2;
		}

		printf("The Binary Equivalent is\n");
		for(j=7; j>=0; j--){
			printf("%d", binary[j]);
		}
		printf("\n");
	}else if(choice == 2){
		bitwise(number);
		printf("\n");

	}else
		printf("Invalid choice. Closing program\n");

	return EXIT_SUCCESS;
}

int bitwise(unsigned short n){

	unsigned int range=32768;
	printf("The Binary Eqivalent is \n");
	xy:
	if(range > 0){
		if((n & range) == 0 ){
			range = range >> 1 ;
	        goto xy;
		}
		else{
			while(range>0){
			if((n & range) == 0 )
				printf("0");
			else
				printf("1");
			range = range >> 1 ;
			}
		}
	}
	return 0;
}
