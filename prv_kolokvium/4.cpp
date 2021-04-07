/*
(40 поени)

Да се креира класа Patnik во која се чуваат податоци за патниците на еден воз и тоа: име (низа од максимум 100 знаци), класа на вагон во која се вози (цел број 1 или 2) и велосипед (булова променлива).

За оваа класа да се преоптоварат:

Оператор << - за печатење на информациите за патникот во формат:
Име на патник

Бројот на класата (1 или 2)

Дали има велосипед?

Потоа да се креира клaса Voz во која се чува: крајна дестинација (низа од максимум 100 знаци), динамички алоцирана низа од објекти од класата Patnik, како и број на елементи во низата (цел број), број на дозволени велосипеди (цел број).

За класата да се обезбедат:

Оператор += – за додавање нов патник во воз. Патник со велосипед ќе може да се качи во воз само ако возот го дозволува тоа.
Оператор << - за печатење на крајната дестинација до која вози и листата на патници
Функција со потпис: patniciNemaMesto(). Со оваа функција се пресметува вкупниот број на патници (од 1-ва класа и 2-ра класа) за кои нема место да влезат во возот со велосипед. Притоа треба да се внимава дека во пресметувањето на вкупниот број патници со велосипеди кои ќе влезат во возот прво треба да се земат предвид патниците од 1-ва класа, а потоа се дозволува да влегуваат патниците од 2-ра класа се додека не се достигне максималниот број на дозволени велосипеди во возот. На крај се печати бројот на патници со велосипеди кои остануваат (не влегуваат во возот) од 1-ва класа, а потоа од 2-ра класа.
*/
#include <iostream>
#include <cstring>
using namespace std;

class Patnik {
    private:
        char ime[100];
        int klasa;
        bool velosiped;
    public:
        Patnik (char *ime = "", int klasa = 1, bool velosiped = false){
            strcpy(this->ime,ime);
            this->klasa = klasa;
            this->velosiped = velosiped;
        }
        Patnik & operator = (const Patnik &other) {
            if(this!=&other) {
                strcpy(this->ime, other.ime);
                this->klasa = other.klasa;
                this->velosiped = other.velosiped;
            }
            return *this;
        }
        friend ostream & operator << (ostream &out, const Patnik &a) {
            return out << a.ime << "\n" << a.klasa << "\n" <<a.velosiped<<endl;
        }
        bool getVeolosiped () const {
            return velosiped;
        }
        int getKlasa () const {
            return klasa;
        }
};

class Voz {
private:
    char destinacija[100];
    Patnik *patnici;
    int brPatnici;
    int brDozvoleniVelosipedi;

    bool proverka () {
        int tempPK=0, tempVK=0;
        for(int i=0;i<brPatnici;i++)
        {
            if((patnici[i].getKlasa() == 1)&&(patnici[i].getVeolosiped()))
                tempPK++;
            else if ((patnici[i].getKlasa() == 2)&&(patnici[i].getVeolosiped()))
                tempVK++;
        }
        if(tempPK < brDozvoleniVelosipedi || tempVK < brDozvoleniVelosipedi)
            return true;
        return false;
    }

    void dodadi (const Patnik p) {
        Patnik *tempPatnici = new Patnik [brPatnici+1];
        for(int i=0;i<brPatnici;i++)
            tempPatnici[i]=patnici[i];
        tempPatnici[brPatnici] = p;
        brPatnici++;
        delete [] patnici;
        patnici = new Patnik [brPatnici];
        for(int i=0;i<brPatnici;i++) {
            patnici[i].operator=(tempPatnici[i]);
        }
        delete [] tempPatnici;
    }

public:
    Voz (char *destinacija = "", int brDozvoleniVelosipedi = 0) {
        strcpy(this->destinacija, destinacija);
        this->brDozvoleniVelosipedi = brDozvoleniVelosipedi;
        brPatnici = 0;
        patnici = nullptr;
    }

    friend ostream & operator << (ostream &out, const Voz &v) {
        out << v.destinacija << "\n";
        for(int i=0;i<v.brPatnici;i++)
            out<<v.patnici[i]<<endl;
        return out;
    }

    Voz & operator += (const Patnik &p) {
        if (p.getVeolosiped() == true) {
            if(brDozvoleniVelosipedi!=0)
                if(proverka()) {
                    dodadi(p);
                    return *this;
                }
        }
        else {
            dodadi(p);
            return *this;
        }
    }
    void patniciNemaMesto() {
        int tempPK=0, tempVK=0;
        for(int i=0;i<brPatnici;i++)
        {
            if((patnici[i].getKlasa() == 1)&&(patnici[i].getVeolosiped()))
                tempPK++;
            else if ((patnici[i].getKlasa() == 2)&&(patnici[i].getVeolosiped()))
                tempVK++;
        }
        int preostanati_mesta = 0;
        preostanati_mesta = brDozvoleniVelosipedi - tempPK;
        if(preostanati_mesta>0) {
            cout<<"Brojot na patnici od 1-va klasa koi ostanale bez mesto e: 0"<<endl;
            preostanati_mesta-=tempVK;
            if(preostanati_mesta>0)
                cout<<"Brojot na patnici od 2-ra klasa koi ostanale bez mesto e: 0"<<endl;
            else
                cout<<"Brojot na patnici od 2-ra klasa koi ostanale bez mesto e: "<<abs(brDozvoleniVelosipedi-(tempPK+tempVK))<<endl;
        }
        else {
            cout<<"Brojot na patnici od 1-va klasa koi ostanale bez mesto e: "<<abs(preostanati_mesta)<<endl;
            cout<<"Brojot na patnici od 2-ra klasa koi ostanale bez mesto e: "<<tempVK<<endl;
        }
    }
};

int main () {
	Patnik p;
	char ime[100], destinacija[100];
	int n;
	bool velosiped;
	int klasa;
	int maxv;
	cin >> destinacija >> maxv;
	cin >> n;
	Voz v(destinacija, maxv);
	//cout<<v<<endl;
	for (int i = 0; i < n; i++){
		cin >> ime >> klasa >> velosiped;
		Patnik p(ime, klasa, velosiped);
		//cout<<p<<endl;
		v += p;
	}
	cout << v;
	v.patniciNemaMesto();
    return 0;
}
