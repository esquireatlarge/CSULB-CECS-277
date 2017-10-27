//Filename:  towered.h
//Author:  Matt Sguerri
//Date written:  Wednesday, October 8th, 2008.
//Program Description:  This header file contains a class
//for a towered airport, which is derived from the airport
//class.

#pragma once
#include <iostream>
#include <assert.h>
#include "airport.h"
using namespace std;

class Towered:public airport{
	friend ostream& operator<<(ostream& trout, const Towered& t);
	//Precondition:  Intakes a constant towered airport reference.
	//Postcondition:  Passes the output buffer to the print function.

public:
	Towered(char* apprch, const char* nm = "Defaulto Airport",
		const char* id = "DFT", const char* num="007", int len = 30);
	//Constructor.
	//Precondition:  Intakes the primary approach.
	//Postcondition:  Creates a towered airport.

	Towered(const Towered&);
	//Copy constructor.
	//Precondition:  Intakes a reference to a Towered airport.
	//Postcondition:  Copies the Towered airport.

	~Towered();
	//Destructor.
	//Precondition:  None.
	//Postcondition:  Destroys the approach, reallocating memory.

	void setApproach(const char* app = "Klingon");
	//Precondition: Intakes a character array for approach.
	//Postcondition: Sets the primary instrument approach.

	const Towered& operator=(const Towered& rhs);
	//Precondition:  Intakes the address of an towered airport instance.
	//Postcondition:  Assigns the members of the towered airport class to
	//the other instance of a towered airport.

	virtual ostream& print(ostream&) const;
	//Precondition:  The output buffer.
	//Postcondition:  Displays the primary instrument approach.

	char* getApproach() const;
	//Precondition:  None.
	//Postcondition:  Returns the primary instrument approach.

private:
	char* approach; //Instrument approach.
};