/*
Да се дефинира класа Ekipa за коjа се чуваат следниве информации:

името на екипата (низа од наjмногу 15 знаци)
броj на порази
броj на победи
За оваа класа да се дефинира метод pecati() коjа ги печати податоците за екипаta. Од оваа класа да се изведe новa класa, FudbalskaEkipa.

За фудбалската екипа дополнително се чуваат информации за:

вкупниот броj на црвени картони
вкупниот броj жолти картони
броjот на нерешени натпревари
За фудбалската екипа да се преоптовари методот pecati(), така што покрај останатите информации, ќе се испечатат и бројот на нерешени резултати и вкупен број на поени во формат: Име на екипа, броj на победи, броj на порази, броj на нерешени натпревари и вкупен броj на поени (за победа фудбалската екипа добива 3 поени, додека за нерешен резултата, 1 поен);
*/
#include <iostream>
#include <cstring>
using namespace std;

class Ekipa {
    private:
        char ime[16];
        int brPorazi;
        int brPobedi;
    public:
        Ekipa (char ime[15]="---undefined---", int brPorazi = 0, int brPobedi = 0) {
            strcpy(this->ime,ime);
            this->brPorazi = brPorazi;
            this->brPobedi = brPobedi;
        }
        void pecati () {
            cout<<"Ime: "<<ime<<" Pobedi: "<<brPobedi<<" Porazi: "<<brPorazi;
        }
        ~Ekipa () {}
        int poeni() {
            return brPobedi*3;
        }
};

class FudbalskaEkipa : public Ekipa {
    private:
        int brCrveni;
        int brZolti;
        int nereseni;
    public:
        FudbalskaEkipa (char ime[15] = "--undefined--", int brPobedi = 0, int brPorazi = 0, int brCrveni = 0, int brZolti = 0, int nereseni = 0): Ekipa(ime,brPorazi,brPobedi) {
            this->brCrveni = brCrveni;
            this->brZolti = brZolti;
            this->nereseni = nereseni;
        }
        int poeni() {
            return Ekipa::poeni()+nereseni;
        }
        ~FudbalskaEkipa () {}
        void pecati () {
            Ekipa::pecati();
            cout<<" Nereseni: "<<nereseni<<" Poeni: "<<poeni()<<endl;
        }
};

int main(){
	char ime[15];
	int pob,por,ck,zk,ner;
	cin>>ime>>pob>>por>>ck>>zk>>ner;
	FudbalskaEkipa f1(ime,pob,por,ck,zk,ner);
	f1.pecati();
	return 0;
}
