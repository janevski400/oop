#include <iostream>
#include <cstring>
using namespace std;

class Oglas {
private:
    char naslov[51];
    char kategorija[31];
    char opis[101];
    float cena;
public:
    Oglas (char *naslov="", char *kategorija = "", char *opis = "", float cena = 0) {
        strcpy(this->naslov,naslov);
        strcpy(this->kategorija,kategorija);
        strcpy(this->opis,opis);
        this->cena = cena;
    }
    bool operator > (Oglas &other) {
        return (this->cena > other.cena);
    }
    friend ostream &operator << (ostream &out, Oglas &other) {
        out<<other.naslov<<endl;
        out<<other.opis<<endl;
        out<<other.cena<<" evra"<<endl;
        out<<endl;
        return out;
    }
    Oglas &operator =(Oglas &other) {
        strcpy(this->naslov,other.naslov);
        strcpy(this->kategorija,other.kategorija);
        strcpy(this->opis,other.opis);
        this->cena = other.cena;
    }
    float getCena() {return cena;}
    char *getNaslov() {return naslov;}
    char *getKategorija() {return kategorija;}
    char *getOpis() {return opis;}
    ~Oglas() {}
};

class NegativnaVrednost
{
public:
    void message()
    {
        cout<<"Oglasot ima nevalidna vrednost za cenata i nema da bide evidentiran!"<<endl;
    }
};

class Oglasnik {
private:
    char naziv[21];
    Oglas *oglasi;
    int brOglasi;
public:
    Oglasnik(char *naziv = "") {
        strcpy(this->naziv,naziv);
        brOglasi = 0;
        oglasi = new Oglas [0];
    }
    ~Oglasnik () {delete [] oglasi;}
    Oglasnik &operator += (Oglas &novOglas) {
        if(novOglas.getCena() < 0.0)
            throw NegativnaVrednost();
        else {
            Oglas *tempOglasi = new Oglas [brOglasi+1];
            for(int i=0;i<brOglasi;i++)
                tempOglasi[i]=oglasi[i];
            tempOglasi[brOglasi]=novOglas;
            brOglasi++;
            if(brOglasi != 0) {
                delete [] oglasi;
            }

            oglasi = new Oglas [brOglasi];
            for(int i=0;i<brOglasi;i++)
                oglasi[i]=tempOglasi[i];

            //delete [] tempOglasi;
            return *this;
        }
    }
    void oglasiOdKategorija(const char *k) {
        for(int i=0;i<brOglasi;i++) {
            if(!strcmp(oglasi[i].getKategorija(),k))
                cout<<oglasi[i];
        }
    }
    void najniskaCena () {
        float najniska = oglasi[0].getCena();
        int index = 0;
        for(int i=1;i<brOglasi;i++){
            if(oglasi[i].getCena() < najniska) {
                najniska = oglasi[i].getCena();
                index = i;
            }
        }
        cout<<oglasi[index];
    }
    Oglas &operator [](int i) {
        return oglasi[i];
    }
    int getBrojOglasi () {return brOglasi;}
    char *getNaziv () {return naziv;}
};

ostream &operator << (ostream &out, Oglasnik &oglasnik) {
    out<<oglasnik.getNaziv()<<endl;
    for(int i=0;i<oglasnik.getBrojOglasi();i++){
        cout<<oglasnik[i];
    }
    return out;
}


int main(){

    char naslov[50];
    char kategorija[30];
    char opis[100];
    float cena;
    char naziv[50];
    char k[30];
    int n;

    int tip;
    cin>>tip;

    if (tip==1){
        cout<<"-----Test Oglas & operator <<-----" <<endl;
        cin.get();
		cin.getline(naslov,49);
        cin.getline(kategorija,29);
        cin.getline(opis,99);
        cin>>cena;
        Oglas o(naslov, kategorija, opis, cena);
        cout<<o;
    }
    else if (tip==2){
    	cout<<"-----Test Oglas & operator > -----" <<endl;
        cin.get();
		cin.getline(naslov,49);
        cin.getline(kategorija,29);
        cin.getline(opis,99);
        cin>>cena;
        Oglas o1(naslov, kategorija, opis, cena);
        cin.get();
		cin.getline(naslov,49);
        cin.getline(kategorija,29);
        cin.getline(opis,99);
        cin>>cena;
        Oglas o2(naslov, kategorija, opis, cena);
        if (o1>o2) cout<<"Prviot oglas e poskap."<<endl;
        else cout<<"Prviot oglas ne e poskap."<<endl;
    }
    else if (tip==3){
        cout<<"-----Test Oglasnik, operator +=, operator << -----" <<endl ;
        cin.get();
		cin.getline(naziv,49);
        cin>>n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++){
            cin.get();
            cin.getline(naslov,49);
            cin.getline(kategorija,29);
            cin.getline(opis,99);
            cin>>cena;
        	Oglas o(naslov, kategorija, opis, cena);
        	try {
                ogl+=o;
        	}
        	catch (NegativnaVrednost &neg) {
                neg.message();
        	}
        }
        cout<<ogl;
    }
    else if (tip==4){
      	cout<<"-----Test oglasOdKategorija -----" <<endl ;
      	cin.get();
		cin.getline(naziv,49);
        cin>>n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++){
            cin.get();
            cin.getline(naslov,49);
            cin.getline(kategorija,29);
            cin.getline(opis,99);
            cin>>cena;
        	Oglas o(naslov, kategorija, opis, cena);
            try {
                ogl+=o;
        	}
        	catch (NegativnaVrednost &neg) {
                neg.message();
        	}
        }
        cin.get();
		cin.getline(k,29);
        cout<<"Oglasi od kategorijata: " <<k<<endl;
      	ogl.oglasiOdKategorija(k);

    }
    else if (tip==5){
    	cout<<"-----Test Exception -----" <<endl ;
      	cin.get();
		cin.getline(naziv,49);
        cin>>n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++){
            cin.get();
            cin.getline(naslov,49);
            cin.getline(kategorija,29);
            cin.getline(opis,99);
            cin>>cena;
        	Oglas o(naslov, kategorija, opis, cena);
        	try {
                ogl+=o;
        	}
        	catch (NegativnaVrednost &neg) {
                neg.message();
        	}
        }
        cout<<ogl;
    }
    else if (tip==6){
    	cout<<"-----Test najniskaCena -----" <<endl ;
      	cin.get();
		cin.getline(naziv,49);
        cin>>n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++){
            cin.get();
            cin.getline(naslov,49);
            cin.getline(kategorija,29);
            cin.getline(opis,99);
            cin>>cena;
        	Oglas o(naslov, kategorija, opis, cena);
        	try {
                ogl+=o;
        	}
        	catch (NegativnaVrednost &neg) {
                neg.message();
        	}
        }
        cout<<"Oglas so najniska cena:"<<endl;
      	ogl.najniskaCena();

    }
    else if (tip==7){
    	cout<<"-----Test All -----" <<endl ;
      	cin.get();
		cin.getline(naziv,49);
        cin>>n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++){
            try{
                cin.get();
                cin.getline(naslov,49);
                cin.getline(kategorija,29);
                cin.getline(opis,99);
                cin>>cena;
                Oglas o(naslov, kategorija, opis, cena);
                ogl+=o;
            }
            catch (NegativnaVrednost &ex) {
                ex.message();
            }
        }
        cout<<ogl;
        cin.get();
        cin.get();
		cin.getline(k,27);
        cout<<"Oglasi od kategorijata: " <<k<<endl;
      	ogl.oglasiOdKategorija(k);

        cout<<"Oglas so najniska cena:"<<endl;
      	ogl.najniskaCena();
    }
	return 0;
}
