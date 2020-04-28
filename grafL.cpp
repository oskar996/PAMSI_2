#include "grafL.hpp"

void graf_l::Dodaj_krawedz(int info, wierzcholek_l* poc, wierzcholek_l* koni){
    krawedz_l* kraw = new krawedz_l;
    kraw->Dodaj_info(info);
    lista_krawedzi_l.Dodaj_na_poczatek(kraw);
    kraw->Dodaj_pocz(poc);
    poc->Dodaj_do_listy(kraw);
    kraw->Dodaj_kon(koni);
    koni->Dodaj_do_listy(kraw);
    kraw->Dodaj_pozycje(lista_krawedzi_l.Pierwszy_wsk());
}

void graf_l::Dodaj_wierzch(int info){
    wierzcholek_l* wierz = new wierzcholek_l;
    wierz->Dodaj_info(info);
    lista_wiercholkow_l.Dodaj_na_poczatek(wierz);
    wierz->Dodaj_pozycje(lista_wiercholkow_l.Pierwszy_wsk());
}

void graf_l::Wyczysc_graf(){
    wierzcholek_l* pom1;
    krawedz_l* pom2;
        
    while(!lista_krawedzi_l.Czy_pusta()){
        pom2 = lista_krawedzi_l.Usun_z_przodu();
        delete pom2;
    }

    while(!lista_wiercholkow_l.Czy_pusta()){
        pom1=lista_wiercholkow_l.Usun_z_przodu();
        delete pom1;
    }
}

bool graf_l::Czy_pusty(){
    if(lista_wiercholkow_l.Czy_pusta()){
        if(lista_krawedzi_l.Czy_pusta()){
            return true;
        }
        else{
            return false;
        }
    }
    else{
        return false;
    }
}

void graf_l::Losuj_graf2(int ile_wierzch, double gestosc){
    int max_licz_kraw=(ile_wierzch*(ile_wierzch-1))/2;
    int li_kraw = gestosc*max_licz_kraw;
    
    wierzcholek_l* pom1;
    wierzcholek_l* pom2;
    
    int los_ind1;
    int los_ind2;
    Lista<wierzcholek_l*> tab_pom1;
    Lista<wierzcholek_l*> tab_pom2;                          
        
    for(int i=ile_wierzch-1;i>=0;i--){                             
        wierzcholek_l* wierz = new wierzcholek_l;
        wierz->Dodaj_info(i);                                  
        lista_wiercholkow_l.Dodaj_na_poczatek(wierz);
        wierz->Dodaj_pozycje(lista_wiercholkow_l.Pierwszy_wsk());
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
        
    while(lista_krawedzi_l.Dlugosc_tablicy() < li_kraw){
        los_ind1=rand()%lista_wiercholkow_l.Dlugosc_tablicy();
        los_ind2=rand()%lista_wiercholkow_l.Dlugosc_tablicy();
        pom1= lista_wiercholkow_l.Odczytaj(los_ind1);
        pom2= lista_wiercholkow_l.Odczytaj(los_ind2);

        /*if(lista_wiercholkow_l.Odczytaj(los_ind1) != lista_wiercholkow_l.Odczytaj(los_ind2) && !lista_wiercholkow_l.Odczytaj(los_ind1)->Czy_sa(lista_wiercholkow_l.Odczytaj(los_ind2))){
            Dodaj_krawedz(10000,lista_wiercholkow_l.Odczytaj(los_ind1),lista_wiercholkow_l.Odczytaj(los_ind2));
        }*/
        if(pom1 != pom2 && !pom1->Czy_sa(pom2)){
            Dodaj_krawedz(rand()%999+1,pom1,pom2);
        }
    }
        
}



bool graf_l::Zapisz_graf_do_pliku(const char* NazwaPliku){
        fstream plik;
        krawedz_l* pom;

        plik.open(NazwaPliku,ios::out);
        if(plik.good()){
            plik << lista_wiercholkow_l.Dlugosc_tablicy() << "  " << lista_krawedzi_l.Dlugosc_tablicy() <<endl;
            for(int i=0;i<lista_krawedzi_l.Dlugosc_tablicy();i++){
                pom=lista_krawedzi_l.Odczytaj(i);
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

bool graf_l::Wczytaj_graf(const char* NazwaPliku){
        
    fstream plik;
    int ile_wierzch;
    int ile_kraw;
    wierzcholek_l* pom;
    wierzcholek_l* pom2;
    int pom3;
    int pom4;
    int info;

    plik.open(NazwaPliku,ios::in);
    if(plik.good()){
        plik>>ile_wierzch;
        plik>>ile_kraw;

        for(int i=ile_wierzch-1;i>=0;i--){                             
            wierzcholek_l* wierz = new wierzcholek_l;
            wierz->Dodaj_info(i);                                  
            lista_wiercholkow_l.Dodaj_na_poczatek(wierz);
            wierz->Dodaj_pozycje(lista_wiercholkow_l.Pierwszy_wsk());
        }

        for(int k=0;k<ile_kraw;k++){
            plik>>pom3;
            plik>>pom4;
            plik>>info;
               
            pom=lista_wiercholkow_l.Odczytaj(pom3);
            pom2=lista_wiercholkow_l.Odczytaj(pom4);

            krawedz_l* kraw = new krawedz_l;
            kraw->Dodaj_info(info);
            lista_krawedzi_l.Dodaj_na_poczatek(kraw);
            kraw->Dodaj_pocz(pom);
            pom->Dodaj_do_listy(kraw);
            kraw->Dodaj_kon(pom2);
            pom2->Dodaj_do_listy(kraw);
            kraw->Dodaj_pozycje(lista_krawedzi_l.Pierwszy_wsk());
                
        }
    }
    else{
        cout << "Blad otwarcia pliku" <<endl;
        return false;
    }
    plik.close();
    return true;
}

