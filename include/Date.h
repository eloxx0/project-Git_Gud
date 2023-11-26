#ifndef DATE_H
#define DATE_H

#include "Year.h"
#include <iostream>


enum class Month{
    jan = 1, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec
};

class Date{
    private:

    int d;

    Month m;

    Year y;
    //funzione privata che permette restituisce true se i dati privati sono validi
    //false se sono invalidi 
    bool is_valid();

    public:

    //eccezione lanciata dal costruttore nel caso in cui i dati inseriti non sono validi
    class Invalid_argument{};

    //costruttore di base della classe Date. Inizializza i parametri alla prima data utilizzabile
    Date();

    //costruttore della classe Date. Richiede come parametri in ordine il giorno, il mese e l'anno
    Date(int d, Month m, Year y);

    int get_day() const{
        return d;
    }

    Month get_month() const{
        return m;
    }

    Year get_year() const{
        return y;
    }



};

//overload dell'operatore <<, permette di ottenere un ostream da un Date
std::ostream& operator<<(std::ostream& o, const Date& d);


//restituisce il numero di giorni che contiene un mese in un determinato anno(tenendo conto degli anni
//bisestiili)
int day_for_month(Month mon, Year yea);

//ritorna la stringa corrispondente al mese passato per parametro
std::string month_to_string(Month mm);


#endif // DATE_H
