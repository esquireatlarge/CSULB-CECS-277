//Filename: runway.cpp
//Author:  Matt Sguerri
//Date written:  Wednesday, September 17th, 2008.
//Class description:  Contains coding for methods in the runway
//header file.

#include "runway.h"

ostream& operator<<(ostream& trout, const runway& run){
	trout << " " << setw(4) << run.number << setw(14)
		<< " "  << run.length
		<< endl;

	return trout;
}

runway::runway(const char* num, int len){
	number = NULL;
	length = 0;
	setNumber(num);
	setLength(len);

}

runway::runway(const runway& run){
	number = new char[strlen(run.number)];
	strcpy(number, run.number);
}

const runway& runway::operator=(const runway& rhs){
	if(this != &rhs){
		delete [] number;
		number = new char[strlen(rhs.number) + 1];
		strcpy(number, rhs.number);
		length = rhs.length;
	}
	else
		cerr << "Error:  Self assignment! (runway.cpp)" << endl;

	return *this;
}

void runway::setNumber(const char* num){
	if(number != NULL) delete [] number;
	number = new char[strlen(num) + 1];
	assert(number != NULL);
	strcpy(number, num);
}

void runway::setLength(int len){
	if(len < 0){
		cerr << "Runway length was negative -- reset to zero."
			<< endl;
		length = 0;
	}
	else
		length = len;
}

runway::~runway(){
	delete [] number;
}
