#include <iostream>
using namespace std;

class Kvadrat {
protected:
    double a;
public:
    Kvadrat (double a = 0) {
        this->a = a;
    }
    Kvadrat (const Kvadrat &other) {
        this->a = other.a;
    }
    double perimetar () {
        return 4*a;
    }
    double plostina() {
        return a*a;
    }
    void pecati (){
        cout<<"Kvadrat so dolzina a="<<a<<" ima plostina P="<<plostina()<<" i perimetar L="<<perimetar()<<endl;
    }
    Kvadrat &operator = (const Kvadrat &other) {
        this->a = other.a;
        return *this;
    }
};

class Pravoagolnik: public Kvadrat{
private:
    double x,y;
public:
    Pravoagolnik (double x = 0.0, double y = 0.0){
        this->a = 0.0;
        this->x = 0.0;
        this->y = 0.0;
    }
    Pravoagolnik (const Kvadrat &k, double x, double y):Kvadrat(k){
        this->x = x+a;
        this->y = y+a;
    }
    Pravoagolnik (const Pravoagolnik &other) {
        this->a = other.a;
        this->y = other.y;
        this->x = other.x;
    }
    double perimetar () {
        double tempReturn;
        if(x==y) {
            double tempA = a;
            a=x;
            tempReturn=Kvadrat::perimetar();
            a=tempA;
        }
        else {
            tempReturn = Kvadrat::perimetar()+(2*(x-a))+(2*(y-a));
        }
        return tempReturn;
    }
    double plostina() {
        double tempReturn;
        if(x==y) {
            double tempA = a;
            a=x;
            tempReturn=Kvadrat::plostina();
            a=tempA;
        }
        else {
            double tempPlostina = (y*x)-Kvadrat::plostina();
            tempReturn = tempPlostina + Kvadrat::plostina();
        }
        return tempReturn;
    }
    void pecati () {
        if(x==y) {
            double tempA = a;
            a = x;
            Kvadrat::pecati();
            a = tempA;
        }
        else
            cout<<"Pravoagolnik so strani: "<<x<<" i "<<y<<" ima plostina P="<<plostina()<<" i perimetar L="<<perimetar()<<endl;
    }
    Pravoagolnik &operator = (const Pravoagolnik &other) {
        this->a = other.a;
        this->x = other.x;
        this->y = other.y;
        return *this;
    }
};

int main() {
    int n;
    double a, x, y;
    Kvadrat* kvadrati;
    Pravoagolnik* pravoagolnici;

    cin >> n;

    kvadrati = new Kvadrat[n];
    pravoagolnici = new Pravoagolnik[n];

    for (int i = 0; i < n; i++) {
        cin >> a;

        kvadrati[i] = Kvadrat(a);
    }

    for (int i = 0; i < n; i++) {
        cin >> x >> y;

        pravoagolnici[i] = Pravoagolnik(kvadrati[i], x, y);
    }

    int testCase;
    cin >> testCase;

    if (testCase == 1) {
        cout << "===Testiranje na klasata Kvadrat===" << endl;
        for (int i = 0; i < n; i++)
            kvadrati[i].pecati();
    }
    else {
        cout << "===Testiranje na klasata Pravoagolnik===" << endl;
        for (int i = 0; i < n; i++)
            pravoagolnici[i].pecati();
    }
}
