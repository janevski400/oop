//Stefan Janevski - 201117
#include<iostream>
#include<cstring>
using namespace std;

class Date {
private:
    int year;
    int month;
    int day;
public:

    Date (int year = 1900, int month = 1, int day = 1)
    {
        this->year = year;
        this->month = month;
        this->day = day;
    }

    Date (const Date &a) {
        year = a.year;
        month = a.month;
        day = a.day;
    }

    ~Date() {

    }
    void print() {
        cout<<this->year<<"."<<this->month<<"."<<this->day<<endl;
    }

};

class Person {
private:
    char name[20];
    char lastName[20];
public:
    Person (char *name = "", char *lastName = "") {
        strcpy(this->name, name);
        strcpy(this->lastName, lastName);
    }
    ~Person() {

    }
    void print() {
        cout<<name<<" "<<lastName<<endl;
    }
};

class Car{
private:
    Person Owner;
    Date purchaseDate;
    float price;
public:
    Car(const Person Owner = {"", ""}, Date purchaseDate = {1990, 1, 1}, float price = 0) {
        this->Owner = Owner;
        this->purchaseDate = purchaseDate;
        this->price = price;
    }

    void print () {
        Owner.print();
        purchaseDate.print();
        cout<<"Price: "<<price;
    }

    float getPrice () {
        return price;
    }

};

void cheaperThan (Car *cars, int numCars, float price)
{
    while(numCars--)
    {
        if(cars[numCars].getPrice() < price)
            cars->print();
    }
}

int main() {
    char name[20];
    char lastName[20];
    int year;
    int month;
    int day;
    float price;

    int testCase;
    cin >> testCase;

    if (testCase == 1) {
        cin >> name;
        cin >> lastName;
        Person lik(name, lastName);

        cin >> year;
        cin >> month;
        cin >> day;
        Date date(year, month, day);

        cin >> price;
        Car car(lik, date,  price);

        car.print();
    }
    else if (testCase == 2) {
        cin >> name;
        cin >> lastName;
        Person lik(name, lastName);

        cin >> year;
        cin >> month;
        cin >> day;
        Date date(Date(year, month, day));

        cin >> price;
        Car car(lik, date,  price);
        car.print();
    }
    else {
        int numCars;
        cin >> numCars;

        Car cars[10];
        for (int i = 0; i < numCars; i++) {
            cin >> name;
            cin >> lastName;
            Person lik(name, lastName);

            cin >> year;
            cin >> month;
            cin >> day;
            Date date(year, month, day);

            cin >> price;
            cars[i] = Car(lik, date,  price);
        }
        float priceLimit;
        cin >> priceLimit;
        cheaperThan(cars, numCars, priceLimit);
    }


    return 0;
}
