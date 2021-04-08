#include<iostream>
#include<cstring>
#include <cmath>
using namespace std;

class Product {
private:
    char *ime;
    int cena;
    int popust;
    int dostapnaKolicina;
public:

    Product (char *ime = "", int cena = 0, int popust = 0, int dostapnaKolicina = 0 ){
        this->ime = new char [strlen(ime)+1];
        strcpy(this->ime,ime);
        this->cena = cena;
        this->popust = popust;
        this->dostapnaKolicina = dostapnaKolicina;
    }
    ~Product () {
        delete [] ime;
    }

    Product (const Product &a) {
            this->ime = new char [strlen(a.ime)+1];
            strcpy(this->ime, a.ime);
            this->cena = a.cena;
            this->popust = a.popust;
            this->dostapnaKolicina = a.dostapnaKolicina;
    }

    friend ostream & operator << (ostream &out, const Product &a) {
        return out << a.ime << " Regular price: " << a.cena <<" Price with discount: " << round(a.cena-((a.cena/100.0)*a.popust)) << " Quantity: " << a.dostapnaKolicina <<endl;
    }

    Product & operator += (int broj) {
        if(this->popust < 99) {
            if(this->popust+broj >= 99) {
                this->popust=99;
                return *this;
            }
            else {
                this->popust+=broj;
            }
        }
        return *this;
    }

    Product operator ++ (int) {
        Product p(*this);
        this->dostapnaKolicina++;
        return p;
    }
    int getQuantity () {
        return this->dostapnaKolicina;
    }
    Product & operator = (const Product &a) {
        if(this!=&a) {
            delete [] this->ime;
            this->ime = new char [strlen(a.ime)+1];
            strcpy(this->ime,a.ime);
            this->cena = a.cena;
            this->dostapnaKolicina = a.dostapnaKolicina;
            this->popust = a.popust;
        }
        return *this;
    }
};

class Store {
private:
    char ime[50];
    Product *proizvodi;
    int brProizvodi;
public:
    Store (char *_ime = "") {
        strcpy(ime,_ime);
        proizvodi = nullptr;
        brProizvodi = 0;
    }
    Store (const Store &a) {
        strcpy(this->ime, a.ime);
        proizvodi = new Product [a.brProizvodi];
        for(int i=0; i<a.brProizvodi; i++) {
            proizvodi[i]=a.proizvodi[i];
        }
        brProizvodi = a.brProizvodi;
    }
    ~Store () {
        delete [] proizvodi;
    }
    friend ostream & operator << (ostream &out, const Store &a) {
        out << a.ime <<endl;
        for(int i=0;i<a.brProizvodi;i++) {
            out<<a.proizvodi[i];
        }
        return out;
    }
    Store & operator += (const Product &a) {
            Product *tempProizvodi;
            tempProizvodi = new Product [this->brProizvodi + 1];
            for(int i=0;i<this->brProizvodi;i++)
                tempProizvodi[i] = proizvodi[i];
            tempProizvodi[brProizvodi] = a;
            brProizvodi++;
            delete [] this->proizvodi;
            this->proizvodi = new Product [brProizvodi];
            for(int i=0;i<brProizvodi;i++)
                proizvodi[i]=tempProizvodi[i];
            delete [] tempProizvodi;
    }

    Store & operator -= (int broj) {
        for(int i=0;i<brProizvodi;i++) {
            if( proizvodi[i].getQuantity() <broj)
                proizvodi[i]+=20;
        }
    }
};

int main() {
    int testCase;
    cin >> testCase;


    if (testCase == 1) {
        cout << "TESTING CONSTRUCTOR FOR PRODUCT" << endl;
        Product p;
        cout << "TEST FOR DEFAULT CONSTRUCTOR PASSED" << endl;
        Product p1("pizza", 250, 10);
        cout << "TEST FOR CONSTRUCTOR WITH 3 ARGUMENTS PASSED" << endl;
        Product p2("pizza", 250, 10, 100);
        cout << "TEST FOR CONSTRUCTOR WITH 4 ARGUMENTS PASSED" << endl;
    } else if (testCase == 2) {
        cout << "TESTING COPY-CONSTRUCTOR AND OPERATOR = (ASSIGNMENT) FOR PRODUCT" << endl;
        Product p("pizza", 250, 10, 100);
        Product p1(p);
        cout << "TEST FOR COPY CONSTRUCTOR PASSED" << endl;
        Product p2;
        p2 = p;
        cout << "TEST FOR OPERATOR = (ASSIGNMENT) PASSED" << endl;
    } else if (testCase == 3) {
        cout << "TESTING OPERATOR << FOR PRODUCT" << endl;
        Product p("pizza", 250, 10, 100);
        cout << p;
    } else if (testCase == 4) {
        cout << "TESTING OPERATORs << FOR PRODUCT" << endl;
        char name[100];
        int price, discount, quantity;
        cin >> name >> price >> discount >> quantity;
        Product p(name, price, discount, quantity);
        cout << p;
    } else if (testCase == 5) {
        cout << "TESTING OPERATOR ++ (POSTFIX) FOR PRODUCT" << endl;
        Product p("pizza", 250, 10, 100);
        int quantity = p.getQuantity();
        if (quantity == (p++).getQuantity()) {
            if ((quantity + 1) == p.getQuantity())
                cout << "CHECK PASSED" << endl;
            else
                cout << "CHECK FAILED" << endl;
        } else {
            cout << "CHECK FAILED" << endl;
        }
    } else if (testCase == 6) {
        cout << "TESTING OPERATOR += FOR PRODUCT" << endl;
        Product p("pizza", 250, 10, 100);
        p += 10;
        cout << p;
        p += 20;
        cout << p;
        p += 59;
        cout << p;
        p += 10;
        cout << p;
    } else if (testCase == 7) {
        cout << "TESTING CONSTRUCTOR FOR STORE" << endl;
        Store s("FINKI STORE");
        cout << "TEST PASSED" << endl;
    } else if (testCase == 8) {
        cout << "TESTING OPERATORS += AND << FOR STORE" << endl;
        Store s("FINKI STORE");
        Product p("pizza", 250, 10, 100);
        s += p;
        Product p1("shampoo", 289, 15, 150);
        s += p1;
        cout << s;
    } else if (testCase == 9) {
        cout << "TESTING OPERATORS += AND << FOR STORE" << endl;
        Store s("MYFINKI_STORE");
        int n;
        cin >> n;
        while (n) {
            char name[100];
            int price, discount, quantity;
            cin >> name >> price >> discount >> quantity;
            Product p(name, price, discount, quantity);
            s += p;
            --n;
        }
        cout << s;
    } else if (testCase == 10) {
        cout << "TESTING OPERATORS +=, << AND -= FOR STORE" << endl;
        Store s("FINKI STORE");
        Product p("pizza", 250, 10, 100);
        s += p;
        Product p1("shampoo", 289, 15, 150);
        s += p1;
        cout << s;
        s -= 110;
        cout << s;
    } else if (testCase == 11) {
        cout << "TESTING OPERATORS +=, << AND -= FOR STORE" << endl;
        Store s("MYFINKI_STORE");
        int n;
        cin >> n;
        while (n) {
            char name[100];
            int price, discount, quantity;
            cin >> name >> price >> discount >> quantity;
            Product p(name, price, discount, quantity);
            s += p;
            --n;
        }
        cout << s;
        int maxDiscount;
        cin >> maxDiscount;
        s -= maxDiscount;
        cout << s;
    }  else if (testCase == 12) {
        cout << "TESTING COPY CONSTRUCTOR AND OPERATOR = FOR STORE" << endl;
        Store s("FINKI STORE");
        Product p("pizza", 250, 10, 100);
        s += p;
        Product p1("shampoo", 289, 15, 150);
        s += p1;

        Store s1 = s; //copy constructor
        Store s2;
        s2 = s1; //operator =
        cout<<s1;
        cout<<s2;
        cout<<"TEST PASSED"<<endl;
    }
    return 0;
}
