#include <iostream>
using namespace std;

template <typename T>
bool dali_integer(const T &x) {
    return sizeof(x) == sizeof(int);
}


class Number {
protected:

public:
    virtual double doubleValue() = 0;
    virtual int intValue() = 0;
    virtual void print() = 0;
    bool operator == (Number &other) {
        if (dali_integer(other))
            return other.intValue() == this->intValue();
        else
            return other.doubleValue() == this->doubleValue();
    }
};

class Integer : public Number {
private:
    int intNum;
public:
    Integer(int _intNum = 0) {
        intNum = _intNum;
    }
    ~Integer(){}
    double doubleValue() {
        return intNum;
    }
    int intValue() {
        return intNum;
    }
    void print() {
        cout<<"Integer: "<<intNum<<endl;
    }

};

class Double : public Number {
private:
    double doubleNum;
public:
    Double (double _doubleNum = 0.0) {
        doubleNum = _doubleNum;
    }
    ~Double(){}
    double doubleValue() {
        return doubleNum;
    }
    int intValue() {
        return doubleNum;
    }
    void print() {
        cout << "Double: " << doubleNum << endl;
    }
};

class Numbers {
private:
    Number **arrOfNum;
    int numOfElements;
public:
    Numbers () {
        arrOfNum = new Number * [0];
        numOfElements = 0;
    }
    ~Numbers() {
        delete [] arrOfNum;
    }
    Numbers &operator += (Number *other) {
        for (int i = 0; i < numOfElements; i++) {
            if(arrOfNum[i]->operator==(*other)) {
                return *this;
            }
        }
        Number **temp = new Number * [numOfElements + 1];

        for(int i=0;i<numOfElements;i++)
            temp[i]=arrOfNum[i];
        temp[numOfElements]=other;
        numOfElements++;
        delete [] arrOfNum;
        arrOfNum = new Number * [numOfElements];
        for(int i=0;i<numOfElements;i++)
            arrOfNum[i] = temp[i];
        delete [] temp;
        return *this;
    }
    void statistics() {
        cout<<"Count of numbers: "<<numOfElements<<endl;
        double tempSum = 0, intCount = 0, doubleCount = 0, intSum = 0, doubleSum = 0;
        for(int i=0;i<numOfElements;i++) {
            if(dynamic_cast<Double *>(arrOfNum[i])) {
                tempSum += arrOfNum[i]->doubleValue();
                doubleCount++;
                doubleSum += arrOfNum[i]->doubleValue();
            }
            else {
                tempSum += arrOfNum[i]->intValue();
                intCount++;
                intSum += arrOfNum[i]->intValue();
            }
        }
        cout<<"Sum of all numbers: "<<tempSum<<endl;
        cout<<"Count of integer numbers: "<<intCount<<endl;
        cout<<"Sum of integer numbers: "<<intSum<<endl;
        cout<<"Count of double numbers: "<<doubleCount<<endl;
        cout<<"Sum of double numbers: "<<doubleSum<<endl;
    }
    void integersLessThan (Integer n) {
        bool flag = true;
        for (int i = 0; i < numOfElements; i++) {
            if (dynamic_cast<Integer *>(arrOfNum[i])) {
                if(arrOfNum[i]->intValue() < n.intValue()) {
                    flag = false;
                    arrOfNum[i]->print();
                }
            }
        }
        if (flag)
            cout<<"None"<<endl;
    }
    void doublesBiggerThan (Double n){
        bool flag = true;
        for (int i = 0; i < numOfElements; i++) {
            if (dynamic_cast<Double *>(arrOfNum[i])) {
                if(arrOfNum[i]->intValue() > n.intValue()) {
                    flag = false;
                    arrOfNum[i]->print();
                }
            }
        }
        if(flag)
            cout<<"None"<<endl;
    }
};
int main() {

    int n;
    cin>>n;
    Numbers numbers;
    for (int i=0;i<n;i++){
        int type;
        double number;
        cin>>type>>number;
        if (type==0){//Integer object
            Integer * integer = new Integer((int) number);
            numbers+=integer;
        }
        else {
            Double * doublee = new Double(number);
            numbers+=doublee;
        }
    }

    int lessThan;
    double biggerThan;

    cin>>lessThan;
    cin>>biggerThan;

    cout<<"STATISTICS FOR THE NUMBERS\n";
    numbers.statistics();
    cout<<"INTEGER NUMBERS LESS THAN "<<lessThan<<endl;
    numbers.integersLessThan(Integer(lessThan));
    cout<<"DOUBLE NUMBERS BIGGER THAN "<<biggerThan<<endl;
    numbers.doublesBiggerThan(Double(biggerThan));

    return 0;
}
