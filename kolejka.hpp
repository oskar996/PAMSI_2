#ifndef KOLEJKA_HPP
#define kOLEJKA_HPP

#include <iostream>

using namespace std;

class wierzcholek_m;
class krawedz_m;


struct elem_kopca{
    int priorytet;
    wierzcholek_m* dane;
};

void zamien(elem_kopca **x, elem_kopca **y);
 
class MinKop{ 
    
    elem_kopca **Tab;   // wskaźnik na liste kopca 
    int poj;            // maksymalny rozmiar kopca 
    int a_roz;          // aktualny rozmiar kopca 

public: 
    MinKop(int poj1); 
    void MinKopcowanie(int i); 
    int rodzic(int i) { return (i-1)/2; } 
    int lewy(int i) { return (2*i + 1); } 
    int prawy(int i) { return (2*i + 2); } 
    elem_kopca* zwrocMin(); 
    void decreaseKey(wierzcholek_m* wie, int new_val); 
    int liczba_elem()    {return a_roz; }
    elem_kopca* podajMin()    { return Tab[0]; }  
    void wsadz(wierzcholek_m* wie, int prio); 
    wierzcholek_m* Zwroc(int i){
        return Tab[i]->dane;
    }
    int Zwroc_prio(int i){
        return Tab[i]->priorytet;
    }
}; 
   
 
   
#endif