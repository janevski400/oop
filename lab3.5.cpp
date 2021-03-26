//Stefan Janevski - 201117
#include <iostream>
#include <cstring>
using namespace std;

class Rabotnik {
    private:
        char ime[30];
        char prezime[30];
        int plata;
    public:
        Rabotnik () {
            strcpy(ime, "");
            strcpy(prezime, "");
            plata = 0;
        }
        Rabotnik (char *ime, char *prezime, int plata) {
            strcpy(this->ime, ime);
            strcpy(this->prezime, prezime);
            this->plata = plata;
        }
        Rabotnik (const Rabotnik &a)
        {
            strcpy(this->prezime,a.prezime);
            strcpy(this->ime,a.ime);
            this->plata = a.plata;
        }
        int getPlata() {
            return plata;
        }
        void pecati () {
            cout<<ime<<" "<<prezime<<" "<<plata<<endl;
        }
};

class Fabrika {
    private:
        Rabotnik rab[100];
        int brojVraboteni;
    public:
    Fabrika (Rabotnik *rab, int brojVraboteni) {
        this->brojVraboteni = brojVraboteni;
        for(int i = 0; i<brojVraboteni; i++) {
            this->rab[i] = rab[i];
        }
    }
    void pecatiVraboteni() {
        for(int i=0; i<brojVraboteni;i++)
            rab[i].pecati();
    }

    void pecatiSoPlata (int plata) {
        for(int i=0;i<brojVraboteni;i++) {
            if(rab[i].getPlata()>plata)
                rab[i].pecati();
        }
    }
};

int main()
{
    int n, plata, maxPlata;
    char ime[30], prezime[30];
    Rabotnik rabotnik[100];
    cin>>n;
    for(int i=0;i<n;i++)
    {
        cin>>ime;
        cin>>prezime;
        cin>>plata;
        rabotnik[i] = Rabotnik(ime,prezime,plata);
    }
    cin>>maxPlata;
    cout<<"Site vraboteni: "<<endl;
    Fabrika x(rabotnik,n);
    x.pecatiVraboteni();
    cout<<"Vraboteni so plata povisoka od "<<maxPlata<<" :"<<endl;
    x.pecatiSoPlata(maxPlata);
    return 0;
}
