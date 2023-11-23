#include  "../include/Book.h"

Book::Book(std::string nome, std::string cognome, std::string titolo): name{nome}, surname{cognome}, title{titolo}{
	available=true;
}

Book::Book(std::string nome, std::string cognome, std::string titolo, int data): name{nome}, surname{cognome}, title{titolo}, date{data}{
	available=true;
}

std::string Book::getTitle(void) const{
	return title;
}

std::string Book::getName(void) const{
	return name;
}

std::string Book::getSurname(void) const{
	return surname;
}

int Book::getDate(void) const{
	return date;
}

bool Book::loan(void){
	available=false;
	
	return available;
}

bool Book::present(void){
	available=true;
	
	return available;
}
