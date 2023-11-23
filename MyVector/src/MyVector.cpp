#include "../include/MyVector.h"
#include <iostream>
#include <initializer_list>

const int BASE_CAPACITY = 5;

MyVector::MyVector(int length) : capacity{length + BASE_CAPACITY}, elem{new double[length + BASE_CAPACITY]}, length{length}{
    //inizializza a zero gli elementi
    for(int i = 0; i < length; i++){
        elem[i] = 0;
    }
}

MyVector::MyVector(std::initializer_list<double> lst) : capacity{static_cast<int>(lst.size())}, elem{new double[lst.size()]}, length{static_cast<int>(lst.size())}{
    //copia la lista
    std::copy(lst.begin(), lst.end(), elem);
}

//inizializza vettore vuoto se non imposto la lunghezza
//uso una capacità di base che alloco per evitare di dover reallocare spazio
MyVector::MyVector() : capacity{BASE_CAPACITY}, elem{new double[BASE_CAPACITY]}, length{0}{}

//creo un costruttore di copia per permettere una deep copy, e cioè che gli elementi
//tra i due vettori non siano condivisi ma siano proprio copiati in altri indirizzi
//di memoria
MyVector::MyVector(const MyVector& v) : capacity{v.capacity}, elem{new double[v.capacity]}, length{v.length}{
    std::copy(v.elem, v.elem + v.capacity, elem);
}

//creo un costruttore di move che permette di spostare un vettore
//uso una rvalue reference (&&) che è la sintassi che indica il riferimento
//ad un rvalue in modo da permettere di spostare le risorse senza usare la copia
//e utilizzare un rvalue come un lvalue
MyVector::MyVector(MyVector&& v) : capacity{v.capacity}, elem{v.elem}, length{v.length}{
    //elimina v
    //questo impedisce al distruttore di liberare più volte le risorse
    v.length = 0;
    v.capacity = 0;
    v.elem = nullptr;
}

//assegnamento move, serve per assegnare un rvalue senza usare una copia
//non posso usare const MyVector&& come parametro perchè viene modificato
MyVector& MyVector::operator=(MyVector&& v){
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
MyVector& MyVector::operator=(const MyVector& v){
    //uso il costruttore di copia, poi alla fine dello scope v2 viene 
    //deallocato dal distruttore
    MyVector v2 = MyVector(v);
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
double& MyVector::operator[](int a){
    return elem[a];
}


double MyVector::operator[](int a) const{
    return elem[a];
}

//il safe_set non va a modificare la lunghezza del vettore
void MyVector::safe_set(int pos, double a){
    if(pos >= length || pos < 0){
        throw Invalid_position();
    }

    elem[pos] = a;
}

const double& MyVector::safe_get(int pos) const{
    if(pos >= length || pos < 0){
        throw Invalid_position();
    }

    return elem[pos];
}

double& MyVector::safe_get(int pos){
    if(pos >= length || pos < 0){
        throw Invalid_position();
    }
    
    //ritorna una reference che punta all'elemento in posizione pos del vettore
    return elem[pos];
    
}


void MyVector::resize(int new_l){
    //il resize opera in tre modi diversi: se la nuova lunghezza è minore della lunghezza vecchia, gli elementi in più vengono eliminati e il vettore viene 
    //ridotto(senza influire sulla capacità), se invece la nuova lunghezza è maggiore, gli elementi in più vengono inizializzati a 0 oppure a un valore determinato
    //(per il metodo resize(int new_l, double a)). Se invece new_l è maggiore della capacità, alloco nuovo spazio. Lo spazio allocato è maggiore della new_length
    //per evitare di dover reallocare al primo push_back()

    //nel caso in cui new_l è minore della capacità o della lunghezza, non vado a modificare la capacità, ma devo fare in modo che gli elmementi in più (nel
    //caso in cui new_l è minore di length) vengano distrutti, e che gli elementi compresi tra new_l e capacity NON siano inizializzati ma solo allocati
    //per questo non posso utilizzare il costruttore MyVector(int length), poichè quando gli passo la lunghezza vado anche ad inizializzare i valori

    if(new_l <= capacity){
        double* temp = new double[capacity];
        //solo i primi new_l elementi sono copiati. Se new_l è maggiore di length, vengono copiati valori a caso che successivamente
        //vengono inizializzati nel for
        std::copy(elem, elem + new_l, temp);
        //inizializzo gli elementi in più nel caso in cui new_l sia maggiore di length
        for(int i = length; i < new_l; i++){
            temp[i] = 0;
        }
        //disalloco lo spazio a cui punta elem per riassegnarli il puntatore temp
        delete[] elem;
        length = new_l;
        elem = temp;
    }
    else{
        //in questo caso devo allocare nuovo spazio
        //il reserve copia in automatico gli elementi, ma devo inizializzare gli elementi in più
        reserve(new_l + BASE_CAPACITY);
        for(int i = length; i < new_l; i++){
            elem[i] = 0;
        }
        length = new_l;
    }




}

void MyVector::reserve(int size){
    if(size <= capacity){
        return;
    }
    //alloco nuovo spazio
    //non uso il costruttore in modo da non modificare la lunghezza
    double* temp = new double[size];
    /* std::copy(elem, elem + capacity, temp); */
    for(int i = 0; i < capacity; i++){
        temp[i] = elem[i];
    }
    delete[] elem;
    capacity = size;
    elem = temp;


}

void MyVector::push_back(double a){
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
void MyVector::pop_back(){
    resize(length - 1);

}

double& MyVector::at(int pos){
    return safe_get(pos);
}

const double& MyVector::at(int pos) const{
    return safe_get(pos);
}







