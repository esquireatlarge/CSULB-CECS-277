//Filename:  nontowered.cpp
//Author:  Esquire At Large
//Date written:  Monday, October 13th, 2008.
//Program Description:  This code file contains class definitions
//for a nontowered airport, which is derived from the airport
//class.

#include "nontowered.h"

ostream& operator<<(ostream& trout, const Nontowered& nt){
	nt.print(trout);
	return trout;
}

Nontowered::Nontowered(const double freq, const char* nm, const char* id,
		const char* num, int len):airport(nm, id, num, len){
	setCTAFFreq(freq);
}

void Nontowered::setCTAFFreq(const double freq){
	ctaf = freq;
}

const Nontowered& Nontowered::operator=(const Nontowered& rhs){
	if(this != &rhs){
		ctaf = rhs.ctaf;
	}

	return *this;
}

ostream& Nontowered::print(ostream& trout) const{
	airport::print(trout);
	trout << setw(22) << ctaf << endl;

	return trout;
}

double Nontowered::getCTAF() const{
	return ctaf;
}