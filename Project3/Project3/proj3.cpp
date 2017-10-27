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
using namespace std;

const int MAX_NM = 26;
const int MAX_NUM = 4;
const int MAX_APPR = 5;

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

int main(){
	//Variable declaration
	int menu_opt;
	airport arpt;
	set<airport> airportSet;
	set<airport>::iterator loc; //Location iterator.
	//The iterator below was found on MSDN:
	//http://msdn.microsoft.com/en-us/library/547ckb56(VS.80).aspx
	//It determines the success of the insert.
	pair< set<airport>::iterator, bool > success; 

	progIntro(); //Introduce the program.

	do{
		menu_opt = getMenuOption();
		switch(menu_opt){
			case 1:  //Enter airport in list.
				cout << endl;
				arpt = createAirport();
				success = airportSet.insert(arpt);
				if(success.second == true){
					cout << endl << ">>> The airport " << arpt.getIdentifier()
						<< " has been inserted successfully." << endl;
				}
				else{
					cerr << endl << "<<< The airport " << arpt.getIdentifier() 
						<< " already exists in the list!" << endl;
				}
				break;
			case 2:  //Delete an airport.
				if(airportSet.size() == 0)
					cerr << endl << "<<< There are no airports to remove." << endl;
				else{
					cout << endl;
					arpt = getAirportByID("Enter the ID of the airport to remove: "); 
					//Ask the user which airport he wants to remove.
					loc = airportSet.find(arpt);
					if(loc == airportSet.end()){
						cerr << endl << "<<< Error, airport not found in set." << endl;
					}
					else{
						airportSet.erase(loc);	
						cerr << endl << ">>> The airport " << arpt.getIdentifier()
							<< " has been removed." << endl;
					}
				}
				break;
			case 3:  //Locate and display an airport.
				cout << endl;
				arpt = getAirportByID("Enter the ID of the airport to display: ");
				loc = airportSet.find(arpt); //find_res is a constant iterator.
				if(loc == airportSet.end())
					cerr << endl << "<<< Error, airport not found in set." << endl;
				else{
					cout << endl;
					displayHdg();
					cout << *loc << endl;
				}
				break;
			case 4: //Clear list of airports.
				if(airportSet.size() == 0)
					cerr << endl << "<<< The list is already empty." << endl;
				airportSet.clear();
				cout << endl << ">>>The list of airports has been cleared." << endl;
				break;
			case 5: //Display in ascending identifier order.
				if(airportSet.size() == 0)
					cerr << endl << "<<< There are no airports to display." << endl;
				else{
					cout << endl;
					displayHdg();
					for(loc = airportSet.begin(); loc != airportSet.end(); loc++)
						cout << *loc << endl;
				}
				break;
			case 6:  //Quit program.
				cout << endl << "**Thanks for using this program!"
					<< endl;
				break;
			default:  //Invalid option selected.
				cerr << "<<< Invalid menu option selected." 
					<< "  Please re-enter." << endl;
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
		<< "4>  Clear the list of all airports." << endl
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
	getString(ID, MAX_ID, "Enter the airport ID (Maximum 3 characters): ");
	getString(name, MAX_NM,
		"Enter the airport name (Maximum 25 characters): ");
	airport a;
	a.setAirportID(ID);
	a.setAirportName(name);
	//Copy over the respective data to the created airport.
	
	return a;
}

void displayHdg(){
	cout << "ID  " << setw(35) << left << "Name" << endl
		<< "------------------------" 
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