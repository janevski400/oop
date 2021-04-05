/*
Фирмата FINKI Cloud има потреба од решение за управување со image датотеките од различните оперативни системи кои ги користат при сетирање на нови сервери. За таа цел потребно е да се дефинираат следниве класи:

OperativenSistem
Во класата OperativenSistem треба да се чуваат следниве податоци:

име на оперативниот систем (динамички алоцирана низа од знаци)
верзија (float)
тип (енумерација со можни вредности LINUX, UNIX, WINDOWS)
големина (во GB) (float)
Дополнително, во рамките на класата потребно е да се дефинира:

конструктори со и без параметри
copy constructor
destructor
преоптоварување на операторот =
метод за печатење на информациите - void pecati() (видете го излезот од тест примерите за структурата)
метод за проверка на еднаквост помеѓу два оперативни системи (два оперативни системи се еднакви ако имаат исто име, верзија, тип и големина) - bool ednakviSe(const OperativenSistem &os)
метод за споредба на верзии помеѓу два оперативни система - int sporediVerzija(const OperativenSistem &os), кој ќе враќа 0 доколку верзиите се исти, -1 доколку верзијата на оперативниот систем од аргументот е поголема и 1 во преостанатиот случај.
метод за проверка дали два оперативни системи се од иста фамилија. Два оперативни системи се од иста фамилија доколку имаат исто име и се од ист тип. bool istaFamilija(const OperativenSistem &sporedba)
Repozitorium
Во класата Repozitorium треба да се чуваат следниве податоци:

име на репозиториумот (низа од 20 знака)
динамички алоцирана низа од OperativenSistem
број на оперативни системи кои моментално се наоѓаат во репозиториумот (int)
Дополнително, во рамките на класата потребно е да се дефинира:

конструктор Repozitorium(const char *ime)
деструктор
метод void pecatiOperativniSistemi() кој ќе ги печати сите оперативни системи кои се дел од репозиториумот
метод void izbrishi(const OperativenSistem &operativenSistem) кој ќе го избрише оперативниот систем проследен како аргумент, доколку тој се наоѓа во репозиториумот. Да се користи методот ednakviSe за споредба на два оперативни система.
метод за додавање на оперативен систем (void dodadi(const OperativenSistem &nov)) кој ќе го има следново однесување:
Доколку веќе постои оперативен систем од иста фамилија (да се користи методот за проверка на фамилија) кој е постар од проследениот оперативен систем, тогаш постоечкиот оперативен систем се заменува со новиот.
Во секој друг случај, проследениот оперативен систем се додава како дополнителен во репозиториумот.
*/
#include <iostream>
#include <cstring>
using namespace std;

enum Tip {
    LINUX,
    UNIX,
    WINDOWS
};

class OperativenSistem {
    private:
        char *ime;
        float verzija;
        Tip tip;
        float golemina;
    public:
        OperativenSistem (const char *ime = "", float verzija=0.0, Tip tip=UNIX, float golemina = 0.0) {
            this->ime = new char [strlen(ime)+1];
            strcpy(this->ime,ime);
            this->verzija = verzija;
            this->tip = tip;
            this->golemina = golemina;
        }
        void copy (const OperativenSistem &os) {
            this->ime = new char [strlen(os.ime)+1];
            strcpy(this->ime, os.ime);
            this->verzija= os.verzija;
            this->tip = os.tip;
            this->golemina = os.golemina;
        }
        OperativenSistem(const OperativenSistem &os) {
            copy(os);
        }
        ~OperativenSistem() {
            delete [] this->ime;
        }
        void pecati () {
            cout<<"Ime: "<<this->ime<<" Verzija: "<<this->verzija<<" Tip: "<<this->tip<<" Golemina:"<<this->golemina<<"GB"<<endl;
        }
        OperativenSistem & operator = (const OperativenSistem &os) {
            if( this != &os ) {
                delete [] this->ime;
                copy(os);
            }
            return *this;
        }
        bool ednakviSe(const OperativenSistem &other) {
            if(!strcmp(this->ime,other.ime)) {
                if(this->tip == other.tip){
                    if(this->verzija == other.verzija) {
                        if(this->golemina == other.golemina) {
                            return true;
                        }
                    }
                }
            }
            return false;
        }
        int sporediVerzija (const OperativenSistem &other) {
            if(other.verzija>this->verzija)
                return -1;
            else if (other.verzija<this->verzija)
                return 1;
            else
                return 0;
        }
        bool istaFamilija (const OperativenSistem &other) {
            return (this->tip == other.tip) &&(!strcmp(this->ime,other.ime));
        }
}; // sve raboti

class Repozitorium {
    private:
        char ime[20];
        OperativenSistem *sistemi;
        int brojNaSistemi;
    public:
        Repozitorium (const char *ime) {
            strcpy(this->ime, ime);
            sistemi = nullptr;
            brojNaSistemi = 0;
        }
        ~Repozitorium () {
            delete [] sistemi;
        }
        void pecatiOperativniSistemi () {
            cout<<"Repozitorium: "<<ime<<endl;
           for(int i=0; i<brojNaSistemi; i++)
               sistemi[i].pecati();
        }
        void izbrishi (const OperativenSistem &operativenSistem) {
            for (int i=0;i<brojNaSistemi; i++) {
                if(this->sistemi[i].ednakviSe(operativenSistem)) {
                    for(int j=i; i<brojNaSistemi-1;i++) {
                        this->sistemi[j]=this->sistemi[j];
                    }
                    brojNaSistemi--;
                }
            }
        }
        void dodadi(const OperativenSistem &nov) {
            for (int i=0;i<brojNaSistemi; i++) {
                if(this->sistemi[i].istaFamilija(nov)) {
                    if((this->sistemi[i].sporediVerzija(nov)) == -1) {
                        this->sistemi[i] = nov;
                        return;
                    }
                }
            }
            OperativenSistem *tempSys = new OperativenSistem [brojNaSistemi+1];
            for(int i=0;i<brojNaSistemi;i++) {
                tempSys[i] = sistemi[i];
            }
            tempSys[brojNaSistemi]=nov;
            brojNaSistemi++;
            delete [] sistemi;
            sistemi = new OperativenSistem [brojNaSistemi];
            for(int i=0;i<brojNaSistemi;i++) {
                sistemi[i]=tempSys[i];
            }
            delete [] tempSys;
        }
};

int main() {
    char repoName[20];
    cin>>repoName;
    Repozitorium repozitorium=Repozitorium(repoName);
    int brojOperativniSistemi = 0;
    cin>>brojOperativniSistemi;
    char ime[20];
    float verzija;
    int tip;
    float golemina;
    for (int i = 0; i<brojOperativniSistemi; i++){
        cin>>ime;
        cin>>verzija;
        cin>>tip;
        cin>>golemina;
        OperativenSistem os = OperativenSistem(ime, verzija, (Tip)tip, golemina);
        repozitorium.dodadi(os);
    }

    repozitorium.pecatiOperativniSistemi();
    cin>>ime;
    cin>>verzija;
    cin>>tip;
    cin>>golemina;
    OperativenSistem os = OperativenSistem(ime, verzija, (Tip)tip, golemina);
    cout<<"=====Brishenje na operativen sistem====="<<endl;
    repozitorium.izbrishi(os);
    repozitorium.pecatiOperativniSistemi();
    return 0;
}
