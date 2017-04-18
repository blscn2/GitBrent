//===========================================================================
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
using namespace std;


class Customer{
	private:

	public:
}

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
		// Present login screen and track attempts
		unsigned short attempt = 0;
		string username = "", password = "";
		Customer account;
		while(attempt < 3 && account.isOpen())
		{
			cout << "Username: ";
			cin >> username;
			cout << "Password: ";
			cin >> password;
			
			i++;
			account = login(username,password);
		}
		break;
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
