//Filename: runway.cpp
//Author:  Matt Sguerri
//Date written:  Wednesday, September 17th, 2008.
//Class description:  Contains coding for methods in the runway
//header file.

#include "runway.h"

ostream& operator<<(ostream& trout, const runway& run){
	trout << " " << setw(4) << run.number << right << setw(7)
		<< " " << setw(15);

	return trout;
}

runway::runway(const int num){
	setNumber(num);
}

runway::runway(const runway& run){
	number = run.number;
}

const runway& runway::operator=(const runway& rhs){
	if(this != &rhs){
		setNumber(rhs.number);
	}
	else
		cerr << "Error:  Self assignment! (runway.cpp)" << endl;

	return *this;
}

void runway::setNumber(const int num){
	number = num;
}

const int runway::getNum() const{
	return number;
}
