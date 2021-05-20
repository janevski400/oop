#include <iostream>
#include <cstring>
using namespace std;

class Vozac {
protected:
    char ime[101];
    int vozrast;
    int brojTrki;
    bool veteranStatus;
public:
    Vozac (char *_ime, int _vozrast, int _brojTrki, bool _veteranStatus) {
        strcpy(ime,_ime);
        vozrast=_vozrast;
        brojTrki = _brojTrki;
        veteranStatus = _veteranStatus;
    }
    char* getIme () {
        return ime;
    }
    int getVozrast () {
        return vozrast;
    }
    int getBrojTrki () {
        return brojTrki;
    }
    bool getVeteranStatus () {
        return veteranStatus;
    }
    virtual float getZarabotuvackaPoTrka () = 0;
    virtual float danok() = 0;
};

class Avtomobilist : public Vozac {
private:
    float cena;
public:
    Avtomobilist(char *ime = nullptr, int vozrast = 0, int brojTrki = 0, bool veteranStatus = false, float cenaAvto = 0): Vozac(ime,vozrast,brojTrki,veteranStatus) {
        this->cena = cenaAvto;
    }
    float getZarabotuvackaPoTrka () {
        return cena/5.0;
    }
    float danok () {
        if(brojTrki>10)
            return getZarabotuvackaPoTrka()*0.15;
        return getZarabotuvackaPoTrka()*0.10;
    }

};

class Motociklist : public Vozac {
private:
    int mokjnost;
public:
    Motociklist(char *ime = nullptr, int vozrast = 0, int brojTrki = 0, bool veteranStatus = false, int _mokjnost = 0): Vozac(ime,vozrast,brojTrki,veteranStatus) {
        mokjnost = _mokjnost;
    }
    float getZarabotuvackaPoTrka () {
        return mokjnost*20;
    }
    float danok () {
        if(veteranStatus)
            return getZarabotuvackaPoTrka()*0.25;
        return getZarabotuvackaPoTrka()*0.20;
    }
};

ostream &operator << (ostream &out, Vozac &vozac) {
    out<<vozac.getIme()<<endl;
    out<<vozac.getVozrast()<<endl;
    out<<vozac.getBrojTrki()<<endl;
    if(vozac.getVeteranStatus())
        out<<"VETERAN"<<endl;
    return out;
}

bool operator == (Vozac &prv, Vozac &vtor) {
    return (prv.getZarabotuvackaPoTrka() == vtor.getZarabotuvackaPoTrka());
}

int soIstaZarabotuvachka (Vozac **vozaci, int n, Vozac *x) {
    int brojac=0;
    for(int i=0;i<n;i++) {
        if(*vozaci[i]==*x)
            brojac++;
    }
    return brojac;
}

int main() {
    int n, x;
    cin >> n >> x;
    Vozac **v = new Vozac*[n];
    char ime[100];
    int vozrast;
    int trki;
    bool vet;
    for(int i = 0; i < n; ++i) {
        cin >> ime >> vozrast >> trki >> vet;
        if(i < x) {
            float cena_avto;
            cin >> cena_avto;
            v[i] = new Avtomobilist(ime, vozrast, trki, vet, cena_avto);
        } else {
            int mokjnost;
            cin >> mokjnost;
            v[i] = new Motociklist(ime, vozrast, trki, vet, mokjnost);
        }
    }
    cout << "=== DANOK ===" << endl;
    for(int i = 0; i < n; ++i) {
        cout << *v[i];
        cout << v[i]->danok() << endl;
    }
    cin >> ime >> vozrast >> trki >> vet;
    int mokjnost;
    cin >> mokjnost;
    Vozac *vx = new Motociklist(ime, vozrast, trki, vet, mokjnost);
    cout << "=== VOZAC X ===" << endl;
    cout << *vx;
    cout << "=== SO ISTA ZARABOTUVACKA KAKO VOZAC X ===" << endl;
    cout << soIstaZarabotuvachka(v, n, vx);
    for(int i = 0; i < n; ++i) {
        delete v[i];
    }
    delete [] v;
    delete vx;
    return 0;
}
