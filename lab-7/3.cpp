#include <iostream>
#include <cmath>
using namespace std;

class Shape {
protected:
    int side;
public:
    virtual double plostina() = 0;
    virtual void pecati() = 0;
    virtual int getType() = 0;
    Shape (int a = 0) {
        side = a;
    }
};
class Square : public Shape {
public:
    Square (int a = 0):Shape(a) {}
    double plostina() {
        return side * side;
    }
    int getType () {
        return 1;
    }
    void pecati () {
        cout<<"Kvadrat so plostina = "<<plostina()<<endl;
    }
};
class Circle : public Shape {
public:
    Circle (int a = 0): Shape(a) {}
    double plostina () {
        return 3.14 * side * side;
    }
    int getType () {
        return 2;
    }
    void pecati () {
        cout<<"Krug so plostina = "<<plostina()<<endl;
    }
};
class Triangle : public Shape {
public:
    double plostina () {
        return (sqrt(3)/4)*side*side;
    }
    int getType () {
        return 3;
    }
    void pecati () {
        cout<<"Triagolnik so plostina = "<<plostina()<<endl;
    }
    Triangle (int a = 0): Shape(a) {}
};

void checkNumTypes (Shape **niza, int n) {
    int countSquare = 0, countCircle = 0, countTriangle = 0;
    for(int i=0;i<n;i++) {
        if (niza[i]->getType() == 1)
            countSquare++;
        else if (niza[i]->getType() == 2)
            countCircle++;
        else
            countTriangle++;
    }
    cout<<"Broj na kvadrati vo nizata = "<<countSquare<<endl;
    cout<<"Broj na krugovi vo nizata = "<<countCircle<<endl;
    cout<<"Broj na triagolnici vo nizata = "<<countTriangle;
}

int main(){
    int n;
    cin >> n;
    Shape **niza;
    niza = new Shape * [n];
    int classType;
    int side;
    for(int i = 0; i < n; ++i){
        cin >> classType;
        cin >> side;
        if(classType == 1)
            niza[i] = new Square(side);
        else if (classType == 2)
            niza[i] = new Circle(side);
        else if (classType == 3)
            niza[i] = new Triangle(side);
    }
    for(int i = 0; i < n; ++i){
        niza[i]->pecati();
    }
    checkNumTypes(niza, n);
    return 0;
}
