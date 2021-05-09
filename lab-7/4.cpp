#include <iostream>
using namespace std;

class Vozilo {
protected:
    double masa;
    int shirina;
    int visina;
public:
    Vozilo (double _masa = 0, int _shirina = 0, int _visina = 0): masa(_masa), shirina(_shirina), visina(_visina) {}
    double getMasa () {
        return masa;
    }
    int getShirina() {
        return shirina;
    }
    int getVisina() {
        return visina;
    }
    virtual int getType () = 0;
};

class Avtomobil : public Vozilo {
protected:
    int brVrati;
public:
    Avtomobil (int masa = 0, int shirina = 0, int visina = 0, int _brVrati = 0): Vozilo(masa,shirina,visina) {
        brVrati = _brVrati;
    }
    int getType () {
        return 1;
    }
    int getVrati () {
        return brVrati;
    }
};

class Avtobus : public Vozilo {
protected:
    int kapacitet;
public:
    Avtobus(int masa = 0, int shirina = 0, int visina = 0, int _kapacitet = 0):Vozilo(masa,shirina,visina) {
        kapacitet = _kapacitet;
    }
    int getType () {
        return 2;
    }
    int getBrPatnici () {
        return kapacitet;
    }
};

class Kamion : public Vozilo {
protected:
    double nosivost;
public:
    Kamion (int masa = 0, int shirina = 0, int visina = 0, int _nosivost = 0):Vozilo(masa,shirina,visina) {
        nosivost = _nosivost;
    }
    int getType () {
        return 3;
    }
    double getNosivost () {
        return nosivost;
    }
};

class ParkingPlac {
private:
    Vozilo **vozila;
    int brojVozila;
public:
    ParkingPlac () {
        vozila = new Vozilo * [0];
        brojVozila = 0;
    }
    ~ParkingPlac() {
        delete [] vozila;
    }
    ParkingPlac &operator += (Vozilo *other) {
        Vozilo **temp = new Vozilo * [brojVozila+1];
        for(int i=0;i<brojVozila;i++)
            temp[i] = vozila[i];
        temp[brojVozila]=other;
        brojVozila++;
        delete [] vozila;
        vozila = new Vozilo * [brojVozila];
        for(int i=0;i<brojVozila;i++)
            vozila[i] = temp[i];
        delete [] temp;
        return *this;
    }
    float presmetajVkupnaMasa () {
        float tempSum = 0;
        for(int i=0;i<brojVozila;i++)
            tempSum += vozila[i]->getMasa();
        return tempSum;
    }
    int brojVozilaPoshirokiOd(int i) {
        int broj = 0;
        for(int i=0;i<brojVozila;i++) {
            if (vozila[i]->getShirina() > i) { broj++; }
        }
        return broj-1;
    }
    void pecati () {
        int brAvtomobili = 0, brAvtobusi = 0, brKamioni = 0;
        for(int i=0;i<brojVozila;i++){
            if(vozila[i]->getType() == 1)
                brAvtomobili++;
            else if (vozila[i]->getType() == 2)
                brAvtobusi++;
            else
                brKamioni++;
        }
        cout<<"Brojot na avtomobili e "<<brAvtomobili<<", brojot na avtobusi e "<<brAvtobusi<<" i brojot na kamioni e "<<brKamioni<<"."<<endl;
    }
    int pogolemaNosivostOd (Vozilo &v) {
        int brojKamioni = 0;
        for(int i=0;i<brojVozila;i++) {
            if(dynamic_cast<Kamion *>(vozila[i])) {
                Kamion *ptr = dynamic_cast<Kamion *>(vozila[i]);
                if(ptr->getNosivost() > v.getMasa())
                    brojKamioni++;
            }
        }
        return brojKamioni;
    }
    int vratiDnevnaZarabotka() {
        int zarabotka = 0;
        for(int i=0;i<brojVozila;i++) {
            if (dynamic_cast<Avtomobil *>(vozila[i])) {
                Avtomobil *temp = dynamic_cast<Avtomobil *>(vozila[i]);
                if(temp->getVrati() < 5)
                    zarabotka += 100;
                else
                    zarabotka += 130;
            }
            else if (dynamic_cast<Kamion *>(vozila[i])) {
                Kamion *temp = dynamic_cast<Kamion *>(vozila[i]);
                zarabotka += (temp->getMasa()+temp->getNosivost())*0.02;
            }
            else {
                Avtobus *temp = dynamic_cast<Avtobus *>(vozila[i]);
                zarabotka += temp->getBrPatnici()*5;
            }
        }
        return zarabotka;
    }
};

int main(){
    ParkingPlac p;

    int n;
    cin>>n;
    int shirina,visina, broj;
    float masa,nosivost;
    for (int i=0;i<n;i++){
        int type;
        cin>>type;
        if(type==1){
            cin>>masa>>shirina>>visina>>broj;
            Avtomobil *a=new Avtomobil(masa,shirina,visina,broj);
            p+=a;
        }
        if(type==2){
            cin>>masa>>shirina>>visina>>broj;
            p+=new Avtobus(masa,shirina,visina,broj);
        }
        if(type==3){
            cin>>masa>>shirina>>visina>>nosivost;
            p+=new Kamion(masa,shirina,visina,nosivost);
        }
    }

    p.pecati();

    cout<<"\nZarabotkata e "<<p.vratiDnevnaZarabotka()<<endl;
    cout<<"Vkupnata masa e "<<p.presmetajVkupnaMasa()<<endl;
    cout<<"Brojot poshiroki od 5 e "<<p.brojVozilaPoshirokiOd(5)<<endl;
    Avtomobil a(1200,4,3,5);
    cout<<"Brojot na kamioni so nosivost pogolema od avtomobilot e "<<p.pogolemaNosivostOd(a)<<endl;


}
