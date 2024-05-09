#ifndef PRODUKT_H
#define PRODUKT_H

#include <iostream>

using namespace std;

class Produkt {
private:
    string nazwa;
    float cenaJednostkowa;
    int ilosc, id;

public:
    Produkt()=default;

    Produkt(int id, string nazwa, float cena, int ilosc) {
        this->nazwa = nazwa;
        this->cenaJednostkowa = cena;
        this->ilosc = ilosc;
        this->id = id;
    }

    string getName() { return this->nazwa; }
    float getPrice() { return this->cenaJednostkowa; }
    int getAmount() { return this->ilosc; }
    int getID() { return this->id; }
    size_t contain(string _subString, string _string) { return _string.find(_subString); }
    void setAmount(int _amount) { this->ilosc = _amount; }
    void setPrice(float _price) { this->cenaJednostkowa = _price; }
    string wypisz() { return (nazwa + " " + to_string(cenaJednostkowa) + " " + to_string(ilosc) + " " + to_string(id) + "\n"); }
};

#endif