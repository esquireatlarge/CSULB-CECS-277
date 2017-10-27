//Filename:  towered.cpp
//Author:  Esquire At Large
//Date written:  Wednesday, October 8th, 2008.
//Program Description:  This code file contains class definitions
//for a towered airport, which is derived from the airport
//class.

#include "towered.h"

ostream& operator<<(ostream& trout, const Towered& t){
	t.print(trout);
	return trout;
}

Towered::Towered(char *apprch, const char* nm,
		const char* id, const char* num, int len):airport(nm, id, num, len){
			approach = NULL;
			setApproach(apprch);
}

Towered::Towered(const Towered& t):airport(t){
	setApproach(t.approach);
}

Towered::~Towered(){
	delete [] approach;
}

void Towered::setApproach(const char *app){
	//if(approach != NULL) delete [] approach;
	approach = new char[strlen(app) + 1];
	assert(approach != NULL);
	strcpy(approach, app);
}

const Towered& Towered::operator=(const Towered& rhs){
	if(this != &rhs){
		setApproach(rhs.approach);
	}
	else
		cerr << "Error:  Self assignment! (towered.cpp)" << endl;

	return *this;
}

ostream& Towered::print(ostream& trout) const{
	airport::print(trout);
	trout << approach << endl;

	return trout;
}

char* Towered::getApproach() const{
	return approach;
}