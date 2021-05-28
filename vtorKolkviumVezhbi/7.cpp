#include<iostream>
#include<string.h>
using namespace std;

class Karticka
{
protected:
    char smetka[16];
    int pin;
    bool povekjePin;
    static int P;
public:
    Karticka(char* smetka,int pin)
    {
        strcpy(this->smetka,smetka);
        this->pin=pin;
        this->povekjePin=false;
    }
    Karticka(Karticka &other)
    {
        strcpy(this->smetka,other.smetka);
        this->pin = other.pin;
        this->povekjePin = other.povekjePin;
    }
    virtual int tezinaProbivanje()
    {
        int tempPin = pin;
        int tezhina = 0;
        while(tempPin)
        {
            tezhina++;
            tempPin/=10;
        }
        return tezhina;
    }
    friend ostream &operator <<(ostream &o, Karticka &card)
    {
        return o<<card.smetka<<": "<<card.tezinaProbivanje();
    }
    virtual bool getDopolnitelenPin ()
    {
        return false;
    }
    bool operator ==(char *s)
    {
        if(!strcmp(this->smetka,s)) {
            return true;
        }
        return false;
    }
    char *getSmetka () {return smetka;}
};
int Karticka::P=4;

class OutOfBoundException
{
private:
    char m[50];
public:
    OutOfBoundException(const char *msg)
    {
        strcpy(m,msg);
    }
    void message ()
    {
        cout<<m;
    }
};

class SpecijalnaKarticka : public Karticka
{
private:
    int *pinKodovi;
    int brPinKodovi;

public:
    SpecijalnaKarticka(char *smetka, int pin):Karticka(smetka,pin)
    {
        this->povekjePin=true;
        brPinKodovi=0;
        pinKodovi = nullptr;
    }
    SpecijalnaKarticka(SpecijalnaKarticka &other):Karticka(other)
    {
        this->brPinKodovi = other.brPinKodovi;
        pinKodovi = new int [brPinKodovi];
        for(int i=0; i<brPinKodovi; i++)
            this->pinKodovi[i]=other.pinKodovi[i];
    }
    ~SpecijalnaKarticka ()
    {
        delete [] pinKodovi;
    }
    int tezinaProbivanje()
    {
        return this->Karticka::tezinaProbivanje()+brPinKodovi;
    }
    friend ostream &operator <<(ostream &o, SpecijalnaKarticka &card)
    {
        return o<<card.getSmetka()<<": "<<card.tezinaProbivanje();
    }
    SpecijalnaKarticka &operator += (int newPin)
    {
        if(brPinKodovi==4)
            throw OutOfBoundException("Brojot na pin kodovi ne moze da go nadmine dozvolenoto\0");

        int *tempArray = new int [brPinKodovi+1];
        for(int i=0; i<brPinKodovi; i++)
            tempArray[i]=pinKodovi[i];
        tempArray[brPinKodovi]=newPin;
        brPinKodovi++;
        delete [] pinKodovi;
        pinKodovi = new int [brPinKodovi];
        for(int i=0; i<brPinKodovi; i++)
            pinKodovi[i]=tempArray[i];
        delete [] tempArray;
        return *this;
    }
    bool getDopolnitelenPin() {return true;}
};

class Banka
{
private:
    char naziv[30];
    Karticka *karticki[20];
    int broj;
    static int LIMIT;
public:
    Banka(char *naziv, Karticka** karticki,int broj )
    {
        strcpy(this->naziv,naziv);
        for (int i=0; i<broj; i++)
        {
            if (karticki[i]->getDopolnitelenPin())
            {
                this->karticki[i]=new SpecijalnaKarticka(*dynamic_cast<SpecijalnaKarticka*>(karticki[i]));
            }
            else this->karticki[i]=new Karticka(*karticki[i]);
        }
        this->broj=broj;
    }
    ~Banka()
    {
        for (int i=0; i<broj; i++) delete karticki[i];
    }
    static void setLIMIT(int lim)
    {
        LIMIT = lim;
    }
    void pecatiKarticki ()
    {
        cout<<"Vo bankata Komercijalna moze da se probijat kartickite:"<<endl;
        for(int i=0; i<broj; i++)
        {
            if(karticki[i]->tezinaProbivanje() <= LIMIT) {
                cout<<*karticki[i]<<endl;
            }
        }
    }
    void dodadiDopolnitelenPin(char *s, int novPin)
    {
        for(int i=0; i<broj; i++)
        {
            if(*karticki[i]==s) {
                if(karticki[i]->getDopolnitelenPin()) {
                    dynamic_cast<SpecijalnaKarticka&>(*karticki[i])+=novPin;
                }
            }
        }
    }
};

int Banka::LIMIT=7;

int main()
{

    Karticka **niza;
    int n,m,pin;
    char smetka[16];
    bool daliDopolnitelniPin;
    cin>>n; //2
    niza=new Karticka*[n];
    for (int i=0; i<n; i++)
    {
        cin>>smetka; //ab123..,bh455..
        cin>>pin; // 345,876
        cin>>daliDopolnitelniPin; //0,1
        if (!daliDopolnitelniPin)
            niza[i]=new Karticka(smetka,pin);
        else
            niza[i]=new SpecijalnaKarticka(smetka,pin);
    }

    Banka komercijalna("Komercijalna",niza,n);

    for (int i=0; i<n; i++) delete niza[i];
    delete [] niza;

    cin>>m;
    for (int i=0; i<m; i++)
    {
        cin>>smetka>>pin;
        try {
            komercijalna.dodadiDopolnitelenPin(smetka,pin);
        }
        catch (OutOfBoundException &ex) {
            ex.message();
        }

    }
    Banka::setLIMIT(5);
    komercijalna.pecatiKarticki();
    return 0;
}
