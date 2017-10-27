//Filename:  index.h
//Author:  Matt Sguerri
//Date written:  Wednesday, December 3rd, 2008.
//Program Description:  This header file contains the index
//class to be used for writing to the index file.

#include <iostream>
#include <cstring>
#pragma once
const int ID = 4;

class I{
	friend ostream& operator<<(ostream& trout, const I& index){
	//Precondition:  Intakes an instance of the ostream class and
	//a reference to the I class.
	//Postcondition:  Displays the contents of the class.
		trout << "<" << index.getID() << "," << index.getRRN() << ">"
			<< endl;

		return trout;
	}
public:
	//Default constructor
	I(){
		setRRN(-1);
		setID("def");
	}
	//Constructor.
	I(int rrn, char id[]){
		setRRN(rrn);
		setID(id);
	}

	void setRRN(const int rrn){
	//Precondition:  Intakes the RRN number.
	//Postcondition:  Sets the RRN number.
		RRN = rrn;
	}

	void setID(const char id[]){
	//Precondition:  Intakes ID.
	//Postcondition:  Sets the RRN number.
		strcpy(ID, id);
	}

	const int getRRN() const{
	//Precondition:  None.
	//Postcondition:  Returns the Relative Record
	//Number for use in locating byte position.
		return RRN;
	}

	const char* getID()  const{
	//Precondition:  None.
	//Postcondition:  Returns the ID, which is the
	//unique key for the set as well as the
	//identifier for the airport.
		return ID;
	}

	bool operator==(const I& index) const{
	//Precondition: Intakes the Index class's identifier.
	//Postcondition: Compares the identifiers of two airports
	//to determine if they are equal, and if so, returns true.
		if(strcmp(ID, index.getID())==0)
			return true;  //Discard 
		else
			return false; //Keep
	}

	bool operator<(const I& index) const{
	//Precondition:  Intakes the Index class's identifier.
	//Postcondition: Returns true if the compared argument
	//(identifier) are not equal.  Meaning the implicit argument
	//is less than the explicit one.
	if(strcmp(ID, index.getID()) < 0){
		return true;
	}
	else 
		return false;
	}
	
	bool operator>(const I& index) const{
	//Postcondition: Returns true if the compared arguments
	//(identifiers) are not equal.  Meaning the implicit argument
	//is greater than the explicit one.
		if(strcmp(ID, index.getID()) > 0){
		return true;
	}
	else 
		return false;
	}

private:
	//Unique key.
	char ID[4];
	//Relative record number.
	int RRN;
};