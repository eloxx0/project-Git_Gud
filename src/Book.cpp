#include  "../include/Book.h"

Book::Book():name{""}, surname{""}, title{""},available{true}, isbn{}, date{} {}
//gli ultimi due dati membro essendo udt richiamo il costruttore vuoto definito nella loro classe, i primi 3 dati membro sono stringhe vuote
//poichè costruito dal costruttore di base settiamo la variabile available a true in modo che se andiamo 
//a utilizzare Bookshelf(10) quando vado a printare la libreria risulta composta da libri senza titolo nome e cognome
//ma con un codice isbn valido

Book::Book(std::string nome, std::string cognome, std::string titolo, Isbn isbn): name{nome}, surname{cognome}, title{titolo}, isbn{isbn}{
	available=true;
}

Book::Book(std::string nome, std::string cognome, std::string titolo, Isbn isbn, Date data): name{nome}, surname{cognome}, title{titolo}, date{data}, isbn{isbn}{
	available=true;
}

void Book::set_availability(bool b){
    available = b;
}

void borrow_book(Book& book){
    if(book.getAvailability()){
        std::cout << "il libro è stato preso in prestito" << std::endl;
        book.set_availability(false);
        return;
    }
    std::cout << "il libro non è disponibile per essere preso in prestito" << std::endl;

}

void return_book(Book& book){
    if(!book.getAvailability()){
        std::cout << "il libro è stato restituito" << std::endl;
        book.set_availability(true);
        return;
    }
    std::cout << "il libro è già disponibile" << std::endl;

}

bool Book::operator==(const Book& b)
{
    if(isbn == b.isbn) return true;
    return false;
}

bool Book::operator !=(const Book& b)
{
    if(isbn != b.isbn) return true;
    return false;
}

std::ostream& operator<<(std::ostream& os, const Book& b)
{
    return os<<"Titolo: "<<b.getTitle()<<"\nAutore: "<<b.getName()<<" "<<b.getSurname()<<"\nISBN: "<<b.getIsbn()<<"\nData di pubblicazione: "<<b.getDate();
}
