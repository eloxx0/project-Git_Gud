#include "../include/Date.h"
#include <vector>
//initializer list utilizza il costruttore della classe Year per inizializzare. Lancia eventualmente l'eccezione Invalid_year
Date::Date(int d, Month m, Year y) : d{d}, m{m}, y{y}{
    if(!is_valid()) throw Invalid_argument();
}

//costruttore di base inizializza alla prima data assegnabile
Date::Date() : d{1}, m{Month(1)}, y{Year::MIN_Y}{}

bool Date::is_valid(){

    if(m < Month(1) || m > Month(12) ) return false;

    else if(d > day_for_month(m, y) || d < 1) return false;

    else return true;

}

int day_for_month(Month mon, Year yea){
    if(mon == Month::apr || mon == Month::jun || mon == Month::aug || mon == Month::nov ){
        return 30;
    }
    else if(mon == Month::feb){

        if(yea.is_leap_year()) return 29;

        else return 28;
    }
    return 31;
}

std::string month_to_string(Month mm){
    std::vector<std::string> month_v = {"jan", "feb", "mar", "apr", "may", "jun", "jul", "aug", "sep", "oct", "nov", "dec"};

    return month_v[int(mm) - 1];
}

std::ostream& operator<<(std::ostream& o, const Date& d){

    return o << std::to_string(d.get_day()) + " " + month_to_string(d.get_month()) + " " + std::to_string(d.get_year().year_int());
}
