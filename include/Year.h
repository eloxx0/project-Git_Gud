#ifndef YEAR_H
#define YEAR_H

class Year{
    static const int min_y = 1899;
    static const int max_y = 2025;

    private:
    int y;

    public:
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
