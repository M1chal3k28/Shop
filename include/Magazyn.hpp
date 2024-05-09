#ifndef MAGAZYN_H
#define MAGAZYN_H

#include <map>

#include "Produkt.hpp"
#include "Plik.hpp"
#include "Funkcje.hpp"

using namespace Funkcje;

class Magazyn : Plik {
private:
    map<int, Produkt*> produkty;

public:
    void odczytajProdukty() {
        plik.open("produkty.txt", ios::in);

            if(!plik.good()) {
                plik.close();

                plik.open("produkty.txt", ios::out);
                plik << ">";
                plik.close();
                return;
            }

            string nazwa;
            float cenaJednostkowa;
            int ilosc, id;

            while(!plik.eof()) {
                plik >> nazwa;
                if (nazwa == ">")
                        break;

                plik >> cenaJednostkowa;
                plik >> ilosc;
                plik >> id;

                produkty.insert({id, new Produkt(id, nazwa, cenaJednostkowa, ilosc)});
            }
                    
        plik.close();
    }

    int dodajProdukt() {
        string informacjaZwrotna = "", nazwa, cena, ilosc;
        bool czyBlad = false;
        WynikWcisnietegoKlawisza wpisuje = Tak;
        char wpisanyZnak;

        bool poprawnoscIlosci = false, poprawnoscCeny = false; 
        PoprawnoscStringa poprawnoscNazwy = Istnieje;

        do{
            system("cls");

            if(czyBlad) {
                cout << informacjaZwrotna;
                informacjaZwrotna = "";
                czyBlad = false;
                poprawnoscNazwy = Istnieje;
                Sleep(1500);
            }

            do{
                system("cls");
                cout << "Dodawanie Produktu:\n\n";
                cout << "Podaj nazwe: " << nazwa;
                wpisanyZnak = getch();
                wpisuje = wpiszDoStringa(&nazwa, wpisanyZnak, Funkcje::String);
                
                if(wpisuje == Nie && (nazwa == "" || nazwa.length() < 2))
                    wpisuje = Tak;

                if(wpisuje == Cofnij)
                    return -1;

            }while(wpisuje == Tak);

            do{
                system("cls");
                cout << "Dodawanie Produktu:\n\n";
                cout << "Nazwa -> " << nazwa << "\n";
                cout << "\nPodaj cene jednostkowa: " << cena;
                wpisanyZnak = getch();
                wpisuje = wpiszDoStringa(&cena, wpisanyZnak, Funkcje::Numeryczne);

                if(wpisuje == Nie && cena == "")
                    wpisuje = Tak;

                if(wpisuje == Cofnij)
                    return -1;

            }while(wpisuje == Tak);

            do{
                system("cls");
                cout << "Dodawanie Produktu:\n\n";
                cout << "Nazwa -> " << nazwa << "\n";
                cout << "Cena -> " << cena << "\n";
                cout << "\nPodaj ilosc: " << ilosc;
                wpisanyZnak = getch();
                wpisuje = wpiszDoStringa(&ilosc, wpisanyZnak, Funkcje::Numeryczne);
                
                if(wpisuje == Nie && ilosc == "")
                    wpisuje = Tak;

                if(wpisuje == Cofnij)
                    return -1;

            }while(wpisuje == Tak);

            poprawnoscCeny = (stof(cena)>0.0f);
            poprawnoscIlosci = (stoi(ilosc)>=1);
            poprawnoscNazwy = sprawdzNazweProduktu(nazwa);

            if(!poprawnoscCeny) {
                czyBlad = true;
                informacjaZwrotna = informacjaZwrotna + "Podana cena jest za mala ! \n";
            }

            if(!poprawnoscIlosci) {
                czyBlad = true;
                informacjaZwrotna = informacjaZwrotna + "Podana ilosc jest za mala ! \n";
            }

            if(poprawnoscNazwy == Istnieje) {
                czyBlad = true;
                informacjaZwrotna = informacjaZwrotna + "Produkt o takiej nazwie juz istnieje !\n";
            }

        }while(czyBlad);
        int idProduktu = this->wyznaczID();
        produkty.insert({idProduktu, new Produkt(idProduktu, nazwa, stof(cena), stoi(ilosc))});

        return idProduktu;
    }

    PoprawnoscStringa sprawdzNazweProduktu(string _nazwa) {
        for(auto [key, value] : this->produkty) {
            if(duzeLitery(value->getName()) == duzeLitery(_nazwa))
                return Istnieje;
        }

        return Ok;
    } 

    int wyznaczID() {
        return produkty.size() + 1;
    }

    void listaWprowadzonychZmian(map<int, Produkt*> stareDane, vector<int>* zmienioneID, vector<int>* dodaneID, map<int, Produkt*> aktualneDane) {
        system("cls");
        cout << "Dodane Produkty: \n";
        for(auto e : *dodaneID) {
            cout << "   Dodany produkt o id " << e << " | Nazwa -> " << aktualneDane.at(e)->getName() 
                                                   << " | Cena jednostkowa -> " << aktualneDane.at(e)->getPrice() << " zl"
                                                   << " | Ilosc -> " << aktualneDane.at(e)->getAmount() << "\n";
        }

        cout << "Zmienione Produkty: \n";
        for(auto e : *zmienioneID) {
            if(stareDane[e] != nullptr) {
                int nowaIlosc = aktualneDane.at(e)->getAmount();
                int staraIlosc = stareDane.at(e)->getAmount();
                int roznicaIlosci = nowaIlosc - staraIlosc;
                string iloscRoznicaString = "";

                float nowaCena = aktualneDane.at(e)->getPrice();
                float staraCena = stareDane.at(e)->getPrice();
                float roznicaCen = nowaCena - staraCena;
                string cenaRoznicaString = "";

                if(roznicaIlosci < 0)
                    iloscRoznicaString = to_string(roznicaIlosci);
                else if(roznicaIlosci > 0)
                    iloscRoznicaString = "+" + to_string(roznicaIlosci);
                else
                    iloscRoznicaString = to_string(staraIlosc);

                if(roznicaCen < 0)
                    cenaRoznicaString = to_string(roznicaCen);
                else if(roznicaCen > 0)
                    cenaRoznicaString = "+" + to_string(roznicaCen);
                else 
                    cenaRoznicaString = to_string(staraCena);

                cout << "   Produkt o id " << e << " | Nazwa -> " << aktualneDane.at(e)->getName() 
                                           << " | Cena jednostkowa -> " << cenaRoznicaString << " zl"
                                           << " | Ilosc -> " << iloscRoznicaString << "\n";
            }
        }
        system("pause>nul");
    }
    
    void wyswietlWyszystkieProdukty() {
        system("cls");
        int index = 1;
            for (auto [key, value] : produkty) {
                    cout << value->getName();
                    cout.width(20 - value->getName().length());
                    cout << setprecision(2) << fixed;
                    cout << value->getPrice() << " zl";
                    cout.width(30 - to_string(value->getPrice()).length());
                    cout << "Ilosc " << to_string(value->getAmount()) << "\n";
            }
        system("pause>nul");
    }

    Produkt* wyszukiwarkaProduktuPoNazwie() {
        string nazwa = "";
        char wpisanyZnak;
        WynikWcisnietegoKlawisza wpisuje = Tak;
        zaznaczonaOpcja = 1;
        map<int, int> IDdlaIndexu;
        int index = 1;
        
        string opcja;
        vector<string> opcje;
        string tytulMenu = "Wybierz Produkt z listy ponizej !"; 

        int wybranyIndex = 1;
        int idWybranegoProduktu = 1;

        while(true) {
            system("cls");
            while(wpisuje == Tak) {
                cout << "Wyszukiwarka produktow po nazwie: " << nazwa << czyWybrany(1, zaznaczonaOpcja) << "\n";
                

                wpisanyZnak = getch();
                wpisuje = wpiszDoStringa(&nazwa, wpisanyZnak, Funkcje::String);

                if(wpisuje == Cofnij)
                    return nullptr;
                
                system("cls");

                index = 1;
                IDdlaIndexu.clear();
                opcje.clear();
                opcja = "";                

                for (auto [key, value] : produkty) {
                    if (value->contain(duzeLitery(nazwa), duzeLitery(value->getName())) != string::npos) {

                        opcja = "ID " + to_string(value->getID()) 
                              + " | " + value->getName()
                              + " | Cena -> " + to_string(value->getPrice()) + "zl"
                              + " | Ilosc -> " + to_string(value->getAmount());

                        cout << setprecision(2) << opcja << "\n";

                        IDdlaIndexu.insert({index, value->getID()});
                        opcje.push_back(opcja);
                        index++;
                    }
                }
                opcje.push_back("\nCofnij");
            };

            wpisuje = Tak;
            wybranyIndex = kreatorMenu(tytulMenu, opcje);

            if(wybranyIndex == index)
                return nullptr;
            else {
                idWybranegoProduktu = IDdlaIndexu[wybranyIndex];
                tytulMenu = "Czy jestes pewny, ze chcesz wybrac produkt: " + this->getProductByID(idWybranegoProduktu)->getName();
                opcje = {"TAK", "NIE"};

                if(kreatorMenu(tytulMenu, opcje) == 1) 
                    return this->getProductByID(idWybranegoProduktu);
                
                tytulMenu = "Wybierz Produkt z listy ponizej !"; 
            }
        }
    }

    void porzucZmiany(map<int, Produkt*> daneDoNadPisania) {
        this->produkty = daneDoNadPisania;
    }
    
    void zapiszZmianyProduktow() {
        plik.open("produkty.txt", ios::out); 

        for (auto [key, value] : produkty) {
            plik << value->wypisz();
        }

        plik << '>';

        plik.close();
    }

    int aktualizacjaDanychProduktu() {   
        bool czyZmiana = false;

        Produkt* _produkt = this->wyszukiwarkaProduktuPoNazwie();
        if (_produkt == nullptr) {
            delete _produkt;
            return -1;
        }

        int idProduktu = _produkt->getID();
        string nazwaProduktu = this->getProductByID(idProduktu)->getName();
        string ilosc = to_string(this->getProductByID(idProduktu)->getAmount());
        string cena = to_string(this->getProductByID(idProduktu)->getPrice());

        while(true) {
            string tytulMenu = "Wybrany przez Ciebie produkt : " + nazwaProduktu
                    + "\nAktualna ilosc produktu na magazynie : " + ilosc 
                    + "\nAktualna cena za jeden produkt : " + cena;

            vector<string> opcje = {"Ilosc",
                                "Cene",
                                "Powrot"};

            switch(kreatorMenu(tytulMenu, opcje)) {
                case 1: {
                    //Produkt* _produkt = this->getProductByID(idProduktu);
                    if(_produkt == nullptr)
                        return -1;
                    else if(zmianaIlosciProduktu(_produkt) > 0) {
                        ilosc = to_string(_produkt->getAmount());
                        czyZmiana = true;
                    }
                }; break;

                case 2: {
                    //Produkt* _produkt = this->getProductByID(idProduktu);
                    if(_produkt == nullptr)
                        return -1;
                    else if(zmianaCenyProduktu(_produkt) > 0) {
                        cena = to_string(this->getProductByID(idProduktu)->getPrice());
                        czyZmiana = true;
                    }
                }; break;
                case 3: _produkt = nullptr; delete _produkt; return (czyZmiana ? idProduktu : -1); break;
            }
        }

        _produkt = nullptr; delete _produkt;
        return (czyZmiana ? idProduktu : -1);
    };

    int zmianaIlosciProduktu(Produkt* _produkt) {
        Funkcje::WynikWcisnietegoKlawisza wpisuje = Tak;

        int staraIlosc = _produkt->getAmount();
        string nowaIlosc;
        char wpisanyZnak = ' ';

        string tytulMenu = "Czy jestes pewien zmiany ?\n" + _produkt->getName() + " | Ilosc " + to_string(staraIlosc) + " -> " + nowaIlosc;
        vector<string> opcje = {"TAK", "NIE"};

        while(true){
            staraIlosc = _produkt->getAmount();
            do{
                system("cls");
                cout << "Aktualna ilosc " << _produkt->getName() << " to " << staraIlosc << endl;
                cout << "Podaj nowa ilosc > " << nowaIlosc;

                wpisanyZnak = getch();
                wpisuje = wpiszDoStringa(&nowaIlosc, wpisanyZnak, Funkcje::NumeryczneINT);

                if(wpisuje == Cofnij)
                    return -1;

            }while(wpisuje == Tak);

            if(nowaIlosc == "") 
                continue;
            else if( stoi(nowaIlosc) <= _produkt->getAmount() )
                continue;;

            system("cls");
            tytulMenu = "Czy jestes pewien zmiany ?\n" + _produkt->getName() + " | Ilosc " + to_string(staraIlosc) + " -> " + nowaIlosc;
            if(kreatorMenu(tytulMenu, opcje) == 1) 
                break;
        }

        _produkt->setAmount(stoi(nowaIlosc));

        _produkt = nullptr;
        delete _produkt;
        return 1;
    }
    
    int zmianaCenyProduktu(Produkt* _produkt) {
        Funkcje::WynikWcisnietegoKlawisza wpisuje = Tak;

        float staraCena;
        string nowaCena;
        char wpisanyZnak = ' ';

        string tytulMenu;
        vector<string> opcje = {"TAK", "NIE"};

        while(true){
            staraCena = _produkt->getPrice();
            do{
                system("cls");
                cout << "Aktualna cena " << _produkt->getName() << " to " << setprecision(2) << staraCena << endl;
                cout << "Podaj nowa cene > " << nowaCena;

                wpisanyZnak = getch();
                wpisuje = wpiszDoStringa(&nowaCena, wpisanyZnak, Funkcje::NumeryczneINT);

                if(wpisuje == Cofnij)
                    return -1;

            }while(wpisuje == Tak);

            if(nowaCena == "") 
                continue;
            else {
                if (stof(nowaCena) == 0) 
                    continue;
            }

            system("cls");
            tytulMenu = "Czy jestes pewien zmiany ?\n" + _produkt->getName() + " | Cena " + to_string(staraCena) + " -> " + nowaCena;
            if(kreatorMenu(tytulMenu, opcje) == 1) 
                break;
        }

        _produkt->setPrice(stof(nowaCena));
        return 1;
    }
    
    map<int, Produkt*> kopiujListeProduktow() { 
        map<int, Produkt*> nowaMapa;

        for(auto [key, value] : this->produkty) {
            nowaMapa.insert({key, new Produkt(*value)});
        }

        return nowaMapa;
    }
    map<int, Produkt*>* getProdukty() { return &this->produkty; }
    Produkt* getProductByID(int id) { return this->produkty.at(id); }
};

#endif