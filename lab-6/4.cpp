/*
Да се развие класа Nediviznina за коjа се чуваат следниве информации:

адреса (динамички алоцирана низа од знаци)
квадратура (цел боj)
цена за квадрат (цел боj)
За оваа класа да се имплементираат соодветните конструктори и следните методи:

cena() коj ќе jа враќа цената на недвижнината (квадратура * цена-за-квадрат)
pecati() коj ќе ги испечати сите информации за истата
danokNaImot() коj го ваќа данокот што се плаќа за недвижнината, а истиот се пресметува како 5% од цената на недвижнината.
Од оваа класа да се изведе класа Vila за коjа дополнително се чува данок на луксуз (цел боj, пр. 10%). За оваа класа да се преоптоварат методите:

pecati()
danokNaImot() со тоа што пресметаниот данок се зголемува процентуално за данокот на луксуз.
И за двете класи треба да се преоптовари operator >>.
*/
#include <iostream>
#include <cstring>
using namespace std;

class Nedviznina {
    private:
        char *adresa;
        int kvadratura;
        int cenaKvadrat;
    public:
        Nedviznina(char *adresa = "-------------undefined-------------", int kvadratura = 0, int cenaKvadrat = 0) {
            this->adresa = new char [strlen(adresa)+1];
            strcpy(this->adresa,adresa);
            this->kvadratura = kvadratura;
            this->cenaKvadrat = cenaKvadrat;
        }
        ~Nedviznina () {
            delete [] adresa;
        }
        int cena () {
            return kvadratura*cenaKvadrat;
        }
        void pecati () {
            cout<<adresa<<", Kvadratura: "<<kvadratura<<", Cena po Kvadrat: "<<cenaKvadrat<<endl;
        }
        double danokNaImot() {
            return (cena()*0.05);
        }
        friend istream &operator >> (istream &in, Nedviznina &other){
            delete [] other.adresa;
            other.adresa = new char [50];
            in>>other.adresa;
            in>>other.kvadratura;
            in>>other.cenaKvadrat;
            //return in;
        }
        char * getAdresa () {
            return adresa;
        }
        int getKvadratura () {
            return kvadratura;
        }
        int getCenaKvadrat () {
            return cenaKvadrat;
        }
};


class Vila : public Nedviznina {
    private:
        int danokNaLuksuz;
    public:
        Vila (const int &danokNaLuksuz = 0):Nedviznina() {
            this->danokNaLuksuz = danokNaLuksuz;
        }
        ~Vila () {}
        double danokNaImot () {
            return (Nedviznina::danokNaImot()+Nedviznina::cena()/100*danokNaLuksuz);
        }
        void pecati() {
            cout<<getAdresa()<<", Kvadratura: "<<getKvadratura()<<", Cena po Kvadrat: "<<getCenaKvadrat()<<", Danok na luksuz: "<<danokNaLuksuz<<endl;
        }
        friend istream &operator >> (istream &in, Vila &other){
            Nedviznina *pParent = &other; //pokazhuvach kon Nedvizhnina preku koj go koristime operator >> za objekti od Nedvizhnina za vnesuvanje na potrebni informacii
            in>>*pParent;
            in>>other.danokNaLuksuz;
            //return in;
        }
};

int main(){
    Nedviznina n;
    Vila v;
    cin>>n;
    cin>>v;
    n.pecati();
    cout<<"Danok za: "<<n.getAdresa()<<", e: "<<n.danokNaImot()<<endl;
    v.pecati();
    cout<<"Danok za: "<<v.getAdresa()<<", e: "<<v.danokNaImot()<<endl;
    return 0;
}
