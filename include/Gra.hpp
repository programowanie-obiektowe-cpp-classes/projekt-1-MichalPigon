#ifndef GRA_HPP
#define GRA_HPP

#include "Firma.hpp"

class Gra{
public:
    Gra(){
        f = make_unique<Firma>();
    }
    unique_ptr<Firma> f;
    void set_stan(bool state){stan = state;}
    bool get_stan(){return stan;}
    void tick()
    {
        cout<<"KONIEC TURY"<<endl;
        f->otrzymaj_przychod();
        f->splac_raty();
        f->zaplac_wynagrodzenie();
        cout<<"Stan firmy na koniec tury: "<<endl;
        f->stan();
        stan = false;
    }
    void akcja_gracza(string s)
    {
        if(s == "lp")
        {
            f->drukuj_pracownikow();
        }
        else if(s == "zinz")
        {
            f->zatrudnij(make_unique<Inz>());
            stan = true;
        }
        else if(s == "zmag")
        {
            f->zatrudnij(make_unique<Mag>());
        }
        else if(s == "zmkt")
        {
            f->zatrudnij(make_unique<Mkt>());
        }
        else if(s == "zrob")
        {
            f->zatrudnij(make_unique<Rob>());
        }
        else if(s == "kred")
        {   
            double kwota, limit;
            limit = M * f->wartosc_firmy() - f->calk_zadluzenie();
            if(limit>0)
            {   
                int czas_splaty = X + 1;
                kwota = limit + 1;
                cout<<"Podaj kwote mniejsza od "<<limit<<" aby zadluzenie nie przekroczylo dozwolonej wartosci"<<endl;
                while(true)
                    {
                        cin>>kwota;
                        if (kwota > limit)
                        {
                            cout<<"Kwota niedozwolona- zadluzenie nie moze wzrosnac ponad "<<M * f->wartosc_firmy()<<endl;
                        }
                        else {break;}
                    }
                cout<<"Podaj czas splaty mniejszy od  "<<X + 1<<endl;
                while(true) 
                {
                    cin>>czas_splaty;
                    if(cin.fail() || czas_splaty>X)
                    {
                        cin.clear(); // Clear the error flag
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout<<"Niedozwolony czas splaty, sprobuj ponownie"<<endl;
                    }
                    else {break;}
                }
                f->wez_kredyt(kwota, czas_splaty);
                cout<<"Wzieto kredyt"<<endl;
            }
            else if(kwota>limit && f->wartosc_firmy()==0) {cout<<"Firma jest bezwartosciowa, nie mozna wziac kredytu"<<endl;}
            else {cout<<"Zadluzenie za duze- nie mozna wziac kredytu"<<endl;}
        }
        else if (s == "kt")
        {
            tick();
            stan = false;
        }
        else {cout<<"Nieznana komenda, sprobuj ponownie"<<endl;}
    }
private:
    bool stan =  true;
};

#endif