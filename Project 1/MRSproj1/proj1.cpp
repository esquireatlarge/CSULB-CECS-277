//Filename:  proj1.cpp
//Author:  Matt Sguerri
//Date written:  Monday, September 15th, 2008.
//Program Description:  This program maintains
//a list of airports and allows
//the user to edit said list.

#include <iostream>
#include <cstdlib>
#include "airport.h"
#include "ListException.h"
#include <assert.h>
#include <iomanip>
using namespace std;

const int MAX_NM = 26;
const int MAX_NUM = 4;

void progIntro();
//Precondition:  None.
//Postcondition:  Introduces user to the program.

int getMenuOption();
//Precondition:  None.
//Postcondition:  Prompts the user for the menu option
//and calls a function to validate the input.

int getValidNonNegInt(char * prompt);
//Pre-condition: prompt is the prompt for the integer.
//Post-condition: Displays the validity of the integer
//input by the user.

airport* createAirport();
//Precondition:  None.
//Postcondition:  Creates an instance of the airport class by
//receiving info describing the new airport.

void getString(char str[], int length, char* prompt);
//Precondition:  Intakes a prompt, length of a string
//and the string.
//Postcondition:  Displays the prompt, and receives user
//input of a certain length within the string.

void addToList(int& size, airport* list[], airport* arpt, int max);
//Precondition:  Intakes size of list, list of airports, and
//an airport to input.
//Postcondition:  Adds the airport to the list.

void displayHdg();
//Precondition:  None.
//Postcondition:  Displays headings for the columns containing
//airport data.

void EditAirportMenu();
//Precondition:  None.
//Postcondition:  Displays the menu for changing an airplane.

void changeAirportName(airport* ar);
//Precondition:  Intakes an airport.
//Postcondition:  Calls the airport's setName function
//with the user's new input.

void changeAirportNumber(airport* ar);
//Precondition:  Intakes an airport.
//Postcondition:  Calls the airport's setNumber function
//with the user's new input.

void changeAirportLength(airport* ar);
//Precondition:  Intakes an airport.
//Postcondition:  Calls the airport's setLength function
//with the user's new input.

int pickAirport(airport* list[], int size);
//Precondition:  Intakes the airport list.
//Postcondition:  Returns the index of the airport
//in the array.

int main(){
	//Variable declaration
	int menu_opt;
	const int MAX_LIST = 25;
	int size = 0, a_to_e = 0, length = 0;
	airport* airportList[MAX_LIST];
	airport* arpt;

	progIntro(); //Introduce the program.

	do{
		menu_opt = getMenuOption();
		switch(menu_opt){
			case 1:  //Enter information for an airport.
				if(size < 25){
					arpt = createAirport();
					addToList(size, airportList, arpt, MAX_LIST);
				}
				else
					cerr << "The list of airports is full." << endl;
				break;
			case 2:  //Change an airport's information.
				if(size == 0)
					cerr << "The list is empty!" << endl;
				else{
					a_to_e = pickAirport(airportList, size);
					do{
						EditAirportMenu();
						menu_opt = getValidNonNegInt("Enter an option between 1 and 4:");
						switch(menu_opt){
							case 1: //Change name
								changeAirportName(airportList[a_to_e]);
								break;
							case 2: //Runway number
								changeAirportNumber(airportList[a_to_e]);
								break;
							case 3: //Runway length
								changeAirportLength(airportList[a_to_e]);
								break;
							case 4:
								cout << "Returning to main menu." << endl;
								break;
						}
					}while(menu_opt != 4);
					menu_opt = 0;
				}
				break;
			case 3:  //Display list of airports.
				if(size == 0)
					cout << "The list is empty." << endl;
				else{
					displayHdg();
					for(int i = 0; i < size; i++){
						cout << setw(3) << i << *airportList[i];
					}
				}
				break;
			case 4:  //Quit program.
				cout << endl << "**Thanks for using this program!"
					<< endl;
				break;
			default:  //Invalid option selected.
				cerr << "**Invalid menu option selected." 
					<< "  Please re-enter." << endl;
		}
	}while(menu_opt != 4);

	return 0;
}

void progIntro(){
	cout << "Welcome, this program allows the " 
		<< "user to edit and display" << endl
		<< "a list of local airports." << endl;
}

int getMenuOption()
{
	int menuOption;
	
	cout << endl;
	cout << "-------------Main Menu---------------" << endl;
	cout << "Select an option from those below: " << endl
		<< "1>  Enter an airport's information." << endl
		<< "2>  Change an airport's information." << endl
		<< "3>  Display the list of airports." << endl
		<< "4>  Exit this program." << endl;
	cout << "-------------------------------------" << endl;
	menuOption = getValidNonNegInt("Enter a menu option from 1 to 4: ");	
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

airport* createAirport(){
//Precondition:  None.
//Postcondition:  Creates an instance of the airport class
//by receiving user info describing the new airport.
	//AKA getAirport Info
	const int MAX_ID = 4;
	char name[MAX_NM], ID[MAX_ID], number[MAX_NUM];
	int length;
	getString(ID, MAX_ID, "Enter the airport ID (Maximum 3 characters): ");
	getString(name, MAX_NM,
		"Enter the airport name (Maximum 25 characters): ");
	getString(number, MAX_NUM, 
		"Enter the airport runway number (Maximum 3 characters): ");
	length = getValidNonNegInt("Enter the runway length: ");
	airport* airprt = new airport(name,ID,number, length);
	assert(airprt != NULL); 
	//Make sure that memory could be allocated, if not
	//kill the program.
	
	return airprt;
}

void getString(char str[], int length, char* prompt){
//Precondition:  Intakes a prompt, length of a string
//and the string.
//Postcondition:  Displays the prompt, and receives user
//input of a certain length within the string.
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

void addToList(int& size, airport* list[], airport* arpt, int max){
	assert(size != max);
	list[size] = arpt;
	size++;
}

void displayHdg(){
	cout << "#" << "  ID  " << setw(29) << left << "Name" << setw(5)
		<< " Runway Number" 
		<< setw(5) << " " << "Runway Length" << endl;
	cout << "-------------------------------------"
		<< "----------------------------------" 
		<< endl;
}

void EditAirportMenu(){
	cout << "---------Airport Edit Menu---------" << endl;
	//cout << "1>Select an airport from the list." << endl;
	cout << "1>Change the airport's name." << endl;
	cout << "2>Change the airport's runway number." << endl;
	cout << "3>Change the airport's runway length." << endl;
	cout << "4>Return to main menu." << endl;
	cout << "-----------------------------------" << endl;
}

void changeAirportName(airport* ar){
	char name[MAX_NM];
	getString(name, MAX_NM,
		"Enter the new name (25 ch. max): ");
	ar->setAirportName(name);
}

void changeAirportNumber(airport* ar){
	char number[MAX_NUM];
	getString(number, MAX_NUM,
		"Enter the new number (3 ch. max): ");
	ar->setNumber(number);
}

void changeAirportLength(airport* ar){
	int length = 0;
	length = getValidNonNegInt("Enter the new length: ");
	ar->setLength(length);
}

int pickAirport(airport* list[], int size){
	int index = 0;
	cout << endl;
	cout << "The following airports can be edited: " << endl;
	displayHdg();
	for(int i = 0; i < size; i++)
		cout << setw(3) << i << *list[i];
	cout << endl;
	index = getValidNonNegInt("Enter the airport # to edit: ");
	do{
		if(index >= size){
			cerr << "Non-existent airport!" << endl;
			index = getValidNonNegInt("Enter the airport # to edit: ");
		}
	}while(index >= size);

	return index;
}