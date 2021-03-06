//Filename:  airport.cpp
//Author:  Esquire At Large
//Date written:  Wednesday, September 17th, 2008.
//Program Description:  This file contains the function 
//definitions for the airport class.

#include "airport.h"

ostream& operator<<(ostream& trout, const airport& arpt){	
	arpt.print(trout);

	return trout;
}

airport::airport(const char *nm, const char *id, const char* num,
				 int len):runwy(num,len){
					 identifier = NULL;
					 name = NULL;
					 setAirportID(id);
					 setAirportName(nm);
}

airport::airport(const airport & a):runwy(a.runwy){
	name = new char[strlen(a.name) + 1];
	assert(name != NULL);
	strcpy(name, a.name);
	identifier = new char[strlen(a.identifier) +1 ];
	assert(identifier != NULL);
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
		runwy = rhs.runwy;
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

void airport::setNumber(const char* num){
	runwy.setNumber(num);
}

void airport::setLength(int length){
	runwy.setLength(length);
}

char* airport::getAirportID() const{
	return identifier;
}

char* airport::getAirportName() const{
	return name;
}


char* airport::getRunwayNumber() const{
	return runwy.getNum();
}

int airport::getRunwayLength() const{
	return runwy.getLength();
}



ostream& airport::print(ostream& trout) const{
	trout << left << setw(3) << identifier << " " <<setw(25)
		<< left << name << runwy;

	return trout;
}