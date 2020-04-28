#include "grafM.hpp"


void graf_m::Dodaj_krawedz(int info, wierzcholek_m* poc, wierzcholek_m* koni){
    krawedz_m* kraw = new krawedz_m;
    kraw->Dodaj_info(info);
    lista_krawedzi_m.Dodaj_na_poczatek(kraw);
    kraw->Dodaj_pocz(poc);
    kraw->Dodaj_kon(koni);
    kraw->Dodaj_pozycje(lista_krawedzi_m.Pierwszy_wsk());
    Macierz[poc->Zwroc_info()][koni->Zwroc_info()]=kraw;
    Macierz[koni->Zwroc_info()][poc->Zwroc_info()]=kraw;
}

void graf_m::Dodaj_wierzch(int info){
    wierzcholek_m* wierzch= new wierzcholek_m;
    wierzch->Dodaj_info(info);
    lista_wierzcholkow_m.Dodaj_na_poczatek(wierzch);
    wierzch->Dodaj_pozycje(lista_wierzcholkow_m.Pierwszy_wsk());
}

bool graf_m::Czy_pusty(){
    if(lista_wierzcholkow_m.Czy_pusta()){
        if(lista_krawedzi_m.Czy_pusta()){
            return true;
        }
    }    
    return false;
}

void graf_m::Wyczysc_graf(){
    wierzcholek_m* pom1;
    krawedz_m* pom2;
    int pom;

    while(!lista_krawedzi_m.Czy_pusta()){
        pom2 = lista_krawedzi_m.Usun_z_przodu();
        
        
        delete pom2;
    }
    pom=lista_wierzcholkow_m.Dlugosc_tablicy();
    while(!lista_wierzcholkow_m.Czy_pusta()){
        pom1=lista_wierzcholkow_m.Usun_z_przodu();
        
        delete pom1;
    }

    for(int i =0;i<pom;i++){
        delete [] Macierz[i];
    }
    delete Macierz;


}

int graf_m::Ile_sa(int pozycja_wierzch){
    int ilosc = 0;
    for(int i=0;i<lista_wierzcholkow_m.Dlugosc_tablicy();i++){
        if(Macierz[pozycja_wierzch][i]!=nullptr){
            ilosc++;
        }
    }
    return ilosc;
}

krawedz_m* graf_m::Zwroc_sa(int wierzch,int nr_sa){
    int sasiedzi=0;
        
        for(int i=0;i<lista_wierzcholkow_m.Dlugosc_tablicy();i++){
            if(Macierz[wierzch][i]!=nullptr){
                sasiedzi++;
                
                if(sasiedzi==nr_sa){
                    return Macierz[wierzch][i];
                }
            }
        }
        cout<<"blad"<<endl;
        return nullptr;
    }



void graf_m::Losuj_graf2(int ile_wierzch, double gestosc){
    int max_licz_kraw=(ile_wierzch*(ile_wierzch-1))/2;
    int li_kraw = gestosc*max_licz_kraw;

    wierzcholek_m* pom1;
    wierzcholek_m* pom2;
        
    int los_ind1;
    int los_ind2;
    
    Lista<wierzcholek_m*> tab_pom1;
    Lista<wierzcholek_m*> tab_pom2;                          
        
    Macierz = new krawedz_m**[ile_wierzch];
    for(int i=0;i<ile_wierzch;i++){
        Macierz[i]=new krawedz_m*[ile_wierzch];
        for(int k=0;k<ile_wierzch;k++){
            Macierz[i][k]=nullptr;
        }
    }
    wielkosc_mac=ile_wierzch;
    
    
    
    for(int i=ile_wierzch-1;i>=0;i--){                             
        wierzcholek_m* wierz = new wierzcholek_m;
        wierz->Dodaj_info(i);                                  
        lista_wierzcholkow_m.Dodaj_na_poczatek(wierz);
        wierz->Dodaj_pozycje(lista_wierzcholkow_m.Pierwszy_wsk());
        tab_pom1.Dodaj_na_poczatek(wierz);
    }
    
    los_ind1=rand()%tab_pom1.Dlugosc_tablicy();
    tab_pom2.Dodaj_na_poczatek(tab_pom1.Usun(los_ind1));
    los_ind1=rand()%tab_pom1.Dlugosc_tablicy();
    Dodaj_krawedz(rand()%999+1,tab_pom2.Pierwszy(),tab_pom1.Odczytaj(los_ind1));
    tab_pom2.Dodaj_na_poczatek(tab_pom1.Usun(los_ind1));
    
        
    while(!tab_pom1.Czy_pusta()){
        los_ind1=rand()%tab_pom1.Dlugosc_tablicy();
        los_ind2=rand()%tab_pom2.Dlugosc_tablicy();
        Dodaj_krawedz(rand()%999+1,tab_pom2.Odczytaj(los_ind2),tab_pom1.Odczytaj(los_ind1));
        tab_pom2.Dodaj_na_poczatek(tab_pom1.Usun(los_ind1));
    }
    
    while(lista_krawedzi_m.Dlugosc_tablicy() < li_kraw){
        los_ind1=rand()%lista_wierzcholkow_m.Dlugosc_tablicy();
        los_ind2=rand()%lista_wierzcholkow_m.Dlugosc_tablicy();
        pom1= lista_wierzcholkow_m.Odczytaj(los_ind1);
        pom2= lista_wierzcholkow_m.Odczytaj(los_ind2);

        /*if(lista_wierzcholkow_m.Odczytaj(los_ind1) != lista_wierzcholkow_m.Odczytaj(los_ind2) && Macierz[los_ind1][los_ind2]==nullptr){
            Dodaj_krawedz(10000,lista_wierzcholkow_m.Odczytaj(los_ind1),lista_wierzcholkow_m.Odczytaj(los_ind2));
        }*/
        if(pom1 != pom2 && Macierz[los_ind1][los_ind2]==nullptr){
            Dodaj_krawedz(rand()%999+1,pom1,pom2);
        }
    }
}
    
bool graf_m::Zapisz_graf_do_pliku(const char* NazwaPliku){
    fstream plik;
    krawedz_m* pom;

    plik.open(NazwaPliku,ios::out);
    if(plik.good()){
        plik << lista_wierzcholkow_m.Dlugosc_tablicy() << "  " << lista_krawedzi_m.Dlugosc_tablicy() <<endl;
        for(int i=0;i<lista_krawedzi_m.Dlugosc_tablicy();i++){
            pom=lista_krawedzi_m.Odczytaj(i);
            plik << pom->Zwroc_pocz()->Zwroc_info() <<"   "<<pom->Zwroc_kon()->Zwroc_info()<<"    "<<pom->Zwroc_info()<<endl;
        }
    }
    else{
        cout<<"Problem z plikiem"<<endl;
        return false;
    }
    plik.close();
    return true;
}

