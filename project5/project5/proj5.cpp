//YOU CHANGED THE SETTINGS FROM ALLEGRO ONES!
//THE FOLLOWING WERE CHANGED:
//Program Database for Edit and Continue
//And others.
//Filename:  proj3.cpp
//Author:  Esquire At Large
//Date written:  Tuesday, October 28th, 2008.
//Program Description:  This is the main file, which possesses
//a set that will contain different airports stored in descending
//order.

#include <iostream>
#include <set>
#include <cstdlib>
#include <assert.h>
#include <iomanip>
#include "airport.h"
#include "index.h"
#include <fstream>
using namespace std;

const int MAX_NM = 26;
//The RRN from the index file will be
//stored into the char-array of this 
//constant size.
const int BUFFER_MAX = 10;

void progIntro();
//Precondition:  None.
//Postcondition:  Introduces user to the program.

int getMenuOption();
//Precondition:  None.
//Postcondition:  Prompts the user for the menu option
//and calls a function to validate the input.

int getValidNonNegInt(char * prompt);
//Precondition: prompt is the prompt for the integer.
//Postcondition: Returns a valid positive integer value.

airport createAirport();
//Precondition:  None.
//Postcondition:  Creates an instance of the airport class by
//receiving info describing the new airport.

void getString(char str[], int length, char* prompt);
//Precondition:  Intakes a prompt, length of a string
//and the string.
//Postcondition:  Displays the prompt, and receives user
//input of a certain length within the string.

void displayHdg();
//Precondition:  None.
//Postcondition:  Displays headings for the columns containing
//airport data.

airport getAirportByID(char* prompt);
//Precondition:  prompt is the message to display to the user.
//Postcondition:  Returns an airport, with its ID being user input.

void writeIndexFile(ostream& ostream, int RRN, set<I> indexSet);
//Precondition:  Intakes an instance of the base class ostream,
//either for console or file manipulation.  Also intakes the
//last RRN to write to and the set containing the records.

int establishFiles(fstream&, fstream&, set<I>& indexSet);
//Precondition:  Two files and the indexSet merely to pass to
//another function.
//Postcondition:  Sets up the files for use by the program, returns
//the RRN to write to if successfull.

void deleteRecord(set<I>& indexSet, fstream& masterFile);
//Precondition:  Intakes the set containing information from
//the index file, and the master file, from which the record
//will be deleted.
//Postcondition:  Flags a record for deletion by marking the first
//byte with an unused character.

set<I> loadIntoSet(int& rrn);
//Precondition:  Intakes the set containing information
//from the index file.
//Postcondition:  Loads information from the index file
//into the set.

void displayAirport(set<I> index, fstream& master);
//Precondition:  Intakes the set containing the rrn and id
//of the airport in the master file, and the master file.
//Postcondition:  Displays a singular airport from the 
//master file.

void displayAllAirports(set<I> index, fstream& master);
//Precondition:  Intakes the set containing the rrn and id
//of the airport in the master file, and the master file.
//Postcondition:  Displays all the airports in the master file
//in ascending identifier order.

void updateRunwayNumber(set<I> index, fstream& master);
//Precondition:  Intakes the set containing the rrn and id
//of the airport in the master file, and the master file.
//Postcondition:  Updates the master file with the new
//runway number of the airport.

int main(){
	//Variable declaration
	int menu_opt, currentRRN = 0;
	//CurrentRRN is the RRN at which the record lies.
	airport arpt;

	set<I> indexSet;
	set<I>::iterator locator;
	//The iterator below was found on MSDN:
	//http://msdn.microsoft.com/en-us/library/547ckb56(VS.80).aspx
	//It determines the success of the insert.
	pair< set<I>::iterator, bool > success; 
	fstream indexFile, masterFile;

	I indexInfo(currentRRN, "");

	progIntro(); //Introduce the program.

	//Initialize RRN;
	currentRRN = establishFiles(indexFile, masterFile, indexSet);

	do{
		menu_opt = getMenuOption();
		switch(menu_opt){
			case 1:  //Enter airport in list.
				cout << endl;
				arpt = createAirport();
				indexInfo.setID(arpt.getIdentifier());
				indexInfo.setRRN(currentRRN);
				success = indexSet.insert(indexInfo);
				if(success.second == true){
					//Writing to the master file.
					//Make sure to append to the end of the master file.
					masterFile.seekp(currentRRN*sizeof(airport));
					masterFile.write(reinterpret_cast<const char*>(&arpt), sizeof(airport));
					//Increment the current RRN, which is the RRN at which to write next.
					currentRRN++;
					cout << endl << ">>> The airport " << indexInfo.getID()
						<< " has been inserted successfully." << endl;
				}
				else{
					cerr << endl << "<<< The airport " << indexInfo.getID()
						<< " is a duplicate!" << endl;
				}
				break;
			case 2:  //Delete an airport.
				deleteRecord(indexSet, masterFile);
				break;
			case 3:  //Locate and display an airport.
				displayAirport(indexSet, masterFile);
				break;
			case 4: //Change runway number of airport
				updateRunwayNumber(indexSet, masterFile);
				break;
			case 5: //Display in ascending identifier order.
				displayAllAirports(indexSet, masterFile);
				break;
			case 6:  //Quit program.
				//Reopen index file.
				indexFile.open("index.txt", ios::out);

				//Write out to index file.
				writeIndexFile(indexFile, currentRRN, indexSet);
				//Close the index file.
				indexFile.close();
				//Clear the status bits.
				indexFile.clear();
				//Close masterfile.
				masterFile.close();
				masterFile.clear();
				cout << endl << "**Thanks for using this program!"
					<< endl;
				break;
			default:  //Invalid option selected.
				cerr << "<<< Invalid menu option selected." 
					<< "  Please re-enter." << endl;
				break;
		}
	}while(menu_opt != 6);

	return 0;
}

void progIntro(){
	cout << "Welcome!  This program allows the " 
		<< "user to enter and display" << endl
		<< "a list of airports in ascending order." << endl;
}

int getMenuOption()
{
	int menuOption;
	
	cout << endl;
	cout << "-------------Main Menu----------------------" << endl;
	cout << "Select an option from those below: " << endl
		<< "1>  Enter an airport's information." << endl
		<< "2>  Remove an airport from the list." << endl
		<< "3>  Locate and display an airport." << endl
		<< "4>  Change the runway number of an airport." << endl
		<< "5>  Display list of airports in ascending order." << endl
		<< "6>  Exit program." << endl;
	cout << "--------------------------------------------" << endl;
	menuOption = getValidNonNegInt("Enter a menu option from 1 to 6: ");	
	return menuOption;
}

int getValidNonNegInt(char* prompt)
{ 
	const int MAX = 80;
	char buffer[MAX];
	int i;
	cout << prompt;
	cin.getline(buffer,MAX);
	while(strlen(buffer) != strspn(buffer, "0123456789"))
	{
		cout << "\nInvalid integer, please re-enter: ";
		cin.getline(buffer, MAX);
	}
	i = atoi(buffer);
	return i;
}

void getString(char str[], int length, char* prompt){
	const int MAX_BUFFER = 80;
	char buffer[MAX_BUFFER];
	cout << prompt;
	cin.getline(buffer, MAX_BUFFER);
	while(strlen(buffer) >= length){
		cout << "Entry is too long, please re-enter: ";
		cin.getline(buffer, MAX_BUFFER);
	}
	strcpy(str, buffer);
}

airport createAirport(){
//Precondition:  None.
//Postcondition:  Creates an instance of the airport class
//by receiving user info describing the new airport.
	//AKA getAirport Info
	const int MAX_ID = 4;
	char name[MAX_NM], ID[MAX_ID];
	int number;
	getString(ID, MAX_ID, "Enter the airport ID (Maximum 3 characters): ");
	getString(name, MAX_NM,
		"Enter the airport name (Maximum 25 characters): ");
	number = getValidNonNegInt("Enter the runway number: ");
	airport a;
	a.setAirportID(ID);
	a.setAirportName(name);
	a.setRunwayNumber(number);
	//Copy over the respective data to the created airport.
	
	return a;
}

void displayHdg(){
	cout << "ID  " << setw(26) << left << "Name" 
		<< "Runway #" << endl
		<< "--------------------------------------" 
		<< endl;
}

airport getAirportByID(char* prompt){
	const int MAX_ID = 4;
	char ID[MAX_ID];
	airport a;
	getString(ID, MAX_ID, prompt);
	a.setAirportID(ID);
	return a;
}

void writeIndexFile(ostream& ostream, int RRN, set<I> indexSet){
	char buffer[80], buffer2[20];
	set<I>::iterator locator;
	
	ostream << RRN << "\n";
	for(locator = indexSet.begin(); locator != indexSet.end(); locator++){
		strcpy(buffer, locator->getID());
		strcat(buffer, " ");
		//Convert RRN to a string
		itoa(locator->getRRN(), buffer2, 10);
		strcat(buffer, buffer2);
		strcat(buffer, "\n");
		//Null terminate the string.
		strcat(buffer, "\0");

		//Write out the string to the index file.
		ostream << buffer;
	}
}

int establishFiles(fstream& indexFile, fstream& masterFile, set<I>& indexSet){
	//Establishing master file.

	int RRN;
	char buff[BUFFER_MAX];

	masterFile.open("master.bin", ios::in);
	if(masterFile.fail()){
		//The file was not found, so create it.
		cout << endl << "<<< Failed to open the master file!  A new one"
			<< " has been created." << endl;

		masterFile.close();
		//Clear status bits.
		masterFile.clear();
		masterFile.open("master.bin", ios::out|ios::binary);

		//Initialize RRN to zero for first record to insert.
		RRN = 0;
	}
	masterFile.close();
	masterFile.clear();
	masterFile.open("master.bin", ios::in|ios::out|ios::binary);

	indexFile.open("index.txt", ios::in);
	if(indexFile.fail()){
		cout << endl << "<<< Failed to open the index file!  A new one"
			<< " was created." << endl;
		indexFile.close();
		indexFile.clear();
		indexFile.open("index.txt", ios::out|ios::in);

		//This doesn't necessarily mean that the master file isn't there.
		//Therefore here we would have to scan for the largest RRN...
		//But we are not creating a new index file from the master file
		//in case of error here.
		RRN = 0;
	}
	else{
		indexSet = loadIntoSet(RRN);
	}
	indexFile.close();
	indexFile.clear();

	return RRN;
}

void deleteRecord(set<I>& indexSet, fstream& masterFile){
	airport a;
	I indexInfo;
	set<I>::iterator locator;
	char buff[MAX_NM]; //A buffer to store airport from
	//master file.

	if(indexSet.empty() == true)
		cout << endl << "<<< There are no airports to remove." << endl;
	else{
		cout << endl;
		a = getAirportByID("Enter the ID of the airport to remove: ");
		indexInfo.setID(a.getIdentifier());
		locator = indexSet.find(indexInfo);
		if(locator == indexSet.end())
			//The airport was not found in the set.
			cout << endl << "<<< The airport was not found in the list!" << endl;
		else{
			//The airport was found in the set.
			
			//Replace name with *.
			masterFile.seekp(locator->getRRN()*sizeof(airport));
			//Write to the first byte of the record, to flag it
			//for deletion.
			masterFile.write("*", 1);

			//Remove from the indexSet.
			indexSet.erase(locator);
			cout << endl << ">>> The airport was removed from the list." << endl;
		}
	}
}

set<I> loadIntoSet(int& rrn){
	char buff[BUFFER_MAX];
	ifstream indexFile;
	indexFile.open("index.txt", ios::in);
	I indexInfo; //Used to store into set.
	set<I> set;

	//Get the current rrn
	indexFile.seekg(0);
	indexFile.getline(buff, BUFFER_MAX, '\n');
	rrn = atoi(buff);
	//PERHAPS CHANGE TO VERTICAL BAR??
	while(indexFile && !indexFile.eof()){
		//Based off the notes, getline moves the seekg pointer too...
		indexFile.getline(buff, BUFFER_MAX, ' ');
		indexInfo.setID(buff);
		indexFile.getline(buff, BUFFER_MAX, '\n');
		indexInfo.setRRN(atoi(buff));
		strcpy(buff, "\n");
		set.insert(indexInfo);
		//PERHAPS SEARCH TO \0?
	}
	//The first element in the set must be erased
	//because it shows up as a <,0> pair, which is
	//erroneous.
	set.erase(set.begin());
	//Now close the index file.
	indexFile.close();
	//Clear the status bits.
	indexFile.clear();

	return set;
}

void displayAirport(set<I> index, fstream& master){
	set<I>::iterator pos;
	airport a;
	I id;
	char buff[MAX_NM];
	char buff2[MAX_ID];
	
	cout << endl;
	a = getAirportByID("Enter the ID of the airport to display: ");
	id.setID(a.getIdentifier());
	pos = index.find(id);
	if(pos == index.end())
		cout << endl << "<<< The airport doesn't exist!" << endl;
	else{
		//Load in airport from master file.
		master.seekg((pos->getRRN())*sizeof(airport));
		master.read(reinterpret_cast<char*>(&a), sizeof(airport));
		//master.getline(buff, 10);
		//a.setAirportName(buff);
		//master.getline(buff2, MAX_ID);
		//a.setAirportID(buff2);
		displayHdg();
		cout << a << endl;
	}
}

void displayAllAirports(set<I> index, fstream& master){
	set<I>::iterator pos;
	airport a;
	if(index.empty())
		cerr << "<<< There are no airports to display." << endl;
	else{
		displayHdg();
		for(pos = index.begin(); pos != index.end(); pos++){
			//Update to next record.
			master.seekg((pos->getRRN()*sizeof(airport)));
			master.read(reinterpret_cast<char*>(&a), sizeof(airport));
			cout << a << endl;
		}
	}
}

void updateRunwayNumber(set<I> index, fstream& master){
	airport a;
	I id;
	int runway = 0;
	set<I>::iterator pos;

	if(index.empty())
		cerr << endl << "<<< There are no airports to update." << endl;
	else{
		a = getAirportByID("Enter the id of the airport to update: ");
		id.setID(a.getIdentifier());
		pos = index.find(id);
		if(pos == index.end())
			cerr << endl << "<<< That airport was not found." << endl;
		else{
			master.seekg((pos->getRRN()*sizeof(airport)));
			master.read(reinterpret_cast<char*>(&a), sizeof(airport));
			do{
				cout << endl;
				runway = getValidNonNegInt("Enter the new runway number (1-36): ");
				if(runway < 1 || runway > 36){
					cout << endl << "<<< Runway outside valid bounds." 
						<< "  Please re-enter." << endl;
					runway = getValidNonNegInt("Enter the new runway number (1-36): ");
				}
			}while(runway < 1 || runway > 36);
			a.setRunwayNumber(runway);
			master.seekp((pos->getRRN()*sizeof(airport)));
			master.write(reinterpret_cast<const char*>(&a), sizeof(airport));
			cout << ">>> The airport has been updated!" << endl;
		}
	}
}

