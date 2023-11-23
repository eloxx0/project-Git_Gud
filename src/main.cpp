#include "../include/Date.h"
#include "../include/Year.h"
#include "../include/Isbn.h"
#include <iostream>
int main(){

    Date a{15, Month(3), 2000};
    std::cout << a;
    Date b;
    std::cout << b;
}
