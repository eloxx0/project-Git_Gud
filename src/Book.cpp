#include  "../include/Book.h"

Book::Book():name{""}, surname{""}, title{""},available{true}, isbn{}, date{} {}
//gli ultimi due dati membro essendo udt richiamo il costruttore vuoto definito nella loro classe, i primi 3 dati membro sono stringhe vuote

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
        std::cout << "il libro è stato preso in prestito";
        book.set_availability(false);
        return;
    }
    std::cout << "il libro non è disponibile per essere preso in prestito";

}

void return_book(Book& book){
    if(!book.getAvailability()){
        std::cout << "il libro è stato restituito";
        book.set_availability(true);
        return;
    }
    std::cout << "il libro è già disponibile";

}
