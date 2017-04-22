//============================================================================
// Name        : Lab 8
// Author      : Brent Schultz
// Version     :
// Copyright   : Your copyright notice
// Description : Morse Code Generator
//============================================================================

#include <iostream>
#include <string>

#define NUM_LETTERS 26

using namespace std;

string Letters = "abcdefghijklmnopqrstuvwxyz";
string mCode[] = { ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--.." };


class Message { 
	protected: string msg;

	public:
		virtual void printInfo(void);
		// Constructors
		Message();
		Message(string m);
		//Destructor
		~Message();
};

//Empty constructor will ask for an input
Message::Message() { 
	cout << "Enter a message: ";
	cin >> msg;
}

//Takes input from command line if given
Message::Message(string m) {
	msg = m;
}

//Print just the message using the base class...
void Message::printInfo(void) {
	cout << "Original text: " << msg << endl;
	cout << endl;
}

Message::~Message() {
	cout<<"Base class destructor" << endl;
}
	


class morseCodeMessage : public Message {
	private:
		string *translated_msg;
		void translate();
	public:


		// Overrides virtual:
		void printInfo();
		// Constructor
		morseCodeMessage();
		// Destructor
		~morseCodeMessage();
};
//Constructor
morseCodeMessage::morseCodeMessage() {
	translated_msg = new string[msg.length()];
	translate();
}
//Destructor
morseCodeMessage::~morseCodeMessage() {
	delete[] translated_msg;
	cout<< "morseCodeMessage destructor." <<endl;
}

//Translates the input
void morseCodeMessage::translate() {
	for(int i=0; i<msg.length(); i++)
	{
		for(int j=0; j<NUM_LETTERS; j++)
		{
			if(msg[i] == Letters[j])
			{
				translated_msg[i] = mCode[j];
				break;
			}
		}
	}
}
//Prints the original message followed by the translated message		
void morseCodeMessage::printInfo() {
	cout << "Original text: " << msg << endl;
	cout << "Morse code: ";
	for(int i=0; i<msg.length(); i++)
	{
		cout << translated_msg[i];
	}
	cout << endl;
	cout << endl;
}

class messageStack {
	public:
		
		Message *stack[10]; 
		messageStack(Message *);
		int stack_top_index;
		int num_obj;
		//~messageStack();
		void pop();         //LIFO
		void push(Message *); //LIFO
		void printStack();
	private:

};

messageStack::messageStack(Message *m) {
	stack_top_index = 9;
	num_obj = 0;
	push(m);
}

void messageStack::printStack(void) {
//	cout << "Stack top index: " << stack_top_index << endl;
	cout << "-------------------" << endl;
	
	for(int i=stack_top_index; i<10; i++)
	{
//		cout << "Current index: " << i << endl;
		stack[i]->printInfo();
	}
}
		
//LIFO pops off the top of the stack
void messageStack::pop(void) {
	if(num_obj == 0)
	{
		stack_top_index = 9;
		cout << "Stack empty\n";
		return;
	}
	else
	{
		num_obj--;
		(stack_top_index > 9) ? stack_top_index=9 : stack_top_index++;
	}
}

//Pushes the new message to the top of the stack
void messageStack::push(Message *m) {
	if(num_obj == 0)
	{
		stack[stack_top_index] = m;
	}
	else
	{
		if(stack_top_index == 0)
		{
			cout << "Stack full\n"; 
			return;
		}
		stack[--stack_top_index] = m;
	}
	num_obj++;

	}


int main(int argc, char **argv) {

	if(argc > 1) 
	{
		//Print a command line argument to show that the base class works on its own.
		Message m1 = Message(argv[1]);
		m1.printInfo();

	}

	// Ask user for message to translate
	morseCodeMessage m1 = morseCodeMessage();
//	m1.printInfo();
	morseCodeMessage m2 = morseCodeMessage();
	morseCodeMessage m3 = morseCodeMessage();
	Message m4 = Message("new mesage");
	
	cout<<endl;

	messageStack ms1 = messageStack(&m1);
	ms1.push(&m2);
	ms1.push(&m3);
	ms1.push(&m4);

	ms1.printStack();
	
	cout<< "First pop" << endl;
	ms1.pop();
	ms1.printStack();

	cout<< "Second pop" << endl;
	ms1.pop();
	ms1.printStack();

	cout<< "Ending program" << endl;
	return 0;
}
