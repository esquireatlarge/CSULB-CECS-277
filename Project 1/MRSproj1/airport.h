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

const int MAX_NAME = 25;
const int MAX_ID = 4;

class airport{
	friend ostream& operator<<(ostream&, const airport&);

public:
	airport(const char* nm = "Defaulto Airport", const char* id = "DFT",
		const char* num="007", int len = 30);
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
	
	~airport();
	//Destructor
	//Precondition:  None.
	//Postcondition:  Destroys dynamically allocated airport members.

	const airport& operator=(const airport& rhs);
	//Precondition:  Intakes the address of an airport instance.
	//Postcondition:  Assigns the members of the airport class to
	//the other instance of airport.

	void setAirportName(const char* nm = "Defaulto Airport");
	//Precondition:  Intakes name of airport.
	//Postcondition:  If there are no invalid characters for the name of
	//the airport, it is assigned to the name field.

	void setAirportID(const char* id = "DFT");
	//Precondition:  Intakes an airport's identifier.
	//Postcondition:  If nothing is wrong with the identifier, it is
	//assigned to the identifier field.
	
	void setNumber(const char* num = "70L");
	//Precondition:  Intakes a character array for the runway number. 
	//Postcondition:  Performs actions to copy character array into
	//runway member.
	
	void setLength(int len= 300);
	//Precondition: Intakes an integer for runway length.
	//Postcondition: Performs actions to copy integer into
	//runway member.
	
	const char* getAirport() const;
	//Precondition:  None.
	//Postcondition:  Returns the name and ID of an airport.


private:
	char* name;
	char* identifier;
	runway runwy;
};
