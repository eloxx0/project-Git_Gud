#ifndef BOOK
#define BOOK

#include "Date.h"
#include <iostream>
#include "Year.h"
#include <string>

class Book{

	private:
		
	std::string title;
	std::string name;
	std::string surname;
	int date;
	bool onloan;
	bool available;
	
	public:
	
	std::string getTitle(void);
	std::string getName(void);
	std::string getSurname(void);
	int getDate(void);
	
};

#endif // BOOK
