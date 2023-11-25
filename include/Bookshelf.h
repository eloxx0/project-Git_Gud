#ifndef BOOKSHELF
#define BOOKSHELF

#include "../MyVector/include/MyVector.h"
#include <initializer_list>
#include <iostream>
#include "Book.h"


class Bookshelf{
    private:
    int length;
    //la capacità indica il numero di elementi allocati. E' diverso dalla lunghezza, che dipende dal numero di elementi inseriti
    int capacity;
    //puntatore al primo elemento
    Book *elem;

    public:

    class Invalid_position{};

    //costruttore di base. A differenza del costruttore a cui passo la lunghezza, alloca dello spazio ma senza inizializzare gli elementi
    Bookshelf();
    //inizializza a 0 e alloca lo spazio, in modo da avere length elementi accessibili senza errori (per esempio con il safe_set o safe_get)
    explicit Bookshelf(int length);

    //caso in cui voglio inizializzare un vettore tramite una lista di libri
    Bookshelf(std::initializer_list<Book> list);

    Bookshelf(const Bookshelf& v);

    //costruttore che accetta come parametro un riferimento al rvalue
    Bookshelf(Bookshelf&& v);

    //ritorna la lunghezza del vettore definito
    int size() const {
        return length;
    }

    //ritorna il numero di elementi allocati dal vettore
    int dimension() const{
        return capacity;
    }

    //operatore di accesso agli elementi del vettore. Ritorna l'elemento in posizione
    //richiesta dall'indice inserito
    //ritorna una REFERENCE in modo da permettere anche l'accesso in scrittura!!
    Book& operator[](int a);

    //in questo caso non va a modificare il vettore di partenza ma
    //ne restituisce un altro poichè è const
    //ritorna solo il libro e non una reference in modo che non sia possibile
    //accedere in scrittura al vettore (e quindi lo mantiene costante)
    Book operator[](int a) const;

    Bookshelf& operator=(const Bookshelf& v);

    //assegnamento move
    Bookshelf& operator=(Bookshelf&& v);

    //controlla che la posizione nell'array sia valida, se si inserisce il valore book nella
    //posizione corretta
    //accede all'elemento in posizione pos se è entro i limiti DI LUNGHEZZA del vettore, non di capacità
    //in modo da evitare errori logici dati dalla presenza di elementi assegnati un posizioni "lontane"
    //con distanza tra loro maggiore della lunghezza del vettore

    void safe_set(int pos, Book a);

    //posso applicarla a vettori costanti
    //ritorna l'elemento in posizione pos se è entro i limiti DI LUNGHEZZA del vettore, non di capacità
    const Book& safe_get(int pos) const;

    //ritorno una reference per permettere l'accesso in scrittura
    Book& safe_get(int pos);

    //resiza il vettore alla lunghezza indicata come parametro. Se la lunghezza è minore,
    //c'è una perdita di dati, se invece la lunghezza indicata è maggiore della capacity viene allocato
    //nuovo spazio
    //attenzione che il resize oltre ad allocare eventualmente nuovi elementi, anche
    //li inizializza, quindi porta length ad aumentare!
    void resize(int new_l);

    //se new_l è maggiore di length ma minore della capacità aumenta length assegnando ai nuovi
    //elementi il valore val (o 0 nel caso in cui non viene specificato)
    void resize(int new_l, Book val);

    //imposta la capacità del vettore, e cioè alloca la memoria necessaria per permettere di salvare
    //n elementi senza modificare la lunghezza del vettore
    void reserve(int size);
    
    //aggiunge il double a in fondo al vettore, aumentando lo spazio allocato in modo
    //dinamico 
    void push_back(Book a);

    //rimuove l'ultimo elemento inserito e riduce la dimensione
    //se il vettore è vuoto potrebbe causare errori in esecuzione
    void pop_back();

    //il metodo at ritorna una reference all'elemento in posizione vector
    //controllando che sia all'interno della lunghezza
    //lancia Invalid_position() se si cerca di accedere al di fuori dei
    //bounds del vettore
    Book& at(int pos);

    //permette di accedere all'elemento di un vettore costante ma senza
    //permettere di modificarlo (infatti ritorna una const reference e non la reference)
    const Book& at(int pos) const;

    ~Bookshelf(){
        //usando le parentesi mi riferisco a tutto lo spazio di memoria allocato con new[] e puntato da 
        //elem
        delete[] elem;
    }

};

#endif // BOOKSHELF
