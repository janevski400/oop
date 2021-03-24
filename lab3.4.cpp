//Stefan Janevski - 201117
#include <iostream>
#include <cstring>
using namespace std;

class Masa {
    private:
        int length;
        int width;
    public:
        Masa() {

        }
        Masa(int length, int width) {
            this->length = length;
            this->width = width;
        }

        void pecati () {
            cout<<"Masa: "<<length<<" "<<width<<endl;
        }
};

class Soba {
    private:
        Masa M;
        int length;
        int width;
    public:

        Soba () {

        }

        Soba (int width, int length, const Masa &M) {
            this->M = M;
            this->width = width;
            this->length = length;
        }

        void pecati() {
            cout<<"Soba: "<<width<<" "<<length<<" ";
            M.pecati();
        }

};

class Kukja {
    private:
        Soba room;
        char address[50];
    public:

        Kukja () {

        }

        Kukja (Soba &room, char *address) {
            this->room = room;
            strcpy(this->address,address);
        }

        void pecati() {
            cout<<"Adresa: "<<address<<" ";
            room.pecati();
        }
};

int main(){
    int n;
    cin>>n;
    for(int i=0;i<n;i++){
    	int masaSirina,masaDolzina;
        cin>>masaSirina;
        cin>>masaDolzina;
    	Masa m(masaSirina,masaDolzina);
    	int sobaSirina,sobaDolzina;
        cin>>sobaSirina;
        cin>>sobaDolzina;
    	Soba s(sobaSirina,sobaDolzina,m);
    	char adresa[30];
        cin>>adresa;
    	Kukja k(s,adresa);
    	k.pecati();
	}

    return 0;
}
