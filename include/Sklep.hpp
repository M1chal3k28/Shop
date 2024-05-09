#ifndef SKLEP_H
#define SKLEP_H

#include <limits>
#include <conio.h>
#include <windows.h>
#include <cstdlib>
#include <vector>

#include "Klienci.hpp"
#include "Magazyn.hpp"
#include "Funkcje.hpp"
#include "Koszyk.hpp"

using namespace Funkcje;

class Sklep: public Klienci, public Magazyn, public Koszyk {
  private: 
  
  bool kontoWybrane = false;
  bool przegladanieBezKonta = false;
  char input;

  public: 

  void wyloguj() {
    this->wylogujKlienta();
    this->przegladanieBezKonta = true;
    this->kontoWybrane = false;
  }

  Sklep() {
    this -> odczytajProdukty();
    this -> odczytajKlientow();
  }

  void logowanie(bool _return) {
    string nazwaUzytkownika;
    string haslo;
    string informacjaZwrotna = "";
    bool statusLogowania = true;
    WynikWcisnietegoKlawisza wpisuje = Tak;
    char wpisanyZnak;

    do {
      system("cls");

      if(!statusLogowania) {
        cout << informacjaZwrotna;
        informacjaZwrotna = "";
        Sleep(2000);
      }

      statusLogowania = false;

      do{
        system("cls");
        cout << "Logowanie:\n\n";
        cout << "Nazwa uzytkownika: " << nazwaUzytkownika;
        wpisanyZnak = getch();
        wpisuje = wpiszDoStringa(&nazwaUzytkownika, wpisanyZnak, Funkcje::String);
      }while(wpisuje == Tak);

      if(wpisuje == Cofnij) 
        return;

      if( this->sprawdzNazweUzytkownika(nazwaUzytkownika) == Istnieje ) {
        do{
          system("cls");
          cout << "\nPodaj haslo do konta "<<nazwaUzytkownika<<":\n\n";
          cout << "Haslo: " << haslo;

          wpisanyZnak = getch();
          wpisuje = wpiszDoStringa(&haslo, wpisanyZnak, Funkcje::String);

        }while(wpisuje == Tak);

        if(wpisuje == Cofnij) 
         return;

        // Proba zalogowania uzytkownika przy uzyciu podanego hasła
        if(!(statusLogowania = this->probaLogowania(nazwaUzytkownika, haslo)))
          informacjaZwrotna = informacjaZwrotna + "Haslo jest niepoprawne ! \n";

      } else 
        informacjaZwrotna = informacjaZwrotna + "Konto o nazwie (" + nazwaUzytkownika + ") nie istnieje !\n";

    } while (!statusLogowania);

    cout << "\nPoprawnie zalogowano na konto!\n";
    this -> kontoWybrane = true;
    this -> przegladanieBezKonta = false;
    Sleep(1000);

    if(_return)
      return;
    else
      this->zakupy();
  }

  void start() {
    while(true){
      maksymalnaOpcja = 3;
      zaznaczonaOpcja = 1;
      while(true){
        system("cls");
        cout << "Witaj w sklepie online !\n";
        cout << "Aby korzystac ze sklepu musze wiedziec z kim mam doczynienia !\n";
        cout << "Poruszajac sie stralkami w gore i w dol wybierz opcje i zatwierdz ja enterem\n\n";

        cout << "Klient"                    << czyWybrany(1, zaznaczonaOpcja) << "\n";
        cout << "Menadzer"                  << czyWybrany(2, zaznaczonaOpcja) << "\n";
        cout << "Zakoncz Prace Programu"    << czyWybrany(3, zaznaczonaOpcja) << "\n";
        
        system("pause>nul");

          if (GetAsyncKeyState(VK_DOWN))
            if(zaznaczonaOpcja == maksymalnaOpcja) 
              zaznaczonaOpcja = 1;
            else 
              zaznaczonaOpcja++;
          else if (GetAsyncKeyState(VK_UP)) 
            if(zaznaczonaOpcja == 1) 
              zaznaczonaOpcja = maksymalnaOpcja;
            else 
              zaznaczonaOpcja--;
          else if(GetAsyncKeyState(VK_RETURN)) 
            break;
      }

      switch(zaznaczonaOpcja) {
        case 1: this->logowanieMenu(false); break;
        case 2: this->dostawaMenu(); break;
        case 3: return; break;
      }
    }
  }

  void dostawaMenu() {
    map<int, Produkt*> stareDaneMapy = this->kopiujListeProduktow();
    vector<int> listaZmienionychId;
    vector<int> listaDodanychId;

    bool czyZmiana = false;
    bool czyZapisal = false;

    string tytulMenu = "Menu przyjmowania dostaw do magazynu";
    vector<string> opcje;

    while(true) {
      zaznaczonaOpcja = 1;
      opcje.clear();

      if(czyZmiana) {
        opcje = {"Dodaj nowy",
                 "Dodaj istniejacy",
                 "Lista wprowadzonych zmian",
                 "Zapisz zmiany",
                 "Powrot"};
      } else {
        opcje = {"Dodaj nowy",
                 "Dodaj istniejacy",
                 "Powrot"};
      }

      switch(kreatorMenu(tytulMenu, opcje)) {
        case 1: {
            int wynikFunckji = this->dodajProdukt();
            
            if(wynikFunckji > 0) {
              czyZmiana = true;
              czyZapisal = false;
              listaDodanychId.push_back(wynikFunckji); 
            }
          } break;

        case 2: {
            int wynikFunckji = this->aktualizacjaDanychProduktu();
            
            if(wynikFunckji > 0) {
              bool zapiszID = true;
              czyZmiana = true;
              czyZapisal = false;
              
              for(auto e : listaZmienionychId) {
                if(e == wynikFunckji)
                  zapiszID = false;
              }

              for(auto e : listaDodanychId) {
                if(e == wynikFunckji)
                  zapiszID = false;
              }

              if(zapiszID)
                listaZmienionychId.push_back(wynikFunckji);
            }
          } break;

        case 3: {
          if(czyZmiana)
            this->listaWprowadzonychZmian(stareDaneMapy, &listaZmienionychId, &listaDodanychId, this->kopiujListeProduktow());
          else
            return;
        } break;

        case 4: {
          this->zapiszZmianyProduktow();
          czyZapisal = true;
          czyZmiana = false;
          listaZmienionychId.clear();
          listaDodanychId.clear();
          stareDaneMapy = this->kopiujListeProduktow();
        } break;
        case 5: {
          if(czyZmiana && !czyZapisal) {
            system("cls");
            string informacja = "Nie zapisales zmian !\nJesli wybierzesz OK to zostana one porzucone !";
            vector<string> opcje = {"OK", "ANULUJ"};

            switch(kreatorMenu(informacja, opcje)) {
              case 1: {
                this->porzucZmiany(stareDaneMapy);
                return;
              } break;
            } 
          } else if(czyZapisal)
            return;
        } break;
      }
    }
  }

  void logowanieMenu(bool _return) {
    system("cls");
    this->przegladanieBezKonta = false;
    this->kontoWybrane = false;

    string tytulMenu = "Wybierz odpowiednia dla Siebie opcje !";

    vector<string> opcje;

    if(!_return)
      opcje = {"Mam konto",
               "Chce stworzyc konto",
               "Nie chce sie logowac",
               "Powrot"};
    else
      opcje = {"Mam konto",
               "Chce stworzyc konto",
               "Powrot"};

    do {
        switch (kreatorMenu(tytulMenu, opcje)) {
          case 1: this -> logowanie(_return); break;

          case 2: this -> rejestracja(); break;

          case 3: {
              this -> kontoWybrane = false;
              this -> przegladanieBezKonta = true;

              if(_return)
                return;
              else
                this->zakupy();
              break;
          }

          case 4: return; break;
        }
      system("cls");
    } while (!(this -> kontoWybrane) && this -> przegladanieBezKonta != true);
  }

  void zakupy() {
    string tytulMenu = "Wybierz zdarzenie !";
    vector<string> opcje;
    bool stanKoszyka = false;
    int iloscWKoszyku = 0;

    while(true){
      if(this->przegladanieBezKonta)
        opcje = {"Wyszukaj produkt po nazwie",
                "Pokaz liste wszystkich produktow",
                "Moj koszyk",
                "Zaloguj",
                "Wyjscie"};
      else 
        opcje = {"Wyszukaj produkt po nazwie",
                "Pokaz liste wszystkich produktow",
                "Moj koszyk",
                "Stan konta",
                "Wyloguj",
                "Wyjscie"};

      switch(kreatorMenu(tytulMenu, opcje)) {
        case 1: {
          Produkt * _produkt = this->wyszukiwarkaProduktuPoNazwie();
          if (_produkt == nullptr) {
            delete _produkt;
            break;
          }

          if (this->menuDodawaniaDoKoszyka(_produkt) != -1) {
            stanKoszyka = true;
            iloscWKoszyku++;
          }

          _produkt = nullptr;
          delete _produkt;
        } break;
        
        case 2: this->wyswietlWyszystkieProdukty(); break;

        case 3: this->menuKoszyk(&stanKoszyka, &iloscWKoszyku); break;

        case 4: {
          if(this->przegladanieBezKonta) 
            this->logowanieMenu(true);
          else {
            system("cls");
            cout << "Stan konta " << this->aktualnyKlient()->getNazwaUzytkownika() << " -> " << this->aktualnyKlient()->getMoney() << " zl\n";
            system("pause>nul");
          }
        } break;

        case 5: {
          if(this->przegladanieBezKonta) {
            if(stanKoszyka) {
              string tytulMenu = "W koszyku znajduja sie przedmioty\nJesli teraz wyjdziesz stracisz swoje zakupy!";
              vector<string> opcje = {"OK", "ANULUJ"};

              if(kreatorMenu(tytulMenu, opcje) == 1) {
                iloscWKoszyku = 0;
                stanKoszyka = false;
                this->wyczyscKoszyk(false, this->getProdukty());
                return;
              }
            } else 
              return;
          } else
            this->wyloguj();
        } break;

        case 6: {
          if(stanKoszyka) {
              string tytulMenu = "W koszyku znajduja sie przedmioty\nJesli teraz wyjdziesz stracisz swoje zakupy!";
              vector<string> opcje = {"OK", "ANULUJ"};

              if(kreatorMenu(tytulMenu, opcje) == 1) {
                iloscWKoszyku = 0;
                stanKoszyka = false;
                this->wyczyscKoszyk(false, this->getProdukty());
                return;
              }
            } else 
              return;
          }break;
      }
    }
  }

  void menuKoszyk(bool *stanKoszyka, int *iloscWKoszyku) { 
        string tytulMenu = "Zarzadzanie swoim koszykiem !";
        vector<string> opcje;

        while(true) {
            while(true) {
                if(*stanKoszyka) {
                  opcje = {"Zawartosc",
                           "Zmien ilsoc produktu w koszyku",
                           "Zamow i zaplac",
                           "Powrot"};
                } else 
                  opcje = {"Powrot"};

                switch (kreatorMenu(tytulMenu, opcje)) {
                  case 1: {
                    if(*stanKoszyka)
                      this->wyswietlKoszyk(this->kopiujListeProduktow(), true);
                    else {
                      stanKoszyka = nullptr;
                      iloscWKoszyku = nullptr;

                      delete stanKoszyka;
                      delete iloscWKoszyku;
                      return;
                    }
                  } break;

                  case 2: {
                    this->zmienIloscProduktuWKoszyku(stanKoszyka, iloscWKoszyku, this->getProdukty()); 
                    if(*iloscWKoszyku <= 0)
                      *stanKoszyka = false;
                  } break;

                  case 3: {
                    while(przegladanieBezKonta) {
                      system("cls");
                      string tytulMenu = "Aby kupic produkty ze swojego koszyka musisz sie zalogowac !";
                      vector<string> opcje = {"Loguj", "Anuluj"};

                      if(kreatorMenu(tytulMenu, opcje) == 1) 
                        this->logowanieMenu(true);

                      break;
                    }

                    if(!przegladanieBezKonta) {
                      bool czyZaplacil = this->zamowIzaplac(this->getProdukty(), this->aktualnyKlient());

                      if(czyZaplacil) {
                        this->wyczyscKoszyk(true, this->getProdukty());
                        this->zapiszZmianyProduktow();
                        this->zaktualizujPlikKlientow();
                        *iloscWKoszyku = 0;
                        *stanKoszyka = false;
                        
                        stanKoszyka = nullptr;
                        iloscWKoszyku = nullptr;

                        delete stanKoszyka;
                        delete iloscWKoszyku;
                        return;
                      }
                    }
                  } break;

                  case 4: {
                    stanKoszyka = nullptr;
                    iloscWKoszyku = nullptr;

                    delete stanKoszyka;
                    delete iloscWKoszyku;
                    return;
                  } break;
                }
            }
        }

        stanKoszyka = nullptr;
        iloscWKoszyku = nullptr;

        delete stanKoszyka;
        delete iloscWKoszyku;
        return;
    }

};
 
#endif