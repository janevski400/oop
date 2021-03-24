//Stefan Janevski - 201117
#include <iostream>
#include <cstring>

using namespace std;

class Potpisuvac
{
    private:
        char name[20];
        char lastName[20];
        char embg[15];
    public:
        Potpisuvac()
        {
            strcpy(name, "");
            strcpy(lastName, "");
            strcpy(embg,"");
        }
        Potpisuvac (const char *name, const char *lastName, const char *embg)
        {
            strcpy(this->name,name);
            strcpy(this->lastName,lastName);
            strcpy(this->embg,embg);
        }
        Potpisuvac (const Potpisuvac &a)
        {
            strcpy(name,a.name);
            strcpy(lastName, a.lastName);
            strcpy(embg,a.embg);
        }
        ~Potpisuvac() {}
        char * getEmbg ()
        {
            return embg;
        }
};

class Dogovor
{
    private:
        int brDog;
        char kategorija[50];
        Potpisuvac potpisuvac[3];
    public:
        Dogovor (int brDog, char *kategorija, Potpisuvac *p)
        {
            this->brDog = brDog;
            strcpy(this->kategorija,kategorija);
            this->potpisuvac[0]=p[0];
            this->potpisuvac[1]=p[1];
            this->potpisuvac[2]=p[2];
        }
        bool proverka() {
            int i = 0, j = 0;
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    if (i == j)
                        continue;
                    else if (strcmp(potpisuvac[i].getEmbg(), potpisuvac[j].getEmbg()) == 0)
                        return true;
                }
            }
            return false;
        }


};

int main()
{
    char embg[15], ime[20], prezime[20], kategorija[20];
    int broj, n;
    cin >> n;
    for(int i = 0; i < n; i++){
        cin >> embg >> ime >> prezime;
        Potpisuvac p1(ime, prezime, embg);
        cin >> embg >> ime >> prezime;
        Potpisuvac p2(ime, prezime, embg);
        cin >> embg >> ime >> prezime;
        Potpisuvac p3(ime, prezime, embg);
        cin >> broj >> kategorija;
        Potpisuvac p[3];
        p[0] = p1; p[1] = p2; p[2] = p3;
        Dogovor d(broj, kategorija, p);
        cout << "Dogovor " << broj << ":" << endl;
        if(d.proverka()==true)
            cout << "Postojat potpishuvaci so ist EMBG" << endl;
        else
            cout << "Ne postojat potpishuvaci so ist EMBG" << endl;
    }
    return 0;
}
