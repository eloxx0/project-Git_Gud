#include "../include/Bookshelf.h"

const int BASE_CAPACITY = 5;

Bookshelf::Bookshelf(int length) : capacity{length + BASE_CAPACITY}, elem{new Book[length + BASE_CAPACITY]}, length{length}{
    //inizializza a zero gli elementi, l'unico modo per farlo è richiamare il costruttore vuoto di Book

    //******non serve chiamare il costruttore di base, viene fatto in automatico dall'operatore new!!*******
}

Bookshelf::Bookshelf(std::initializer_list<Book> lst) : capacity{static_cast<int>(lst.size())}, elem{new Book[lst.size()]}, length{static_cast<int>(lst.size())}{
    //copia la lista
    std::copy(lst.begin(), lst.end(), elem);
}

//inizializza libreria vuota se non imposto la lunghezza
//uso una capacità di base che alloco per evitare di dover reallocare spazio
Bookshelf::Bookshelf() : capacity{BASE_CAPACITY}, elem{new Book[BASE_CAPACITY]}, length{0}{}

//creo un costruttore di copia per permettere una deep copy, e cioè che gli elementi
//tra i due vettori non siano condivisi ma siano proprio copiati in altri indirizzi
//di memoria
Bookshelf::Bookshelf(const Bookshelf& v) : capacity{v.capacity}, elem{new Book[v.capacity]}, length{v.length}{
    std::copy(v.elem, v.elem + v.capacity, elem);
}

//creo un costruttore di move che permette di spostare un vettore
//uso una rvalue reference (&&) che è la sintassi che indica il riferimento
//ad un rvalue in modo da permettere di spostare le risorse senza usare la copia
//e utilizzare un rvalue come un lvalue
Bookshelf::Bookshelf(Bookshelf&& v) : capacity{v.capacity}, elem{v.elem}, length{v.length}{
    //elimina v
    //questo impedisce al distruttore di liberare più volte le risorse
    v.length = 0;
    v.capacity = 0;
    v.elem = nullptr;
}

//assegnamento move, serve per assegnare un rvalue senza usare una copia
//non posso usare const Bookshelf&& come parametro perchè viene modificato
Bookshelf& Bookshelf::operator=(Bookshelf&& v){
    //gestisco il caso in cui cerco di assegnare l'oggetto a sè stesso: in questo
    //modo non rischio di deallocare lo spazio che mi serviva
    if(this != &v){
        //dealloco prima lo spazio allocato dall'oggetto chiamante, poichè devo riassegnarlo
        delete[] elem;
        capacity = v.capacity;
        elem = v.elem;
        length = v.length;
        
        v.length = 0;
        v.capacity = 0;
        v.elem = nullptr;
    }
    //dato un rvalue in assegnazione restituisce un lvalue
    return *this;
}

//assegnamento di copia, fa una deep copy(stessi elementi in diverse posizioni in memoria) e 
//la assegna all'oggetto chiamante
//se non faccio la deep copy viene generato un errore in compilazione poichè il distruttore
//viene chiamato due volte sullo stesso spazio di memoria
Bookshelf& Bookshelf::operator=(const Bookshelf& v){
    //uso il costruttore di copia, poi alla fine dello scope v2 viene 
    //deallocato dal distruttore
    Bookshelf v2 = Bookshelf(v);
    //dealloco lo spazio allocato dall'oggetto chiamante
    delete[] elem;
    elem = v2.elem;
    capacity = v2.capacity;
    length = v2.length;
    //non posso usare delete perchè v2 punta allo stesso spazio allocato a cui punta elem. Per fare in modo
    //che non ci siano due puntatori che puntano alla stessa memoria devo riassegnarlo a null
    v2.elem = nullptr;
    v2.capacity = 0;
    v2.length = 0;
    return *this;
}

//nel caso in cui lo utilizzo per assegnare elementi al di fuori degli elementi inizializzati(quindi compresi nella lunghezza) ha un 
//comportamento indefinito, non vengono considerati all'interno della lunghezza dell'array anche se sono interni allo spazio allocato
Book& Bookshelf::operator[](int a){
    return elem[a];
}


Book Bookshelf::operator[](int a) const{
    return elem[a];
}

//il safe_set non va a modificare la lunghezza del vettore
void Bookshelf::safe_set(int pos, Book a){
    if(pos >= length || pos < 0){
        throw Invalid_position();
    }

    elem[pos] = a;
}

const Book& Bookshelf::safe_get(int pos) const{
    if(pos >= length || pos < 0){
        throw Invalid_position();
    }

    return elem[pos];
}

Book& Bookshelf::safe_get(int pos){
    if(pos >= length || pos < 0){
        throw Invalid_position();
    }
    
    //ritorna una reference che punta all'elemento in posizione pos del vettore
    return elem[pos];
    
}


void Bookshelf::resize(int new_l){
    //il resize opera in tre modi diversi: se la nuova lunghezza è minore della lunghezza vecchia, gli elementi in più vengono eliminati e il vettore viene 
    //ridotto(senza influire sulla capacità), se invece la nuova lunghezza è maggiore, gli elementi in più vengono inizializzati a 0 oppure a un valore determinato
    //(per il metodo resize(int new_l, Book a)). Se invece new_l è maggiore della capacità, alloco nuovo spazio. Lo spazio allocato è maggiore della new_length
    //per evitare di dover reallocare al primo push_back()

    //nel caso in cui new_l è minore della capacità o della lunghezza, non vado a modificare la capacità, ma devo fare in modo che gli elementi in più (nel
    //caso in cui new_l è minore di length) vengano distrutti, e che gli elementi compresi tra new_l e capacity NON siano inizializzati ma solo allocati
    //per questo non posso utilizzare il costruttore Bookshelf(int length), poichè quando gli passo la lunghezza vado anche ad inizializzare i valori

    if(new_l <= capacity){
        Book* temp = new Book[capacity];
        //solo i primi new_l elementi sono copiati. Se new_l è maggiore di length, vengono copiati valori a caso che successivamente
        //vengono inizializzati nel for
        std::copy(elem, elem + new_l, temp);
        
        //******NON serve inizializzare i nuovi elementi poichè per come funziona l'operatore new,
        //quando va ad allocare nuovo spazio dinamicamente, utilizza il costruttore di base
        //per inizializzare gli elementi all'interno dello spazio di memoria allocata
        
        delete[] elem;
        length = new_l;
        elem = temp;
    }
    else{
        //in questo caso devo allocare nuovo spazio
        //il reserve copia in automatico gli elementi, ma devo inizializzare gli elementi in più
        reserve(new_l + BASE_CAPACITY);
        
        //****Analogamente al caso precedente, non serve inizializzare gli elementi in più poichè vengono inizializzati
        //usando il costruttore di default quando viene chiamato l'opteratore new
        length = new_l;
    }

}

void Bookshelf::resize(int new_l, Book& val){
    if(new_l <= capacity){
        Book* temp = new Book[capacity];
        //solo i primi new_l elementi sono copiati. Se new_l è maggiore di length, vengono copiati valori a caso che successivamente
        //vengono inizializzati nel for
        std::copy(elem, elem + new_l, temp);
        
        //in questo caso bisogna inizializzare gli elementi
        for(int i = length; i < new_l; i++){
            temp[i] = val;
        }
        
        delete[] elem;
        length = new_l;
        elem = temp;
    }
    else{
        //in questo caso devo allocare nuovo spazio
        //il reserve copia in automatico gli elementi, ma devo inizializzare gli elementi in più
        reserve(new_l + BASE_CAPACITY);
        
        //assegno ai nuovi elementi il valore val
        for(int i = length; i < new_l; i++){
            elem[i] = val;
        }
        length = new_l;
    }
}

void Bookshelf::reserve(int size){
    if(size <= capacity){
        return;
    }
    Book* temp = new Book[size]; 
    /* std::copy(elem, elem + capacity, temp); */
    for(int i = 0; i < capacity; i++){
        temp[i] = elem[i];
    }
    delete[] elem;
    capacity = size;
    elem = temp;


}

void Bookshelf::push_back(Book a){
    //nel caso in cui la lunghezza è uguale alla capacità alloco nuovo spazio
    //per evitare di dover allocare nuovo spazio ogni volta che uso il push_back, alloco 
    //il doppio rispetto alla capacità precedente

    if(length == capacity){
        reserve(capacity * 2);
    }
    elem[length++] = a;
}

//uso un resize in modo che non solo venga ridotta la dimensione ma anche venga eliminato
//l'elemento
void Bookshelf::pop_back(){
    resize(length - 1);

}

Book& Bookshelf::at(int pos){
    return safe_get(pos);
}

const Book& Bookshelf::at(int pos) const{
    return safe_get(pos);
}







