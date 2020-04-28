#ifndef KOLEJKAL_HPP
#define kOLEJKAL_HPP

#include <iostream>

using namespace std;

class wierzcholek_l;
class krawedz_l;

/////////////////////////////////////////////////////////////////////////////////////

struct elem_kopcaL{
    int priorytet;
    wierzcholek_l* dane;
};

void zamien(elem_kopcaL **x, elem_kopcaL **y);
 
class MinKopL{ 
    
    elem_kopcaL **Tab;   // wskaźnik na liste kopca 
    int poj;            // maksymalny rozmiar kopca 
    int a_roz;          // aktualny rozmiar kopca 

public: 

    MinKopL(int poj1); 
    void MinKopcowanie(int i); 
    int rodzic(int i) { return (i-1)/2; } 
    int lewy(int i) { return (2*i + 1); } 
    int prawy(int i) { return (2*i + 2); } 
    elem_kopcaL* zwrocMin(); 
    void decreaseKey(wierzcholek_l* wie, int new_val); 
    int liczba_elem()    {return a_roz; }
    elem_kopcaL* podajMin()    { return Tab[0]; }  
    void wsadz(wierzcholek_l* wie, int prio);
     
}; 



#endif