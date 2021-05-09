#include <iostream>
#include <cstring>
using namespace std;

class Employee {
protected:
    char name[30];
    int age;
    int experience;
public:
    explicit Employee (char *_name = nullptr, int _age = 0, int _experience = 0 ):age(_age),experience(_experience) {
        strcpy(name, _name);
    }
    virtual double plata () =0;
    virtual double bonus () = 0;
    bool operator == (Employee &other) {
        if(other.age == this->age)
            if(other.bonus() == this->bonus())
                return 1;
        return 0;
    }
};

class SalaryEmployee : public Employee {
private:
    int basePay;
public:
    explicit SalaryEmployee(char *_name = nullptr, int _age =0, int _experience = 0, int _basePay = 0):Employee(_name,_age,_experience){
        basePay = _basePay;
    }
    SalaryEmployee (SalaryEmployee &other);
    double bonus () {
        return (basePay*experience)/100;
    }
    double plata () {
        return basePay + bonus();
    }
    ~SalaryEmployee() = default;
};

class HourlyEmployee : public Employee {
private:
    int hours;
    int hourlyPay;
public:
    explicit HourlyEmployee(char *name = "/", int age =0, int experience = 0, int _hours = 0, int _hourlyPay = 0): Employee(name,age,experience){
        hours = _hours;
        hourlyPay = _hourlyPay;
    }
    HourlyEmployee (HourlyEmployee &other);
    double bonus () {
        if (hours>320) {
            return (hours - 320)*hourlyPay*0.5;
        }
        return 0;
    }
    double plata () {
        return hours * hourlyPay + bonus();
    }
    ~HourlyEmployee() = default;
};

class Freelancer : public Employee {
private:
    int numProjects;
    double *payPerProject;
public:
    explicit Freelancer(char *name = "/", int age = 0, int experience = 0, int _numProjects = 0, double *projects = nullptr ): Employee (name,age,experience) {
        numProjects = _numProjects;
        payPerProject = new double [numProjects];
        for (int i = 0 ; i < numProjects ; i++)
            payPerProject[i] = projects[i];
    }
    Freelancer(Freelancer &other);
    double bonus () {
        if (numProjects > 5)
            return (numProjects-5)*1000;
        return 0;
    }
    double plata () {
        double tempSum = 0 ;
        for (int i = 0 ; i < numProjects ; i++) {
            tempSum += payPerProject[i];
        }
        return tempSum + bonus();
    }
    ~Freelancer() {
        delete [] payPerProject;
    }
};

class Company {
private:
    char companyName[30];
    int numberEmp;
    Employee **emp;
    static int SalaryEmp;
    static int HourlyEmp;
    static int Freelancers;
    void copyStuff (Employee *z) {
        Employee **temp = new Employee *[numberEmp +1]; // alociranje na numberEmp+1 (za prv element kje bide 0+1 mesto)
        for (int i = 0; i < numberEmp; i++) {
            //emp[i]->print();
            temp[i] = emp[i]; // dodeluvanje na vrednosti od emp vo temp
        }
        temp[numberEmp] = z; //noviot vraboten se zachuvuva vo temp[numberEmp] (za prv element kje se zachuva vo temp[0])
        delete[] emp;
        numberEmp++;
        emp = new Employee *[numberEmp];
        for (int i = 0; i < numberEmp; i++) emp[i] = temp[i];
        delete[] temp;
    }
public:
    explicit Company (char *name = nullptr) {
        emp = new Employee *[0];
        strcpy(companyName,name);
        numberEmp = 0;
    }
    ~Company() {
        delete[] emp;
    }
    Company &operator += (Employee *other) {
        if (dynamic_cast<SalaryEmployee*>(other)) {
            SalaryEmployee *z;
            z = (dynamic_cast<SalaryEmployee *>(other));
            copyStuff(z);
            SalaryEmp++;
        }
        if (dynamic_cast<HourlyEmployee*>(other)) {
            HourlyEmployee *z;
            z = (dynamic_cast<HourlyEmployee *>(other));
            copyStuff(z);
            HourlyEmp++;
        }
        if (dynamic_cast<Freelancer*>(other)) {
            Freelancer *z;
            z = (dynamic_cast<Freelancer *>(other));
            copyStuff(z);
            Freelancers++;
        }
        return *this;
    }
    friend ostream &operator << (ostream &out, Company &other){
        out<<other.numberEmp<<endl;
        for (int i = 0; i < other.numberEmp; i++) { out << other.emp[i] <<" KRAJ" << endl; }
        return out;
    }
    int vkupnaPlata() {
        int tempSum = 0;
        for(int i = 0; i<numberEmp ; i++) {
            tempSum += emp[i]->plata();
        }
        return tempSum;
    }
    int filtriranaPlata(Employee *_emp){
        int tempSum = 0;
        for(int i = 0; i<numberEmp ; i++) {
            if (emp[i]->operator==(*_emp)) {
                tempSum += emp[i]->plata();
            }
        }
        return tempSum;
    }
    void pecatiRabotnici () {
        cout<<"Vo kompanijata "<<companyName<<" rabotat:"<<endl;
        cout<<"Salary employees: "<<SalaryEmp<<endl;
        cout<<"Hourly employees: "<<HourlyEmp<<endl;
        cout<<"Freelancers: "<<Freelancers<<endl;
    }
};
int Company::Freelancers=0;
int Company::SalaryEmp=0;
int Company::HourlyEmp=0;
int main() {

    char name[50];
    cin >> name;
    Company c(name);

    int n;
    cin >> n;

    char employeeName[50];
    int age;
    int experience;
    int type;

    for (int i=0; i <n; ++i) {
        cin >> type;
        cin >> employeeName >> age >> experience;

        if (type == 1) {
            int basicSalary;
            cin >> basicSalary;
            c += new SalaryEmployee(employeeName, age, experience, basicSalary);
        }

        else if (type == 2) {
            int hoursWorked;
            int hourlyPay;
            cin >> hoursWorked >> hourlyPay;
            c += new HourlyEmployee(employeeName, age, experience, hoursWorked, hourlyPay);
        }

        else {
            int numProjects;
            cin >> numProjects;
            double projects[10];
            for (int i=0; i < numProjects; ++i) {
                cin >> projects[i];
            }
            c += new Freelancer(employeeName, age, experience, numProjects, projects);
        }
    }

    c.pecatiRabotnici();
    cout << "Vkupnata plata e: " << c.vkupnaPlata() << endl;
    Employee * emp = new HourlyEmployee("Petre_Petrov",31,6,340,80);
    cout << "Filtriranata plata e: " << c.filtriranaPlata(emp);

    delete emp;
}
