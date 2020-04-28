#include "kolejka.hpp"

void zamien(elem_kopca **x, elem_kopca **y){                //zamiana dwóch elementów 
    elem_kopca* pom = *x; 
    *x = *y; 
    *y = pom; 
}

MinKop::MinKop(int poj1){

    a_roz = 0; 
    poj = poj1; 
    Tab = new elem_kopca* [poj1]; 
} 
   
void MinKop::wsadz(wierzcholek_m* wie, int prio){ 
    if (a_roz == poj){
        cout << "\n Przepełnienie kopca \n"; 
        return; 
    } 
    
    elem_kopca* h = new elem_kopca;         //tworzenie nowego elementu kopca
    h->dane = wie;
    h->priorytet = prio;
 
    a_roz++; 
    int i = a_roz - 1; 
    Tab[i] = h; 
   
    while (i != 0 && Tab[rodzic(i)]->priorytet > Tab[i]->priorytet){ 
       elem_kopca* pom=Tab[i];
       Tab[i]=Tab[rodzic(i)];
       Tab[rodzic(i)]=pom;
       //zamien(&Tab[i], &Tab[rodzic(i)]); 
       i = rodzic(i); 
    } 
    MinKopcowanie(0); 
}

 
void MinKop::MinKopcowanie(int i){ 
    
    int l = lewy(i); 
    int r = prawy(i); 
    int najmniejszy = i; 
    
    if (l < a_roz && Tab[l]->priorytet < Tab[i]->priorytet){ 
        najmniejszy = l; 
    }
    
    if (r < a_roz && Tab[r]->priorytet < Tab[najmniejszy]->priorytet){ 
        najmniejszy = r; 
    }
    
    if (najmniejszy != i) 
    { 
        zamien(&Tab[i], &Tab[najmniejszy]); 
        MinKopcowanie(najmniejszy);
    } 
}
  
 
void MinKop::decreaseKey(wierzcholek_m* wie, int new_val) 
{ 
    int i=0;
    
    while(wie != Tab[i]->dane){
        i++;
        if(i>a_roz){
            return;
        }
    }
    
    Tab[i]->priorytet = new_val; 

    while (i != 0 && Tab[rodzic(i)]->priorytet > Tab[i]->priorytet) 
    { 
       zamien(&Tab[i], &Tab[rodzic(i)]); 
       i = rodzic(i); 
    }
    MinKopcowanie(0); 
} 
   
elem_kopca* MinKop::zwrocMin() 
{ 
    if (a_roz <= 0){
        cout<<"blad"<<endl;
        return nullptr; 
    }
    else if (a_roz == 1) 
    { 
        a_roz--; 
        return Tab[0]; 
    } 
   
    elem_kopca* root = Tab[0]; 
    Tab[0] = Tab[a_roz-1]; 
    a_roz--; 
    MinKopcowanie(0); 
  
    return root; 
}