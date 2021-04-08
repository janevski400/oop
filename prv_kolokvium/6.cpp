/*
Да се креира структура Воз во која се чуваат податоци за релацијата по која се движи возот (низа од најмногу 50 знаци), предвиден бројот на километри што треба да се поминат (реален број), како и бројот на патници во возот (цел број).

Потоа да се креирa структура ZeleznickaStanica во која се чуваат податоци за градот во кој се наоѓа (низа од 20 знаци), низа од возови што поаѓаат од станицата (најмногу 30) и бројот на возови (цел број).

Треба да се направи функција со потпис

void najkratkaRelacija(ZeleznickaStanica* zs, int n, char* grad)
во која се печати релацијата и бројот на километри на возот што поминува најкратка релација (најмалку километри), а поаѓа од железничката станица од градот што се проследува како влезен аргумент. Ако има повеќе возови со ист најмал број на километри, да се испечати релацијата на последниот таков.

Забелешка: Задачата да се реши во програмскиот јазик C++
*/
#include <iostream>
#include <cstring>
using namespace std;

struct Voz {
    char relacija[50];
    float predvidenBrojKilometri;
    int brojPatnici;
};

struct ZeleznickaStanica {
    char grad[20];
    Voz vozovi[30];
    int brVozovi;
};

void najkratkaRelacija(ZeleznickaStanica* zs, int n, char* grad) {
    float minR = 1000000;
    char temp[50];
    for(int i=0;i<n;i++) {
        for(int j=0;j<zs[i].brVozovi;j++) {
            if(!strncmp(zs[i].vozovi[j].relacija,grad,strlen(grad))) {
                if(zs[i].vozovi[j].predvidenBrojKilometri <= minR) {
                    minR = zs[i].vozovi[j].predvidenBrojKilometri;
                    strcpy(temp,zs[i].vozovi[j].relacija);
                }
            }
       }
    }
    cout<<"Najkratka relacija: "<<temp<<" ("<<minR<<" km)"<<endl;
}

int main(){

    int n;
	cin>>n;
    ZeleznickaStanica zStanica[100];
    for (int i=0;i<n;i++){
        cin>>zStanica[i].grad;
        cin>>zStanica[i].brVozovi;
        for(int j=0;j<zStanica[i].brVozovi;j++) {
            cin>>zStanica[i].vozovi[j].relacija>>zStanica[i].vozovi[j].predvidenBrojKilometri>>zStanica[i].vozovi[j].brojPatnici;
        }
    }
    char grad[25];
    cin>>grad;
	najkratkaRelacija(zStanica,n,grad);
	return 0;
}
