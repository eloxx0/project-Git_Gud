#include "../include/Year.h"

Year::Year(int year) : y{year}{
    if(year < min_y || year > max_y){
        throw Invalid_year();
    }
}

bool Year::is_leap_year(){
    if(y % 4 == 0 && y % 100 != 0) return true;

    else if(y % 100 == 0 && y % 400 == 0) return true;

    return false;
}
