//============================================================================
// Name        : lab8.cpp
// Author      : Brent Schultz
// Version     :
// Copyright   : Your copyright notice
// Description : Lab 8 Morse Code Generator
//============================================================================

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
using namespace std;

// string letters = "abcd...z";
// morsecode[] = {".-","-...",...};       DELETE THESE
// int index = letters.find('c')
// int l = letters.length();
// isupper()/tolower()

// Message Class
class Message {
	// protected members that can be accessed by derived classes
	protected:
		string msg;
		string transformed;
	// public members and methods
	public:
		Message();				//default constructor
		Message(string);		//given the message
		virtual ~Message();		//destructor
		// virtual print_msg() method
		virtual void print_msg();
};

// Message constructor with string parameter
Message::Message(string message){
	msg = message;
}
// Message constructor with no parameters
Message::Message(){
	cout << "Enter message: ";
	cin >> msg;
}
// Redefined print_msg()
void Message::print_msg(){
	cout << "\n__ Inside Message Print ___________" << endl;
	cout << "\tThe message is: " << msg << endl;
	cout << "___________________________________\n";
}

Message::~Message(){
	cout << "Goodbye Message" << endl;

}

// MoreCodeMessage class
class MorseCodeMessage : public Message{
	// no private members
	private:
	// public members and methods
	public:
		void translate();
		void print_msg();
		MorseCodeMessage(string m);
		MorseCodeMessage();
		~MorseCodeMessage();
};

// MorseCodeMessage constructor when no message is given
MorseCodeMessage::MorseCodeMessage() : Message(){
	// If no message is given
	// This is needed so that if a MoreCodeMessage is created, the base class is called
}

// MorseCodeMessage constructor when a message is given
MorseCodeMessage::MorseCodeMessage(string m) : Message(m){
	// If a message is given
	// This is needed so that if a MoreCodeMessage is created, the base class is called
}

MorseCodeMessage::~MorseCodeMessage(){
	cout << "Goodbye MorseCodeMessage" << endl;
}


// Converts the input message to morse code and stores it in the transformed
// member of the Message class protected
void MorseCodeMessage::translate(){
	int i;
	string letters = "abcdefghijklmnopqrstuvwxyz";
	string morseCode[26] = {".-","-...","-.-.","-..",".","..-.","--.","....","..",".---","-.-",".-..","--","-.","---",".--.","--.-",".-.","...","-","..-","...-",".--","-..-","-.--","--.."};
	// Goes through the message converting each character to morse code
	for(i=0;i<msg.length();i++){
		int index = letters.find(tolower(msg[i]));		// converts to lowercase is uppercase and then finds that character in letters
		transformed = transformed + morseCode[index];	// adds on each character based on the index from the letters
		transformed = transformed + "#";				// adds a seperator between each character
		//cout << morseCode[index] << endl;
	}
	transformed = transformed+'$'; // tacks on an "end of string" character
}

// Redefined print_msg() for the MoreCodeMessage class
void MorseCodeMessage::print_msg(){
	cout << "\n__ Inside MorseCodeMessage Print ______" << endl;
	cout << "\tMessage: " << msg << endl;
	cout << "\tMorse Code: ";
	int i = 0;
	// Goes through the transformed message looking for spaces (#) or
	// the end of string ($) while printing each morse code character
	for(i=0;i<transformed.length();i++){
		if(transformed[i] == '$'){ 			// if end of string
			break;
		}else if(transformed[i] == '#'){	// if "space"
			cout << "  ";
		}else{
			cout << transformed[i];			// print out morse code value
		}
	}
	cout << "\n_______________________________________\n";

}

// messageStack class
class messageStack{
	public:
		messageStack();
		~messageStack();
		void push(Message *obj);
		void pop();
		void print_stack();
		Message *stackptr[10];
};

// constructor messageStack
messageStack::messageStack(){
	int i;
	// initializes each steachptr pointer to NULL
	for(i=0;i<10;i++){
		stackptr[i] = NULL;
	}
}

// message stack destructor
messageStack::~messageStack(){
	cout << "Goodbye messageStack" << endl;
}

// method to push a Message object onto the stack
// takes in an object pointer to allow for dynamic binding
void messageStack::push(Message *obj){
	int i;
	// start at the bottom of the stack and look for the top of the stack to add the new object too
	for(i=9;i>=0;i--){				// reverse order for lifo
		if(stackptr[i] == NULL){	// if stackptr location is empty, otherwise move to the next location
			stackptr[i] = obj;
			return;
		}
	}
	cout << "\nThe stack is full, cannot push anything else\n" << endl;
}

void messageStack::pop(){
	int i;

	// start at the top of the stack and look for a not NULL location
	for(i=0;i<10;i++){
		if(stackptr[i] != NULL){
			stackptr[i] = NULL;
			return;
		}
	}
	cout << "\nThe stack is empty\n" << endl;
	// Notice the object that is being popped does not need to be
	// freed because it was never directly allocated memory by me,
	// so it it still handled
}

// print_stack to print each object in the stack
void messageStack::print_stack(){
	int i;
	cout << "\n########## Printing the stack... ##########" << endl;
	for(i=0;i<10;i++){
		if(stackptr[i] != NULL){
			stackptr[i]->print_msg();		// calls each objects respective print_msg()
		}
	}
	cout << "\n###########################################" << endl;
}

int main(void){

	messageStack st = messageStack();		// form the stack

	Message m1("Bottom"), m2, m3;			// create some Message objects
	st.push(&m1);							// push these message objects to the stack
	st.push(&m2);
	st.push(&m3);

	MorseCodeMessage c1,c2,c3("Top");		// create some MorseCodeMessage objects
	c1.translate();							// translate these objects to Morse Code
	c2.translate();
	c3.translate();

	st.push(&c1);							// push these MorseCodeMessage objects to the stack
	st.push(&c2);
	st.push(&c3);
	st.print_stack();						// print out the stack
	st.pop();								// pop from the stack
	st.print_stack();						// print out the stack

	return 0;
}
