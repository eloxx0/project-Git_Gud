#ifndef YEAR_H
#define YEAR_H

class Year{

    private:

    int y;

    public:

    static const int MIN_Y = 1899;
    static const int MAX_Y = 2023;

    Year(int year);
    
    //eccezione lanciata dal costruttore nel caso in cui l'anno non appartiene ai
    //limiti scelti
    class Invalid_year{};

    int year_int(){
        return y;
    }

    //ritorna true se l'anno è bisestile, false se non è bisestile
    bool is_leap_year();
};

#endif // YEAR_H
