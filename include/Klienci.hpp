#ifndef KLIENCI_H
#define KLIENCI_H

#include <iostream>
#include <map>

#include "Klient.hpp"
#include "Plik.hpp"
#include "Funkcje.hpp"

using namespace Funkcje;
using namespace std;

class Klienci : Plik {
private:
    map<string, Klient*> klienci;
    string zalogowanyKlientNazwa = "";

public:
    Funkcje::PoprawnoscStringa sprawdzNazweUzytkownika(string nazwa) {

        if ( klienci[nazwa] != nullptr ) 
            return Istnieje;

        return Funkcje::sprawdzString(nazwa);
    }

    void odczytajKlientow() {
        klienci.clear();
            plik.open("klienci.txt", ios::in);

                if(!plik.good()) {
                    plik.close();

                    plik.open("klienci.txt", ios::out);
                    plik << ">";
                    plik.close();
                    return;
                }

                string imie, nazwisko, nazwaUzytkownika, haslo;
                float pieniadzeWPortfelu;
                bool czyStaly;
                int iloscZakupow;

                while(!plik.eof()) {
                    plik >> imie;
                    if (imie == ">" || imie == "") {
                        plik.close();
                        return;
                    }

                    plik >> nazwisko;
                    plik >> nazwaUzytkownika;
                    plik >> haslo;
                    plik >> czyStaly;
                    plik >> pieniadzeWPortfelu;
                    plik >> iloscZakupow;

                    klienci[nazwaUzytkownika] = new Klient(imie, nazwisko, nazwaUzytkownika, haslo, czyStaly, pieniadzeWPortfelu, iloscZakupow);
                }
                        
            plik.close();
        }
    
    void zaktualizujPlikKlientow() {
        plik.open("klienci.txt", ios::out); 

        for (auto [key, value] : klienci) {
            plik << value->wypisz();
        }

        plik << '>';

        plik.close();
    }

    bool probaLogowania(string uzytkownik, string haslo) {

            if(klienci[uzytkownik] != nullptr) {
                if(klienci[uzytkownik]->getHaslo() == haslo) {
                    zalogowanyKlientNazwa = uzytkownik;
                    return true;
                } else 
                    return false;
            }  

            return false;
		}

    void dodajKlienta(string imie, string nazwisko, string nazwaUzytkownika, string haslo, bool czyStaly, float pieniadze, int ileZakupow) {
        this->klienci[nazwaUzytkownika] = new Klient(imie, nazwisko, nazwaUzytkownika, haslo, czyStaly, pieniadze, ileZakupow);
        this->zaktualizujPlikKlientow();
    }

    void wylogujKlienta() {
        this->zalogowanyKlientNazwa = "";
    }

    void rejestracja() {
        string imie, nazwisko, nazwaUzytkownika, haslo, hasloPowtorzone, pieniadze, informacjaZwrotna = "";
        bool czyBlad = false, haslaTeSame = false;
        WynikWcisnietegoKlawisza wpisuje = Tak;
        char wpisanyZnak;
        Funkcje::PoprawnoscStringa poprawnoscHasla;
        Funkcje::PoprawnoscStringa poprawnoscNazwyUzytkownika;

        do{
            system("cls");

            if(czyBlad) {
                cout << informacjaZwrotna;
                informacjaZwrotna = "";
                czyBlad = false;
                Sleep(2000);
            }
            
            do{
                system("cls");
                cout << "Rejestracja:\n\n";
                cout << "Podaj imie: " << imie;
                
                wpisanyZnak = getch();
                wpisuje = wpiszDoStringa(&imie, wpisanyZnak, Funkcje::String);

                if(wpisuje == Cofnij)
                    return;

                if(wpisuje == Nie && imie.length() < 3)
                    wpisuje = Tak;

            }while(wpisuje == Tak);

            do{
                system("cls");
                cout << "Rejestracja:\n\n";
                cout << "Imie -> " << imie << "\n";

                cout << "\nPodaj nazwisko: " << nazwisko;
                wpisanyZnak = getch();
                wpisuje = wpiszDoStringa(&nazwisko, wpisanyZnak, Funkcje::String);

                if(wpisuje == Cofnij)
                    return;

                if(wpisuje == Nie && imie.length() < 3)
                    wpisuje = Tak;

            }while(wpisuje == Tak);

            do{
                system("cls");
                cout << "Rejestracja:\n\n";
                cout << "Imie -> " << imie << "\n";
                cout << "Nazwisko -> " << nazwisko << "\n";

                cout << "\nPodaj nick: " << nazwaUzytkownika << "\n";
                wpisanyZnak = getch();
                wpisuje = wpiszDoStringa(&nazwaUzytkownika, wpisanyZnak, Funkcje::String);

                if(wpisuje == Cofnij)
                    return;

                if(wpisuje == Nie && imie.length() < 3)
                    wpisuje = Tak;

            }while(wpisuje == Tak);

            do{
                system("cls");
                cout << "Rejestracja:\n\n";
                cout << "Imie -> " << imie << "\n";
                cout << "Nazwisko -> " << nazwisko << "\n";
                cout << "Nick -> " << nazwaUzytkownika << "\n";

                cout << "\nPodaj haslo: " << haslo << "\n";
                wpisanyZnak = getch();
                wpisuje = wpiszDoStringa(&haslo, wpisanyZnak, Funkcje::String);

                if(wpisuje == Cofnij)
                    return;

            }while(wpisuje == Tak);

            do{
                system("cls");
                cout << "Rejestracja:\n\n";
                cout << "Imie -> " << imie << "\n";
                cout << "Nazwisko -> " << nazwisko << "\n";
                cout << "Nick -> " << nazwaUzytkownika << "\n";
                cout << "Haslo -> " << haslo << "\n";

                cout << "\nPowtorz haslo: " << hasloPowtorzone;
                wpisanyZnak = getch();
                wpisuje = wpiszDoStringa(&hasloPowtorzone, wpisanyZnak, Funkcje::String);

                if(wpisuje == Cofnij)
                    return;

            }while(wpisuje == Tak);

            do{
                system("cls");
                cout << "Rejestracja:\n\n";
                cout << "Imie -> " << imie << "\n";
                cout << "Nazwisko -> " << nazwisko << "\n";
                cout << "Nick -> " << nazwaUzytkownika << "\n";
                cout << "Haslo -> " << haslo << "\n";
                cout << "Powtorzone Haslo -> " << hasloPowtorzone << "\n";

                cout << "\nWpisz jakim budzetem dysponujesz: " << pieniadze;
                wpisanyZnak = getch();
                wpisuje = wpiszDoStringa(&pieniadze, wpisanyZnak, Funkcje::Numeryczne);

                if(wpisuje == Nie && pieniadze == "")
                    wpisuje = Tak;

                if(wpisuje == Cofnij)
                    return;

            }while(wpisuje == Tak);

            poprawnoscNazwyUzytkownika = this->sprawdzNazweUzytkownika(nazwaUzytkownika);
            poprawnoscHasla = Funkcje::sprawdzString(haslo);
            haslaTeSame = ( haslo == hasloPowtorzone );

            if (poprawnoscHasla == Znak) {
                czyBlad = true;
                informacjaZwrotna = informacjaZwrotna + "Haslo nie moze zawierac spacji ! \n";
            } else if(poprawnoscHasla == Dlugosc) {
                czyBlad = true;
                informacjaZwrotna = informacjaZwrotna + "Haslo jest za krotkie ! \n";
            }

            if (!haslaTeSame) {
                czyBlad = true;
                informacjaZwrotna = informacjaZwrotna + "Hasla sa rozne ! \n";
            }

            if (poprawnoscNazwyUzytkownika == Znak) {
                czyBlad = true;
                informacjaZwrotna = informacjaZwrotna + "Nazwa uzytkownika nie moze zawierac spacji ! \n";
            } else if (poprawnoscNazwyUzytkownika == Istnieje) {
                czyBlad = true;
                informacjaZwrotna = informacjaZwrotna + "Nazwa uzytkownika zajeta ! \n\n";
            }

        }while(czyBlad);

        this->dodajKlienta(imie, nazwisko, nazwaUzytkownika, haslo, 0, stof(pieniadze), 0);
    }
    
    map<string, Klient*>* getClients() { return &this->klienci; }
	Klient * aktualnyKlient() { 
            if(klienci[zalogowanyKlientNazwa] != nullptr) 
                return klienci[zalogowanyKlientNazwa];

            return nullptr;
        }
};

#endif