//Filename:  proj4.cpp
//Author:  Esquire At Large
//Date written:  Wednesday, November 5th, 2008.
//Remember, remember, the fifth of November...
//Program Description:  This is the main file, which possesses
//four arrays:  two of integers and two of airports.
//These two arrays will be sorted using two different types
//of sorting algorithms.

#include <iostream>
#include <set>
#include <cstdlib>
#include <assert.h>
#include <iomanip>
#include "airport.h"
using namespace std;

//Constants for airport information.
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

int getValidInt(char* prompt);
//Precondition:  prompt is the prompt for the integer.
//Postcondition:  Returns a valid integer.

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

template <typename T>
void insertionSort(T arr[], int size);
//Precondition:  Intakes an array and the size of said array.
//Postcondition:  Sorts the array in situ using insertion sort. 

template <typename T>
int binarySearch(const T arr[], int first, int last, T target);
//Precondition:  Intakes the array to search through, and 
//the first position and last position of the array.  The
//first and last position are for recursive use.  
//Also intaken is the target to search for.
//Postcondition:  Returns the integer value corresponding 
//to the location of the item within the array.

template <typename T>
void mergeSort(T arr[], int begin, int end);
//Precondition:  Intakes an array and the size of said array.
//Also intakes the beginning and end of the array.
//Postcondition:  Splits array and calls for mergeArrays (not in situ).

template <typename T>
void mergeArrays(T arr[], int first, int mid, int last);
//Precondition:  Intakes the array, as well as the first element,
//the middle of the array, the element after that middle, the last 
//element in the array, and the size of the array.
//Precondition:  Sorts array using merge sort (not in situ).

const int ARRAY_SIZE = 7;

int main(){
	//Variable declaration
	int menu_opt;
	airport arpt;
	//The size of the arrays will always be seven.
	int IntegerArray1[ARRAY_SIZE], IntegerArray2[ARRAY_SIZE];
	airport AirportArray1[ARRAY_SIZE], AirportArray2[ARRAY_SIZE];
	//The location of the element after a binary search.
	//The element being searched for is target.
	int foundElementLoc = 0, target = 0;
	airport airquery;

	progIntro(); //Introduce the program.

	do{
		menu_opt = getMenuOption();
		switch(menu_opt){
			case 1:  //Enter seven integers and display sorted.
				//Entering integers.
				cout << endl << "Enter seven integers: " << endl << endl;

				for(int i = 0; i < ARRAY_SIZE; i++){
					IntegerArray1[i] = getValidInt("Enter an integer: ");
					IntegerArray2[i] = IntegerArray1[i];
				}

				//Call for insertion sort.
				insertionSort(IntegerArray1, ARRAY_SIZE);

				//Display array sorted using insertion sort.
				cout << endl << "After an insertion sort, the array contains: ";
				for(int d = 0; d < ARRAY_SIZE; d++)
					cout << IntegerArray1[d] << ", ";

				//Call for merge sort.
				mergeSort(IntegerArray2, ARRAY_SIZE - ARRAY_SIZE, ARRAY_SIZE - 1);

				cout << endl << "After a merge sort, the array contains: ";
				for(int k = 0; k < ARRAY_SIZE; k++)
					cout << IntegerArray2[k] << ", ";
				cout << endl;
				break;
			case 2:  //Search for integer and display location.
				cout << endl;
				target = getValidInt("Enter the integer to search for: ");
				foundElementLoc = binarySearch(IntegerArray1, 0, ARRAY_SIZE-1, target);
				if(foundElementLoc == -1) //Element not found.
					cout << endl << "<<< The integer " << target << " was not found." << endl;
				else{
					cout << endl << ">>> The integer " << target << " was found at location "
						<< ++foundElementLoc << "." << endl;
				}
				break;
			case 3:  //Enter seven airports and display sorted.
				cout << endl << "Enter seven airports: " << endl << endl;
				for(int i = 0; i < ARRAY_SIZE; i++){
					AirportArray1[i] = createAirport();
					AirportArray2[i] = AirportArray1[i];
				}

				//Call to insertionSort
				insertionSort(AirportArray1, ARRAY_SIZE);
				cout << endl << "After an insertion sort, the array contains: " << endl << endl;
				displayHdg();
				for(int i = 0; i < ARRAY_SIZE; i++){
					cout << AirportArray1[i] << endl;
				}
				cout << endl;

				//Call to mergeSort
				mergeSort(AirportArray2, ARRAY_SIZE - ARRAY_SIZE, ARRAY_SIZE - 1);
				cout << endl << "After a merge sort, the array contains: " << endl << endl;
				displayHdg();
				for(int i = 0; i < ARRAY_SIZE; i++){
					cout << AirportArray2[i] << endl;
				}
				cout << endl;

				break;
			case 4: //Search for airport and display location.
				cout << endl;
				airquery = getAirportByID("Enter the ID of the airport to search for: ");
				foundElementLoc = binarySearch(AirportArray1, 0, ARRAY_SIZE - 1, airquery);
				if(foundElementLoc == -1) //Element not found.
					cout << endl << "<<< The airport " << airquery.getIdentifier() << " was not found." << endl;
				else{
					cout << endl << ">>> The airport " << airquery.getIdentifier() << " was found at location "
						<< ++foundElementLoc << "." << endl;
				}
				break;
			case 5: //Exit.
				cout << endl << "**Thanks for using this program!"
					<< endl;
				break;
			default:  //Invalid option selected.
				cerr << "<<< Invalid menu option selected." 
					<< "  Please re-enter." << endl;
		}
	}while(menu_opt != 5);

	return 0;
}

void progIntro(){
	cout << "Welcome!  This program allows the " 
		<< "user to enter 7 integers and 7" << endl
		<< " airports, which will then be sorted accordingly." << endl;

}

int getMenuOption()
{
	int menuOption;
	
	cout << endl;
	cout << "-------------Main Menu----------------------" << endl;
	cout << "Select an option from those below: " << endl
		<< "1>  Enter 7 integers and display sorted." << endl
		<< "2>  Search arrays for an integer." << endl
		<< "3>  Enter 7 airports and display sorted." << endl
		<< "4>  Search arrays for an airport." << endl
		<< "5>  Exit Program." << endl;
	cout << "--------------------------------------------" << endl;
	menuOption = getValidNonNegInt("Enter a menu option from 1 to 5: ");	
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

int getValidInt(char* prompt)
{ 
	const int MAX = 80;
	char buffer[MAX];
	int i;
	cout << prompt;
	cin.getline(buffer,MAX);
	//Now a negative integer is also valid.
	while(strlen(buffer) != strspn(buffer, "-0123456789"))
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



template <typename T>
void insertionSort(T arr[], int size){
	//Using insertion sort, the incoming array will
	//be sorted.  The array is divided into two parts,
	//one sorted and the other unsorted.  The first
	//element from the unsorted part of the array is
	//moved into the sorted part in the proper location,
	//and then the next item in the unsorted area
	//is moved.  The process continues as such.

	for(int unsorted = 1; unsorted < size; unsorted++){
		T next = arr[unsorted];
		int loc = unsorted;
		for(; (loc >0) && (arr[loc -1] > next); --loc){
			//Shift array to right
			arr[loc] = arr[loc - 1];
		}
		arr[loc] = next;
	}
}

template <typename T>
int binarySearch(const T arr[], int first, int last, T target){
	int mid; //The middle point of this binary search...
	if(first <= last){ //Make sure that the first element isn't
		//greater than the last...
		mid = (first + last)/2; //Calculate middle of array...
		if(arr[mid] == target)
			//If the query is the middle of the array, the search
			//has complete.
			return mid;
		else if(arr[mid] > target)
			//If the middle of the array is bigger than the target
			//perform another binary search using the lower part
			//of the array.  This is recursive...
			return binarySearch(arr, first, mid - 1, target);
		else if(arr[mid] < target)
			//If the middle of the array is less than the target, 
			//perform another binary search using the higher part of
			//the array.  This is recursive...
			return binarySearch(arr, mid + 1, last, target);
	}
	//Return a -1 indicating the search was not successfull...
	return -1;
}

template <typename T>
void mergeSort(T arr[], int begin, int end){
	int mid;

	//Make sure the array is bigger than one.
	if(begin < end){
		//Calculate midpoint...
		mid = (begin + end)/2;
		
		//Recursively call this function
		//with the lower part of the array.
		mergeSort(arr, begin, mid);

		//Recusrively call this function
		//with the higher part of the array.
		mergeSort(arr, mid + 1, end);

		//Merge arrays.
		mergeArrays(arr, begin, mid, end);
	}

	
}

template <typename T>
void mergeArrays(T arr[], int first, int mid, int last){
	T mergingArray[ARRAY_SIZE]; //The array that will be merged.
	int lbegin, rbegin, mergingPos;
	lbegin = first; //First item in the array.
	rbegin = mid + 1; //The item after the middle.
	mergingPos = first; //Set the index of the merging array to
	//the beginning.

	for(; (lbegin <= mid) && (rbegin <= last); ++mergingPos){
		//If the beginning of the array is less than the
		//beginning of the upper part of the array...
		if(arr[lbegin] < arr[rbegin]){
			//The merging array is assigned values
			//from the beginning of the array to
			//the middle.
			mergingArray[mergingPos] = arr[lbegin];
			++lbegin;
		}
		else{
			//The merging array is assigned values
			//from the middle of the array to
			//the middle.
			mergingArray[mergingPos] = arr[rbegin];
			++rbegin;
		}
	}

	for(; lbegin <= mid; ++lbegin, ++mergingPos){
		//The merging array is assigned remaining values until
		//the middle.
		mergingArray[mergingPos] = arr[lbegin];
	}

	for(; rbegin <= last; ++rbegin, ++mergingPos){
		//The merging array is assigned remaining values until
		//the end of the array.
		mergingArray[mergingPos] = arr[rbegin];
	}

	for(mergingPos = first; mergingPos <= last; ++mergingPos){
		//The merging array is copied over into the original array.
		arr[mergingPos] = mergingArray[mergingPos];
	}
}