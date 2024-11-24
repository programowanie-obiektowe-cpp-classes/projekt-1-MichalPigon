#include "Gra.hpp"

int main()
{
    class Gra g;
    g.f->stan();
    cout<<"Komendy do gry:\nzinz: zatrudnij inzyniera\nzmkt: zatrudnij marketingowca\nzmag: zatrudnij magazyniera\nzrob: zatrudnij robotnika"<<endl;
    cout<<"lp: wylistuj pracownikow\nkred: wez kredyt\nkt: zakoncz ture"<<endl;
    while(g.f->get_stan_konta()>0 && g.f->wartosc_firmy()<goal)
    {   
        g.set_stan(true);
        while(g.get_stan()==true)
            {
            string akcja;
            cin>>akcja;
            g.akcja_gracza(akcja);
            }
    }
    if(g.f->get_stan_konta()<=0) {cout<<"Porazka"<<endl;}
    else if(g.f->wartosc_firmy()>=goal) {cout<<"Zwyciestwo"<<endl;}
    else {cout<<"Cos poszlo nie tak"<<endl;}
    return 0;
    // Firma f;
    // unique_ptr<Pracownik> p = make_unique<Inz>();
    // cout<<f.oblicz_przychod()<<endl;
    // f.zatrudnij(move(p));
    // f.zatrudnij(make_unique<Inz>());
    // cout<<f.get_ninz()<<endl;
    // cout<<f.oblicz_przychod()<<endl;

}
