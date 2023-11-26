#include "../include/Isbn.h"
#include <cmath>
#include <iostream>

Isbn::Isbn(std::string isbn){
    if(string_isbn_valid(isbn)){
        this ->isbn = isbn;
    }
    else{
        throw Invalid_Isbn_Argument();
    }
}

Isbn::Isbn(){
    this ->isbn = generate_isbn();
}


bool string_isbn_valid(std::string s){

    //uso il costruttore di std::vector<char>(iterator a, iterator b)
    std::vector<char> s_vec(s.begin(), s.end());

    //rimuovo i caratteri a tratti dall'isbn
    for(int i = 0; i < s_vec.size(); i++){
        if(s_vec[i] == '-'){
            s_vec.erase(s_vec.begin() + i);
        }
    }
    //se sono presenti meno di 13 caratteri numerici, la stringa non è corretta
    if(s_vec.size() != 13) return false;

    std::vector<int> s_vec_int;
    for(int i = 0; i < s_vec.size(); i++){
        //converto da char a int
        s_vec_int.push_back(s_vec[i] - '0');
    }

    int control = isbn_control_value(s_vec_int);

    if(control == (s_vec_int[12])) return true;
    else return false;

    //controlla che i primi tre caratteri siano quelli dello standard isbn. Il codice
    //978 identifica che il prodotto è un libro
    int ean = s_vec_int[0] + s_vec_int[1] + s_vec_int[2];
    if(ean == 978 || ean == 979) return true;
    else return false;


}


bool Isbn::operator==(const Isbn& i){
    return isbn.compare(isbn);
}

bool Isbn::operator!=(const Isbn& i){
    return !(*this == i);
}

std::string generate_isbn(){
    int random = 100000000 + ( std::rand() % 100000000);
    std::string a = "978-" + std::to_string(random);
    std::vector<char> s_vec(a.begin(), a.end());

    std::vector<int> s_vec_int;
    for(int i = 0; i < s_vec.size(); i++){
        //converto da char a int
        s_vec_int.push_back(s_vec[i] - '0');
    }

    int control = isbn_control_value(s_vec_int);

    a += std::to_string(control);
    return a;
}

//algoritmo di verifica del codice isbn: se la somma delle cifre moltiplicate per un peso che
//assume valore 1 o 3 in modo alternato. Si divide la somma per 10 e si sottrae il resto della
//divisione a 10. Se la divisione non ha resto si tiene 0 come valore. Se la cifra di controllo
//è uguale all'ultima cifra del isbn, allora è valido
int isbn_control_value(std::vector<int>& s_vec_int){
    int weight;
    int control = 0;
    for(int i = 1; i < 13; i++){

        (i % 2 == 0) ? weight = 3 : weight = 1;
        control += (s_vec_int[i - 1] * weight);
    }
    control = control % 10;
    control = (10 - control) % 10;
    return control;
}

std::ostream& operator<<(std::ostream& os, const Isbn& i)
{
    return os<< i.get_isbn();
}


