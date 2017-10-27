//Filename:  airport.cpp
//Author:  Matt Sguerri
//Date written:  Tuesday, October 28th, 2008.
//Program Description:  This code file contains the function 
//definitions for the airport class.

#include "airport.h"

ostream& operator<<(ostream& trout, const airport& arpt){	
	trout << left << setw(3) << arpt.identifier << " " <<setw(29)
		<< left << arpt.name << arpt.runwy;

	return trout;
}

airport::airport(const char nm[], const char id[], const int num):runwy(num){
					 setAirportID(id);
					 setAirportName(nm);
}

airport::airport(const airport & a):runwy(a.runwy){
	strcpy(name, a.name);
	strcpy(identifier, a.identifier);
}

//airport::~airport(){
//	delete [] name;
//	delete [] identifier;
//}

const airport& airport::operator =(const airport &rhs){
	if(this != &rhs){
		setAirportID(rhs.identifier);
		setAirportName(rhs.name);
		runwy = rhs.runwy;
	}
	else
		cerr << "Error:  Self assignment! (airport.cpp)" << endl;

	return *this;
}

void airport::setAirportID(const char id[]){
	strcpy(identifier, id);
}

void airport::setAirportName(const char nm[]){
	strcpy(name, nm);
}

void airport::setRunwayNumber(const int num){
	runwy.setNumber(num);
}

const char* airport::getIdentifier() const{
	return identifier;
}

const char* airport::getName() const{
	return name;
}

const int airport::getRunwayNumber() const{
	return runwy.getNum();
}

bool airport::operator==(const airport& a) const
//Postcondition: Returns true if the compared arguments are equal to one another.
{
	if(strcmp(identifier, a.identifier)==0)
		return true;  //Discard 
	else
		return false; //Keep
}

bool airport::operator<(const airport& a) const
//Postcondition:  Returns true if the compared arguments (species then name)
//are not equal.  Meaning the implicit argument is less than the explicit
//argument.
{
	if(strcmp(identifier, a.identifier) < 0){
		return true;
	}
	else 
		return false;
}

bool airport::operator>(const airport& a) const
//Postcondition:  Returns true if the compared arguments (species then name)
//are not equal.  Meaning the implicit argument is less than the explicit
//argument.
{
	if(strcmp(identifier, a.identifier) > 0){
		return true;
	}
	else 
		return false;
}
