#include <iostream>
#include <cstring>
using namespace std;

class Book {
protected:
    char ISBN[21];
    char naslov[51];
    char avtor[31];
    double osnovnaCena;
public:
    Book (char *_ISBN, char *_naslov, char *_avtor, double _osnovnaCena) {
        strcpy(ISBN,_ISBN);
        strcpy(naslov,_naslov);
        strcpy(avtor,_avtor);
        osnovnaCena = _osnovnaCena;
    }
    virtual double bookPrice() = 0;
    void setISBN(char *_isbn) {
        strcpy(ISBN,_isbn);
    }
    char* getISBN () {
        return ISBN;
    }
    char* getNaslov() {
        return naslov;
    }
    char* getAvtor () {
        return avtor;
    }
};

class OnlineBook : public Book{
private:
    char *url;
    int golemina;
public:
    OnlineBook (char *ISBN, char *naslov, char *avtor , double osnovnaCena, char *_url, int _golemina) : Book(ISBN,naslov,avtor,osnovnaCena){
        url = new char [strlen(_url)+1];
        strcpy(url,_url);
        golemina = _golemina;
    }
    OnlineBook(void *a, void *b, void *c, int d, OnlineBook &other):Book(other.ISBN,other.naslov,other.avtor,other.osnovnaCena) {
        this->url = new char [strlen(other.url)+1];
        strcpy(this->url,other.url);
        this->golemina = other.golemina;
    }
    ~OnlineBook() {
        delete url;
    }
    double bookPrice() {
        if(golemina>20)
            return osnovnaCena+(osnovnaCena*0.20);
        else
            return osnovnaCena;
    }
};

class PrintBook : public Book {
private:
    double masa;
    bool zaliha;
public:
    //books[i] = new PrintBook(isbn, title, author, price, weight, inStock);
    PrintBook (char *_ISBN, char *_naslov, char *_avtor , double _osnovnaCena, double _masa, bool _zaliha) :Book(_ISBN,_naslov,_avtor,_osnovnaCena) {
        masa = _masa;
        zaliha = _zaliha;
    }
    double bookPrice () {
        if(masa>0.7)
            return osnovnaCena+(osnovnaCena*0.15);
        else
            return osnovnaCena;
    }
};

bool operator > (Book &a, Book &b) {
    return (a.bookPrice()>b.bookPrice());
}

ostream &operator << (ostream &out, Book &other) {
    return out<<other.getISBN()<<": "<<other.getNaslov()<<", "<<other.getAvtor()<<" "<<other.bookPrice()<<endl;
}

void mostExpensiveBook(Book **books, int n) {
    Book *mostExpensive = books[1];
    int onlineBookCounter=0, printBookCounter=0;
    for(int i=0;i<n;i++) {
        if(dynamic_cast<OnlineBook*>(books[i]))
            onlineBookCounter++;
        else
            printBookCounter++;
        if(books[i]->bookPrice() > mostExpensive->bookPrice())
            mostExpensive=books[i];
    }
    cout<<"FINKI-Education"<<endl;
    cout<<"Total number of online books: "<<onlineBookCounter<<endl;
    cout<<"Total number of print books: "<<printBookCounter<<endl;
    cout<<"The most expensive book is: "<<endl;
    cout<<*mostExpensive;
}

int main(){

    char isbn[20], title[50], author[30], url[100];
    int size, tip;
    float price, weight;
    bool inStock;
    Book  **books;
    int n;

    int testCase;
    cin >> testCase;

    if (testCase == 1){
        cout << "====== Testing OnlineBook class ======" << endl;
        cin >> n;
        books = new Book *[n];

        for (int i = 0; i < n; i++){
            cin >> isbn;
            cin.get();
            cin.getline(title, 50);
            cin.getline(author, 30);
            cin >> price;
            cin >> url;
            cin >> size;
            cout << "CONSTRUCTOR" << endl;
            books[i] = new OnlineBook(isbn, title, author, price, url, size);
            cout << "OPERATOR <<" << endl;
            cout << *books[i];
        }
        cout << "OPERATOR >" << endl;
        cout << "Rezultat od sporedbata e: " << endl;
        if (*books[0] > *books[1])
            cout << *books[0];
        else
            cout << *books[1];
    }
    if (testCase == 2){
        cout << "====== Testing OnlineBook CONSTRUCTORS ======" << endl;
        cin >> isbn;
        cin.get();
        cin.getline(title, 50);
        cin.getline(author, 30);
        cin >> price;
        cin >> url;
        cin >> size;
        cout << "CONSTRUCTOR" << endl;
        OnlineBook ob1(isbn, title, author, price, url, size);
        cout << ob1 << endl;
        cout << "COPY CONSTRUCTOR" << endl;
        OnlineBook ob2(nullptr, nullptr, nullptr, 0, ob1);
        cin >> isbn;
        ob2.setISBN(isbn);
        cout << ob1 << endl;
        cout << ob2 << endl;
        cout << "OPERATOR =" << endl;
        ob1 = ob2;
        cin >> isbn;
        ob2.setISBN(isbn);
        cout << ob1 << endl;
        cout << ob2 << endl;
    }
    if (testCase == 3){
        cout << "====== Testing PrintBook class ======" << endl;
        cin >> n;
        books = new Book *[n];

        for (int i = 0; i < n; i++){
            cin >> isbn;
            cin.get();
            cin.getline(title, 50);
            cin.getline(author, 30);
            cin >> price;
            cin >> weight;
            cin >> inStock;
            cout << "CONSTRUCTOR" << endl;
            books[i] = new PrintBook(isbn, title, author, price, weight, inStock);
            cout << "OPERATOR <<" << endl;
            cout << *books[i];
        }
        cout << "OPERATOR >" << endl;
        cout << "Rezultat od sporedbata e: " << endl;
        if (*books[0] > *books[1])
            cout << *books[0];
        else
            cout << *books[1];
    }
    if (testCase == 4){
        cout << "====== Testing method mostExpensiveBook() ======" << endl;
        cin >> n;
        books = new Book *[n];

        for (int i = 0; i<n; i++){

            cin >> tip >> isbn;
            cin.get();
            cin.getline(title, 50);
            cin.getline(author, 30);
            cin >> price;
            if (tip == 1) {

                cin >> url;
                cin >> size;

                books[i] = new OnlineBook(isbn, title, author, price, url, size);

            }
            else {
                cin >> weight;
                cin >> inStock;

                books[i] = new PrintBook(isbn, title, author, price, weight, inStock);
            }
        }
        mostExpensiveBook(books, n);
    }
    for (int i = 0; i<n; i++) delete books[i];
    delete[] books;
    return 0;
}
