#ifndef FUNKCJE_H
#define FUNKCJE_H

#include <iostream>
#include <algorithm>
#include <iomanip>

using namespace std;

namespace Funkcje {
    int zaznaczonaOpcja;
    int maksymalnaOpcja;

    enum WynikWcisnietegoKlawisza {
        Tak,
        Nie,
        Cofnij
    };

    enum TypWpisywany {
        Numeryczne,
        NumeryczneINT,
        String
    };

    enum PoprawnoscStringa{
        Znak,
        Dlugosc,
        Istnieje,
        Ok
    };

    WynikWcisnietegoKlawisza wpiszDoStringa(string *dana, char character, Funkcje::TypWpisywany typ);

    void dodajZnakDoStringa(string *dana, char character, Funkcje::TypWpisywany typ);

    string czyWybrany(int indeks, int zaznaczonaOpcja);

    PoprawnoscStringa sprawdzString(string dana);

    string duzeLitery(string _string);

    int kreatorMenu(string tytulMenu, vector<string> opcje);
};

Funkcje::WynikWcisnietegoKlawisza Funkcje::wpiszDoStringa(string *dana, char character, Funkcje::TypWpisywany typ) {
            switch(character) {
            case 8: {
                if(dana->length() >= 1)
                dana->pop_back();
            } break;
            case 27: return Cofnij; break;
            case 13: return Nie; break;

            default: Funkcje::dodajZnakDoStringa(dana, character, typ);
            }
        return Tak;
    }

void Funkcje::dodajZnakDoStringa(string *dana, char character, Funkcje::TypWpisywany typ) {
        string allowedCharacters = "";

        if(typ == Numeryczne)
            allowedCharacters = "1234567890.";
        else if(typ == String)
            allowedCharacters = "abcdefghijklmnoprstuwxyzABCDEFGHIJKLMNOPRSTUOWXYZ1234567890!@#$%^&*(){}[]?qQvV,./*-+";
        else if(typ == NumeryczneINT)
            allowedCharacters = "1234567890";

        bool isCorrect = false;
        for(auto c : allowedCharacters) {
            if(c == character)
                isCorrect = true;
        }

        if(isCorrect)
            dana->push_back(character);
    }

string Funkcje::czyWybrany(int indeks, int zaznaczonaOpcja) {
        return (indeks == zaznaczonaOpcja) ? " <--" : " ";
    }

Funkcje::PoprawnoscStringa Funkcje::sprawdzString(string dana) {
        for (char znak : dana) {
            if (znak == ' ')
                return Znak;
        }

        if (dana.length() < 3)
            return Dlugosc;

        return Ok;
    }

string Funkcje::duzeLitery(string _string) {
    transform(_string.begin(), _string.end(), _string.begin(), ::toupper);
    return _string;
}

int Funkcje::kreatorMenu(string tytulMenu, vector<string> opcje) {
    int _ileOpcji = opcje.size() + 1;
    zaznaczonaOpcja = 1;
    maksymalnaOpcja = _ileOpcji - 1;

    
    while(true) {
        system("cls");

        cout << tytulMenu << "\n\n";

        for(int i = 1; i < _ileOpcji; i++) {
            cout << setprecision(2) << opcje.at(i-1) << czyWybrany(i, zaznaczonaOpcja) << "\n";
        }

        system("pause>nul");

        if (GetAsyncKeyState(VK_DOWN)){
            if(zaznaczonaOpcja == maksymalnaOpcja) { 
                zaznaczonaOpcja = 1;
            } else 
                zaznaczonaOpcja++;
        } else if (GetAsyncKeyState(VK_UP)) {
            if(zaznaczonaOpcja == 1) 
                zaznaczonaOpcja = maksymalnaOpcja;
            else {
                zaznaczonaOpcja--;
            }
        } else if(GetAsyncKeyState(VK_RETURN)) { break; }
    }

    return zaznaczonaOpcja;
}

#endif