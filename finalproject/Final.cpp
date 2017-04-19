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
#include <string>
#include <vector>
#include <fstream>

using namespace std;


//============================ Classes =======================================
class Person {
	protected:
		string name = "John Doe";
		int accountnumber = 123456;
		string username;
		string password;

	public:
		virtual void printInfo( void ) = 0;
		bool isOpen( );
		Person( );
		Person( string , int, string, string);
		~Person( );
};

class Customer: public Person {
	protected:
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

};
//============================ Class functions ================================
/*	Default constructor
	Initializes everyting to their zero value */
Person::Person( )
{
	name = "";
	num = 0;
}

/*	Parametric constructor
	Initializes the two private variables to the passed values */
Person::Person(string n, int num, string user, string pass)
{
	name = n;
	accountnumber = num;
	username = user;
	password = pass;
}

/*	Public function
	Returns is the account has been open: i.e. initialized. */
bool Person::isOpen( )
{
	return ( name.empty ); // I am not completely sure this will give output wanted.
}

/*	Deconstructor
	Does nothing currently since nothing is dynamically allocated */
Person::~Person( )
{

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

//============================ Other functions ===============================
/*	Global funciton
	Opens fills and checks the information to validate the correct user is there*/
Person* login( string user, string pass ) throw(string)
{
	fstream in( "Accounts.txt", fstream::in );
	
	string name;
	string word;
	char type;

	while( cin >> name >> word >> type )
	{
		try {
			if( name == user )
			{
				if( word != pass )
				{
					throw "Invalid username or password";
				}
				else
					break;
			}
			else
				continue;
		}
	}

	return NULL;
}

//============================ Main ==========================================
int main(int argc, char* argv[])
{
	char choice = '0';
	
	// Output welcome message and primary menu
	cout << "Welcome to "<<endl;
	do {
		
		cout << "How might we be of service?\n"
		     << "1) Open new account\n"
		     << "2) Login"
		     << "3) Quit" << endl;
		cin >> choice;
		
		// Check for bad input
		if( choice < 49 || choice > 51 )
		{
			cout << "I'm sorry. That is not an option.\n"
			     << "Please choose again\n";
		}
	// loop if there was bad input
	} while(  choice < 49 || choice > 51 );
	
	//Branch based on menu choice.
	switch(choice)
	{
	case '1':
		// Present New account screen
		break;
	case '2':
	{
		// Present login screen and track attempts
		unsigned short attempt = 0;
		string username;
		string password;
		Customer account;
		while(attempt < 3 && !account.isOpen())
		{
			cout << "Username: ";
			cin >> username;
			cout << "Password: ";
			cin >> password;

			attempt++;
			try {
				account = login( username, password );
			}
			catch( string s )
			{
				cout << s << endl;
			}
		}
		break;
	}
	case '3':
		// Do nothing because quiting.
		break;
	default:
		cerr << "Computer malfunction. Exiting!\n"<<endl;
		break;
	}
	
	cout << "Thank you!" <<endl;
	return 0;
}
