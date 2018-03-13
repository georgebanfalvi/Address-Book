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


#pragma once
#include <string>

using namespace std;

class Contact
{
public:
	Contact();
	Contact(string name, string phone);
	virtual ~Contact();

	int SetName(char *name);
	string GetName();
	int SetPhone(char *phone);
	string GetPhone();
	int GetRecordID();
	int SetMarkedForDeletion(int state);	// 0=not marked for deletion
	int GetMarkedForDeletion();
	int SetNextContact(Contact *ptrNextContact);
	Contact* GetNextContact();
	int SetPrevContact(Contact *ptrPrevContact);
	Contact* GetPrevContact();
	int AddRecord(Contact* ptrContact);
	int DeleteRecord(Contact* ptrContact);
	Contact* GetRecordByIndex(int index);		// Returns a record by its 0-based index
	int GetIndexByRecord(Contact* ptrContact);  // Returns a 0-based index of the record
	static int GetNumberOfRecords();
	static Contact* GetFirstContact();
	static Contact* GetLastContact();


private:
	string m_name;
	string m_phone;
	int m_recordID;
	int m_markedForDeletion;
	Contact* m_ptrNextContact = 0;
	Contact* m_ptrPrevContact = 0;

	static int m_totalNumberOfRecords;
	static Contact* m_ptrFirstContact;
	static Contact* m_ptrLastContact;
	static int m_nextAvailRecordID;
	


};

