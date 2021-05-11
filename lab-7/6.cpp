#include <iostream>
#include <cstring>
using namespace std;

class Task {
protected:
    char id[6];
public:
    explicit Task (char *_id="") {
        strcpy(id,_id);
    }
    Task (Task &other){
       strcpy(id,other.id);
    }
    virtual int getOrder () = 0;
    virtual void print () = 0;
    char *getId (){
        return id;
    };
};

class TimedTask : public Task {
private:
    int time;
public:
    TimedTask(char *id = "", int _time = 0):Task(id) {
        time = _time;
    }
    TimedTask (TimedTask &other ):Task(other) {
        this->time = other.time;
    }
    int getOrder () {
        return time;
    }
    void print () {
        cout<<"TT->"<<id<<":"<<time<<endl;
    }
    ~TimedTask() {}
};

class PriorityTask : public Task{
private:
    int priority;
public:
    PriorityTask(char *id = "", int _priority = 0):Task(id) {
        priority = _priority;
    }
    int getOrder () {
        return priority;
    }
    void print () {
        cout<<"PT->"<<this->id<<":"<<priority<<endl;
    }
    ~PriorityTask(){}
};

void scheduleTimedTasks (Task **tasks, int n, int t) {
    int counter=0;
    TimedTask *mainTemp = new TimedTask [1];
    for (int i=0;i<n;i++) {
        if(dynamic_cast<TimedTask *>(tasks[i])) {
            if(tasks[i]->getOrder() < t) {
                TimedTask *temp = new TimedTask [counter+1];
                for (int j = 0; j < counter; j++) temp[j] = mainTemp[j];
                temp[counter]=dynamic_cast<TimedTask &>(*tasks[i]);
                counter++;
                delete [] mainTemp;
                mainTemp = new TimedTask [counter];
                for (int j = 0; j < counter; j++) mainTemp[j] = temp[j];
                delete [] temp;
            }
        }
    }
    while(1) {
        bool swapped = false;
        for (int i = 0; i < counter-1; i++) {
            if(mainTemp[i].getOrder() > mainTemp[i+1].getOrder()) {
                TimedTask helper = mainTemp[i];
                mainTemp[i]=mainTemp[i+1];
                mainTemp[i+1]=helper;
                swapped = true;
            }
        }
        if(!swapped)
            break;
    }
    for(int i=0;i<counter;i++)
        mainTemp[i].print();
}

void schedulePriorityTasks(Task ** tasks, int n, int p) {
    int counter=0;
    PriorityTask *mainTemp = new PriorityTask [1];
    for (int i=0;i<n;i++) {
        if(dynamic_cast<PriorityTask *>(tasks[i])) {
            if(tasks[i]->getOrder() < p) {
                PriorityTask *temp = new PriorityTask [counter+1];
                for (int j = 0; j < counter; j++) temp[j] = mainTemp[j];
                temp[counter]=dynamic_cast<PriorityTask &>(*tasks[i]);
                counter++;
                delete [] mainTemp;
                mainTemp = new PriorityTask [counter];
                for (int j = 0; j < counter; j++) mainTemp[j] = temp[j];
                delete [] temp;
            }
        }
    }
    while(1) {
        bool swapped = false;
        for (int i = 0; i < counter-1; i++) {
            if(mainTemp[i].getOrder() > mainTemp[i+1].getOrder()) {
                PriorityTask helper = mainTemp[i];
                mainTemp[i]=mainTemp[i+1];
                mainTemp[i+1]=helper;
                swapped = true;
            }
        }
        if(!swapped)
            break;
    }
    for(int i=0;i<counter;i++)
        mainTemp[i].print();
}

bool operator==(Task *first, Task &second) {
    return(!strcmp(first->getId(),second.getId())&&first->getOrder()==second.getOrder());
}

int main () {
    int testCase;
    int n;
    cin>>testCase;

    if (testCase==0){
        cin>>n;
        Task ** tasks;
        tasks = new Task * [n];
        for (int i=0;i<n;i++){
            char id [5];
            int timeOrPriority;
            int type; //0 za timed, 1 za priority
            cin >> type >>id >> timeOrPriority;
            if (type==0)
                tasks[i] = new TimedTask(id,timeOrPriority);
            else
                tasks[i] = new PriorityTask(id,timeOrPriority);
            //tasks[i]->print();
        }

        cout<<"SCHEDULING PRIORITY TASKS WITH PRIORITY DEGREE LESS THAN 10"<<endl;
        schedulePriorityTasks(tasks,n,10);

    }
    else if (testCase==1) {
        cin>>n;
        Task ** tasks;
        tasks = new Task * [n];
        for (int i=0;i<n;i++){
            char id [5];
            int timeOrPriority;
            int type; //0 za timed, 1 za priority
            cin >> type >>id >> timeOrPriority;
            if (type==0)
                tasks[i] = new TimedTask(id,timeOrPriority);
            else
                tasks[i] = new PriorityTask(id,timeOrPriority);
            //tasks[i]->print();
        }


        cout<<"SCHEDULING TIMED TASKS WITH EXECUTION TIME LESS THAN 50"<<endl;
        scheduleTimedTasks(tasks,n,50);
    }
    else {
        TimedTask * tt1 = new TimedTask("11",10);
        TimedTask * tt2 = new TimedTask("11",11);
        TimedTask * tt3 = new TimedTask("11",11);
        PriorityTask * pp1 = new PriorityTask("aa",10);
        PriorityTask * pp2 = new PriorityTask("11",10);

        cout << (tt1==(*tt2))<<endl;
        cout << (tt2==(*tt3))<<endl;
        cout << (pp1==(*pp2))<<endl;
        cout << (pp2==(*tt1))<<endl;
    }

    return 0;
}
