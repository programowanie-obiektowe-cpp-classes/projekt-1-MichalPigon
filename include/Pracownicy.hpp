#ifndef PRACOWNIK_HPP
#define PRACOWNIK_HPP

#include "RandomName.hpp"
#include <iostream>

using namespace std;
class Pracownik{
public:
    Pracownik(){
        imie = getRandomName();
    }
    double get_salary() {return placa;}
    string imie;
    virtual void print()
    {
        cout<<imie<<endl;
    }
    virtual ~Pracownik() {}
    virtual string get_type() {return "nie wiadomo";}
protected:
    double placa = 0;
};
class Inz : public Pracownik{
public:
    Inz() {placa=8000;}
    void print() override {cout<< imie << " "<< placa<<" PLN, wydzial: "<<wydzial<< endl;}
    string get_type()  override { return "inz"; }
private:
    string wydzial = "MEiL";
};
class Mag : public Pracownik{
public:
    Mag() {placa = 4000;}
    void print() override {cout<< imie << " "<< placa<<" PLN, wozek:"<<wozek<< endl;}
    string get_type()  override { return "mag"; }
private:
    bool wozek = true;
};
class Mkt : public Pracownik{
public:
    Mkt() {placa = 6500;}
    void print() override {cout<< imie << " "<< placa<<" PLN, follows: "<<follows<<endl;}
    string get_type()  override { return "mkt"; }
private:
    int follows = 100;
};
class Rob : public Pracownik{
public:
    Rob() {placa = 5000;}
    void print() override {cout<< imie << " "<< placa<<" PLN, but: "<<but<< endl;}
    string get_type()  override { return "rob"; }
private:
    double but = 43;
};

#endif