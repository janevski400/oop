#include <iostream>
#include <cstring>
using namespace std;

class ZicanInstrument {
protected:
    char ime[20];
    int brojZhici;
    int osnovnaCena;
public:
    ZicanInstrument(char *_ime = "", int brZici = 0, int cena = 0): brojZhici(brZici), osnovnaCena(cena){
        strcpy(ime,_ime);
    }
    bool operator == (ZicanInstrument &other) {
        if(this->brojZhici == other.brojZhici)
            return true;
        return false;
    }
    virtual float cena () = 0;
};

class Mandolina : public ZicanInstrument {
private:
    char forma[20];
public:
    Mandolina (char *ime = "", int brojZici = 0, int cena = 0, char *_forma = ""):ZicanInstrument(ime,brojZici,cena) {
        strcpy(forma,_forma);
    }
    float cena () {
        if(!strcmp(forma,"Neapolitan")) {
            return osnovnaCena+(osnovnaCena*0.15);
        }
        else
            return osnovnaCena;
    }
};

class Violina : public ZicanInstrument {
private:
    float golemina;
public:
    Violina (char *ime = "", int brZici = 0, int cena = 0, float _golemina = 0.0):ZicanInstrument(ime,brZici,cena) {
        this->golemina = _golemina;
    }
    float cena () {
        if(golemina == 0.25)
            return osnovnaCena+(osnovnaCena/100*10);
        else if (golemina == 1)
            return osnovnaCena+(osnovnaCena/100*20);
        else
            return osnovnaCena;
    }
};

void pecatiInstrumenti(ZicanInstrument &zi, ZicanInstrument **instrument, int n) {
    for(int i=0;i<n;i++) {
        ZicanInstrument *ptr = instrument[i];
        if (*ptr == zi) { cout << instrument[i]->cena() << endl; }
    }
}

int main() {
    char ime[20];
    int brojZici;
    float cena;
    char forma[20];
    cin >> ime >> brojZici >> cena >> forma;
    Mandolina m(ime, brojZici, cena, forma);
    int n;
    cin >> n;
    ZicanInstrument **zi = new ZicanInstrument*[2 * n];
    for(int i = 0; i < n; ++i) {
        cin >> ime >> brojZici >> cena >> forma;
        zi[i] = new Mandolina(ime, brojZici, cena, forma);
    }
    for(int i = 0; i < n; ++i) {
        float golemina;
        cin >> ime >> brojZici >> cena >> golemina;
        zi[n + i] = new Violina(ime, brojZici, cena, golemina);
    }
    pecatiInstrumenti(m, zi, 2 * n);
    for(int i = 0; i < 2 * n; ++i) {
        delete zi[i];
    }
    delete [] zi;
    return 0;
}
