#ifndef ISBN_H
#define ISBN_H

#include <string>
#include <vector>

//ISBN è un codice a 13 cifre che identifica univocamente un libro. Presenta un 
//prefisso di tre cifre prefissato e una cifra di controllo finale che 
//viene calcolata a partire dalle altre cifre e verifica che il codice
//isbn sia valido
class Isbn{
    private:
        std::string isbn;

    public:
    //costruttore di base. Genera un isbn casuale che rispetta lo standard
    Isbn();
    //costruttore. Lancia l'eccezione Invalid_Isbn_Argument() se la stringa non rispetta lo standard
    Isbn(std::string isbn);

    class Invalid_Isbn_Argument{};

    //ritorna la stringa dell'isbn
    std::string get_isbn() const{
        return isbn;
    }

    //verifica se due isbn sono uguali. Restituisce true se contengono le stesse cifre, false
    //altrimenti. I trattini vengono considerati: se due isbn con le stesse cifre
    //numeriche presentano trattini in posizione diverse, risultano diversi
    bool operator==(const Isbn& i);

    //verifica se due isbn sono diversi. Restituisce false se contengono le stesse cifre,
    //true altrimenti
    bool operator!=(const Isbn& i);
};
//genera un isbn casuale che rispetta lo standard ISBN
std::string generate_isbn();

//verifica che la stringa sia valida secondo lo standard. Ritorna true se è valido, false se non è valido
bool string_isbn_valid(std::string s);

//dato un vettore di interi, dalle prime 12 cifre ricava una potenziale cifra di controllo valida
//per in isbn
int isbn_control_value(std::vector<int>& s);

#endif //ISBN_H
