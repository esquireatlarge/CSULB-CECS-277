//Filename:  airport.cpp
//Author:  Matt Sguerri
//Date written:  Tuesday, October 28th, 2008.
//Program Description:  This code file contains the function 
//definitions for the airport class.

#include "airport.h"

ostream& operator<<(ostream& trout, const airport& arpt){	
	trout << left << setw(3) << arpt.identifier << " " <<setw(29)
		<< left << arpt.name;

	return trout;
}

airport::airport(const char *nm, const char *id){
					 identifier = NULL;
					 name = NULL;
					 setAirportID(id);
					 setAirportName(nm);
}

airport::airport(const airport & a){
	name = new char[strlen(a.name) + 1];
	strcpy(name, a.name);
	identifier = new char[strlen(a.identifier) +1 ];
	strcpy(identifier, a.identifier);
}

airport::~airport(){
	delete [] name;
	delete [] identifier;
}

const airport& airport::operator =(const airport &rhs){
	if(this != &rhs){
		setAirportID(rhs.identifier);
		setAirportName(rhs.name);
	}
	else
		cerr << "Error:  Self assignment! (airport.cpp)" << endl;

	return *this;
}

void airport::setAirportID(const char* id){
	if(identifier != NULL) delete [] identifier;
	identifier = new char[strlen(id)+1];
	assert(identifier != NULL);
	strcpy(identifier, id);
}

void airport::setAirportName(const char *nm){
	if(name != NULL) delete [] name;
	name = new char[strlen(nm) + 1];
	assert(name != NULL);
	strcpy(name, nm);
}

const char* airport::getIdentifier() const{
	return identifier;
}

const char* airport::getName() const{
	return name;
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
