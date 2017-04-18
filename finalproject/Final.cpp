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
		double amount;


		virtual void printInfo(void);
		void Withdrawal();
		void Deposit();
		void Invest();
		void Options();

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

void Customer::Withdrawal(){
	cout << "Current account balance: $" << balance << endl << "How much would you like to withdraw?" << endl;
	cin >> amount;
	try{
		if( amount > balance){
			throw "Unable to process this transaction. (Withdrawal of this size would result in negative balance";
		}
		balance -= amount;
	}
}

void Customer::Deposit(){
	cout << "Current acount balance: $" << balance << endl << "How much would you like to deposit?" << endl;
	cin >> amount;
	balance += amount;
	cout << "Your new balance is: $" << balance << endl;
}

void Customer::Options(){

}

int main(int argc, char* argv[])
{
	cout << "Thank you!" <<endl;
	return 0;
}
