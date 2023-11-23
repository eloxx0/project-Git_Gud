#include  "../include/Book.h"

Book::Book(std::string nome, std::string cognome, std::string titolo): name{nome}, surname{cognome}, title{titolo}{}

Book::Book(std::string nome, std::string cognome, std::string titolo, int data): name{nome}, surname{cognome}, title{titolo}, date{data}{}

std::string Book::getTitle(void){
	return title;
}

std::string Book::getName(void){
	return name;
}

std::string Book::getSurname(void){
	return surname;
}

int Book::getDate(void){
	return date;
}
