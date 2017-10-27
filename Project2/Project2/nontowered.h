//Filename:  nontowered.h
//Author:  Matt Sguerri
//Date written:  Monday, October 13th, 2008.
//Program Description:  This header file contains a class
//for a nontowered airport, which is derived from the airport
//class.

#pragma once
#include <iostream>
#include <assert.h>
#include "airport.h"
using namespace std;

class Nontowered:public airport{
	friend ostream& operator<<(ostream& trout, const Nontowered& nt);
	//Precondition:  Intakes a reference to a nontowered airport.
	//Postcondition:  Displays the frequency of the nontowered airport.
public:
	Nontowered(const double freq, const char* nm = "Defaulto Airport", const char* id = "DFT",
		const char* num="007", int len = 300);
	//Constructor.
	//Precondition:  Intakes the CTAF frequency as
	//a double.
	//Postcondition:  Creates a nontowered airport.

	void setCTAFFreq(const double freq = 0.0);
	//Precondition: Intakes a double for approach.
	//Postcondition: Sets the CTAF frequency.

	const Nontowered& operator=(const Nontowered& rhs);
	//Precondition:  Intakes the address of an towered airport instance.
	//Postcondition:  Assigns the members of the towered airport class to
	//the other instance of a towered airport.

	virtual ostream& print(ostream&) const;
	//Precondition:  The output buffer.
	//Postcondition:  Displays the CTAF frequency.

	double getCTAF() const;
	//Precondition:  None.
	//Postcondition:  Returns the CTAF frequency.

private:
	double ctaf; //CTAF frequency.
};