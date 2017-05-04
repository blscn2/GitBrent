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


//Prototypes
int getNewNumber( );

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
		string getName( ) { return name; }
		string getAccountNum( ) { return to_string( accountnumber ); }
		string getUser( ) { return username; }
		string getPass( ) { return password; }
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
		void DeleteAcct();

		~Customer();

};

class Employee: public Person {

	public:
		void printInfo( );
		virtual void Options( );
		void openPayRoll( );
		void controlAccounts( );
		void viewStats( );
		Employee( string, int, string, string );
};

class Loan {

	private:
		double balance;
		double rate;
		Customer* client;
	public:
		void display( );
		void interest( );
		void paySome( double amount );
		bool isIssuedTo( string );
		string save( );
		Loan( string, double, double );
		~Loan( );
};

class Manager: public Employee {
	private:
		vector<Loan> investments;
		vector<Employee> staff;
	public:
		void Options( );
		void controlStaff( );
		void investClient( );
		void createPayRoll( );
		Manager( string, int, string, string ) throw(char);
		~Manager( );
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
		if ( amount > balance + 100){
				cout << "This withdrawal will result in outstanding negative balance.\nCancelling the withdrawal" << endl;
				return;
		}	
		cout << "Withdrawal of this size will result in negative balance. \nDo you still wish to withdraw this amount?" << endl;
		cout << "1) Yes\n2) No\nTHIS WILL RESULT IN A $30 OVERDRAW FEE!!!" << endl;
		cin >> yon;
		if (yon == 1){
			balance -= 30; //overdraft fee
		}
		else if (yon == 2){
			cout << "Cancelling withdrawal. Your balance is still $" << balance << endl;
			return;
		}
		else{
			cout << "Invalid choice. Cancelling withdrawal." << endl; //too many invalid attempts
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
			<< "3) Close the account\n"
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
		DeleteAcct();
		} else if (accntclose == 2){
			cout << "Account will not be closed. Returning to menu." << endl;
		} else {
			cout << "Invalid choice. Try again (one attempt remaining)." << endl;
			cout << "Are you sure you wish to delete the account?\nType:\n1 for yes\n2 for no."<< endl;
					cin >> accntclose;
					if (accntclose == 1 ){
						DeleteAcct();
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
// Delete account keeps data but removes accessiblily from customer.
void Customer::DeleteAcct(){
		
	cout << "All account information will be deleted from the system and current balance paid out." << endl;
		
	fstream userFile( "accounts\\" + username + ".txt", fstream::trunc | fstream::out );
	username = "NULL";
	password = "NULL";
	balance = 0;
	
	userFile << username << " " << password << " C" << endl;
	userFile << name << "\n" << accountnumber << endl;
	userFile << accounttype << " " << balance << endl;
	
	userFile.close( );
}	

Employee::Employee( string n, int an, string u, string p ): Person( n, an, u, p )
{

}

void Employee::printInfo( )
{
	cout << "STUFF PRINT INFO" << endl;
	return;
}

void Employee::Options( )
{
	cout << "EMPLOYEE OPTIONS" << endl;
	return;
}

void Employee::controlAccounts()
{
	cout << "CONTROL ACCOUNTS" << endl;
	return;
}

void Employee::viewStats()
{
	cout << "VIEW STATS" << endl;
	return;
}

	
void Employee::openPayRoll( ) {
	fstream in( "payroll.txt", fstream::in );
	string u;
	string schedule;
	while( !in.eof( ) && !( username == u ) )
	{
		getline( in, u );
		getline( in, schedule );
	}
	if( in.eof( ) )
	{
		cout << "You are not within this system\n" << endl;
		return;
	}
	cout << "You are scheduled to work:" << endl;
	int j;
	for( j = 0; j < schedule.size( ); j++ )
	{
		switch( schedule.at( j ) - 48 )
		{
			case 1:
				cout << "Monday in the ";
				break;
			case 2:
				cout << "Tuesday in the ";
				break;
			case 3:
				cout << "Wednesday in the ";
				break;
			case 4:
				cout << "Thursday in the ";
				break;
			case 5:
				cout << "Friday in the ";
				break;
			case 6:
				cout << "Saturday in the ";
				break;
			case 7:
				cout << "Sunday in the ";
				break;
		}
		while( isspace( schedule.at( j ) ) )
			j++;

		if			( schedule.at( j ) == 'a' )
			cout <<"morning." << endl;
		else
			cout <<"afternoon." << endl;
	}
	
}

//========= Manager functions ================
void Manager::Options( )
{
	string choice;

	do {
		cout << "What do you want to do?\n"
			<< "1) Control client accounts\n"
			<< "2) View bank statistics\n"
			<< "3) Manage employees\n"
			<< "4) Manage Loans\n"
			<< "5) Create payroll/schedule\n"
			<< "6) Exit" << endl;
		cin >> choice;
		try {
			if( choice.length( ) > 1 )
				throw "I'm sorry. That is not an option.\nPlease choose again\n";
			if( choice.at( 0 ) < '1' || choice.at( 0 ) > '6' )
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
			controlAccounts( );
			break;
		case '2':
			viewStats( );
			break;
		case '3':
			controlStaff( );
			break;
		case '4':
			investClient( );
			break;
		case '5':
			createPayRoll( );
			break;
		case '6':
			cout << "Returning to main menu\n" << endl;
			break;
		default:
			throw "Something went wrong. Exiting!";
	}

}
void Manager::controlStaff( )
{
	string choice;
	do {
		cout << "What would you like to do?\n"
			<< "a) Add a new employee\n"
			<< "b) Remove an employee from the system\n" << endl;
		cin >> choice;
//		try {
//			if( choice.size( ) > 1 )
//				cerr << "Only the first character is being looked at";
//			if( choice.at(0) < 'a' || choice.at(0) > 'b' )
//				throw "That is not an option\nPlease choose again";
//		}
//		catch( const char* s )
//		{
//			cout << s << endl;
//			continue;
//		}
		break;
	} while( true );

	switch( choice.at( 0 ) )
	{
		case 'a': {
			string n;
			string u;
			cout << "What is the name?" << endl;
			cin >> ws;
			getline( cin, n );
			fstream in;
			do {
				in.close( );
				cout << "\nWhat is the username?" << endl;
				cin >> u;
				in.open( "accounts/" + u + ".txt", fstream::in );
				if( in.is_open( ) ) //if the username is taken, choose a different one
					cout << "I'm sorry. That username has already been taken." << endl;
			} while( in.is_open( ) );
			in.close( );
			cout << "Default password set as 12345\n"
				<< "This can be changed on first login" << endl;
			staff.push_back( Employee( n, getNewNumber( ), u, "12345" ) );
			break;
		}
		case 'b': {
			int i, num;
			do {
				
				for( i = 0; i < staff.size( ); i++ )
				{
					cout << to_string(i+1)<< ") "<<staff.at( i ).getName( ) << endl;
				}
				cout << to_string( staff.size( ) ) << ") Return to previous screen." << endl;
				cin >> choice;
				try {
					num = atoi( choice.c_str( ) );
					if( num < 1 || num > staff.size( )+1 )
						throw "That is not an option. Please choose again.";
				}
				catch( const char* s)
				{
					cerr << s << endl;
					continue;
				}
				break;
			} while( true );
			break;
			fstream out( "accounts/" + staff.at( num ).getUser( ) + ".txt", fstream::trunc | fstream::out );
			out << staff.at( i ).getUser( ) << " NULL E" << endl;
			out << staff.at( i ).getName( ) << endl;
			out << staff.at( i ).getAccountNum( ) << endl;
			out.close( );
			staff.erase(staff.begin()+ (num-1) );
			cout << "Employee removed\n" << endl;
		}
		default:
			cerr << "Something went very wrong\n" << endl;
			throw 'A';
			break;
	}
	return;

}
void Manager::investClient( )
{
	string choice;
	do {
		try {
			cout << "" << endl;
			cin >> choice;
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
		case '1': {
			string u;
			double amount, r;
			cout << "Enter the username of the client" << endl;
			cin >> u;
			cout << "Enter the amount loaned" << endl;
			cin >> amount;
			cout << "Enter the rate at which it is loaned" << endl;
			cin >> r;
			investments.push_back( Loan( u, amount, r ) );
			cout << "Loan issued\n" << endl;
			break;
		}
		case '2': {
			int i;
			for( i = 0; i < investments.size( ); i++ )
				investments.at( i ).interest( );
			cout << "All investments updated\n" << endl;
			break;
		}
		case '3': {
			int amount, i;
			string u;
			do {
				cout << "Enter the username of the client" << endl;
				cin >> u;
				while( i < investments.size( ) && !investments.at( i ).isIssuedTo( u ) )
					i++;
				try {
					if( i == investments.size( ) )
						throw "That is not a client with a loan out.";
				}
				catch( const char* s )
				{
					cout << s << endl;
					continue;
				}
				break;
			} while( true );
			do {
				cout << "Enter the amount being paid off\n";
				investments.at( i ).display( );
				cout << endl;
				cin >> amount;
				try {
					if( amount <= 0 )
						throw "Invalid amount. Please enter another";
				}
				catch( const char* s )
				{
					cout << s << endl;
					continue;
				}
				break;
			} while( true );

			investments.at( i ).paySome( amount );
			break;
		}
		default:
			break;
	}
	
}
void Manager::createPayRoll( )
{
	int* placed = new int[ 14 ];
	string choice;
	cout << "This system works by going through each employee and\n"
		<< "placing them into the defined schedule\n"
		<< "The number of hours determine pay\n"<< endl;
	cout << "Enter days of the week as numbers starting with monday at 1\n"
		<< "and place an a or p next to it to determine am or pm work\n" << endl;
	int i;
	int j;
	fstream out( "payroll.txt", fstream::trunc | fstream::out );
	for( i = 0; i < staff.size( ); i++ )
	{
		do {
			try {
				cout << "Current placings have a layout of: " << endl;
				cout << "\tM\tT\tW\tTh\tF\tS\tS\nAM:\t";
				for( j = 0; j < 14; j++ )
				{
					cout << placed[ j ] << "\t";
					if( j == 7 )
					{
						cout << endl << "PM\t";
					}
				}
				cout << endl;
				cout << "Now scheduling: " << staff.at( i ).getName( ) << endl;
				getline( cin, choice );
				for( j = 0; j < choice.size( ); j++ )
				{
					if( choice.at( j ) < '1' || choice.at( j ) > '7' )
						throw "That is an invalid scheduling\nPlease try again\n";
					int num = choice.at( j ) - 48;
					while( isspace( choice.at( j ) ) )
						   j++;
					if( choice.at( j ) != 'a' && choice.at( j ) != 'p' )
						throw "That is an invalid scheduling\nPlease try again\n";
					if( choice.at( j ) == 'a' )
						placed[ num ]++;
					else
						placed[ num + 7 ]++;
				}
				out << staff.at( i ).getUser( ) << endl;
				out << choice << endl;
			}
			catch( const char* s )
			{
				cout << s << endl;
				continue;
			}
			break;
		} while( true );
	}
	out.close( );
}
Manager::Manager( string n, int an, string u, string p ) throw(char): Employee( n, an, u, p )
{
	fstream in( "Employees.txt", fstream::in );
	if( !in.is_open( ) )
		throw 'A';

	int num;
	in >> num;

	int i;
	fstream employIn;
	string user, pass, name;
	char t;
	int account;

	for( i = 0; i < num; i++ )
	{
		in >> user;
		employIn.open( "accounts/" + user + ".txt", fstream::in );
		employIn >> user >> pass >> t >> ws;
		getline( employIn, name );
		in >> account;
		staff.push_back( Employee( name, account, user, pass ) );
		employIn.close( );
	}
	in.close( );

	i = 0;
	in.open( "loans/" + to_string(i) + ".txt", fstream::in );
	while( in.is_open( ) )
	{
		double b, r;
		string user;
		in >> user >> b >> r;
		investments.push_back( Loan( user, b, r ) );

		in.close( );
		i++;
		in.open( "loans/" + to_string(i) + ".txt" , fstream::in);
	}
	in.close( );
}
Manager::~Manager( )
{
	fstream out( "Employees.txt", fstream::trunc | fstream::out );

	out << staff.size( ) << endl;
	
	int i;
	fstream employOut;

	for( i = 0; i < staff.size( ); i++ )
	{
		out << staff.at( i ).getUser() << endl;
		employOut.open( "accounts/" + staff.at(i).getUser() + ".txt", fstream::trunc | fstream::out );
		employOut << staff.at( i ).getUser() << " " << staff.at( i ).getPass() << " E" << endl;
		employOut << staff.at( i ).getName() << endl;
		employOut << staff.at(i).getAccountNum() << endl;
		employOut.close( );
	}
	out.close( );

	for( i = 0; i < investments.size( ); i++ )
	{
		out.open( "loans/" + to_string( i ) + ".txt", fstream::trunc | fstream::out );
		out << investments.at( i ).save() << endl;
		out.close( );
	}
}


//=================== Loan functions ======================
void Loan::display( )
{
	client ->printInfo( );
	cout << "currently has a loan out for\n"
		<< balance << " at a rate of " << rate << endl << endl;
}
void Loan::interest( )
{
	balance *= ( 1 + rate );
}
void Loan::paySome( double amount )
{
	balance -= amount;
}
bool Loan::isIssuedTo( string u )
{
	return ( client->getUser( ) == u );
}
string Loan::save( )
{
	string one(client->getUser() +" " + to_string(balance) + " " + to_string(rate) );
	return one;
}
Loan::Loan( string u, double b, double r )
{
	fstream in( "accounts/" + u + ".txt" );
	if( !in.is_open( ) )
		throw 'C';

	string p, n, type;
	double bal;
	char t;
	int a;
	in >> u >> p >> t >>ws;
	getline( in, n );
	in >> a >> type >> b;

	in.close( );
	client = new Customer( n, a, u, p, bal,type );
	balance = b;
	rate = r;
}

Loan::~Loan( )
{
	delete client;
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
			return new Employee( name, accountnumber, username, password );
			break;
		case 'M':
			return new Manager( name, accountnumber, username, password );
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

	cout << "Welcome to Mizzou Bank!"<<endl;
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
			if( choice.at(0) < '1' || choice.at(0) > '4' )
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
				continue; // This will cause the program to loop again.
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
		delete (Employee*) account;
		break;
	case 'M':
		delete (Manager*) account;
		break;
	default:
		delete account;
		break;
	}

	cout << "Thank you!" <<endl;
	return 0;
}
