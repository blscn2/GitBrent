//============================================================================
// Name        : Project
// Author      : Brent Schultz, Shayne Wadle
// Version     :
// Copyright   : Your copyright notice
// Description : Final Project
//============================================================================

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <vector>
using namespace std;


class Customer{
	protected:
		string name = "John Doe";
		int accountnumber = 123456;
		double balance = 356.25;
		string accounttype = "Standard or student or loyal";

	public:
		virtual void printInfo(void);
		void Withdrawal();
		void Deposit();
		void Invest();

		void CloseAccount();
		~Customer();

}

void Customer::printInfo(void){
	cout << "Account holder name: " << name << endl;
	cout << "Account number: " << accountnumber << endl;
	cout << "Account balance: $" << balance << endl;
	cout << "Account type: " << accounttype << endl;
}

Customer::~Customer(){

}

int main(int argc, char* argv[])
{
	cout << "Thank you!" <<endl;
	return 0;
}
