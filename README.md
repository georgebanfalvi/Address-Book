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

