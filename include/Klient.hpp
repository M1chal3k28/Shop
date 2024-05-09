#ifndef KLIENT_H
#define KLIENT_H
#include <iostream>

using namespace std;

class Klient {
private:
    string nazwaUzytkownika, haslo, imie, nazwisko;
    bool czyStaly;
    float pieniadzeWPortfelu;
    int iloscZakupow;
    
public:
    Klient()=default;

    Klient(string imie, string nazwisko, string nazwaUzytkownika, string haslo, bool czyStaly, float pieniadze, int ileZakupow) {
        this->imie = imie;
        this->nazwisko = nazwisko;
        this->nazwaUzytkownika = nazwaUzytkownika;
        this->haslo = haslo;
        this->czyStaly = czyStaly;
        this->pieniadzeWPortfelu = pieniadze;
        this->iloscZakupow = ileZakupow;
    }

    string getNazwaUzytkownika() { return this->nazwaUzytkownika; }
    string getHaslo() { return this->haslo; }
    float getMoney() { return this->pieniadzeWPortfelu; }
    bool getStalyKlient() { return this->czyStaly; }
    void dodajZakup() { this->iloscZakupow++; }
    int getIloscZakupow() { return this->iloscZakupow; }
    void setMoney(float _ile) { this->pieniadzeWPortfelu = _ile; }
    void setStalyKlient() { this->czyStaly = true; }
    string wypisz() { return (this->imie + " " + this->nazwisko + " " + this->nazwaUzytkownika + " " + this->haslo + " " + to_string(this->czyStaly) + " " + to_string(this->pieniadzeWPortfelu) + " " + to_string(this->iloscZakupow) + "\n"); }
};

#endif
