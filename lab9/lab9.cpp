//============================================================================
// Name        : Lab 9
// Author      : Brent Schultz
// Version     :
// Copyright   : Your copyright notice
// Description : Morse Code Generator and LED outputter?
//============================================================================


#include <iostream>
#include <string>
#include <stdlib.h>
#include <sys/mman.h>
#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

using namespace std;


#define NUM_LETTERS 52

string Letters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
string mCode[] = {
		".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---",
		"-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-", "..-", "...-",
		".--", "-..-", "-.--", "--..",
		".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---",
		"-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-", "..-", "...-",
		".--", "-..-", "-.--", "--.."
};

//Using the classes already defined in Lab 8

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
	getline(cin, msg);
}

//Takes input from command line if given
Message::Message(string m) {
	msg = m;
}

// Print just the message using the base class...
void Message::printInfo(void) {
	cout << "Original text: " << msg << endl;
	cout << endl;
}

//Base class destructor
Message::~Message() {
}

class morseCodeMessage : public Message {
	protected:
		string *translated_msg;
		void translate();
	public:
		// Override virtual printinfo:
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
			else{
				translated_msg[i] = ' ';
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

class morseCodeLED : public morseCodeMessage {
	private:
		int fd;
		unsigned long *baseptr;
		// Data register, data-direction register
		unsigned long *PBDR,*PBDDR;
		void config(void);
	public:
		// Override virtual
		void printInfo(void);
		//Constructor
		morseCodeLED();


};

//Configure pointers based on template
void morseCodeLED::config(void) {
	fd = open("/dev/mem", O_RDWR|O_SYNC);	// open the special file /dem/mem
	if(fd == -1){
		printf("\n error\n");
		exit(-1);  // failed open
	}

	baseptr = (unsigned long*)mmap(NULL,4096,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0x80840000);
	if(baseptr == MAP_FAILED){
		printf("\nError: Unable to map memory space \n");
		exit(-2);
	}  // failed mmap
	close(fd); // close the special file

	// To access other registers in the page, we need to offset the base pointer to reach the
	// corresponding addresses. Those can be found in the board's manual.
	PBDR = baseptr + 1;	// Address of port B DR is 0x80840004
	PBDDR = baseptr + 5;	// Address of port B DDR is 0x80840014

	*PBDDR &= 0xFFFFFFFE;	// configures port B0 as input (first push button). You could use: &= ~0x01
	// Set B5-B7 as output
	*PBDDR |= 0xE0;
	// Turn all off
	*PBDR &= 0x00;
}

//Reprints the original message as well as the translated message and calls config
morseCodeLED::morseCodeLED() {

	cout << "Original text: " << msg << endl;
	cout << "Morse code: ";
	for(int i=0; i<msg.length(); i++)
	{
		cout << translated_msg[i];
	}
	cout << endl;
	config();
}

//Activates the corresponding led lights
void morseCodeLED::printInfo(void) {

	for(int i=0; i<msg.length(); i++)
	{
		string transmsg = translated_msg[i];

		for(int j=0; j<transmsg.length(); j++)
		{
			sleep(1);
			char c = transmsg[j];
			if(c == '.')
			{
				// Turn on red
				*PBDR |= 0x20;
				cout << "Red." << endl;
				sleep(1);
				// Turn off red
				*PBDR &= ~0x20;
			}
			else if(c == '-')
			{
				// Turn on yellow
				*PBDR |= 0x40;
				cout << "Yellow." << endl;
				sleep(1);
				// Turn off yellow
				*PBDR &= ~0x40;
			}
			else if(c == ' ')
			{
				//  Turn on green
				*PBDR |= 0x80;
				cout << "Green." << endl;
				sleep(1);
				// Turn off green
				*PBDR &= ~0x80;
			}
			else
			{
				cout << "ERROR IN TRANSLATION OR INPUT" << endl;
			}
		}
		sleep(1);
	}
	// Green LED to signify the end of the word
	*PBDR |= 0x80;
	cout << "Green." << endl;

	sleep(1);

	// All LED off
	*PBDR &= 0x00;
}


int main(int argc, char **argv) {

	//Main function simply gets message from the user and calls the necessary functions
	//to display the message on the led board
	//if will also print each color in the terminal while its displayed on the leds

	morseCodeLED msg1 = morseCodeLED();
	msg1.printInfo();


	return 0;
}
