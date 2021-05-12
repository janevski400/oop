#include<cstring>
#include<iostream>
using namespace std;

class Secret{
public:
    virtual double simpleEntropy() = 0;
    virtual int total () = 0;
};

class DigitSecret : public Secret {
private:
   int number[100];
   int countOfNumbers;
public:
    DigitSecret(int nums[], int _count) {
        countOfNumbers = _count;
        for(int i = 0; i<countOfNumbers; i++)
            number[i]=nums[i];
    }
    int total () {
        return countOfNumbers;
    }
    double simpleEntropy() {
        int counterUnique = 0;
        bool flag;
        for (int i = 0; i <countOfNumbers; i++) {
            flag = true;
            for (int j = 0; j < countOfNumbers; j++) {
                if (number[i] == number[j] && j != i)
                    flag = false;
            }
            if (flag)
                counterUnique++;
        }
        return (double)counterUnique /countOfNumbers;
    }
    friend ostream &operator << (ostream &out, DigitSecret &obj) {
        for(int i=0;i<obj.countOfNumbers;i++)
            out<<obj.number[i];
        out<<" Simple entropy: "<<obj.simpleEntropy()<<" Total: "<<obj.total();
        return out;
    }
};

class CharSecret :public Secret { //da se dopolni so izraz za nasleduvanje
private:
    char word[100];
    int countChar;
public:
    CharSecret(char *_word = "") {
        countChar = strlen(_word);
        strcpy(word,_word);
    }
    int total () {
        return countChar;
    }
    double simpleEntropy() {
        int counterUnique = 0;
        bool flag;
        for (int i = 0; i <countChar; i++) {
            flag = true;
            for (int j = 0; j < countChar; j++) {
                if (word[i] == word[j] && j != i)
                    flag = false;
            }
            if (flag)
                counterUnique++;
        }
        return (double)counterUnique/countChar;
    }
    friend ostream &operator << (ostream &out, CharSecret &obj) {
        out<<obj.word<<" Simple entropy: "<<obj.simpleEntropy()<<" Total: "<<obj.total();
        return out;
    }
};

bool operator == (Secret &a, Secret &b) {
    return (a.total()==b.total() && a.simpleEntropy()==b.simpleEntropy());
}
bool operator != (Secret &a, Secret &b) {
    return !(a==b);
}

void process(Secret ** secrets, int n){
    double max = 0;
    Secret *maxEntropy;
    for(int i=0;i<n;i++) {

        if (secrets[i]->simpleEntropy() > max) {
            maxEntropy=secrets[i];
            max=secrets[i]->simpleEntropy();
        }
    }
    if(dynamic_cast<DigitSecret*>(maxEntropy)) {
        cout<<*dynamic_cast<DigitSecret*>(maxEntropy)<<endl;
    }
    else
        cout<<*dynamic_cast<CharSecret*>(maxEntropy)<<endl;
}


void printAll (Secret ** secrets, int n) {
    for(int i=0;i<n;i++) {
        if(dynamic_cast<DigitSecret*>(secrets[i])) {
            cout<<*dynamic_cast<DigitSecret*>(secrets[i])<<endl;
        }
        else
            cout<<*dynamic_cast<CharSecret*>(secrets[i])<<endl;
    }
}

int main() {
    int n;
    cin >> n;
    if(n == 0) {
        cout << "Constructors" << endl;
        int numbers [] = {1,2,3,4,5};
        DigitSecret ds(numbers,5);
        CharSecret cs("abcabc");
        cout << "OK" << endl;
    } else if(n == 1) {
        cout << "operator <<" << endl;
        int numbers [] = {1,2,3,4,5};
        DigitSecret ds(numbers,5);
        CharSecret cs("abcabc");
        cout << ds << endl;
        cout << cs << endl;
    }  else if(n == 2) {
        cout << "== and !=" << endl;
        int numbers [] = {1,2,3,4,5};
        DigitSecret ds(numbers,5);
        CharSecret cs("abcabc");
        CharSecret css("abcabc");
        cout << (ds == cs) << endl;
        cout << (cs != ds) << endl;
        cout << (cs == css) << endl;
        cout << (cs != css) << endl;
    } else if(n == 3) {
        cout << "Secret processor" << endl;
        int numbers1 [] = {1,2,3,4,5,6,4,3,2,1,1,2,3,4,5};
        DigitSecret ds1(numbers1,15);
        int numbers2 [] = {1,2,3,4,5,0,0,0,5,5,4,4,3,3,2};
        DigitSecret ds2(numbers2,15);
        int numbers3 [] = {1,0,9,4,3,8,4,0,9,3,1,4,3,2,1,4,4,3,7,2};
        DigitSecret ds3(numbers3,20);
        CharSecret cs1("fhdaieowujkfjdsafjdsakjhueiqoyroq");
        CharSecret cs2("nvzcfsadrqipqhfjdfncxoqw");
        CharSecret cs3("uyoihfdsanmqeqrzvdhfeqyrq");
        Secret** s = new Secret*[6];
        s[0] = &ds1;
        s[1] = &ds2;
        s[2] = &ds3;
        s[3] = &cs1;
        s[4] = &cs2;
        s[5] = &cs3;
        process(s,6);
        delete [] s;
    }
    else if (n==4){
        cout << "Print all secrets" << endl;
        int numbers1 [] = {1,2,3,4,5,5,4,3,2,1,1,2,3,4,5};
        DigitSecret ds1(numbers1,15);
        int numbers2 [] = {1,2,3,4,5,0,0,0,5,5,4,4,3,3,2};
        DigitSecret ds2(numbers2,15);
        int numbers3 [] = {1,0,9,4,3,8,4,0,9,3,1,4,3,2,1,4,4,3,7,2};
        DigitSecret ds3(numbers3,20);
        CharSecret cs1("fhdaieowujkfjdsafjdsakjhueiqoyroq");
        CharSecret cs2("nvzcfsadrqipqhfjdfncxoqw");
        CharSecret cs3("uyoihfdsanmqeqrzvdhfeqyrq");
        Secret** s = new Secret*[6];
        s[0] = &ds1;
        s[1] = &ds2;
        s[2] = &ds3;
        s[3] = &cs1;
        s[4] = &cs2;
        s[5] = &cs3;
        printAll(s,6);
        delete [] s;
    }
    return 0;
}
