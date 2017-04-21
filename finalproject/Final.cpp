//============================================================================
// Name        : Project
// Author      : Brent Schultz, Shayne Wadle
// Version     :
// Copyright   : Your copyright notice
// Description : Final Project     -std=c++11
//============================================================================

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;


//============================ Classes =======================================
class Person {
	protected:
		string name; // = "John Doe"
		int accountnumber; // = 123456;
		string username; // = "JDoe12"
		string password; // = "Doe#12Donut"

	public:
		virtual void printInfo( void ) = 0;
		bool isOpen( );
		virtual void Options( ) = 0;
		Person( );
		Person( string , int, string, string);
		~Person( );
};

class Customer: public Person {
	protected:
		double balance; // = 356.25;
		string accounttype; // = "Standard or student or loyal";

	public:
		double amount;

		Customer( string, int, string, string, double, string );

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
	accountnumber = 0;
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
	return ( name.empty() ); // I am not completely sure this will give output wanted.
}

/*	Deconstructor
	Does nothing currently since nothing is dynamically allocated */
Person::~Person( )
{

}
// Constructor
Customer::Customer( string n, int an, string u, string p, double b, string t ):Person(n,an,u,p)
{
	balance = b;
	accounttype = t;
}
/* Prints account information and balance */
void Customer::printInfo(void){
	cout << "Account holder name: " << name << endl;
	cout << "Account number: " << accountnumber << endl;
	cout << "Account balance: $" << balance << endl;
	cout << "Account type: " << accounttype << endl;
}

Customer::~Customer(){
	//Nothing dynamically allocated yet.
}
// Allows customer to withdraw from account
void Customer::Withdrawal(){
	cout << "Current account balance: $" << balance << endl << "How much would you like to withdraw?" << endl;
	cin >> amount;
	int yon;
	if( amount > balance ) {
		cout << "Withdrawal of this size will result in negative balance. Do you still wish to withdraw this amount?" << endl;
		cout << "Type 1 for yes or 2 for no." << endl;
		cin >> yon;
		if (yon == 1){
			balance = balance - amount - 30;
		}
		else if (yon == 2){
			cout << "Cancelling withdrawal. Your balance is still $" << balance << endl;
		}
		else{
			cout << "Invalid choice. Cancelling withdrawal." << endl;
		}
		break;
	}
	balance -= amount;
	cout << "Your new balance is: $" << balance << endl;
}
// Allows customer to make a deposit
void Customer::Deposit(){
	cout << "Current account balance: $" << balance << endl << "How much would you like to deposit?" << endl;
	cin >> amount;
	if( amount < 0){
		cout << "Cannot deposit negative numbers..."<< endl;
		break;
	}
	if( amount > sizeof(double)){
		cout << "Our bank can't handle that much money..."<< endl;
		break;
	}
	balance += amount;
	cout << "Your new balance is: $" << balance << endl;
}
// Option menu accessible by the customer
void Customer::Options(){
	string choice;
	do {
		cout << "What do ou want to do?\n"
			<< "1) Deposit\n"
			<< "2) Withdraw\n"
			<< "3) Close the account(Not functional)\n" //Will add more options later (interest,
			<< "4) Exit" << endl;
		cin >> choice;
		try {
			if( choice.length( ) > 1 )
				throw "I'm sorry. That is not an option.\nPlease choose again\n";
			if( choice.at( 0 ) < '1' || choice.at( 0 ) > '4' )
				throw "I'm sorry. That is not an option.\nPlease choose again\n";
		}
		catch( const char* s )
		{
			cout << s << endl;
			continue;
		}
		break;
	} while( true );

	switch( choice.at( 0 ) )
	{
	case '1':
		Deposit();
		break;
	case '2':
		Withdrawal();
		break;
	case '3':
		int accntclose;
		cout << "Closing your account. All balances will be withdrawn and information destroyed." << endl;
		cout << "Are you sure you wish to delete the account?\nType:\n1 for yes\n2 for no."<< endl;
		cin >> accntclose;
		if (accntclose == 1 ){
//		delete account;
		} else if (accntclose == 2){
			cout << "Account will not be closed. Returning to menu." << endl;
		} else {
			cout << "Invalid choice. Try again (one attempt remaining)." << endl;
			cout << "Are you sure you wish to delete the account?\nType:\n1 for yes\n2 for no."<< endl;
					cin >> accntclose;
					if (accntclose == 1 ){
			//		delete account;
					} else if (accntclose == 2){
						cout << "Account will not be closed. Returning to menu." << endl;
						break;
					} else {
						cout << "Invalid choice. Account will not be deleted." << endl;
					}
		}

		break;
	case '4':
		cout << "Returning to menu." << endl;
		break;
	default:
		throw "Something went wrong. Exiting!";
	}
}

//============================ Other functions ===============================
/*	Global funciton
	Opens fills and checks the information to validate the correct user is there*/
Person* login( string user, string pass ) throw(char)
{
	fstream in( "Accounts.txt", fstream::in );

	if( !in.is_open( ) )
		throw 'B';
	
	string username; //Username
	string password; //Password
	char type; //the kind of person they are.


	//Scanf through file looking for correct username and password combination.
	while( in >> username >> password >> type )
	{
		if( username == user )
		{
			if( password != pass ) // Password does not match username given.
			{
				throw 'A';
			}
			else
				break;
		}
		else
			continue;
	}
	
	if( in.eof( ) ) // No username matches the one given.
		throw 'A'; 

	in.close( );
	
	// Open that users file
	in = fstream( "/accounts/" + user, fstream::in );
	
	if( !in.is_open( ) )
		throw 'B';

	string name;
	int accountnumber;
	in >> name >> accountnumber;
	
	//Load in that user
	switch( type )
	{
		case 'C':
		{
			string type;
			double balance;
			in >> type >> balance;
			in.close( );
			return new Customer( name, accountnumber, username, password, balance, type );
			break;
		}
		case 'E':
			break;
		case 'M':
			break;
	}
	in.close( );
	return NULL;
}

int getNewNumber( )
{
	srand( time( NULL ) );

	fstream in( "AccountNums.txt", fstream::in);
	if( !in.is_open( ) )
		throw "B";
	vector<int> nums = {0000000 };

	int temp;
	while(! in.eof() )
	{
		in >> temp;
		nums.push_back( temp );
	}
	in.close( );
	int newNum;
	do {
		newNum = rand( );
		int i;
		for( i = 0; i < nums.size( ); i++ )
			if( newNum == nums[i])
				continue;
		break;
	} while( true );
	in = fstream( "AccountNums.txt", fstream::app );

	in << newNum << endl;
	in.close( );
	return newNum;
}

//============================ Main ==========================================
int main(int argc, char* argv[])
{
	string choice;
	
	// Output welcome message and primary menu
	cout << "Welcome to "<<endl;
	do {
		try {
			cout << "How might we be of service?\n"
				<< "1) Open new account\n"
				<< "2) Login\n"
				<< "3) Quit" << endl;
			cin >> choice;

			if( choice.length() > 1 )
				throw "I'm sorry. That is not an option\nPlease choose again.\n";
				// Check for bad input
			if( choice.at(0) < '1' || choice.at(0) > '3' )
				throw "I'm sorry. That is not an option.\nPlease choose again\n";		
		}
		catch(const char* s)
		{
			cout << s << endl;
			continue;
		}
		break;
	// loop if there was bad input
	} while( true );
	

	Person* account;
	//Branch based on menu choice.
	switch(choice.at(0))
	{
	case '1':
	{	// Present New account screen
		string n;
		string u;
		string p, p2;
		cout << "Excellent. We just need some information for you to have it open!"
			<< "What is your name?" << endl;
		cin >> n;
		cout << "\nWhat do you want your username to be?" << endl;
		cin >> u;
		do {
			cout << "\nWhat do you want your password to be?" << endl;
			cin >> p;
			cout << "\nPlease type that again to make sure we have that right." << endl;
			cin >> p2;
			try {
				if( p != p2 )
					throw "Those do not match please try again.";
			}
			catch( const char* s )
			{
				cout << s << endl;
				continue;
			}
			break;
		} while( true );

		cout << "Alright just one moment while we initialize your account" << endl;
		account = new Customer( n, getNewNumber( ), u, p, 0.0, "Standard" );

		cout << "There! Your account will open just like you just logged on.\nThank you" << endl;
		break;
	}
	case '2':
	{
		// Present login screen and track attempts
		unsigned short attempt = 0;
		string username;
		string password;
		do
		{
			cout << "Username: ";
			cin >> username;
			cout << "Password: ";
			cin >> password;

			attempt++;
			try {
				account = login( username, password );
			}
			catch( char s )
			{
				switch( s )
				{
				case 'A':
					cout << "Invalid username or password" << endl;
					continue;
					break;
				case 'B':
					cout << "Our services our currently down. Please try again at another time." << endl;
					continue;
					break;
				default:
					cerr << "Something went wrong" << endl;
					continue;
					break;
				}
			}
			break;
		} while( attempt < 3);
		break;
	}
	case '3':
		// Completely exit as one has not opened anything.
		cout << "Thank you!" << endl;
		return 0;
		break;
	default:
		cerr << "Computer malfunction. Exiting!\n"<<endl;
		return 1;
		break;
	}
	
	account->printInfo( );
	try {
		account->Options( );
	}
	catch( const char * )
	{

	}
	cout << "Thank you!" <<endl;
	return 0;
}
