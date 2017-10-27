//Filename:  runway.h
//Author:  Esquire At Large
//Date written:  Wednesday, September 17th, 2008
//Class description:  This header contains function declarations
//for the runway class, which is a member of the airport class.

#include <iostream>
#include <cstring>
#include <assert.h>
#include <iomanip>
using namespace std;
#pragma once

const int MAX_NUM = 4;

class runway{
	friend ostream& operator<<(ostream&, const runway&);
	//Precondition:  Intakes an instance of the ostream class 
	//and runway class.
	//Postcondition:  Displays the runway members.
public:
	runway(const int num = 12);
	//Precondition:  Constructor.
	//Postcondition:  Passes parameters to respective functions.
	
	runway(const runway&);
	//Precondition:  Copy constructor, intakes a reference of runway.
	//Postcondition:  Performs appropriate copy for runway class.
	
	//Runway no longer requires a destructor because of integer values.
	//~runway();
	//Precondition:  Destructor, intakes nothing.
	//Postcondition:  Destroys runway's dynamically allocated members.
	
	const runway& operator=(const runway& rhs);
	//Precondition:  Intakes an instance of runway.
	//Postcondition:  Assigns the members of runway to another instance.

	void setNumber(const int num = 12);
	//Precondition:  Intakes a character array of the runway number.
	//Postcondition:  Copies the num string to the number data member.

	void setLength(int len);
	//Precondition:  Intakes an integer for the runway length.
	//Postcondition:  Assigns the value of the len integer to the data 
	//member length.

	const int getNum() const;
	//Precondition:  None.
	//Postcondition:  Returns the runway number.

private:
	int number;
};
