#ifndef BOOK_H
#define BOOK_H

#include "Date.h"
#include <ostream>
#include "Isbn.h"

class Book{

	private:
		
	std::string title;
	std::string name;
	std::string surname;
	Date date;
    Isbn isbn;
	bool available;
	
	public:
	
    //quando un oggetto di tipo book viene creato, la variabile available viene assegnata true, poichè il libro
    //risulta come disponibile per essere preso in prestito
    Book();

	Book(std::string nome, std::string cognome, std::string titolo, Isbn isbn);

	Book(std::string nome, std::string cognome, std::string titolo, Isbn isbn, Date data);
	
	//getter
	std::string getTitle(void) const{
        return title;
    }
	std::string getName(void) const{
        return name;
    }
	std::string getSurname(void) const{
        return surname;
    }
	Date getDate(void) const{
        return date;
    }
    bool getAvailability() const{
        return available;
    }
    Isbn getIsbn() const{
        return isbn;
    }
    //permette di cambiare lo stato di disponibilità di un libro
    void set_availability(bool b);

    //overload dell'operatore ==. Confronta due oggetti di tipo Book in base al codice ISBN
    bool operator==(const Book& b);

    bool operator !=(const Book& b);
	
	
};
//permette di prendere in prestito un libro e quindi di cambiare la sua disponibilità
void borrow_book(Book& book);

void return_book(Book& book);

std::ostream& operator<<(std::ostream& os, const Book& b);

#endif // BOOK_H
