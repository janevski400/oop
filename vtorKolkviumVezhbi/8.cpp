#include <iostream>
#include <cstring>
using namespace std;

class Koncert
{
private:
    char naziv[20];
    char lokacija[20];
    static float sezonskiPopust;
    double cenaBilet;
public:
    Koncert (char *_naziv = nullptr, char *_lokacija = nullptr, double _cenaBilet=0.0)
    {
        strcpy(this->naziv,_naziv);
        strcpy(this->lokacija,_lokacija);
        this->cenaBilet = _cenaBilet;
    }
    virtual double cena()
    {
        return cenaBilet-(cenaBilet*sezonskiPopust);
    }
    float getOsnovnaCena()
    {
        return cenaBilet;
    }
    void setOsnovnaCena(double update)
    {
        cenaBilet = update;
    }
    char *getNaziv()
    {
        return naziv;
    }
    static float getSezonskiPopust ()
    {
        return sezonskiPopust;
    };
    static float setSezonskiPopust (float novaVrednost)
    {
        sezonskiPopust = novaVrednost;
    }
};

float Koncert::sezonskiPopust = 0.2;

class ElektronskiKoncert : public Koncert
{
private:
    char *imeDj;
    float vremetraenje;
    bool dneven;
public:
    ElektronskiKoncert(char *naziv = nullptr, char *lokacija = nullptr, double cenaBilet = 0, char *_imeDj = nullptr, float _vremetraenje = 0, bool _dneven = true):Koncert(naziv,lokacija,cenaBilet)
    {
        this->imeDj = new char[strlen(_imeDj)+1];
        strcpy(this->imeDj,_imeDj);
        this->vremetraenje = _vremetraenje;
        this->dneven = _dneven;
    }
    ~ElektronskiKoncert()
    {
        delete [] imeDj;
    }
    double cena()
    {
        if(vremetraenje>5 && vremetraenje<7)
        {
            if(dneven)
                return this->Koncert::cena()+100;
            return this->Koncert::cena()+250;
        }
        else if (vremetraenje>7)
        {
            if(dneven)
                return this->Koncert::cena()+310;
            return this->Koncert::cena()+460;
        }
        else
        {
            if(dneven)
                return this->Koncert::cena()-50;
            else
                return this->Koncert::cena()+100;
        }
    }

};

void najskapKoncert(Koncert ** koncerti, int n)
{
    int brojElektronski = 0;
    double najskap = 0;
    int index = 0;
    for(int i=0; i<n; i++)
    {
        if(dynamic_cast<ElektronskiKoncert *>(koncerti[i]))
        {
            brojElektronski++;
        }
        if (koncerti[i]->cena() > najskap)
        {
            najskap = koncerti[i]->cena();
            index = i;
        }
    }
    cout<<"Najskap koncert: "<<koncerti[index]->getNaziv()<<" "<<koncerti[index]->cena()<<endl;
    cout<<"Elektronski koncerti: "<<brojElektronski<<" od vkupno "<<n<<endl;
}

bool prebarajKoncert(Koncert ** koncerti, int n, char * naziv, bool elektronski)
{
    for(int i=0; i<n; i++)
    {
        if(elektronski)
        {
            if(dynamic_cast<ElektronskiKoncert *>(koncerti[i]))
            {
                if(!strcmp(koncerti[i]->getNaziv(),naziv))
                {
                    cout<<koncerti[i]->getNaziv()<<" "<<koncerti[i]->cena()<<endl;
                    return true;
                }
            }
        }
        else {
            if(!strcmp(koncerti[i]->getNaziv(),naziv))
            {
                cout<<koncerti[i]->getNaziv()<<" "<<koncerti[i]->cena()<<endl;
                return true;
            }
        }
    }
    return false;
}

int main()
{

    int tip,n,novaCena;
    char naziv[100], lokacija[100], imeDJ[40];
    bool dnevna;
    float cenaBilet, novPopust;
    float casovi;

    cin>>tip;
    if (tip==1) //Koncert
    {
        cin>>naziv>>lokacija>>cenaBilet;
        Koncert k1(naziv,lokacija,cenaBilet);
        cout<<"Kreiran e koncert so naziv: "<<k1.getNaziv()<<endl;
    }
    else if (tip==2) //cena - Koncert
    {
        cin>>naziv>>lokacija>>cenaBilet;
        Koncert k1(naziv,lokacija,cenaBilet);
        cout<<"Osnovna cena na koncertot so naziv "<<k1.getNaziv()<< " e: " <<k1.cena()<<endl;
    }
    else if (tip==3) //ElektronskiKoncert
    {
        cin>>naziv>>lokacija>>cenaBilet>>imeDJ>>casovi>>dnevna;
        ElektronskiKoncert s(naziv,lokacija,cenaBilet,imeDJ,casovi,dnevna);
        cout<<"Kreiran e elektronski koncert so naziv "<<s.getNaziv()<<" i sezonskiPopust "<<s.getSezonskiPopust()<<endl;
    }
    else if (tip==4) //cena - ElektronskiKoncert
    {
        cin>>naziv>>lokacija>>cenaBilet>>imeDJ>>casovi>>dnevna;
        ElektronskiKoncert s(naziv,lokacija,cenaBilet,imeDJ,casovi,dnevna);
        cout<<"Cenata na elektronskiot koncert so naziv "<<s.getNaziv()<<" e: "<<s.cena()<<endl;
    }
    else if (tip==5)  //najskapKoncert
    {

    }
    else if (tip==6)  //prebarajKoncert
    {
        Koncert ** koncerti = new Koncert *[5];
        int n;
        koncerti[0] = new Koncert("Area","BorisTrajkovski",350);
        koncerti[1] = new ElektronskiKoncert("TomorrowLand","Belgium",8000,"Afrojack",7.5,false);
        koncerti[2] = new ElektronskiKoncert("SeaDance","Budva",9100,"Tiesto",5,true);
        koncerti[3] = new Koncert("Superhiks","PlatoUkim",100);
        koncerti[4] = new ElektronskiKoncert("CavoParadiso","Mykonos",8800,"Guetta",3,true);
        char naziv[100];
        najskapKoncert(koncerti,5);
    }
    else if (tip==7){//prebaraj
     	  Koncert ** koncerti = new Koncert *[5];
         int n;
         koncerti[0] = new Koncert("Area","BorisTrajkovski",350);
         koncerti[1] = new ElektronskiKoncert("TomorrowLand","Belgium",8000,"Afrojack",7.5,false);
         koncerti[2] = new ElektronskiKoncert("SeaDance","Budva",9100,"Tiesto",5,true);
         koncerti[3] = new Koncert("Superhiks","PlatoUkim",100);
         koncerti[4] = new ElektronskiKoncert("CavoParadiso","Mykonos",8800,"Guetta",3,true);
         char naziv[100];
         bool elektronski;
     	cin>>elektronski;
     	if(prebarajKoncert(koncerti,5, "Area",elektronski))
             cout<<"Pronajden"<<endl;
         else cout<<"Ne e pronajden"<<endl;

         if(prebarajKoncert(koncerti,5, "Area",!elektronski))
             cout<<"Pronajden"<<endl;
         else cout<<"Ne e pronajden"<<endl;

     }
    else if (tip==8) //smeni cena
    {
        Koncert ** koncerti = new Koncert *[5];
        int n;
        koncerti[0] = new Koncert("Area","BorisTrajkovski",350);
        koncerti[1] = new ElektronskiKoncert("TomorrowLand","Belgium",8000,"Afrojack",7.5,false);
        koncerti[2] = new ElektronskiKoncert("SeaDance","Budva",9100,"Tiesto",5,true);
        koncerti[3] = new Koncert("Superhiks","PlatoUkim",100);
        koncerti[2] -> setSezonskiPopust(0.9);
        najskapKoncert(koncerti,4);
    }

    return 0;
}
