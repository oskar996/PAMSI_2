#ifndef LISTA_HPP
#define LISTA_HPP

#include <iostream>
using namespace std;

template <class klasa>
class El_listy{
    
    klasa dane;
    El_listy *nastepny;

    public:
    klasa Odczytaj_Dane(){
        return dane;
    }
    El_listy* Nastepny(){
        
        
        //if(nastepny){
            return nastepny;
        //}
        /*else{
            cout<< "blad Nastepnego" <<endl;
        }*/
        
    }
    void Zmien_dane(klasa nowe){
        dane = nowe;
    }
    void Ustaw_nastepny(El_listy *nowe){
        nastepny=nowe;
    }
};

template <class klasa>
class Lista{
    
    El_listy<klasa> *Head;
    El_listy<klasa> *Tail;
    int ilosc;

    public:
    
    Lista(){
        Head = nullptr;
        Tail = nullptr;
        ilosc = 0;
    }

    ~Lista(){
        El_listy<klasa> *pom = Head;
        while(pom!=Tail){
            Head = pom->Nastepny();
            delete pom;
            pom=Head;
        }
        delete Tail;
    }

    int Dlugosc_tablicy(){
        return ilosc;
    }

    bool Czy_pusta(){
        if(Head!=nullptr){
            return false;
        }
        else{
            return true;
        }
    }
    
    klasa Pierwszy(){
        if(Head!=nullptr){
            return Head->Odczytaj_Dane();
        }
        else{
            return 0;
        }
    }

    El_listy<klasa>* Pierwszy_wsk(){
        if(Head!=nullptr){
            return Head;
        }
        else{
            return 0;
        }
    }

    void Dodaj_na_poczatek(klasa v){
        El_listy<klasa> *nowy = new El_listy<klasa>;

        nowy->Zmien_dane(v);
        nowy->Ustaw_nastepny(Head);
        if(Head==nullptr){
            Tail = nowy;
        }
        Head=nowy;
        ilosc++;
        
    }
    klasa Usun_z_przodu(){
        if(ilosc>0){
            El_listy<klasa> *stary = Head;
            klasa dane;
            if(Head->Nastepny()){
                Head = Head->Nastepny();
                dane = stary->Odczytaj_Dane();
            }
            else{
                dane=stary->Odczytaj_Dane();
                Head=nullptr;
                Tail=nullptr;
            }

            ilosc--;
            //cout<<ilosc<<endl;
            return dane;
        }
        else{
            cout<< "blad. lista pusta" <<endl;
        }
        return 0;
    }
    void Dodaj_na_tyl(klasa v){
        El_listy<klasa> *nowy = new El_listy<klasa>;

        nowy->Ustaw_nastepny(nullptr);
        nowy->Zmien_dane(v);
        if(Tail!=nullptr){
            Tail->Ustaw_nastepny(nowy);
        }
        if(Head==nullptr){
            Head = nowy;
        }
        Tail=nowy;
        ilosc++;

    }

    klasa Usun_z_tylu(){
        if(ilosc>0){
            El_listy<klasa> *pom =  Head;
            klasa dane;
            if(pom->Nastepny()){
                while(pom->Nastepny()->Nastepny()){
                    pom=pom->Nastepny();
                }
                
                pom->Ustaw_nastepny(nullptr);
                dane = Tail->Odczytaj_Dane();
                //delete Tail;
                Tail=pom;
                ilosc--;
                return dane;
            }
            else{
                Head=nullptr;
                Tail=nullptr;
                return pom->Odczytaj_Dane();
            }
        }
        else{
            cout << "blad. lista pusta" <<endl;
        }
        cout << "blad." <<endl;
        return 0;
    }

    
    void Dodaj(int n, klasa v){
        if(Head){
            if(n>0 && n<ilosc-1){
                El_listy<klasa> *nowy = new El_listy<klasa>;
                El_listy<klasa> *pom =  Head;
                nowy->Zmien_dane(v);
                
                for(int i=1; i<n; i++){    
                    //if(pom->Nastepny()->Nastepny()!=nullptr){
                        pom=pom->Nastepny();
                    //}
                    //else{
                        //cout << "blad 2" <<endl;
                        //break;
                    //}
                }
                nowy->Ustaw_nastepny(pom->Nastepny());
                pom->Ustaw_nastepny(nowy);
                ilosc++;
            }
            else{
                cout<<"blad"<<endl;
            }
        }
        else
        {
            cout << "brak elem listy"<<endl;
        }
        
        
    }

    klasa Usun(int n){
        El_listy<klasa> *pom = Head;
        El_listy<klasa> *poprzedni = nullptr;
        klasa dane;
        if(ilosc>0){
            if(n>0 && n<ilosc-1){
                for(int i=0; i<n; i++){            
                    poprzedni = pom;
                    pom=pom->Nastepny();    
                }
                
                poprzedni->Ustaw_nastepny(pom->Nastepny());
                dane=pom->Odczytaj_Dane();
                //delete pom;
            
                ilosc--;
                return dane;
            }
            else if(n==0){
                return Usun_z_przodu();
            }
            else if(n==ilosc-1){
                return Usun_z_tylu();
            }
            else{
                cout << "blad" <<endl;
                return 0;
            }
        }
        else{
            cout<< "blad" <<endl;
            return 0;
        }
        return 0;

    }

    klasa Odczytaj(int n){
        El_listy<klasa> *pom = Head;
        
        if(ilosc>0 && n>=0 && n<ilosc){    
            for(int i=0; i<n; i++){    
                if(pom->Nastepny()!=nullptr){
                    pom=pom->Nastepny();
                }
                else{
                    break;
                }
            }
        }
        else{
            cout << "blad. wyjscie poza skale" <<endl;
        }
        return pom->Odczytaj_Dane();
        
    }

    klasa Ostatni(){
        if(Tail!=nullptr){
            return Tail->Odczytaj_Dane();
        }
        else{
            return 0;
        }       
    }
};

#endif