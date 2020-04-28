#ifndef GRAFM_HPP
#define GRAFM_HPP


#include <fstream>
#include "lista.hpp"
#include "kolejka.hpp"

class wierzcholek_m;
class krawedz_m{
    int inform;
    wierzcholek_m *wierzch_pocz;
    wierzcholek_m *wierzch_kon;
    El_listy<krawedz_m*> *poz_na_lis_k;
    
    public:
    void Dodaj_info(int nowy){
        inform = nowy;
    }
    void Dodaj_pocz(wierzcholek_m *wierzch){
        wierzch_pocz = wierzch;
    }
    void Dodaj_kon(wierzcholek_m *wierzch){
        wierzch_kon = wierzch;
    }
    void Dodaj_pozycje(El_listy<krawedz_m*> *poz){
        poz_na_lis_k=poz;
    }
    int Zwroc_info(){
        return inform;
    }
    wierzcholek_m* Zwroc_pocz(){
        return wierzch_pocz;
    }
    wierzcholek_m* Zwroc_kon(){
        return wierzch_kon;
    }
    El_listy<krawedz_m*>* Zwroc_poz(){
        return poz_na_lis_k;
    }
};

class wierzcholek_m{
    int inform;
    El_listy<wierzcholek_m*> *poz_na_lis_w;
    
    public:

    void Dodaj_info(int nowy){
        inform = nowy;
    }
    void Dodaj_pozycje(El_listy<wierzcholek_m*> *poz){
        poz_na_lis_w=poz;
    }
    int Zwroc_info(){
        return inform;
    }
    El_listy<wierzcholek_m*>* Zwroc_poz(){
        return poz_na_lis_w;
    }
};


class graf_m{
    Lista <krawedz_m*> lista_krawedzi_m;
    Lista <wierzcholek_m*> lista_wierzcholkow_m;
    krawedz_m*** Macierz;
    int wielkosc_mac;

    public:
    graf_m(){}
    graf_m(int ile_wierzch){
        Macierz = new krawedz_m**[ile_wierzch];
        for(int i=0;i<ile_wierzch;i++){
            Macierz[i]=new krawedz_m*[ile_wierzch];
            for(int k=0;k<ile_wierzch;k++){
                Macierz[i][k]=nullptr;
            }
        }
        wielkosc_mac=ile_wierzch;
    }
    void Dodaj_krawedz(int info, wierzcholek_m* poc, wierzcholek_m* koni);
    void Dodaj_wierzch(int info);
    int Ile_wierz() {return lista_wierzcholkow_m.Dlugosc_tablicy();}
    int Ile_kraw() {return lista_krawedzi_m.Dlugosc_tablicy();}
    bool Czy_pusty();
    wierzcholek_m* Zwroc_wierzch(int poz) {return lista_wierzcholkow_m.Odczytaj(poz);}
    krawedz_m* Zwroc_kraw(int poz) {return lista_krawedzi_m.Odczytaj(poz);}
    void Wyczysc_graf();
    int Ile_sa(int pozycja_wierzch);
    krawedz_m* Zwroc_sa(int wierzch,int nr_sa);
    void Losuj_graf2(int ile_wierzch, double gestosc);
    krawedz_m*** Zwroc_macierz() {return Macierz;}
    bool Zapisz_graf_do_pliku(const char* NazwaPliku);
};

#endif