/*
 ============================================================================
 Name        : Lab1b.c
 Author      : Cameron Tucker, Brent Schultz
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>

int main(void) {
	float cost;
	float sell;
	float loss;
	float gain;

	printf("\nEnter cost of Item\n");
	scanf("%f", &cost);
	printf("\nEnter the selling price of the item\n");
	scanf("%f", &sell);

	if(cost < sell)
	{
		gain = sell - cost;
		printf("\nThe profit is $%.2f \n\n", gain);
	}
	else if(sell < cost)
	{
		loss = cost - sell;
		printf("\nThe loss is $%.2f \n\n", loss);
	}
	else
		printf("\nThere was no loss or gain \n\n");

	return 0;
}
