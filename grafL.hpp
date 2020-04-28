#ifndef GRAFL_HPP
#define GRAFL_HPP

#include "kolejkaL.hpp"
#include "lista.hpp"
#include <fstream>

using namespace std;

class wierzcholek_l;
class krawedz_l{
    int inform;
    wierzcholek_l *wierzch_pocz;
    wierzcholek_l *wierzch_kon;
    El_listy<krawedz_l*> *poz_na_lis_k;

    public:
    void Dodaj_info(int nowy){
        inform = nowy;
    }
    void Dodaj_pocz(wierzcholek_l *wierzch){
        wierzch_pocz = wierzch;
    }
    void Dodaj_kon(wierzcholek_l *wierzch){
        wierzch_kon = wierzch;
    }
    void Dodaj_pozycje(El_listy<krawedz_l*> *poz){
        poz_na_lis_k=poz;
    }
    int Zwroc_info(){
        return inform;
    }
    wierzcholek_l* Zwroc_pocz(){
        return wierzch_pocz;
    }
    wierzcholek_l* Zwroc_kon(){
        return wierzch_kon;
    }
    El_listy<krawedz_l*>* Zwroc_poz(){
        return poz_na_lis_k;
    }


};

class wierzcholek_l{
    int inform;
    El_listy<wierzcholek_l*> *poz_na_lis_w;
    Lista<krawedz_l*> lista_sa;

    public:
    void Dodaj_info(int nowy){
        inform = nowy;
    }
    void Dodaj_pozycje(El_listy<wierzcholek_l*> *poz){
        poz_na_lis_w=poz;
    }
    void Dodaj_do_listy(krawedz_l* wierzch){
        lista_sa.Dodaj_na_poczatek(wierzch);
    }
    int Ile_sa(){
        return lista_sa.Dlugosc_tablicy();
    }
    bool Czy_sa(wierzcholek_l* sasiad){
        for(int i=0;i<lista_sa.Dlugosc_tablicy();i++){
            if(lista_sa.Odczytaj(i)->Zwroc_kon()==sasiad || lista_sa.Odczytaj(i)->Zwroc_pocz()==sasiad){
                return true;
            }
        }
        return false;
    }
    krawedz_l* Zwroc_sa(int ktory){
        return lista_sa.Odczytaj(ktory);
    }
    int Zwroc_info(){
        return inform;
    }
    El_listy<wierzcholek_l*>* Zwroc_poz(){
        return poz_na_lis_w;
    }


};

class graf_l{
    
    
    Lista< wierzcholek_l* > lista_wiercholkow_l;
    Lista< krawedz_l* > lista_krawedzi_l;

    public:
    graf_l(){

    }
    ~graf_l(){

    }
    void Dodaj_krawedz(int info, wierzcholek_l* poc, wierzcholek_l* koni);
    void Dodaj_wierzch(int info);
    wierzcholek_l* Zwroc_wierzch(int poz){return lista_wiercholkow_l.Odczytaj(poz);}
    krawedz_l* Zwroc_kraw(int poz){return lista_krawedzi_l.Odczytaj(poz);}
    void Wyczysc_graf();
    bool Czy_pusty();
    int Ile_wierz(){return lista_wiercholkow_l.Dlugosc_tablicy();}
    int Ile_kraw(){return lista_krawedzi_l.Dlugosc_tablicy();}
    void Losuj_graf2(int ile_wierzch, double gestosc);
    bool Zapisz_graf_do_pliku(const char* NazwaPliku);
    bool Wczytaj_graf(const char* NazwaPliku);
};

#endif