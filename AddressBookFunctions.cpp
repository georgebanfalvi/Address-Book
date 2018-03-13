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



AddressBookFunctions::AddressBookFunctions()
{
}


AddressBookFunctions::~AddressBookFunctions()
{
	int numberOfRecords;
	static Contact*	staticFirstContactRecord;
	Contact* firstContactRecord;
	Contact* currentRecord;
	Contact* tempRecord;

	numberOfRecords = Contact::GetNumberOfRecords();

	if (numberOfRecords != 0) {

		staticFirstContactRecord = Contact::GetFirstContact();

		// Convert static class pointer to object pointer
		firstContactRecord = dynamic_cast<Contact *>(staticFirstContactRecord);

		//	Delete all of the allocated records
		currentRecord = firstContactRecord;
		while (currentRecord != 0) {
			tempRecord = currentRecord;
			currentRecord = currentRecord->GetNextContact();
			delete tempRecord;
		}
	
	}

}

int AddressBookFunctions::ReadAddressFile(string filename) {

	ifstream	inFile;
	ofstream	outFile;
	string	name;
	string  phone;
	string	inString;
	Contact*	ptrContact=0;
	int		returnvalue;
	

	inFile.open(filename);
	if (!inFile) {
		cout << "File not found" << endl;
		return 0;
	}

	getline(inFile, inString);		// Name and Phone labels - 1st line of file.
//	cout << inString << endl;		// Echo out to the screen

	while (inFile.good()) {
		getline(inFile, name, ',');
		getline(inFile, phone, '\n');

		// Add the record to the Linked List - skip this part if a blank line was read.
		if (name != "") {					// This test is needed in case there is a blank line at the end of the file
			cout << name + ',' + phone << endl;	// Echo record out to the screen
			ptrContact = new Contact(name, phone);
			returnvalue = ptrContact->AddRecord(ptrContact);
		}
	}
//	Display # of records in the file.  Remember that this number is STATIC so you can get it from any object.
	cout << "There are " << ptrContact->GetNumberOfRecords() << " records in the file" << endl << endl;
	inFile.close();		// Close input file
	
	return 0;

}


int AddressBookFunctions::WriteAddressFile(string filename) {

	ofstream	outFile;
	string	name;
	string  phone;
	string	outString;
	Contact*	ptrContact = 0;
	int	numberOfRecords;
	int numberOfRecordsWritten = 0;
	static Contact*	staticFirstContactRecord;
	static Contact*	staticLastContactRecord;
	Contact* firstContactRecord;
	Contact* lastContactRecord;
	Contact* currentRecord;


	// Check for no records condition
	numberOfRecords = Contact::GetNumberOfRecords();

	if (numberOfRecords == 0) {						// No records to display
		cout << "Address Book is empty.  Nothing to write." << endl << endl;
		return 0;
	}


	outFile.open(filename);
	outString = "Name,Phone";
	outFile << outString << endl;	// Write 1st line labels to the file


	staticFirstContactRecord = Contact::GetFirstContact();
	staticLastContactRecord = Contact::GetLastContact();

	// Convert static class pointer to object pointer
	firstContactRecord = dynamic_cast<Contact *>(staticFirstContactRecord);
	lastContactRecord = dynamic_cast<Contact *>(staticLastContactRecord);

	// Write contacts to file
	currentRecord = firstContactRecord;
	while (currentRecord != 0) {
		outFile << currentRecord->GetName() << "," << currentRecord->GetPhone() << endl;
		numberOfRecordsWritten++;
		currentRecord = currentRecord->GetNextContact();
	}

	outFile.close();		// Close output file

	cout << numberOfRecordsWritten << " records written to file " << filename << endl << endl;


	return 0;

}

int	AddressBookFunctions::SearchContact(string name) {
	int	numberOfRecords;
	int numberOfRecordsMatched = 0;
	static Contact*	staticFirstContactRecord;
	static Contact*	staticLastContactRecord;
	Contact* firstContactRecord;
	Contact* lastContactRecord;
	Contact* currentRecord;


	numberOfRecords = Contact::GetNumberOfRecords();

	if (numberOfRecords == 0) {						// No records to display
		cout << "Address Book is empty.  Nothing to search." << endl << endl;
		return 0;
	}

	staticFirstContactRecord = Contact::GetFirstContact();
	staticLastContactRecord = Contact::GetLastContact();

	// Convert static class pointer to object pointer
	firstContactRecord = dynamic_cast<Contact *>(staticFirstContactRecord);
	lastContactRecord = dynamic_cast<Contact *>(staticLastContactRecord);

	// Search the records for matches
	currentRecord = firstContactRecord;
	while (currentRecord != 0) {
		string recordname = currentRecord->GetName();
		string typedname = name;
		GetLowerCase(recordname);
		GetLowerCase(typedname);

		//		if (GetLowerCase(currentRecord->GetName()) == GetLowerCase(name)) {		// Issue with this statement
		if (recordname == typedname) {
			cout << currentRecord->GetName() << "," << currentRecord->GetPhone() << endl;
			numberOfRecordsMatched++;
		}
		currentRecord = currentRecord->GetNextContact();
	}

	cout << "There were " << numberOfRecordsMatched << " records matching " << name << endl << endl;

	return 0;
}


int	AddressBookFunctions::DeleteContact(string name) {
	int	numberOfRecords;
	int numberOfRecordsMatched = 0;
	static Contact*	staticFirstContactRecord;
	static Contact*	staticLastContactRecord;
	Contact* firstContactRecord;
	Contact* lastContactRecord;
	Contact* currentRecord;
	string		inString;
	int		recordWasDeleted = 0;


	numberOfRecords = Contact::GetNumberOfRecords();

	if (numberOfRecords == 0) {						// No records to display
		cout << "Address Book is empty.  Nothing to delete." << endl << endl;
		return 0;
	}

	staticFirstContactRecord = Contact::GetFirstContact();
	staticLastContactRecord = Contact::GetLastContact();

	// Convert static class pointer to object pointer
	firstContactRecord = dynamic_cast<Contact *>(staticFirstContactRecord);
	lastContactRecord = dynamic_cast<Contact *>(staticLastContactRecord);

	// Search the records for matches
	currentRecord = firstContactRecord;

	while (currentRecord != 0) {
		string recordname = currentRecord->GetName();
		string typedname = name;
		GetLowerCase(recordname);
		GetLowerCase(typedname);

//		if (GetLowerCase(currentRecord->GetName()) == GetLowerCase(name)) {		// Issue with this statement
		if (recordname == typedname) {
			//Mark the record for possible deletion
			currentRecord->SetMarkedForDeletion(1);

			cout << "ID=" << currentRecord->GetRecordID() << "    " << currentRecord->GetName() << "," << currentRecord->GetPhone() << endl;
			numberOfRecordsMatched++;
		}
		currentRecord = currentRecord->GetNextContact();
	}

	cout << "There were " << numberOfRecordsMatched << " records matching " << name << endl << endl;

	if (numberOfRecordsMatched == 0) {
		return 0;
	}

	cout << "Please type the ID number of the record to be deleted" << endl;

	getline(cin, inString);

	currentRecord = firstContactRecord;
	while (currentRecord != 0) {
		if ((to_string(currentRecord->GetRecordID()) == inString)) {
			if (currentRecord->GetMarkedForDeletion() != 0) {

				cout << "Deleting " << currentRecord->GetRecordID() << "    " << currentRecord->GetName() << "," << currentRecord->GetPhone() << endl << endl;
				currentRecord->DeleteRecord(currentRecord);
				recordWasDeleted = 1;

				break;
			}
		}
		currentRecord = currentRecord->GetNextContact();
	}

	if (recordWasDeleted == 0) {
		cout << "Record ID not one of the choices. Nothing deleted." << endl << endl;
	}

	//	Reset the MarkedForDeletion flag on all of the remaining records
	SetAllMarkedForDeletion(0);

	
	return 0;
}

void AddressBookFunctions::GetLowerCase(string& inString) {
//	string&	AddressBookFunctions::GetLowerCase(string& inString) {

	string outString;
	unsigned int i;

	outString = inString;

	for (i = 0; i < inString.length(); i++)
	{
				outString[i] = tolower(inString[i]);
	}
	inString = outString;

}

int AddressBookFunctions::SetAllMarkedForDeletion(int flag) {
	int	numberOfRecords;
	static Contact*	staticFirstContactRecord;
	static Contact*	staticLastContactRecord;
	Contact* firstContactRecord;
	Contact* lastContactRecord;
	Contact* currentRecord;


	numberOfRecords = Contact::GetNumberOfRecords();

	if (numberOfRecords == 0) {						// No records
		return 0;
	}

	staticFirstContactRecord = Contact::GetFirstContact();
	staticLastContactRecord = Contact::GetLastContact();

	// Convert static class pointer to object pointer
	firstContactRecord = dynamic_cast<Contact *>(staticFirstContactRecord);
	lastContactRecord = dynamic_cast<Contact *>(staticLastContactRecord);

	currentRecord = firstContactRecord;
	while (currentRecord != 0) {
		currentRecord->SetMarkedForDeletion(flag);
		currentRecord = currentRecord->GetNextContact();
	}

	return 0;
}



int AddressBookFunctions::DisplayAddressBook() {
	int	numberOfRecords;
	static Contact*	staticFirstContactRecord;
	static Contact*	staticLastContactRecord;
	Contact* firstContactRecord;
	Contact* lastContactRecord;
	Contact* currentRecord;

	numberOfRecords = Contact::GetNumberOfRecords();

	if (numberOfRecords == 0) {						// No records to display
		cout << "Address Book is empty" << endl << endl;
		return 0;
	}

	staticFirstContactRecord = Contact::GetFirstContact();
	staticLastContactRecord = Contact::GetLastContact();

	// Convert static class pointer to object pointer
	firstContactRecord = dynamic_cast<Contact *>(staticFirstContactRecord);
	lastContactRecord = dynamic_cast<Contact *>(staticLastContactRecord);

	// Display contacts
	currentRecord = firstContactRecord;
	while (currentRecord != 0) {
		cout << currentRecord->GetName() << "," << currentRecord->GetPhone() << endl;
		currentRecord = currentRecord->GetNextContact();
	}

	cout << "Address Book contains " << numberOfRecords << " records" << endl << endl;

	return 0;

}

int AddressBookFunctions::DisplaySortedAddressBook() {
	int	numberOfRecords;
	static Contact*	staticFirstContactRecord;
	static Contact*	staticLastContactRecord;
	Contact* firstContactRecord;
	Contact* winningRecord = 0;
	string winningString;
	string jString;
	int winningIndex;
	int numberOfMarkedWinners;
	Contact* iptrRecord;
	Contact* jptrRecord;
	Contact* kptrRecord;

	numberOfRecords = Contact::GetNumberOfRecords();

	if (numberOfRecords == 0) {						// No records to display
		cout << "Address Book is empty" << endl << endl;
		return 0;
	}

	staticFirstContactRecord = Contact::GetFirstContact();

	// Convert static class pointer to object pointer
	firstContactRecord = dynamic_cast<Contact *>(staticFirstContactRecord);


	iptrRecord = firstContactRecord;
	jptrRecord = firstContactRecord;
	kptrRecord = firstContactRecord;

	// A "winning record" is the record that has a lower alphabetic result.  Ex.  "abc" will win over "def"
	winningRecord = firstContactRecord;
	winningIndex = firstContactRecord->GetIndexByRecord(winningRecord);	// index in the linked list of the winning record

	numberOfMarkedWinners = 0;
	while (numberOfMarkedWinners < numberOfRecords) {		// Scan the list of contacts until all have been alphabetized.

	for (int i = 0; i < numberOfRecords; i++) {
		iptrRecord = firstContactRecord->GetRecordByIndex(i);
		if (iptrRecord->GetMarkedForDeletion() != 0)				// This record has already been printed
		{
			continue;
		}
		winningRecord = iptrRecord;
		winningIndex = iptrRecord->GetIndexByRecord(winningRecord);
		for (int j = 0; j < numberOfRecords; j++)
		{
			jptrRecord = firstContactRecord->GetRecordByIndex(j);
			if (jptrRecord->GetMarkedForDeletion() != 0)				// This record has already been printed
			{
				continue;
			}
			else
			{
				winningString = winningRecord->GetName();
				jString = jptrRecord->GetName();

				if (winningString.compare(jString) > 0) {			// right object is "alphabetically less" than the right object
					winningRecord = jptrRecord;
					winningIndex = firstContactRecord->GetIndexByRecord(winningRecord);
				}

			}
		}

		// Display the next alphabetized contact record and mark it so that it so that it doesn't get used in future comparisons.
		// NOTE:  The objects's "Mark For Deletion" member variable is being used to flag each contact object as it's displayed.
		winningRecord->SetMarkedForDeletion(1);
		numberOfMarkedWinners++;
		cout << winningRecord->GetName() << "," << winningRecord->GetPhone() << endl;

	}		// End of for (int i = 0; i < numberOfRecords; i++)
	}		// End of while (numberOfMarkedWinners < numberOfRecords)

	//	Reset the SetMarkedForDeletion flag on all the records
	for (int k = 0; k < numberOfRecords; k++) {
		kptrRecord = firstContactRecord->GetRecordByIndex(k);
		kptrRecord->SetMarkedForDeletion(0);

	}

	cout << "Address Book contains " << numberOfRecords << " records" << endl << endl;

	return 0;

}

