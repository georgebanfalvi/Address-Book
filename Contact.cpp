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


#include "Contact.h"

int Contact::m_totalNumberOfRecords = 0;
Contact* Contact::m_ptrFirstContact = 0;
Contact* Contact::m_ptrLastContact = 0;
int Contact::m_nextAvailRecordID = 1;



Contact::Contact()
{
}
Contact::Contact(string name, string phone)
{
	m_name = name;
	m_phone = phone;
	m_recordID = m_nextAvailRecordID++;

}


Contact::~Contact()
{
}

int Contact::SetName(char *name) {
	m_name = name;
	return 0;
}
string Contact::GetName() {

	return(m_name);
}
string Contact::GetPhone() {

	return(m_phone);
}
int Contact::SetPhone(char *phone) {
	m_phone = phone;
	return 0;
}

int Contact::SetNextContact(Contact *ptrNextContact) {
	m_ptrNextContact = ptrNextContact;
	return 0;

}

Contact* Contact::GetNextContact() {
	return (m_ptrNextContact);
}


int Contact::SetPrevContact(Contact *ptrPrevContact) {
	m_ptrPrevContact = ptrPrevContact;
	return 0;

}

Contact* Contact::GetPrevContact() {
	return (m_ptrPrevContact);
}


int Contact::GetRecordID() {
	return m_recordID;
}


int Contact::AddRecord(Contact* ptrContact) {		// Add record to linked list
// Add the record to the end of the linked list

	if (m_ptrFirstContact == 0) {					// No records in list
		m_ptrFirstContact = ptrContact;
		m_ptrLastContact = ptrContact;
		m_ptrPrevContact = 0;
		m_ptrNextContact = 0;
	}
	else											// Add record to end of list
	{
		m_ptrLastContact->m_ptrNextContact = ptrContact;
		ptrContact->m_ptrPrevContact = m_ptrLastContact;
		ptrContact->m_ptrNextContact = 0;
		m_ptrLastContact = ptrContact;
	}

	m_totalNumberOfRecords++;
	return m_totalNumberOfRecords;
}

int Contact::DeleteRecord(Contact* ptrContact) {

	//  Sanity check
	if (ptrContact == 0) {
		return 1;
	}

	//	This is the only record in the Address Book
	if (m_ptrFirstContact == m_ptrLastContact) {
		delete ptrContact;
		m_totalNumberOfRecords--;
		m_ptrFirstContact = 0;
		m_ptrLastContact = 0;
		return 0;
	}


	//  This is the 1st record in the Address Book
	if (ptrContact == m_ptrFirstContact) {
		m_ptrFirstContact = ptrContact->GetNextContact();
		m_ptrFirstContact->SetPrevContact(0);
		delete ptrContact;
		m_totalNumberOfRecords--;
		return 0;
	}

	//  This is the last record in the Address Book
	if (ptrContact == m_ptrLastContact) {
		m_ptrLastContact = ptrContact->GetPrevContact();
		m_ptrLastContact->SetNextContact(0);
		delete ptrContact;
		m_totalNumberOfRecords--;
		return 0;
	}

	//  This record is in the middle of the Address Book
	if (m_ptrFirstContact != m_ptrLastContact) {
		Contact* leftContact;
		Contact* rightContact;
		leftContact = ptrContact->GetPrevContact();
		rightContact = ptrContact->GetNextContact();
		leftContact->SetNextContact(rightContact);
		rightContact->SetPrevContact(leftContact);
		delete ptrContact;
		m_totalNumberOfRecords--;
		return 0;
	}

	return 0;

}

int Contact::GetNumberOfRecords() {
	return m_totalNumberOfRecords;
}

int Contact::SetMarkedForDeletion(int state) {
	
	m_markedForDeletion = state;

	return 0;
}

int Contact::GetMarkedForDeletion() {

	return m_markedForDeletion;

	return 0;
}

Contact* Contact::GetRecordByIndex(int index) {
	Contact* ptrContact;

	ptrContact = m_ptrFirstContact;
	for (int i = 0; i < index; i++)
	{
		ptrContact = ptrContact->GetNextContact();
	}
	
	return ptrContact;
}

int Contact::GetIndexByRecord(Contact* ptrContact) {
	Contact* tempPtr;
	int index = 0;

	tempPtr = m_ptrFirstContact;
	while (tempPtr != 0) {
		if (tempPtr == ptrContact) {
			return index;
		}
		tempPtr = tempPtr->GetNextContact();
		index++;
	}
	
	return -1;			// No index was found
}


Contact* Contact::GetFirstContact() {
	return m_ptrFirstContact;
}

Contact* Contact::GetLastContact() {
	return m_ptrLastContact;
}


