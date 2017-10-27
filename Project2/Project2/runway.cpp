//Filename: runway.cpp
//Author:  Esquire At Large
//Date written:  Wednesday, September 17th, 2008.
//Class description:  Contains coding for methods in the runway
//header file.

#include "runway.h"

ostream& operator<<(ostream& trout, const runway& run){
	trout << " " << setw(4) << run.number << right << setw(7)
		<< " " << run.length << " " << setw(15);

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
	length = run.length;
}

const runway& runway::operator=(const runway& rhs){
	if(this != &rhs){
		setNumber(rhs.number);
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

int runway::getLength() const{
	return length;
}

char* runway::getNum() const{
	return number;
}
