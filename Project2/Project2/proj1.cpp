//*****************************************************************
//Filename:  proj1.cpp											  *	
//Author:  Esquire At Large                                           *
//Date written:  Monday, September 15th, 2008.                    *
//Program Description:  This program maintains                    *
//a list of airports and allows                                   *
//the user to edit said list.                                     *
//*****************************************************************

#include <iostream>
#include <cstdlib>
#include "airport.h"
#include "towered.h"
#include "nontowered.h"
#include <assert.h>
#include <iomanip>
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

double getValidNonNegDouble(char* prompt);
//Precondition:  prompt is the prompt for the double.
//Postcondition:  Returns a valid positive double value.

airport* createAirport(bool type);
//Precondition:  Intakes a boolean to determine a towered 
//or non-towered airport.  If false, a towered airport, if
//true, a non-towered airport.
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

void EditAirportMenu(bool type);
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

void changeApproach(Towered* tow);
//Precondition:  Intakes an instance of the derived towered class.
//Postcondition:  Calls the towered class's setApproach function
//with the user's new input.

void changeCTAF(Nontowered* non);
//Precondition:  Intakes an instance of the derived nonttowered class.
//Postcondition:  Calls the nontowered class's setCTAF function with
//the user's new input.

int pickAirport(airport* list[], int size, bool type);
//Precondition:  Intakes the airport list, size of said list, 
//and a boolean to determine the type of airport.
//Postcondition:  Returns the index of the airport
//in the array.

int main(){
	//*****************Variable declaration******************
	int menu_opt; //Hold option selected by user.			*
	const int MAX_LIST = 25; //Maximum list size			*
	//Size is the amount of airports in the list,			*
	//a_to_e is the user selection of airport to edit,		*
	int size = 0, a_to_e = 0, copysize = 0;				  //*
	airport* airportList[MAX_LIST]; //Array of airports		*
	airport* copy[MAX_LIST]; //Copied list.				  //*
	airport* arpt; //A singular airport pointer.			*
	bool airportType;									  //*
	//*******************************************************

	progIntro(); //Introduce the program.

	do{
		menu_opt = getMenuOption(); //Get initial menu option
		cout << endl;
		switch(menu_opt){
			case 1:  //Enter towered airport info
				if(size < MAX_LIST){
					airportType = false; //Towered.
					arpt = createAirport(airportType);
					addToList(size, airportList, arpt, MAX_LIST);
					cout << endl << ">>>Airport successfully stored into list."
						<< endl;
				}
				else
					cerr << "The list of airports is full." << endl;
				break;
			case 2:  //Enter non-towered airport info.
				if(size < MAX_LIST){
					airportType = true; //Nontowered.
					arpt = createAirport(airportType);
					addToList(size, airportList, arpt, MAX_LIST);
					cout << endl << ">>>Airport successfully stored into list."
						<< endl;
				}
				else
					cerr << "The list of airports is full." << endl;
				break;
			case 3: //Change towered airport info.
				airportType =  false;
				Towered* t;
				a_to_e = pickAirport(airportList, size, airportType);
				do{
					EditAirportMenu(airportType);
					menu_opt = getValidNonNegInt("Enter an option between 1 and 5:");
					switch(menu_opt){
						case 1: //Change name
							changeAirportName(airportList[a_to_e]);
							break;
						case 2: //Change runway number.
							changeAirportNumber(airportList[a_to_e]);
							break;
						case 3: //Change runway length.
							changeAirportLength(airportList[a_to_e]);
							break;
						case 4: //Change approach
							t = dynamic_cast<Towered*>(airportList[a_to_e]);
							changeApproach(t);
							break;
						case 5: //To main menu.
							cout << "Returning to main menu." << endl;
							break;
					}
				}while(menu_opt != 5);
				menu_opt = 0;
				break;
			case 4: //Change non-towered airport info.
				airportType = true;
				Nontowered* nt;
				a_to_e = pickAirport(airportList, size, airportType);
				do{
					EditAirportMenu(airportType);
					menu_opt = getValidNonNegInt("Enter an option between 1 and 5:");
					switch(menu_opt){
						case 1:
							changeAirportName(airportList[a_to_e]);
							break;
						case 2:
							changeAirportNumber(airportList[a_to_e]);
							break;
						case 3:
							changeAirportLength(airportList[a_to_e]);
							break;
						case 4:
							nt = dynamic_cast<Nontowered*>(airportList[a_to_e]);
							changeCTAF(nt);
							break;
						case 5:
							cout << "Returning to main menu." << endl;
							break;
					}
				}while(menu_opt != 5);
				menu_opt = 0;
				break;
			case 5:  //Display list.
				if(size == 0)
					cout << "The list is empty." << endl;
				else{
					const Towered* t;
					const Nontowered* nt;
					int air_no = 1;
					displayHdg();
					for(int i = 0; i < size; i++){
						//cout << setw(3) << air_no << *airportList[i];
						t = dynamic_cast<const Towered*>(airportList[i]);
						if(t != 0)
							cout << setw(3) << left << air_no
							<< *airportList[i];
						else{
							nt = dynamic_cast<const Nontowered*>(airportList[i]);
							cout << setw(3) << left << air_no
								<< *airportList[i];
						}
						air_no++;
					}
				}
				break;
			case 6: //Copy list.
				if(size == 0){
					cerr << "There is nothing to copy, the list is empty!"
						<< endl;
				}
				else{
					const Towered* t;
					for(int i = 0; i < size; i++){
						t = dynamic_cast<const Towered*>(airportList[i]);
						if(t != 0) //Object is a towered airport.
							copy[i] = new Towered(*(dynamic_cast<const Towered*>(airportList[i])));
						else //Object is a nontowered airport.
							copy[i] = new Nontowered(*(dynamic_cast<const Nontowered*>(airportList[i])));
					}
					copysize = size;
					cout << ">>>List copied successfully." << endl;
				}
				break;
			case 7: //Display copied list.
				if(copysize == 0)
					cerr << "There is nothing in the copied list!" << endl;
				else{
					const Towered* t;
					const Nontowered* nt;
					int air_no = 1;
					displayHdg();
					for(int i = 0; i < copysize; i++){
						//cout << setw(3) << air_no << *airportList[i];
						t = dynamic_cast<const Towered*>(copy[i]);
						if(t != 0)
							cout << setw(3) << left << air_no
							<< *copy[i];
						else{
							nt = dynamic_cast<const Nontowered*>(copy[i]);
							cout << setw(3) << left << air_no
								<< *copy[i];
						}
						air_no++;
					}
				}
				break;
			case 8:  //Quit program.
				cout << endl << ">>>Thanks for using this program!"
					<< endl;
				break;
			default:  //Invalid option selected.
				cerr << "**Invalid menu option selected." 
					<< "  Please re-enter." << endl;
		}
	}while(menu_opt != 8);

	return 0;
}

void progIntro(){
	cout << "Welcome!  This program allows the " 
		<< "user to edit and display" << endl
		<< "a list of towered or non-towered airports." << endl;
}

int getMenuOption()
{
	int menuOption;
	
	cout << endl;
	cout << "-------------Main Menu----------------------" << endl;
	cout << "Select an option from those below: " << endl
		<< "1>  Enter a towered airport's information." << endl
		<< "2>  Enter a non-towered airport's information." << endl
		<< "3>  Change a towered airport's information." << endl
		<< "4>  Change a non-towered airport's information." << endl
		<< "5>  Display list of airports." << endl
		<< "6>  Copy the list of airports." << endl
		<< "7>  Display the copied list." << endl
		<< "8>  Exit the program." << endl;
	cout << "--------------------------------------------" << endl;
	menuOption = getValidNonNegInt("Enter a menu option from 1 to 8: ");	
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

double getValidNonNegDouble(char* prompt){
	const int MAX = 80;
	char buffer[MAX];
	double d;
	cout << prompt;
	cin.getline(buffer, MAX);
	while(strlen(buffer) != strspn(buffer, ".0123456789"))
	{
		cout << "\nInvalid double, please re-enter: ";
		cin.getline(buffer, MAX);
	}
	d = atof(buffer);
	return d;
}

airport* createAirport(bool type){
	//AKA getAirport Info
	const int MAX_ID = 4;
	char name[MAX_NM], ID[MAX_ID], number[MAX_NUM], approach[MAX_APPR];
	int length;
	double ctaf = 0.0;
	airport* airprt;

	getString(ID, MAX_ID, "Enter the airport ID (Max 3 characters): ");
	getString(name, MAX_NM,
		"Enter the airport name (Max 25 characters): ");
	getString(number, MAX_NUM, 
		"Enter the airport runway number (Max 3 characters): ");
	length = getValidNonNegInt("Enter the runway length: ");
	if(type == false){
		//If user is creating a towered airport, ask for
		//primary instrument approach.
		getString(approach, MAX_APPR, 
			"Enter the primary instrument approach (Max 5 Characters): ");
		airprt = new Towered(approach, name, ID, number, length);
	}
	else{ 
		//If user is creating a non-towered airport, ask for
		//CTAF frequency.
		ctaf = getValidNonNegDouble("Enter the CTAF frequency: ");
		airprt = new Nontowered(ctaf, name, ID, number, length);
	}

	assert(airprt != NULL); 
	//Make sure that memory could be allocated, if not
	//kill the program.
	
	return airprt;
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

void addToList(int& size, airport* list[], airport* arpt, int max){
	assert(size != max); //Make absolutely sure list is not full.
	list[size] = arpt;
	size++;
}

void displayHdg(){
	cout << "#" << "  ID  " << setw(26) << left << "Name" << setw(4)
		<< "Number" 
		<< setw(5) << " " << "Length" <<  setw(10) << " " << "Freq/Approach" << endl;
	cout << "-------------------------------------"
		<< "------------------------------------" 
		<< endl;
}

void EditAirportMenu(bool type){
	cout << endl;
	cout << "---------Airport Edit Menu---------" << endl;
	cout << "1>Change the airport's name." << endl;
	cout << "2>Change the airport's runway number." << endl;
	cout << "3>Change the airport's runway length." << endl;
	if(type == true)
		cout << "4>Change the airport's CTAF frequency." << endl;
	else
		cout << "4>Change the airport's approach." << endl;
	cout << "5>Return to main menu." << endl;
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

void changeApproach(Towered* tow){
	char apprch[MAX_APPR];
	getString(apprch, MAX_APPR, 
		"Enter the new approach (4 ch. max): ");
	tow->setApproach(apprch);
}

void changeCTAF(Nontowered* non){
	double newctaf = 0.0;
	newctaf = getValidNonNegDouble("Enter the new CTAF frequency: ");
	non->setCTAFFreq(newctaf);
}

int pickAirport(airport* list[], int size, bool type){
	int index = 0, num = 1;
	const Towered* t;
	const Nontowered* nt;
	cout << "The following airports can be edited: " << endl;
	displayHdg();
	//If type is true, only the nontowered must be edited.
	//If type is false, only the towered must be edited.
	if(type == true){
		//Show nontowered only.
		for(int i = 0; i < size; i++){
			nt = dynamic_cast<const Nontowered*>(list[i]);
			if(nt != 0) //It is a Nontowered airport.
				cout << setw(3) << left << num << *list[i];
			++num;
		}
	}
	else{
		//Show towered only.
		for(int i = 0; i < size; i++){
			t = dynamic_cast<const Towered*>(list[i]);
			if(t != 0) //It is a Towered airport.
				cout << setw(3) << left << num << *list[i];
			++num;
		}
	}
	cout << endl;
	index = getValidNonNegInt("Enter the airport # to edit: ") - 1;
	do{
		if(index >= size){
			cerr << "Non-existent airport!" << endl;
			index = getValidNonNegInt("Enter the airport # to edit: ");
		}
	}while(index >= size);

	return index;
}
