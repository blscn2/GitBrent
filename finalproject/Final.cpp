//============================================================================
// Name        : Project
// Author      : Brent Schultz, Shayne Wadle
// Version     :
// Copyright   : Your copyright notice
// Description : Final Project     
//============================================================================

// COMPILE USING: g++ Final.cpp -std=c++11 //

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
/* ABC for the different people that use this system*/
class Person {
	protected:
		string name; // = "John Doe"
		int accountnumber; // = 123456;
		string username; // = "JDoe12"
		string password; // = "Doe#12Donut"

	public:
		virtual void printInfo( void ) = 0;
		virtual void Options( ) = 0;
		Person( );
		Person( string , int, string, string);
		~Person( );
};

/*The customers of the bank are through this class
	It inherits off of the ABC Person class
	The printInfo and Options are unique to the class
	Those options are also set out as functions of the class.*/
class Customer: public Person {
	private:
		double balance; // = 356.25;
		string accounttype; // = "Standard or student or loyal";

	public:
		//Used in the functions as an input variable.
		double amount;

		Customer( string, int, string, string, double, string );

		void printInfo(void);
		void Withdrawal();
		void Deposit();
		void Invest();
		void Options();
		void DeleteAcct(string);

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

/*	Does nothing as nothing is dynamically allocated*/
Person::~Person( )
{

}

/*	Parametric constructor for all the variables of this class.
	It loads some through the ABC constructor.
*/
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
	cout << "Account type: " << accounttype <<"\n"<< endl;
}

/*	Save the current account information into the
	file designated by the username in the accounts folder.
	This overwrites the file if it exists. */
Customer::~Customer(){
	fstream userFile( "accounts\\" + username + ".txt", fstream::trunc | fstream::out );

	userFile << username << " " << password << " C" << endl;
	userFile << name << "\n" << accountnumber << endl;
	userFile << accounttype << " " << balance << endl;

	userFile.close( );
	cout << "Account closed." << endl;
}
// Allows customer to withdraw from account
void Customer::Withdrawal(){
	cout << "Current account balance: $" << balance << endl << "How much would you like to withdraw?" << endl;
	cin >> amount;
	int yon;
	if( amount > balance ) {
		cout << "Withdrawal of this size will result in negative balance. \nDo you still wish to withdraw this amount?" << endl;
		cout << "Type 1 for yes or 2 for no.\nTHIS WILL RESULT IN A $30 OVERDRAW FEE!!!" << endl;
		cin >> yon;
		if (yon == 1){
			balance -= 30;
		}
		else if (yon == 2){
			cout << "Cancelling withdrawal. Your balance is still $" << balance << endl;
			return;
		}
		else{
			cout << "Invalid choice. Cancelling withdrawal." << endl;
			return;
		}
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
		return;
	}
	balance += amount;
	cout << "Your new balance is: $" << balance << endl;
}
// Option menu accessible by the customer
void Customer::Options(){
	string choice;

	int contin = 1;
	
	while ( contin == 1){
	
	do {
		cout << "What do you want to do?\n"

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
		cout << "Are you sure you wish to delete the account?\n1) Yes\n2) No"<< endl;
		cin >> accntclose;
		if (accntclose == 1 ){
		DeleteAcct(username);
		} else if (accntclose == 2){
			cout << "Account will not be closed. Returning to menu." << endl;
		} else {
			cout << "Invalid choice. Try again (one attempt remaining)." << endl;
			cout << "Are you sure you wish to delete the account?\nType:\n1 for yes\n2 for no."<< endl;
					cin >> accntclose;
					if (accntclose == 1 ){
						DeleteAcct(username);
					} else if (accntclose == 2){
						cout << "Account will not be closed. Returning to menu." << endl;
						break;
					} else {
						cout << "Invalid choice. Account will not be deleted." << endl;
					}
		}
		return;
		break;
	case '4':
		cout << "Exiting options." << endl;
		return;
		break;
	default:
		throw "Something went wrong. Exiting!";
	}
	
	cout << "Would you like the continue or exit\n"
		<< "1) Continue\n"
		<< "2) Exit\n" << endl;
	cin >> contin;
	}
}

void Customer::DeleteAcct(string username){
		
		cout << "All account information will be deleted from the system and current balance paid out." << endl;
		cout << "Will remove " << username << ".txt file" << endl;
		
		username = "NULL";
}	

//============================ Other functions ===============================
/*	Global funciton
	Opens fills and checks the information to validate the correct user is there
	Returns the proper dynamically bound class for each type of person*/
Person* login( string user, string pass, char* t ) throw(char)
{
	fstream in( "accounts/" + user + ".txt", fstream::in );

	if( !in.is_open( ) )
		throw 'A';
	
	string username; //Username
	string password; //Password
	char type; //the kind of person they are.

	in >> username >> password >> type;
	if( username != user ) // Username is not correct. (Account is deleted)
		throw 'A';
	if( password != pass ) // Password does not match username given.
		throw 'A';
	in >> ws;
	string name;
	int accountnumber;
	getline( in, name );
	in >> accountnumber;
	
	//Load in that user through the proper class
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

/*	Global function
	Opens AccountNums.txt and loads them all in.
	Then generates a random number and checks if it is a repeat
	repeats process until it finds a new number. */
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
	in.open( "AccountNums.txt", fstream::app );

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

			// Check for bad input
			if( choice.length() > 1 )
				throw "I'm sorry. That is not an option\nPlease choose again.\n";
			if( choice.at(0) < '1' || choice.at(0) > '3' )
				throw "I'm sorry. That is not an option.\nPlease choose again\n";		
		}
		catch(const char* s)
		{
			cout << s << endl;
			continue; // if there was bad input this will cause the program to loop again.
		}
		break; // if there was NOT bad input this will cause the pogram to move on
	// loop if there was bad input
	} while( true );
	

	Person* account;
	char type;
	//Branch based on menu choice.
	switch(choice.at(0))
	{
	case '1':
	{	// Present New account screen and get the information.
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
			if( in.is_open( ) ) //if the username is taken, choose a different one
				cout << "I'm sorry. That username has already been taken." << endl;
		} while( in.is_open( ) );
		in.close( );
		do {
			cout << "\nWhat do you want your password to be?" << endl;
			cin >> p;
			cout << "\nPlease type that again to make sure we have that right." << endl;
			cin >> p2;
			try {
				if( p != p2 ) // if the passwords do not match input again.
					throw "Those do not match please try again.";
			}
			catch( const char* s )
			{
				cout << s << endl;
				continue; // This will cause the pogram to loop again.
			}
			break; // This causes the program to move on.
		} while( true );

		// Initalize the account.
		cout << "\nAlright just one moment while we initialize your account" << endl;
		account = new Customer( n, getNewNumber( ), u, p, 00.0, "Standard" );
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
			catch( char s )//If bad inputs, try again.
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
		} while( attempt < 3); // If exceeded attempts exit.
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
	
	// Display the account information.
	account->printInfo( );

	//Then display the options and handle that input there.
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

	//End with deleting the accounts properly.  This also saves them.
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
