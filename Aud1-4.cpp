// Stefan Janevski - 201117 - Aud 1/4 - 04.3.2021
#include <iostream>
using namespace std;

struct pres{
    string name;
    string lastName;
    string party;
};

struct city {
    string ime;
    int population;
};


struct country {
    string name;
    pres president;
    city capital;
    int population;
};

void swp(country &a, country &b)
{
    country temp = a;
    a=b;
    b=temp;
}

void bubbleSort(country *cou, int n)
{
    bool swapped=true;
    while(swapped)
    {
        swapped=false;
        for(int i=0;i<n-1;i++)
            if(cou[i].capital.population < cou[i+1].capital.population)
            {
                swp(cou[i],cou[i+1]);
                swapped=true;
            }
    }
}

int main()
{
    country Countries[100];
    int n=0;
    cin>>n;
    for(int i=0;i<n;i++)
    {
        cin>>Countries[i].name;
        cin>>Countries[i].president.name;
        cin>>Countries[i].president.lastName;
        cin>>Countries[i].president.party;
        cin>>Countries[i].capital.ime;
        cin>>Countries[i].capital.population;
        cin>>Countries[i].population;
        cout<<endl;
    }
    bubbleSort(Countries,n);
    cout<<endl;
    cout<<Countries[0].president.name<<" "<<Countries[0].president.lastName;
    return 0;
}
