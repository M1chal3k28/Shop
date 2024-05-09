#include "include/Sklep.hpp"

int main() {
    Sklep sklep;

    system("title Sklep internetowy");

    cout << setprecision(5);
    cout << std::fixed;
    
    sklep.start();
    return 0;
}