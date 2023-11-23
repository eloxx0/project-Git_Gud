#ifndef BOOK
#define BOOK

#include "Date.h"
#include <iostream>
#include "Year.h"
#include <string>
#include "Isbn.h"

class Book{

	private:
		
	std::string title;
	std::string name;
	std::string surname;
	int date;
	bool onloan;
	bool available;
	
	public:
	
	Book(std::string nome, std::string cognome, std::string titolo);
	Book(std::string nome, std::string cognome, std::string titolo, int data);
	
	//getter
	std::string getTitle(void) const;
	std::string getName(void) const;
	std::string getSurname(void) const;
	int getDate(void) const;
	
};

#endif // BOOK
