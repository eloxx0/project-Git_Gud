#include <iostream>
#include "../include/MyVector.h"

int main(){
    //testo i diversi metodi della classe MyVector
    //
    //testo i diversi costruttori
    //
    //costruttore di base
    MyVector v;

    std::cout << "il vettore v ha dimensione " << v.size() << " e capacità " << v.dimension() << "\n";

    MyVector v1 = MyVector(7);

    std::cout << "il vettore v1 ha dimensione " << v1.size() << " e capacità " << v1.dimension() << "\n";

    //uso costruttore di copia
     
    MyVector v2 = v1;

    std::cout << "il vettore v2 ha dimensione " << v2.size() << " e capacità " << v2.dimension() << "\n";

    //uso il push_back

    v.push_back(0);
    v.push_back(1);
    std::cout << "in v ho aggiunto gli elementi " << v.safe_get(0) << " " << v.safe_get(1) << "\n";

    //uso l'assegnamento di copia

    v2 = v;

    std::cout << "dopo aver copiato v, il vettore v2 ha dimensione " << v2.size() << " e capacità " << v2.dimension() << "\n";
    std::cout << "controllo i primi due elementi di v2: " << v2.safe_get(0) << ", " << v2.safe_get(1) << "\n";

    v1.safe_set(6, 7.1);
    std::cout << "ho inserito in posizione 6 di v1 l'elemento " << v1.safe_get(6) << "\n";
    //lancia eccezione Invalid_position
    /* std::cout << "in posizione 9 (maggiore della lunghezza) ho l'elemento " << v1.safe_get(9); */
    
    v[4] = 7;
    v[2] = 3;
    std::cout << "ho inserito in posizione 4 di v(al di fuori della lunghezza): " << v[4] << " e in posizione 2: " << v[2] << "\n";

    int init_s = v.size();
    v.resize(7);
    std::cout << "aumento la lunghezza di v da " << init_s << " a " << v.size() << " con capacità " << v.dimension() << "\n";
    v.push_back(9);
    std::cout << "stampo gli elementi di v dopo il resize e un push_back :";
    for(int i = 0; i < v.size(); i++){
        std::cout << v[i] << " ";
    }
    std::cout << std::endl;
    std::cout << "noto che se faccio il resize il push_back inserisce alla fine del nuovo spazio inizializzato!";

    for(int i = 0; i < 6; i++){
        v.pop_back();
    }
    std::cout << "dopo aver usato il pop_back 6 volte ottengo v= ";
    for(int i = 0; i < v.size(); i++){
        std::cout << v[i] << " ";
    }
    std::cout << "\ncon la lunghezza di v= " << v.size() << " e lo spazio allocato " << v.dimension() << "\n";
    std::cout << "controllo che il push_back sia in grado di gestire il caso in cui deve allocare nuovo spazio \n";
    MyVector v4;
    std::cout << "lunghezza e capacità del vettore v4: " << v4.size() << ", " << v4.dimension() << "\n";
    for(int i = 0; i < 7; i++){
        v4.push_back(i);
    }
    std::cout << "lunghezza e capacità del vettore v4 dopo 7 push: "  << v4.size() << ", " << v4.dimension() << "\n";
    std::cout << " stampo il vettore v4: \n";
    for(int i = 0; i < v4.size(); i++){
        std::cout << v4[i] << " ";
    }

    std::cout << "\nassegno a v4 in posizione 0 il valore 4.7 usando l'at" << "\n";
    v4.at(0) = 4.7;
    std::cout << "accedo con la funzione at: " << v4.at(0) << ", " << v4.at(1) << ", " << v4.at(2) << "\n";




}
