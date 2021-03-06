#include <iostream>
#include <cstring>
using namespace std;

class Trud {
private:
    char tip;
    int godinaIzdavanje;
    static int boduvanjeKonferenciskiTrud;
    static int boduvanjeTrudVoSpisanie;
public:
    Trud (char tip='0', int godinaIzdavanje=0) {
        this->tip = tolower(tip);
        this->godinaIzdavanje = godinaIzdavanje;
    }
    static void setBoduvanjeKonferenciskiTrud (int newValue) { boduvanjeKonferenciskiTrud = newValue; }
    static void setBoduvanjeTrudVoSpisanie (int newValue) { boduvanjeTrudVoSpisanie = newValue; }
    char getTip(){ return tip; }
    static int getBoduvanjeKonferenciski() { return boduvanjeKonferenciskiTrud; }
    static int getBoduvanjeTrudSpisanie() { return boduvanjeTrudVoSpisanie;}
    friend istream &operator >>(istream &in, Trud &other) {
        in>>other.tip>>other.godinaIzdavanje;
        return in;
    }
    int getGodina () { return godinaIzdavanje; }

    Trud &operator = (Trud &other) {
        this->tip = tolower(other.tip);
        this->godinaIzdavanje = other.godinaIzdavanje;
        return *this;
    }
};

int Trud::boduvanjeKonferenciskiTrud = 1;
int Trud::boduvanjeTrudVoSpisanie = 3;

class Student {
private:
    char ime[30];
    int indeks;
    int godinaUpis;
    int listaOcenkiPolozheniPredmeti[30];
    int brojPolozheniPredmeti;
public:
    Student(char *ime = nullptr, int indeks = 0, int godinaUpis = 0, int *listaOcenkiPolozheniPredmeti = 0, int brojPolozheniPredmeti = 0)
    {
        strcpy(this->ime,ime);
        this->indeks = indeks;
        this->godinaUpis = godinaUpis;
        this->brojPolozheniPredmeti = brojPolozheniPredmeti;
        for(int i=0;i<brojPolozheniPredmeti;i++){
            this->listaOcenkiPolozheniPredmeti[i]=listaOcenkiPolozheniPredmeti[i];
        }
    }
    virtual double rang () {
        double temp = 0;
        for(int i=0;i<brojPolozheniPredmeti;i++){
            temp+=listaOcenkiPolozheniPredmeti[i];
        }
        return temp/(double)brojPolozheniPredmeti;
    }

    int getGodinaUpis () { return godinaUpis; }
    int getIndeks () { return indeks; }
    char* getIme () { return ime; }
};

class Exception {
private:
    char msg[50];
public:
    Exception(char *poraka) {
        strcpy(this->msg,poraka);
    }
    void message () {
        cout<<msg;
        cout<<endl;
    }
};

class PhDStudent : public Student {
private:
    Trud *listaObjaveniTrudovi;
    int brojTrudovi;
public:
    PhDStudent(char *ime = nullptr, int indeks = 0, int godinaUpis = 0, int listaOcenkiPolozheniPredmeti[] = {0}, int brojPolozheniPredmeti = 0, Trud *_listaObjaveniTrudovi = nullptr, int _brojTrudovi = 0):Student(ime,indeks,godinaUpis,listaOcenkiPolozheniPredmeti,brojPolozheniPredmeti)
    {
        brojTrudovi = _brojTrudovi;
        listaObjaveniTrudovi = new Trud [brojTrudovi];
        for(int i=0,j=0;i<brojTrudovi;i++){
            try{
                if(_listaObjaveniTrudovi[i].getGodina()<this->getGodinaUpis()) {
                    throw Exception("Ne moze da se vnese dadeniot trud");
                }
                listaObjaveniTrudovi[j] = _listaObjaveniTrudovi[i];
                j++;

            }
            catch (Exception &ex) {
                ex.message();
            }
        }
    }
    virtual double rang () {
        double tempPoeni = 0;
        int conf = Trud::getBoduvanjeKonferenciski();
        int jour = Trud::getBoduvanjeTrudSpisanie();
        for(int i=0;i<brojTrudovi;i++)
        {
            if(listaObjaveniTrudovi[i].getTip()=='c'){
                tempPoeni+=conf;
            }
            else if(listaObjaveniTrudovi[i].getTip() == 'j'){
                tempPoeni+=jour;
            }
        }
        return tempPoeni+Student::rang();
    }
    PhDStudent &operator +=(Trud &novTrud) {
        if(novTrud.getGodina() < this->getGodinaUpis()){
            throw Exception("Ne moze da se vnese dadeniot trud");
        }
        else {
            Trud *tempLista = new Trud[brojTrudovi+1];
            for(int i=0;i<brojTrudovi;i++)
                tempLista[i] = listaObjaveniTrudovi[i];
            tempLista[brojTrudovi] = novTrud;
            brojTrudovi++;

            delete [] listaObjaveniTrudovi;
            listaObjaveniTrudovi = new Trud [brojTrudovi];
            for(int i=0;i<brojTrudovi;i++)
                listaObjaveniTrudovi[i] = tempLista[i];
            delete [] tempLista;
            return *this;
        }
    }
    ~PhDStudent () {
        delete [] listaObjaveniTrudovi;
    }
};

ostream &operator << (ostream &out, Student &other) {
     return out<<other.getIndeks()<<" "<<other.getIme()<<" "<<other.getGodinaUpis()<<" "<<other.rang()<<endl;
}

int main(){
	int testCase;
	cin >> testCase;

	int god, indeks, n, god_tr, m, n_tr;
	int izbor; //0 za Student, 1 za PhDStudent
	char ime[30];
	int oceni[50];
	char tip;
	Trud trud[50];

	if (testCase == 1){
		cout << "===== Testiranje na klasite ======" << endl;
		cin >> ime;
		cin >> indeks;
		cin >> god;
		cin >> n;
		for (int j = 0; j < n; j++)
			cin >> oceni[j];
		Student s(ime, indeks, god, oceni, n);
		cout << s;

		cin >> ime;
		cin >> indeks;
		cin >> god;
		cin >> n;
		for (int j = 0; j < n; j++)
			cin >> oceni[j];
		cin >> n_tr;
		for (int j = 0; j < n_tr; j++){
			cin >> tip;
			cin >> god_tr;
			Trud t(tip, god_tr);
			trud[j] = t;
		}
		PhDStudent phd(ime, indeks, god, oceni, n, trud, n_tr);
		cout << phd;
	}
	if (testCase == 2){
		cout << "===== Testiranje na operatorot += ======" << endl;
		Student **niza;
		cin >> m;
		niza = new Student *[m];
		for (int i = 0; i<m; i++){
			cin >> izbor;
			cin >> ime;
			cin >> indeks;
			cin >> god;
			cin >> n;
			for (int j = 0; j < n; j++)
				cin >> oceni[j];

			if (izbor == 0){
				niza[i] = new Student(ime, indeks, god, oceni, n);
			}
			else{
				cin >> n_tr;
				for (int j = 0; j < n_tr; j++){
					cin >> tip;
					cin >> god_tr;
					Trud t(tip, god_tr);
					trud[j] = t;
				}
				niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
			}
		}
		// pecatenje na site studenti
		cout << "\nLista na site studenti:\n";
		for (int i = 0; i < m; i++)
			cout << *niza[i];

		// dodavanje nov trud za PhD student spored indeks
		Trud t;
		cin >> indeks;
		cin >> t;

		// vmetnete go kodot za dodavanje nov trud so pomos na operatorot +=
		bool imaStudent = false;
        for(int i=0;i<m;i++)
        {
            try {
                PhDStudent *temp = dynamic_cast<PhDStudent*>(niza[i]);
                if(temp) {
                    if(niza[i]->getIndeks() == indeks) {
                        imaStudent=true;
                        temp->operator+=(t);
                    }
                }
            }
            catch (Exception &ex) {
                ex.message();
            }
        }
        if(!imaStudent)
            cout<<"Ne postoi PhD student so indeks "<<indeks<<endl;

		// pecatenje na site studenti
		cout << "\nLista na site studenti:\n";
		for (int i = 0; i < m; i++)
			cout << *niza[i];
	}
	if (testCase == 3){
		cout << "===== Testiranje na operatorot += ======" << endl;
		Student **niza;
		cin >> m;
		niza = new Student *[m];
		for (int i = 0; i<m; i++){
			cin >> izbor;
			cin >> ime;
			cin >> indeks;
			cin >> god;
			cin >> n;
			for (int j = 0; j < n; j++)
				cin >> oceni[j];

			if (izbor == 0){
				niza[i] = new Student(ime, indeks, god, oceni, n);
			}
			else{
				cin >> n_tr;
				for (int j = 0; j < n_tr; j++){
					cin >> tip;
					cin >> god_tr;
					Trud t(tip, god_tr);
					trud[j] = t;
				}
				niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
			}
		}
		// pecatenje na site studenti
		cout << "\nLista na site studenti:\n";
		for (int i = 0; i < m; i++)
			cout << *niza[i];

		// dodavanje nov trud za PhD student spored indeks
		Trud t;
		cin >> indeks;
		cin >> t;

		// vmetnete go kodot za dodavanje nov trud so pomos na operatorot += od Testcase 2
		bool imaStudent = false;
        for(int i=0;i<m;i++)
        {
            try {
                PhDStudent *temp = dynamic_cast<PhDStudent*>(niza[i]);
                if(temp) {
                    if(niza[i]->getIndeks() == indeks) {
                        imaStudent=true;
                        temp->operator+=(t);
                    }
                }
            }
            catch (Exception &ex) {
                ex.message();
            }
        }
        if(!imaStudent)
            cout<<"Ne postoi PhD student so indeks "<<indeks<<endl;


		// pecatenje na site studenti
		cout << "\nLista na site studenti:\n";
		for (int i = 0; i < m; i++)
			cout << *niza[i];
	}
	if (testCase == 4){
		cout << "===== Testiranje na isklucoci ======" << endl;
		cin >> ime;
		cin >> indeks;
		cin >> god;
		cin >> n;
		for (int j = 0; j < n; j++)
			cin >> oceni[j];
		cin >> n_tr;
		for (int j = 0; j < n_tr; j++){
                cin >> tip;
                cin >> god_tr;
                Trud t(tip, god_tr);
                trud[j] = t;
		}
		PhDStudent phd(ime, indeks, god, oceni, n, trud, n_tr);
		cout << phd;
	}
	if (testCase == 5){
		cout << "===== Testiranje na isklucoci ======" << endl;
		Student **niza;
		cin >> m;
		niza = new Student *[m];
		for (int i = 0; i<m; i++){
			cin >> izbor;
			cin >> ime;
			cin >> indeks;
			cin >> god;
			cin >> n;
			for (int j = 0; j < n; j++)
				cin >> oceni[j];

			if (izbor == 0){
				niza[i] = new Student(ime, indeks, god, oceni, n);
			}
			else{
				cin >> n_tr;
				for (int j = 0; j < n_tr; j++){
					cin >> tip;
					cin >> god_tr;
					Trud t(tip, god_tr);
					trud[j] = t;
				}
				niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
			}
		}
		// pecatenje na site studenti
		cout << "\nLista na site studenti:\n";
		for (int i = 0; i < m; i++)
			cout << *niza[i];

		// dodavanje nov trud za PhD student spored indeks
		Trud t;
		cin >> indeks;
		cin >> t;

		// vmetnete go kodot za dodavanje nov trud so pomos na operatorot += i spravete se so isklucokot
		bool imaStudent = false;
        for(int i=0;i<m;i++)
        {
            try {
                PhDStudent *temp = dynamic_cast<PhDStudent*>(niza[i]);
                if(temp) {
                    if(niza[i]->getIndeks() == indeks) {
                        imaStudent=true;
                        temp->operator+=(t);
                    }
                }
            }
            catch (Exception &ex) {
                ex.message();
            }
        }
        if(!imaStudent)
            cout<<"Ne postoi PhD student so indeks "<<indeks<<endl;

		// pecatenje na site studenti
		cout << "\nLista na site studenti:\n";
		for (int i = 0; i < m; i++)
			cout << *niza[i];
	}
	if (testCase == 6){
		cout << "===== Testiranje na static clenovi ======" << endl;
		Student **niza;
		cin >> m;
		niza = new Student *[m];
		for (int i = 0; i<m; i++){
			cin >> izbor;
			cin >> ime;
			cin >> indeks;
			cin >> god;
			cin >> n;
			for (int j = 0; j < n; j++)
				cin >> oceni[j];

			if (izbor == 0){
				niza[i] = new Student(ime, indeks, god, oceni, n);
			}
			else{
				cin >> n_tr;
				for (int j = 0; j < n_tr; j++){
					cin >> tip;
					cin >> god_tr;
					Trud t(tip, god_tr);
					trud[j] = t;
				}
				niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
			}
		}
		// pecatenje na site studenti
		cout << "\nLista na site studenti:\n";
		for (int i = 0; i < m; i++)
			cout << *niza[i];

		int conf, journal;
		cin >> conf;
		cin >> journal;

        //postavete gi soodvetnite vrednosti za statickite promenlivi
        Trud::setBoduvanjeKonferenciskiTrud(conf);
        Trud::setBoduvanjeTrudVoSpisanie(journal);

		// pecatenje na site studenti
		cout << "\nLista na site studenti:\n";
		for (int i = 0; i < m; i++)
			cout << *niza[i];
	}

	return 0;
}
