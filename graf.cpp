#include <cstdlib>
#include <ctime>
#include <chrono>
#include "grafM.hpp"
#include "grafL.hpp"


using namespace std;

void Dijkstra(graf_m &gr, int* odleglosci, int* ostatni_wierzch){
        
    int ile_wierz = gr.Ile_wierz();
    wierzcholek_m* sasiad;        
    wierzcholek_m* wier;
    krawedz_m* pom;
    MinKop hp(ile_wierz);

    odleglosci[0]=0;
    ostatni_wierzch[0]=-1; //oznaczenie poczatku trasy jako liczbe ujemną
    for(int i=1;i<ile_wierz;i++){
        odleglosci[i] = 100000000;
        ostatni_wierzch[i]=100000000;
    }
   
    for(int i=0;i<ile_wierz;i++){
        hp.wsadz(gr.Zwroc_wierzch(i),odleglosci[i]); 
    }
    
    while(hp.liczba_elem() > 0){
        
        wier = hp.zwrocMin()->dane;
        for(int i=1;i<=gr.Ile_sa(wier->Zwroc_info());i++){
            pom=gr.Zwroc_sa(wier->Zwroc_info(),i);
            if(pom->Zwroc_kon()==wier){
                sasiad=pom->Zwroc_pocz();
            }
            else{
                sasiad=pom->Zwroc_kon();
            }
            
            if(odleglosci[sasiad->Zwroc_info()] > odleglosci[wier->Zwroc_info()] + pom->Zwroc_info()){
                    
                odleglosci[sasiad->Zwroc_info()] = odleglosci[wier->Zwroc_info()] + pom->Zwroc_info();
                hp.decreaseKey(sasiad,odleglosci[sasiad->Zwroc_info()]);
                ostatni_wierzch[sasiad->Zwroc_info()]=wier->Zwroc_info();
            }
        }
    }
}

void Dijkstra(graf_l &gr,int* odleglosci, int* ostatni_wierzch){
        
    int ile_wierz = gr.Ile_wierz();
    wierzcholek_l* sasiad;
    wierzcholek_l* wier;
    MinKopL hp(ile_wierz);


    odleglosci[0]=0;
    ostatni_wierzch[0]=-1; //oznaczenie poczatka trasy jako liczbe ujemną
    for(int i=1;i<ile_wierz;i++){
        odleglosci[i] = 100000000;
        ostatni_wierzch[i]=100000000;
    }
    for(int i=0;i<ile_wierz;i++){
        hp.wsadz(gr.Zwroc_wierzch(i),odleglosci[i]);
    }

    while(hp.liczba_elem() > 0){
        wier = hp.zwrocMin()->dane;
        for(int i=0;i<wier->Ile_sa();i++){
            if(wier->Zwroc_sa(i)->Zwroc_kon()==wier){
                sasiad=wier->Zwroc_sa(i)->Zwroc_pocz();
            }
            else{
                sasiad=wier->Zwroc_sa(i)->Zwroc_kon();
            }
            if(odleglosci[sasiad->Zwroc_info()] > odleglosci[wier->Zwroc_info()] + wier->Zwroc_sa(i)->Zwroc_info()){       
                odleglosci[sasiad->Zwroc_info()] = odleglosci[wier->Zwroc_info()] + wier->Zwroc_sa(i)->Zwroc_info();
                hp.decreaseKey(sasiad,odleglosci[sasiad->Zwroc_info()]);    
                ostatni_wierzch[sasiad->Zwroc_info()]=wier->Zwroc_info();
            }
        }
    }
}


int main(){
    srand(time(NULL));
    
    string Graf("graf");
    string Wynik("wynik");
    double czas_calk=0.000000;
    //graf_l gr;
    graf_l gr;
    
    int pom_dr=2;
    fstream plik;
    char nr_grafu;
    
    
    for(int i=0;i<1;i++){  
        
        int* odleglosci=new int[200];               //pojemność tablic trzeba ustawić tak żeby była wieksza niż ilość wierzchołków
        int* ostatni_wierzch=new int[200];
           
        gr.Losuj_graf2(10,0.25);
        nr_grafu=i;
        
        
        Graf.append(to_string(nr_grafu));
        Graf.append(".txt");
        
        gr.Zapisz_graf_do_pliku(Graf.c_str());

        
        auto poczatek_pom = chrono::steady_clock::now();
        
        Dijkstra(gr,odleglosci,ostatni_wierzch);
        auto koniec_pom = chrono::steady_clock::now();
        chrono::duration<double> czas = koniec_pom-poczatek_pom;
        czas_calk+=czas.count();
        
        
        Graf="graf";
        Wynik="wynik";
        
        Wynik.append(to_string(nr_grafu));
        Wynik.append(".txt");
        
        plik.open(Wynik.c_str(),ios::out);
        
        for (int i = 0; i < gr.Ile_wierz(); i++)
        {
            plik<<i<<"      "<<odleglosci[i]<<"     "<<ostatni_wierzch[i]<<endl;
        }

        plik.close();
        
        gr.Wyczysc_graf();
        delete [] odleglosci;
        delete [] ostatni_wierzch;

    }

    cout<< "czas: " << czas_calk << "s" <<endl;


    
    /*
    for (int i = 0; i < gr.Ile_wierz(); i++)
    {
        cout<<i<<"  "<<odleglosci[i]<<endl;
    }
    cout<<"droga do 2"<<endl;
    while(pom_dr>0){
        cout<<ostatni_wierzch[pom_dr]<<endl;
        pom_dr=ostatni_wierzch[pom_dr];
    }*/

    return 0;
} 



