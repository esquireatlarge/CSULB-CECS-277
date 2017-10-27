//Filename:  airport.h
//Author:  Esquire At Large
//Date written:  Wednesday, September 17th, 2008.
//Program Description:  This header file contains the function 
//declarations for the airport class.

#pragma once
#include <iostream>
#include <cstring>
#include <assert.h>
#include <iomanip>
#include "runway.h"
using namespace std;

const int MAX_NAME = 26;
const int MAX_ID = 4;

class airport{
	friend ostream& operator<<(ostream&, const airport&);

public:
	airport(const char nm[] = "", const char id[] = "", const int num = 1);
	//Constructor
	//Precondition:  Creates an instance of the airport class, if no
	//values are provided, the default ones will be used.
	//Postcondition:  Initializes constant values name, identifier, 
	//runway number, and runway length.

	airport(const airport&);
	//Copy constructor.
	//Precondition:  Intakes an instance of the airport class by reference.
	//Postcondition:  Successfully copies identifier, name, 
	//and runway's members.
	
	//~airport();
	//Destructor
	//Precondition:  None.
	//Postcondition:  Destroys dynamically allocated airport members.

	const airport& operator=(const airport& rhs);
	//Precondition:  Intakes the address of an airport instance.
	//Postcondition:  Assigns the members of the airport class to
	//the other instance of airport.

	void setAirportName(const char nm[] = "Defaulto Airport");
	//Precondition:  Intakes name of airport.
	//Postcondition:  If there are no invalid characters for the name of
	//the airport, it is assigned to the name field.

	void setAirportID(const char id[] = "DFT");
	//Precondition:  Intakes an airport's identifier.
	//Postcondition:  If nothing is wrong with the identifier, it is
	//assigned to the identifier field.

	void setRunwayNumber(const int num = 12);
	//Precondition:  Intakes the runway number.
	//Postcondition:  Accesses the runway set number function.

	const char* getIdentifier() const;
	//Precondition:  None.
	//Postcondition:  Returns solely the ID of an airport.

	const char* getName() const;
	//Precondition:  None.
	//Postcondition:  Returns solely the name of an airport.

	const int getRunwayNumber() const;
	//Precondition:  None.
	//Postcondition:  Returns the runway number.

	bool operator==(const airport&) const;
	//Precondition: Intakes an airport's ID and name, etc.
	//Postcondition: Compares the identifiers of two airports 
	//to determine if they are equal, and if so, returns true.

	bool operator<(const airport&) const;
	//Precondition: Intakes an airport's ID and name, etc.
	//Postcondition: Returns true if the compared arguments
	//(identifiers) are not equal.  Meaning the implicit argument
	//is less than the explicit one.
	
	bool operator>(const airport&) const;
	//Precondition: Intakes an airport's ID and name, etc.
	//Postcondition: Returns true if the compared arguments
	//(identifiers) are not equal.  Meaning the implicit argument
	//is greater than the explicit one.

private:
	char name[MAX_NAME];
	char identifier[MAX_ID];
	runway runwy;
};
