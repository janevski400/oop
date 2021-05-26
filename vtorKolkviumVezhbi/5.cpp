#include <iostream>
#include <cstring>
using namespace std;
#define MAX 50

enum typeC {
    Standard=0,
    Loyal,
    Vip
};

class Customer {
private:
    char name[MAX];
    char email[MAX];
    typeC type;
    static int discount;
    static int additionalDiscount;
    int numberOfBoughtProducts;
public:
    Customer () {
        strcpy(name,"/");
        strcpy(email,"/");
        type = (typeC)0;
        numberOfBoughtProducts = 0;
    }
    Customer (char *_name, char *_email, typeC _type, int _numberOfBoughtProducts) {
        strcpy(name,_name);
        strcpy(email,_email);
        type = _type;
        numberOfBoughtProducts = _numberOfBoughtProducts;
    }
    static void setDiscount1(int a) {
        discount = a;
    }
    friend ostream &operator << (ostream &out, Customer &a) {
        out<<a.name<<endl;
        out<<a.email<<endl;
        out<<a.numberOfBoughtProducts<<endl;
        if(a.type == (typeC)0)
            return out<<"standard 0"<<endl;
        else if(a.type == (typeC)1)
            return out<<"loyal "<<discount<<endl;
        else
            return out<<"vip "<<discount+additionalDiscount<<endl;
    }
    bool operator ==(Customer &a) {
        if(!strcmp(this->email,a.email) || !strcmp(this->name,a.name))
                    return true;
        return false;
    }
    int getType () {
        return type;
    }
    int getNumProducts () {
        return numberOfBoughtProducts;
    }
    void SetType (int n) {
        type = (typeC)n;
    }
    ~Customer () {}
};

int Customer::discount=10;
int Customer::additionalDiscount=20;

class FINKI_bookstore {
private:
    Customer *c;
    int numCustomers;
public:
    FINKI_bookstore () {
        c=new Customer [0];
        numCustomers=0;
    }
    FINKI_bookstore (Customer *_customers, int n){
        numCustomers = n;
        c = new Customer[n];
        for(int i=0;i<numCustomers;i++)
            c[i]=_customers[i];
    }
    ~FINKI_bookstore () {
        delete [] c;
    }
    FINKI_bookstore &operator += (Customer &a) {
        for(int i=0;i<numCustomers;i++)
            if(c[i].Customer::operator==(a)) {
                throw "UserExists";
            }
        Customer *tempC = new Customer [numCustomers+1];
        for(int i=0;i<numCustomers;i++)
            tempC[i]=c[i];
        tempC[numCustomers]=a;
        numCustomers++;
        delete [] c;
        c = new Customer [numCustomers];
        for(int i=0;i<numCustomers;i++)
            c[i]=tempC[i];
        delete [] tempC;
        return *this;
    }
    void update () {
        for(int i=0;i<numCustomers;i++) {
            if(c[i].getType()==0) {
                if(c[i].getNumProducts()>5)
                    c[i].SetType(1);
            }
            else if(c[i].getType()==1) {
                if(c[i].getNumProducts()>10)
                    c[i].SetType(2);
            }
        }
    }

    friend ostream &operator << (ostream &ouut, FINKI_bookstore &store) {
        for(int i=0;i<store.numCustomers;i++) {
            ouut<<store.c[i];
        }
        return ouut;
    }
    void setCustomers(Customer *cust, int n) {
        for(int i=0;i<n;i++) {
            *this+=cust[i];
        }
    }
};


int main(){
  int testCase;
  cin >> testCase;

  char name[MAX];
  char email[MAX];
  int tC;
  int discount;
  int numProducts;


  if (testCase == 1){
    cout << "===== Test Case - Customer Class ======" << endl;
    cin.get();
    cin.getline(name,MAX);
    cin.getline(email,MAX);
    cin >> tC;
    cin >> numProducts;
    cout << "===== CONSTRUCTOR ======" << endl;
    Customer c(name, email, (typeC) tC, numProducts);
    cout << c;

  }

  if (testCase == 2){
    cout << "===== Test Case - Static Members ======" << endl;
    cin.get();
    cin.getline(name,MAX);
    cin.getline(email,MAX);
    cin >> tC;
    cin >> numProducts;
    cout << "===== CONSTRUCTOR ======" << endl;
    Customer c(name, email, (typeC) tC, numProducts);
    cout << c;

    c.setDiscount1(5);

    cout << c;
  }

  if (testCase == 3){
    cout << "===== Test Case - FINKI-bookstore ======" << endl;
    FINKI_bookstore fc;
    int n;
    cin >> n;
    Customer customers[MAX];
    for(int i = 0; i < n; ++i) {
      cin.get();
      cin.getline(name,MAX);
      cin.getline(email,MAX);
      cin >> tC;
      cin >> numProducts;
      Customer c(name, email, (typeC) tC, numProducts);
      customers[i] = c;
    }

    fc.setCustomers(customers, n);
    cout << fc <<endl;
  }

  if (testCase == 4){
    cout << "===== Test Case - operator+= ======" << endl;
    FINKI_bookstore fc;
    int n;
    cin >> n;
    Customer customers[MAX];
    for(int i = 0; i < n; ++i) {
      cin.get();
      cin.getline(name,MAX);
      cin.getline(email,MAX);
      cin >> tC;
      cin >> numProducts;
      Customer c(name, email, (typeC) tC, numProducts);
      customers[i] = c;
    }

    fc.setCustomers(customers, n);
    cout << "OPERATOR +=" << endl;
    cin.get();
    cin.getline(name,MAX);
    cin.getline(email,MAX);
    cin >> tC;
    cin >> numProducts;
    Customer c(name, email, (typeC) tC, numProducts);
    fc+=c;

    cout << fc;
  }

  if (testCase == 5){
    cout << "===== Test Case - operator+= (exception) ======" << endl;
    FINKI_bookstore fc;
    int n;
    cin >> n;
    Customer customers[MAX];
    for(int i = 0; i < n; ++i) {
      cin.get();
      cin.getline(name,MAX);
      cin.getline(email,MAX);
      cin >> tC;
      cin >> numProducts;
      Customer c(name, email, (typeC) tC, numProducts);
      customers[i] = c;
    }

    fc.setCustomers(customers, n);
    cout << "OPERATOR +=" << endl;
    cin.get();
    cin.getline(name,MAX);
    cin.getline(email,MAX);
    cin >> tC;
    cin >> numProducts;
    Customer c(name,email,(typeC)tC,numProducts);
    try {
        fc+=c;
    }
    catch (const char *) {
        cout<<"The user already exists in the list!"<<endl;
    }
    cout << fc;
  }

  if (testCase == 6){
    cout << "===== Test Case - update method  ======" << endl << endl;
    FINKI_bookstore fc;
    int n;
    cin >> n;
    Customer customers[MAX];
    for(int i = 0; i < n; ++i) {
      cin.get();
      cin.getline(name,MAX);
      cin.getline(email,MAX);
      cin >> tC;
      cin >> numProducts;
      Customer c(name, email, (typeC) tC, numProducts);
      customers[i] = c;
    }
    fc.setCustomers(customers, n);
    cout << "Update:" << endl;
    fc.update();
    cout << fc;
  }
  return 0;

}
