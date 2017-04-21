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
		friend save( Person* p );
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

Person::~Person( )
{

}

Customer::Customer( string n, int an, string u, string p, double b, string t ):Person(n,an,u,p)
{
	balance = b;
	accounttype = t;
}

void Customer::printInfo(void){
	cout << "Account holder name: " << name << endl;
	cout << "Account number: " << accountnumber << endl;
	cout << "Account balance: $" << balance << endl;
	cout << "Account type: " << accounttype <<"\n"<< endl;
}

Customer::~Customer(){
	fstream userFile( "accounts\\" + username + ".txt", fstream::trunc | fstream::out );

	userFile << username << " " << password << " C" << endl;
	userFile << name << "\n" << accountnumber << endl;
	userFile << accounttype << " " << balance << endl;

	userFile.close( );
	cout << "Account closed." << endl;
}

void Customer::Withdrawal(){
	cout << "Current account balance: $" << balance << endl << "How much would you like to withdraw?" << endl;
	cin >> amount;
//	try {
		if( amount > balance ) {
			throw "Unable to process this transaction. (Withdrawal of this size would result in negative balance";
		}
		balance -= amount;
//	}
}

void Customer::Deposit(){
	cout << "Current acount balance: $" << balance << endl << "How much would you like to deposit?" << endl;
	cin >> amount;
	balance += amount;
	cout << "Your new balance is: $" << balance << endl;
}

void Customer::Options(){
	string choice;
	do {
		cout << "What do ou want to do?\n"
			<< "1) Deposit\n"
			<< "2) Withdraw\n"
			<< "3) Close the account(Not functional)\n"
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
		break;
	case '2':
		break;
	case '3':
		break;
	case '4':
		break;
	default:
		throw "Something went wrong. Exiting!";
	}
}

//============================ Other functions ===============================
/*	Global funciton
	Opens fills and checks the information to validate the correct user is there*/
Person* login( string user, string pass, char* t ) throw(char)
{
	fstream in( "accounts/" + user + ".txt", fstream::in );

	if( !in.is_open( ) )
		throw 'A';
	
	string username; //Username
	string password; //Password
	char type; //the kind of person they are.

	in >> username >> password >> type;
	if( password != pass ) // Password does not match username given.
	{
		throw 'A';
	}
	in >> ws;
	string name;
	int accountnumber;
	getline( in, name );
	in >> accountnumber;
	
	//Load in that user
	switch( type )
	{
		case 'C':
		{
			string type;
			double balance;
			in >> type >> balance;
			in.close( );
			*t = 'C';
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
	char type;
	//Branch based on menu choice.
	switch(choice.at(0))
	{
	case '1':
	{	// Present New account screen
		string n;
		string u;
		string p, p2;
		cout << "\nExcellent. We just need some information for you to have it open!\n"
			<< "What is your name?" << endl;
		cin >> ws;
		getline( cin, n );
		fstream in;
		do {
			in.close( );
			cout << "\nWhat do you want your username to be?" << endl;
			cin >> u;
			in.open( "accounts/" + u + ".txt", fstream::in);
			if( in.is_open( ) )
				cout << "I'm sorry. That username has already been taken." << endl;
		} while( in.is_open( ) );
		in.close( );
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

		cout << "\nAlright just one moment while we initialize your account" << endl;
		account = new Customer( n, getNewNumber( ), u, p, 0.0, "Standard" );
		type = 'C';
		cout << "There! Your account will open just like you just logged on.\nThank you\n" << endl;
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
			cout << "\nUsername: ";
			cin >> username;
			cout << "Password: ";
			cin >> password;
			cout << endl;

			attempt++;
			try {
				account = login( username, password, &type );
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
		if( attempt == 3 )
		{
			cout << "You have exceeded maximum number of login attempts\n"
				<< "Exiting!" << endl;
			return 3;
		}
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
		cout << "I'm sorry something went wrong.\n"
			<< "Your account will stay as it was when this program was openned.\n"
			<< "Please try again at a later time." << endl;
		return 2;
	}

	cout << endl;
	switch( type )
	{
	case 'C':
		delete (Customer*) account;
		break;
	case 'E':
		break;
	case 'M':
		break;
	default:
		delete account;
		break;
	}

	cout << "Thank you!" <<endl;
	return 0;
}
