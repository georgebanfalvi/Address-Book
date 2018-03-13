//  AUTHOR:		George Banfalvi
//
//	DATE:		03/10/18
//
//  DESCRIPTION:
//				This program reads in a comma delimited CSV file (in this case name and phone number address file) and parses
//				it into a double linked list data structure.
//				The following functionality is provided:
//				1. Read Address File - specify your own CSV filename.  The name will be saved in the "default.txt" file.
//				   Subsequent executions of the program will remember the last file you used.
//				2. Display Address Book - this will display all of the contacts from the linked list structure.
//				3. Sort Address Book - displays a sorted list of the linked list strucure.
//				4. Search For Contact - searches for a contact by name.  Names are case INdePenDENt.
//				5. Delete Contact - Deletes a contact from the contact list on the screen.  It asks for and ID confirmation
//				   before doing so and this is how we specify which item to delete for multiple records.
//				6. Write Address File - this serializes (writes out to a filename you specifiy) the address book.
//				7. Exit - exits the program.
//
//	SOURCE FILES:
//				main.cpp - displays the user interface and initiates the high level functionality calls.
//				AddressBookFunctions.cpp - implemets the funtions in the DESCRIPTION section.
//				AddressBookFunctions.h - .h declaration file for AddressBookFunctions.cpp
//				Contact.cpp - linked list data structure definition and operations.
//				Contact.h - .h declaration file for Contact.cpp
//
//	EXECUTABLE and ENVIRONMENT:
//				"Address Book.exe" - Built using Microsoft Visual Studio Community 2017.
//				default.txt - stores the name of the last CSV input file.
//				data[1][1].csv - supplied comma delimited CSV file.
//				README.txt - this header information is in the README file.


#include <iostream>
#include <fstream>
#include <string>
#include "AddressBookFunctions.h"

using namespace std;

int main() {

	ifstream	inFile;
	ifstream	inDefaultFile;
	ofstream	outFile;
	ofstream	outDefaultFile;
	string		inString;
	string		selection;

	string	name;
	string  phone;
	string	inFilename;
	string	outFilename;

	AddressBookFunctions* ptrAddressBookFunctions = new AddressBookFunctions();

	inDefaultFile.open("default.txt");
	if (!inDefaultFile) {
		cout << "default.txt file not found" << endl << endl;
	}
	else {
		getline(inDefaultFile, inString);		// Get name of default input file
		cout << "Using default input file " << inString << endl << endl;
		ptrAddressBookFunctions->ReadAddressFile(inString);
		inDefaultFile.close();
	}


	do
	{
		cout << "Please make a selection" << endl;
		cout << "1. Read Address File" << endl;
		cout << "2. Display Address Book" << endl;
		cout << "3. Sort Address Book" << endl;
		cout << "4. Search For Contact" << endl;
		cout << "5. Delete Contact" << endl;
		cout << "6. Write Address File" << endl;
		cout << "7. Exit" << endl;

		getline(cin, selection);		// Name and Phone labels - 1st line of file.

		if (selection == "1")
		{
			cout << "Read Address File - enter filename" << endl;
			getline(cin, inFilename);
			ptrAddressBookFunctions->ReadAddressFile(inFilename);

			outDefaultFile.open("default.txt");
			outDefaultFile << inFilename << endl;
			outDefaultFile.close();

		}
		else if (selection == "2")
		{
			cout << "Display Address Book" << endl;
			ptrAddressBookFunctions->DisplayAddressBook();
		}
		else if (selection == "3")
		{
			cout << "Sorted Address Book" << endl << endl;
			ptrAddressBookFunctions->DisplaySortedAddressBook();
					}
		else if (selection == "4")
		{
			string name;
			//char* recordname;

			cout << "Search For Contact - please enter name" << endl;
			getline(cin, name);
			ptrAddressBookFunctions->SearchContact(name);
		}
		else if (selection == "5")
		{
			string name;
			cout << "Delete Contact - please enter name" << endl;

			getline(cin, name);
			ptrAddressBookFunctions->DeleteContact(name);
		}
		else if (selection == "6")
		{
//			cout << "Write Address File" << endl;
			cout << "Write Address File - enter filename" << endl;
			getline(cin, outFilename);
			ptrAddressBookFunctions->WriteAddressFile(outFilename);

			outDefaultFile.open("default.txt");
			outDefaultFile << outFilename << endl;
			outDefaultFile.close();

		}
		else if (selection == "7")
		{
			cout << "Exit" << endl;
		}
		else {
			cout << "Invalid command" << endl << endl;
		}


	} while (selection != "7");


	return 0;
}
