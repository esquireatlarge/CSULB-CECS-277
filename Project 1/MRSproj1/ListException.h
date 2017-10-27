//Filename:  ListException.h
//Author:  Esquire At Large
//Date written: March 3rd, 2008
//Class Description:  Allows for exceptions that might occur in the list
//to be "throw" to the user.

// ListException.h


#pragma once

#include <cstring>
using namespace std;

class ListException
{
public:
	ListException(const char msg[] = "") 
	{
		strcpy(message, msg);
	}

const char* what()
{
	return message;
}
private:
	char message[50];
};


