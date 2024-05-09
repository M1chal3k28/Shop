#ifndef KOSZYK_H
#define KOSZYK_H

#include "Funkcje.hpp"
#include "Produkt.hpp"
#include "Magazyn.hpp"
#include "Klient.hpp"

#include <map>
#include <vector>
#include <conio.h>

using namespace Funkcje;

class Koszyk {
private: 
    map<int, int> koszyk;

public:
    
    bool zamowIzaplac( map<int, Produkt*>* listaProduktow, Klient * aktualnyKlient) {
        
        bool czyZnizka = aktualnyKlient->getStalyKlient();
        bool czyHurtowo = false;
        bool czyStac;

        float znizka = 1;

        int sumaProduktow = 0;
        for(auto [key, value] : this->koszyk) {
            sumaProduktow += value;
        }

        if(sumaProduktow >= 20)
            czyHurtowo = true;
        
        float lacznaCena = wyswietlKoszyk(*listaProduktow, false);
        float stanKontaKlienta = aktualnyKlient->getMoney();

        if(czyHurtowo && czyZnizka) {
            znizka = 0.15f;
            cout << "Posiadasz dwie znizki, za stalego klienta i hurtowy zakup\nLacznie zaoszczedzis 15 procent czyli " << lacznaCena * znizka << " zl\nCena po obnizce " << (lacznaCena -= lacznaCena * znizka);
        } else if(czyHurtowo) {
            znizka = 0.1f;
            cout << "Posiadasz znizke za hurtowy zakup\nZaoszczedzis 10 procent czyli " << lacznaCena * znizka << " zl\nCena po obnizce " << (lacznaCena -= lacznaCena * znizka);
        } else if(czyZnizka) {
            znizka = 0.05f;
            cout << "Posiadasz znizke, za stalego klienta\nZaoszczedzis 5 procent czyli " << lacznaCena * znizka << " zl\nCena po obnizce " << (lacznaCena -= lacznaCena * znizka);
        }

        czyStac = (lacznaCena <= stanKontaKlienta);

        if(!czyStac) {
            cout << "\n\nNie stac cie na wybrane produkty\nWyjmij cos z koszyka !\n" 
                 << "Stan konta " << stanKontaKlienta << " zl \nWymagana kwota " << lacznaCena << " zl \nBrakuje " << lacznaCena - stanKontaKlienta << " zl\n";
            system("pause>nul");
        } else {
            cout << "\nWcisnij dowolny klawisz by kontynuowac";
            system("pause>nul");
            string tytulMenu = "Cena za produkty " + to_string(lacznaCena) 
                             + "\nPieniadze na Twoim koncie " + to_string(stanKontaKlienta) 
                             + "\nPo zakupie zostanie Ci " + to_string(stanKontaKlienta - lacznaCena)
                             + "\n\nPlacisz?";
            vector<string> opcje = {"Tak", "Nie"};

            if(kreatorMenu(tytulMenu, opcje) == 1) {
                aktualnyKlient->setMoney(stanKontaKlienta - lacznaCena);
                aktualnyKlient->dodajZakup();

                if(aktualnyKlient->getIloscZakupow() == 5) {
                    system("cls");
                    cout << "Dziekujemy za korzystanie z naszych uslug to juz 5 zakup, a wiec staje sie Pan/Pani stalym klientem i dostaje znizke !\n";
                    aktualnyKlient->setStalyKlient();
                    system("pause>nul");
                    return true;
                }

                cout << "\nDziekuje za zakupy !";
                system("pause>nul");
                return true;
            }
        }

        aktualnyKlient = nullptr;
        listaProduktow = nullptr;

        delete aktualnyKlient;
        delete listaProduktow;
        return false;
    }

    float wyswietlKoszyk(map<int, Produkt*> listaProduktow, bool czyPauza) {
        system("cls");
        float lacznaCena = 0;

        cout << "W twoim koszyku jest " << this->getKoszykSize() << " rzeczy\n\n";

        for(auto [key, value] : *this->getKoszyk()) {
            cout << " - " << listaProduktow.at(key)->getName() << " x" << value << " Cena za sztuke " << std::fixed << listaProduktow.at(key)->getPrice() << " zl\n";
            lacznaCena += listaProduktow.at(key)->getPrice() * value;
        }

        cout << "\nLaczna cena = " << lacznaCena << " zl\n";
        
        if(czyPauza)
            system("pause>nul");
        else
            return lacznaCena;
        
        return 0.0f;
    }

    void zmienIloscProduktuWKoszyku(bool *stanKoszyka, int *iloscWkoszyku, map<int, Produkt*>* listaProduktow) {
        int idProduktuDoZmiany = wybierzProduktZKoszyka(listaProduktow);
        vector<string> opcje = {"Usunac produkt z koszyka", "Zmienic ilosc tego produktu", "\nPowrot"};
        string tytulMenu = "Co chcesz zrobic ?";

        while (true)
        {
            if(idProduktuDoZmiany == -1)
                break;

            switch(kreatorMenu(tytulMenu, opcje)) {
                case 1: {
                    Produkt * _produkt = listaProduktow->at(idProduktuDoZmiany);
                    
                    vector<string> opcje = {"TAK", "NIE"};
                    string tytulMenu = "Czy jestes pewien, ze chcesz usunac produkt " + _produkt->getName() + " ?";

                    if(kreatorMenu(tytulMenu, opcje) == 1) {
                        int poprzedniaIloscProduktu = _produkt->getAmount();
                        int iloscPrzedmiotuWkoszyku = koszyk.at(idProduktuDoZmiany);
                        int nowaIlosc = poprzedniaIloscProduktu + iloscPrzedmiotuWkoszyku;

                        _produkt->setAmount(nowaIlosc);
                        koszyk.erase(idProduktuDoZmiany);

                        *iloscWkoszyku = *iloscWkoszyku - 1;
                    }

                    _produkt = nullptr;
                    listaProduktow = nullptr;
                    iloscWkoszyku = nullptr;
                    stanKoszyka = nullptr;

                    delete stanKoszyka;
                    delete iloscWkoszyku;
                    delete _produkt;
                    delete listaProduktow;

                    return;
                } break;

                case 2: {
                    Produkt * _produkt = listaProduktow->at(idProduktuDoZmiany);
                    
                    WynikWcisnietegoKlawisza wpisuje = Tak;
                    char wpisanyZnak;
                    string ilosc = "";
                    int maksymalnaDostepnaWMagazynie = _produkt->getAmount() + koszyk.at(idProduktuDoZmiany);

                    while(true) {
                        do {
                            system("cls");
                            cout << "Aktualna ilosc " << _produkt->getName() << " w koszyku to " << koszyk.at(idProduktuDoZmiany) << "\nMaksymalna liczba produktu w magazynie " << maksymalnaDostepnaWMagazynie;
                            cout << "\nNowa ilosc > " << ilosc;

                            wpisanyZnak = getch();
                            wpisuje = wpiszDoStringa(&ilosc, wpisanyZnak, NumeryczneINT);

                            if(wpisuje == Cofnij) {
                                _produkt = nullptr;
                                listaProduktow = nullptr;
                                iloscWkoszyku = nullptr;
                                stanKoszyka = nullptr;

                                delete stanKoszyka;
                                delete iloscWkoszyku;
                                delete _produkt;
                                delete listaProduktow;
                                return; 
                            }

                            if(wpisuje == Nie && ilosc == "")
                                wpisuje = Tak;
                            else if(wpisuje == Nie && (stoi(ilosc) > maksymalnaDostepnaWMagazynie || stoi(ilosc) <= 0))
                                wpisuje = Tak;

                        }while(wpisuje == Tak);

                        vector<string> opcje = {"TAK", "NIE"};
                        string tytulMenu = "Czy jestes pewien, ze chcesz zmienic produkt w koszyku z " + to_string(koszyk.at(idProduktuDoZmiany)) + " na " + ilosc + " ?";

                        if(kreatorMenu(tytulMenu, opcje) == 1) {
                            koszyk.at(idProduktuDoZmiany) = stoi(ilosc);
                            _produkt -> setAmount(maksymalnaDostepnaWMagazynie - stoi(ilosc));
                            break;
                        }

                    }
                    
                    _produkt = nullptr;
                    delete _produkt;
                } break;

                case 3: {
                    listaProduktow = nullptr;
                    iloscWkoszyku = nullptr;
                    stanKoszyka = nullptr;

                    delete stanKoszyka;
                    delete iloscWkoszyku;
                    delete listaProduktow;

                    return;
                } break;
            }
        }

        listaProduktow = nullptr;
        iloscWkoszyku = nullptr;
        stanKoszyka = nullptr;

        delete stanKoszyka;
        delete iloscWkoszyku;
        delete listaProduktow;
    }

    int wybierzProduktZKoszyka(map<int, Produkt*>* listaProduktow) {
        
        string tytulMenu = "";
        vector<string> opcje;
        map<int, int> IDdlaIndexu;
        int wybranyIndex = 1;
        int idWybranegoProduktu = 1;

        tytulMenu = "Wybierz produkt z koszyka i wybierz co chcesz zmienic";

            int index = 1;
            IDdlaIndexu.clear();
            opcje.clear();
            for(auto [key, value] : this->koszyk) {
                Produkt * _produkt = listaProduktow->at(key);
                string opcja = " - " + _produkt -> getName() + " x" + to_string(value) + " Cena za sztuke " + to_string(_produkt->getPrice()) + " zl";
                    
                opcje.push_back(opcja);
                IDdlaIndexu.insert({index, key});
                index++;

                _produkt = nullptr;
                delete _produkt;
            }

            opcje.push_back("\nCofnij");

        while(true) {  
            wybranyIndex = kreatorMenu(tytulMenu, opcje);

            if(wybranyIndex == index)
                return -1;
            else {
                idWybranegoProduktu = IDdlaIndexu[wybranyIndex];
                string tytulMenu = "Czy jestes pewny, ze chcesz wybrac produkt: " + listaProduktow->at(idWybranegoProduktu)->getName() + "\nKtorego masz w koszyku " + to_string(this->koszyk.at(idWybranegoProduktu));
                vector<string> opcje = {"TAK", "NIE"};

                if(kreatorMenu(tytulMenu, opcje) == 1) { 
                    return idWybranegoProduktu;
                    break;
                }
            }

        }

        listaProduktow = nullptr;
        delete listaProduktow;
        return -1;
    }

    void wyczyscKoszyk(bool czyKupil, map<int, Produkt*>* listaProduktow) { 
        if(!czyKupil) {
            for(auto [key, value] : koszyk) {
                Produkt * _produkt = listaProduktow->at(key);
                int iloscDoZmiany = _produkt->getAmount();
                int iloscDoDodania = value;
                
                int nowaIlosc = iloscDoZmiany + iloscDoDodania;
                
                _produkt->setAmount(nowaIlosc);

                _produkt = nullptr;
                delete _produkt;
            }
        }

        this->koszyk.clear();
        listaProduktow = nullptr;
        delete listaProduktow;
    }

    void dodajDoKoszyka(int id, int ilosc) {
        if(this->koszyk.find(id) == this->koszyk.end()) // Nie znaleziono tego id w koszyku
            this->koszyk.insert({id, ilosc});
        else // znaleziono !
            this->koszyk.at(id) += ilosc;
    }

    int getKoszykSize() { return this->koszyk.size(); }

    map<int, int>* getKoszyk() { return &this->koszyk; }

    int menuDodawaniaDoKoszyka(Produkt* _produkt) {
        WynikWcisnietegoKlawisza wpisuje = Tak;
        string podanaIlosc;
        char wpisanyZnak;

        while(true) {
            system("cls");

            do {
                system("cls");

                cout << "Wybrany produkt " << _produkt->getName() << "\nIlosc w magazynie " << to_string(_produkt->getAmount()) << "\n\n";
            
                cout << "Wpisz ile chcesz dodac do koszyka: " << podanaIlosc;

                wpisanyZnak = getch();
                wpisuje = wpiszDoStringa(&podanaIlosc, wpisanyZnak, Funkcje::NumeryczneINT);

                if(wpisuje == Nie && (podanaIlosc.length() <= 0 || podanaIlosc == "0")) {
                    wpisuje = Tak;
                    continue;
                }

                if(wpisuje == Cofnij)
                    return -1;

            }while(wpisuje == Tak);
            
            if(stoi(podanaIlosc) <= 0) {
                wpisuje = Tak;
                continue;
            } else if(stoi(podanaIlosc) > _produkt->getAmount() ) {
                wpisuje = Tak;
                continue;
            }

            string tytulMenu = "Czy jestes pewny, ze chcesz dodac do koszyka " + podanaIlosc + " " + _produkt->getName();
            vector<string> opcje = {"TAK", "NIE"};
            if(kreatorMenu(tytulMenu,opcje) == 1) {
                this->dodajDoKoszyka(_produkt->getID(), stoi(podanaIlosc));

                int iloscDostepnegoProduktu = _produkt->getAmount();
                int nowaIloscPoDodaniuDoKoszyka = iloscDostepnegoProduktu - stoi(podanaIlosc);
                _produkt->setAmount(nowaIloscPoDodaniuDoKoszyka);

                _produkt = nullptr;
                delete _produkt;
                return 1;
            }
        }

        return -1;
    }

};

#endif
