/*
NBAPlayer
Да се дефинира класа NBAPlayer за која ќе се чуваат:

динамички алоцирана низа од карактери за името на играчот
низа од максимум 40 карактери за тимот во кој играчот моментално настапува
просечен број на поени на играчот оваа сезона (double)
просечен број на асистенции на играчот оваа сезона (double)
просечен број на скокови на играчот оваа сезона (double)
За потребите на класата да се дефинираат:

default конструктор и конструктор со аргументи
copy constructor и оператор =
деструктор
метод rating() кој го враќа рејтингот на кошаркарот кој се пресметува како:

45% од поените + 30% од асистенциите + 25% од скоковите

метод print() кој го печати играчот во следниот формат:

Име - тим

Points: поени

Assists: асистенции

Rebounds: скокови

Rating: рејтинг

AllStarPlayer
Од претходната класа NBAPlayer да се изведе класата AllStarPlayer за која дополнително ќе се чуваат и:

просечен број на поени на играчот од All Star натпреварите (double)
просечен број на асистенции на играчот од All Star натпреварите (double)
просечен број на скокови на играчот од All Star натпреварите (double)
За потребите на класата да се дефинираат:

default конструктор
конструктор кој прима објект од NBAPlayer и плус додатните информации (погледни main)
конструктор кој ги прима сите аргументи (погледни main)
copy constructor, оператор =, деструктор
метод allStarRating() кој го враќа рејтингот на кошаркарот од All Star натпреварите и кој се пресметува како:

30% од поените + 40% од асистенциите + 30% од скоковите

Да се препокријат методите:

rating() кој го враќа просекот од обичниот рејтинг на кошаркарот и неговиот All Star рејтинг
print() кој покрај основните информации за кошаркарот печати и:

All Star Rating: рејтингот од All Star натпреварите

New Rating: просечниот рејтинг
*/

#include <iostream>
#include <cstring>
using namespace std;

class NBAPlayer {
    private:
        char *name;
        char team[41];
        double avgPoints;
        double assistsThisSeason;
        double avgShots;
    public:
        NBAPlayer (char *name = "no_name", char *team = "no_team", double avgPoints = 0.0, double assistsThisSeason = 0.0, double avgShots = 0.0) {
            this->name = new char [strlen(name)+1];
            strcpy(this->name,name);
            strcpy(this->team,team);
            this->avgPoints = avgPoints;
            this->assistsThisSeason = assistsThisSeason;
            this->avgShots = avgShots;
        }
        void copyStuff (const NBAPlayer &other) {
            delete [] this->name;
            this->name = new char [strlen(other.name)+1];
            strcpy(this->name, other.name);
            strcpy(this->team, other.team);
            this->avgPoints = other.avgPoints;
            this->assistsThisSeason = other.assistsThisSeason;
            this->avgShots = other.avgShots;
        }
        NBAPlayer (const NBAPlayer &other) {
            copyStuff(other);
        }
        ~NBAPlayer () {
            delete [] name;
        }
        double rating () {
            return (avgPoints*0.45 + assistsThisSeason*0.30 + avgShots*0.25);
        }
        void print () {
            cout<<name<<" - "<<team<<endl;
            cout<<"Points: "<<avgPoints<<endl;
            cout<<"Assists: "<<assistsThisSeason<<endl;
            cout<<"Rebounds: "<<avgShots<<endl;
            cout<<"Rating: "<<rating()<<endl;;
        }
        NBAPlayer &operator = (const NBAPlayer &player ) {
            if (this!=&player)
                copyStuff(player);
            return *this;
        }
};

class AllStarPlayer : public NBAPlayer {
    private:
        double avgPointsAllStar;
        double avgAssistsAllStar;
        double avgShotsAllStar;
    public:
        AllStarPlayer (double avgPointsAllStar = 0.0, double avgAssistsAllStar = 0.0, double avgShotsAllStar = 0.0): NBAPlayer() {
            AllStarPlayer::copyStuff(avgPointsAllStar,avgAssistsAllStar,avgShotsAllStar);
        }
        AllStarPlayer (const NBAPlayer &player, double avgPointsAllStar, double avgAssistsAllStar, double avgShotsAllStar): NBAPlayer(player){
            AllStarPlayer::copyStuff(avgPointsAllStar,avgAssistsAllStar,avgShotsAllStar);
        }
        void copyStuff (double avgPointsAllStar, double avgAssistsAllStar, double avgShotsAllStar) {
            this->avgAssistsAllStar = avgAssistsAllStar;
            this->avgPointsAllStar = avgPointsAllStar;
            this->avgShotsAllStar = avgShotsAllStar;
        }
        AllStarPlayer (char *name, char *team, double avgPoints, double assistsThisSeason, double avgShots, double avgPointsAllStar, double avgAssistsAllStar, double avgShotsAllStar): NBAPlayer(name,team,avgPoints, assistsThisSeason, avgShots) {
                copyStuff(avgPointsAllStar,avgAssistsAllStar,avgShotsAllStar);
        }
        AllStarPlayer &operator = (const AllStarPlayer &other){
            if (this!=&other) {
                NBAPlayer::copyStuff(other);
                this->avgAssistsAllStar = other.avgAssistsAllStar;
                this->avgPointsAllStar = other.avgPointsAllStar;
                this->avgShotsAllStar = other.avgShotsAllStar;
            }
            return *this;
        }
        ~AllStarPlayer () {
        }
        double allStarRating () {
            return (avgPointsAllStar*0.3+avgAssistsAllStar*0.4+avgShotsAllStar*0.3);
        }
        double rating() {
            return ((allStarRating()+NBAPlayer::rating())/2.0);
        }
        void print() {
            NBAPlayer::print();
            cout<<"All Star Rating: "<<allStarRating()<<endl;
            cout<<"New Rating: "<<rating()<<endl;
        }
};

int main() {

  char name[50];
  char team[40];
  double points;
  double assists;
  double rebounds;
  double allStarPoints;
  double allStarAssists;
  double allStarRebounds;

  NBAPlayer * players = new NBAPlayer[5];
  AllStarPlayer * asPlayers = new AllStarPlayer[5];
  int n;
  cin >> n;

  if (n == 1) {

    cout << "NBA PLAYERS:" << endl;
    cout << "=====================================" << endl;
    for (int i = 0; i < 5; ++i) {
      cin >> name >> team >> points >> assists >> rebounds;
      players[i] = NBAPlayer(name,team,points,assists,rebounds);
      players[i].print();
    }
  }
  else if (n == 2) {

    for (int i=0; i < 5; ++i){
      cin >> name >> team >> points >> assists >> rebounds;
      cin >> allStarPoints >> allStarAssists >> allStarRebounds;
      players[i] = NBAPlayer(name,team,points,assists,rebounds);
      asPlayers[i] = AllStarPlayer(players[i],allStarPoints,allStarAssists,allStarRebounds);
    }

    cout << "NBA PLAYERS:" << endl;
    cout << "=====================================" << endl;
    for (int i=0; i < 5; ++i)
      players[i].print();

    cout << "ALL STAR PLAYERS:" << endl;
    cout << "=====================================" << endl;
    for (int i=0; i < 5; ++i)
      asPlayers[i].print();

    }
    else if (n == 3) {

      for (int i=0; i < 5; ++i){
        cin >> name >> team >> points >> assists >> rebounds;
        cin >> allStarPoints >> allStarAssists >> allStarRebounds;
        asPlayers[i] = AllStarPlayer(name, team, points, assists, rebounds,allStarPoints,allStarAssists,allStarRebounds);
      }
      cout << "ALL STAR PLAYERS:" << endl;
      cout << "=====================================" << endl;
      for (int i=0; i < 5; ++i)
        asPlayers[i].print();

    }

    delete [] players;
    delete [] asPlayers;
}
