#ifndef FIRMA_HPP
#define FIRMA_HPP

#include <iostream>
#include <memory>
#include "RandomName.hpp"
#include "Pracownicy.hpp"
#include "constants.hpp"
#include <vector>
using namespace std;
class Kredyt{
public:
    Kredyt(double kwota, int czas_splaty):
    pozostale_raty(czas_splaty), dlug(kwota){
        odsetki = 1 + czas_splaty * 0.01;
    }
    double splac_rate()
    {
        double rata;
        if(pozostale_raty>0)
        {
            rata = dlug / pozostale_raty;
            dlug -= rata;
            pozostale_raty--;
            return rata * odsetki;
        }
        else {return dlug * odsetki;}
    }
    double get_dlug(){return dlug;}
private:
    double dlug, odsetki;
    int pozostale_raty;
};
class Firma{
public:
    Firma(){
        pracownicy.push_back(make_unique<Inz>());
        pracownicy.push_back(make_unique<Mag>());
        pracownicy.push_back(make_unique<Mkt>());
        pracownicy.push_back(make_unique<Rob>());
        n_prac = pracownicy.size();
        ninz = 1;
        nrob = 1;
        nmkt = 1;
        nmag = 1;
    }
    void stan()
    {
        cout<<"Wartosc firmy: "<<wartosc_firmy()<<endl;
        cout<<"Calkowite zadluzenie firmy: "<<calk_zadluzenie()<<endl;
        cout<<"Stan konta: "<<get_stan_konta()<<endl;
    }
    double calk_zadluzenie()
    {
        double zadluzenie = 0.0;
        if(kredyty.size()>0)
        {
            for(auto &it: kredyty)
            {
                zadluzenie += it->get_dlug();
            }
        }
        return zadluzenie;
    }
    void wez_kredyt(double kwota, int czas_splaty)
    {   
        auto k = make_unique<Kredyt>(kwota, czas_splaty);
        kredyty.push_back(move(k));
        n_kredytow++;
        stan_konta += kwota;

    }
    void splac_raty()
    {   if(kredyty.size()>0)
        {
            for(auto it = kredyty.begin(); it != kredyty.end();)
            {   
                double rata;
                rata = (*it)->splac_rate();
                if(rata==0)
                {
                    it = kredyty.erase(it);
                    cout<<"Gratulacje! W poprzedniej turze splacono jeden z kredytow"<<endl;
                }
                else 
                {
                    stan_konta -= rata; it++;
                    cout<<"Splacono rate wraz z odsetkami w wysokosci: "<<rata<<endl;
                }
            }
        }
        
    }
    void zatrudnij(unique_ptr<Pracownik> p)
    {
        cout<<"Sprawdzanie typu pracownika..."<<endl;
        if (p->get_type() == "inz")
        {
            ninz++;
            cout << "Zatrudniono Inzyniera" << endl;
        }
        else if (p->get_type() == "mkt")
        {
            nmkt++;
            cout << "Zatrudniono Marketingowca" << endl;
        }
        else if (p->get_type() == "mag")
        {
            nmag++;
            cout << "Zatrudniono Magazyniera" << endl;
        }
        else if (p->get_type() == "rob")
        {
            nrob++;
            cout << "Zatrudniono Robotnika" << endl;
        }
        else {cout<<"dupa"<<endl;}
        pracownicy.push_back(move(p));
        n_prac = pracownicy.size();
    }
    void drukuj_pracownikow() const
    {
        for (auto &it: pracownicy)
        {
            it->print();
        }
    }
    double get_stan_konta()
    {
        return stan_konta;
    }
    void zaplac_wynagrodzenie()
    {
        for (auto &it: pracownicy)
        {
            stan_konta -= it->get_salary();
        }
    }
    double oblicz_przychod()
    {
        double popyt, l_prod, poj_mag, l_sprzed, cena;
        popyt = double(nmkt) *  CMkt;
        poj_mag = double(nmag) * CMag;
        l_prod = double(nrob) * CR;
        if(l_prod>poj_mag)
        {
            l_prod = poj_mag;
        }
        if (l_prod>popyt) {l_sprzed = popyt;}
        else {l_sprzed = l_prod;}
        cena = double(ninz) * CI;
        return cena * l_sprzed;
    }
    void otrzymaj_przychod()
    {
        double przychod = oblicz_przychod();
        cout<<"Przychod w tym miesiacu: "<<przychod<<endl; 
        stan_konta += przychod;
        historia_przych.push_back(przychod);
    }
    double wartosc_firmy()
    {   
        double suma = 0.0;
        if(historia_przych.size()>0)
            {
            if(historia_przych.size()<=N)
            {
                for(auto &it: historia_przych)
                {
                    suma += it;
                }
                return suma / double(historia_przych.size());
            }
            else
            {
                for(int i = historia_przych.size() - 1; i>=historia_przych.size()-N; i--)
                {
                    suma += historia_przych[i];
                }
                return suma / double(N);
            }
            }
        else {return 0;}
    }
        
private:
    double stan_konta=110000;
    int n_prac, n_kredytow, ninz, nmag, nmkt, nrob;
    vector<unique_ptr<Pracownik>> pracownicy;
    vector<double> historia_przych;
    vector<unique_ptr<Kredyt>> kredyty;
    

};

#endif