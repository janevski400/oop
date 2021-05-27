#include <iostream>
#include <cstring>
using namespace std;

struct date
{
    int month;
    int year;
};

class Game
{
protected:
    char name[101];
    float price;
    bool boughtOnSale;
public:
    Game ()
    {
        strcpy(name,"/");
        price = 0;
        boughtOnSale = false;
    }
    Game(char *name, float price, bool boughtOnSale)
    {
        strcpy(this->name,name);
        this->price=price;
        this->boughtOnSale = boughtOnSale;
    }
    Game (Game &other) {
        this->boughtOnSale = other.boughtOnSale;
        this->price = other.price;
        strcpy(this->name,other.name);
    }
    bool operator == (Game &other)
    {
        if(!strcmp(other.name,this->name))
            return true;
        return false;
    }
    friend istream &operator >> (istream &in, Game &game)
    {
        in.get();
        in.getline(game.name,100);
        in>>game.price>>game.boughtOnSale;
        return in;
    }
    virtual float getPrice ()
    {
        if(boughtOnSale)
            return price*0.30;
        else
            return price;
    }
    virtual float getRegularPrice() {
        return price;
    }
    char *getName()
    {
        return name;
    }
    bool getSale ()
    {
        return boughtOnSale;
    }
};

ostream &operator << (ostream &out, Game &game)
{
    if(game.getSale())
        return out<<"Game: "<<game.getName()<<", regular price: $"<<game.getRegularPrice()<<", bought on sale";
    return out<<"Game: "<<game.getName()<<", regular price: $"<<game.getRegularPrice();
}

class SubscriptionGame : public Game
{
private:
    float monthlyPayment;
    date dateBought;
public:
    SubscriptionGame ():Game()
    {
        monthlyPayment = 0;
        dateBought.month = 0;
        dateBought.year = 0;
    }
    SubscriptionGame (char *_name, float _price, bool _boughtOnSale, float monthlyPayment, int month, int year ):Game(_name,_price,_boughtOnSale)
    {
        this->monthlyPayment = monthlyPayment;
        dateBought.month = month;
        dateBought.year = year;
    }
    SubscriptionGame (SubscriptionGame &other):Game(other) {
        this->monthlyPayment = other.monthlyPayment;
        this->dateBought = other.dateBought;
    }
    friend istream &operator >> (istream &in, SubscriptionGame &game)
    {
        in.get();
        in.getline(game.name,100);
        in>>game.price>>game.boughtOnSale>>game.monthlyPayment>>game.dateBought.month>>game.dateBought.year;
        return in;
    }
    int getMonth ()
    {
        return dateBought.month;
    }
    int getYear ()
    {
        return dateBought.year;
    }
    float getMonthly()
    {
        return monthlyPayment;
    };
    float getRegularPrice() {
        return price;
    }
    float getPrice()
    {
        float _price = price;
        int months = 0;
        if(getYear()<2018) {
            months = (12-getMonth())+(2017-getYear())*12+5;
        }
        else
            months = 5 - getMonth();
        _price += months * getMonthly();
        return _price;
    }

};

ostream &operator << (ostream &out, SubscriptionGame &game)
{
    if(game.getSale())
        return out<<"Game: "<<game.getName()<<", regular price: $"<<game.getRegularPrice()<<", bought on sale, monthly fee: $"<<game.getMonthly()<<", purchased: "<<game.getMonth()<<"-"<<game.getYear()<<endl;
    return out<<"Game: "<<game.getName()<<", regular price: $"<<game.getRegularPrice()<<", monthly fee: $"<<game.getMonthly()<<", purchased: "<<game.getMonth()<<"-"<<game.getYear()<<endl;
}

class ExistingGame
{
private:
    char m[30];
public:
    ExistingGame (char* _m)
    {
        strcpy(m,_m);
    }
    void message ()
    {
        cout<<m;
        cout<<endl;
    }
};

class User
{
private:
    char name[101];
    Game **games;
    int numberOfGames;
public:
    User ()
    {
        games = new Game*[0];
        strcpy(name,"/");
        numberOfGames = 0;
    }
    User (char *name)
    {
        strcpy(this->name,name);
        games = new Game*[0];
        numberOfGames = 0;
    }
    User (User &other)
    {
        strcpy(this->name,other.name);
        this->numberOfGames = other.numberOfGames;
        copy_games(other.games,numberOfGames);
    }

    void copy_games(Game **gamesForCopy,int n)
    {
        this->games = new Game *[n];
        for(int i=0; i<n; i++)
            this->games[i] = gamesForCopy[i];
            //cout<<"Kraj na Copy Games"<<endl;
    }

    User &operator += (Game &newGame)
    {
        for (int i=0; i < numberOfGames; ++i)
            if (*games[i] == newGame)
                throw ExistingGame("The game is already in the collection");


        Game **tempPtr = new Game*[numberOfGames+1];
        for(int i=0; i<numberOfGames; i++)
            tempPtr[i] = games[i];

        SubscriptionGame *ptr = dynamic_cast<SubscriptionGame*>(&newGame);
        if(ptr)
            tempPtr[numberOfGames] = new SubscriptionGame(*ptr);
        else
            tempPtr[numberOfGames] = new Game(newGame);


        delete [] games;

        numberOfGames++;
        copy_games(tempPtr,numberOfGames);

        delete [] tempPtr;


    }
    friend ostream & operator<<(ostream & o, User& u) {
          o<<"\nUser: "<<u.name<<"\n";

          for (int i=0; i < u.numberOfGames; ++i){
              SubscriptionGame * sg;
              sg = dynamic_cast<SubscriptionGame *> (u.games[i]);

              if (sg){
                cout<<"- "<<(*sg)<<endl;;
              }
              else {
                cout<<"- "<<*(u.games[i])<<endl;;
              }
          }
          return o;
    }

    float total_spent () {
        float tempSum = 0;
        for(int i=0;i<numberOfGames;i++)
            tempSum += games[i]->getPrice();
        return tempSum;
    }

    ~ User ()
    {
        for(int i=0; i<numberOfGames; i++)
            delete games[i];
        delete [] games;
    }


};
    int main()
    {
        int test_case_num;

        cin>>test_case_num;

        // for Game
        char game_name[100];
        float game_price;
        bool game_on_sale;

        // for SubscritionGame
        float sub_game_monthly_fee;
        int sub_game_month, sub_game_year;

        // for User
        char username[100];
        int num_user_games;

        if (test_case_num == 1)
        {
            cout<<"Testing class Game and operator<< for Game"<<std::endl;
            cin.get();
            cin.getline(game_name,100);
            //cin.get();
            cin>>game_price>>game_on_sale;

            Game g(game_name, game_price, game_on_sale);

            cout<<g;
        }
        else if (test_case_num == 2)
        {
            cout<<"Testing class SubscriptionGame and operator<< for SubscritionGame"<<std::endl;
            cin.get();
            cin.getline(game_name, 100);

            cin>>game_price>>game_on_sale;

            cin>>sub_game_monthly_fee;
            cin>>sub_game_month>>sub_game_year;

            SubscriptionGame sg(game_name, game_price, game_on_sale, sub_game_monthly_fee, sub_game_month, sub_game_year);
            cout<<sg;
        }
        else if (test_case_num == 3)
        {
            cout<<"Testing operator>> for Game"<<std::endl;
            Game g;

            cin>>g;

            cout<<g;
        }
        else if (test_case_num == 4)
        {
            cout<<"Testing operator>> for SubscriptionGame"<<std::endl;
            SubscriptionGame sg;
            cin>>sg;
            cout<<sg;
        }
        else if (test_case_num == 5)
        {
            cout<<"Testing class User and operator+= for User"<<std::endl;
            cin.get();
            cin.getline(username,100);
            User u(username);
            //cout<<"Here"<<endl;
            int num_user_games;
            int game_type;
            cin >>num_user_games;

            try
            {

                for (int i=0; i<num_user_games; ++i)
                {

                    cin >> game_type;

                    Game *g;
                    // 1 - Game, 2 - SubscriptionGame
                    if (game_type == 1)
                    {
                        cin.get();
                        cin.getline(game_name, 100);

                        cin>>game_price>>game_on_sale;
                        g = new Game(game_name, game_price, game_on_sale);
                    }
                    else if (game_type == 2)
                    {
                        cin.get();
                        cin.getline(game_name, 100);

                        cin>>game_price>>game_on_sale;

                        cin>>sub_game_monthly_fee;
                        cin>>sub_game_month>>sub_game_year;
                        g = new SubscriptionGame(game_name, game_price, game_on_sale, sub_game_monthly_fee, sub_game_month, sub_game_year);
                    }

                    //cout<<(*g);
                    u+=(*g);
                }
            }
            catch(ExistingGame &ex)
            {
                ex.message();
            }

            cout<<u;

//    cout<<"\nUser: "<<u.get_username()<<"\n";

//    for (int i=0; i < u.get_games_number(); ++i){
//        Game * g;
//        SubscriptionGame * sg;
//        g = &(u.get_game(i));

//        sg = dynamic_cast<SubscriptionGame *> (g);

//        if (sg){
//          cout<<"- "<<(*sg);
//        }
//        else {
//          cout<<"- "<<(*g);
//        }
//        cout<<"\n";
//    }

        }
        else if (test_case_num == 6)
        {
            cout<<"Testing exception ExistingGame for User"<<std::endl;
            cin.get();
            cin.getline(username,100);
            User u(username);

            int num_user_games;
            int game_type;
            cin >>num_user_games;

            for (int i=0; i<num_user_games; ++i)
            {

                cin >> game_type;

                Game *g;
                // 1 - Game, 2 - SubscriptionGame
                if (game_type == 1)
                {
                    cin.get();
                    cin.getline(game_name, 100);

                    cin>>game_price>>game_on_sale;
                    g = new Game(game_name, game_price, game_on_sale);
                }
                else if (game_type == 2)
                {
                    cin.get();
                    cin.getline(game_name, 100);

                    cin>>game_price>>game_on_sale;

                    cin>>sub_game_monthly_fee;
                    cin>>sub_game_month>>sub_game_year;
                    g = new SubscriptionGame(game_name, game_price, game_on_sale, sub_game_monthly_fee, sub_game_month, sub_game_year);
                }

                //cout<<(*g);

                try
                {
                    u+=(*g);
                }
                catch(ExistingGame &ex)
                {
                    ex.message();
                }
            }
            cout<<u;
//      for (int i=0; i < u.get_games_number(); ++i){
//          Game * g;
//          SubscriptionGame * sg;
//          g = &(u.get_game(i));

//          sg = dynamic_cast<SubscriptionGame *> (g);

//          if (sg){
//            cout<<"- "<<(*sg);
//          }
//          else {
//            cout<<"- "<<(*g);
//          }
//          cout<<"\n";
//      }
        }
        else if (test_case_num == 7)
        {
            cout<<"Testing total_spent method() for User"<<std::endl;
            cin.get();
            cin.getline(username,100);
            User u(username);

            int num_user_games;
            int game_type;
            cin >>num_user_games;

            for (int i=0; i<num_user_games; ++i)
            {

                cin >> game_type;

                Game *g;
                // 1 - Game, 2 - SubscriptionGame
                if (game_type == 1)
                {
                    cin.get();
                    cin.getline(game_name, 100);

                    cin>>game_price>>game_on_sale;
                    g = new Game(game_name, game_price, game_on_sale);
                }
                else if (game_type == 2)
                {
                    cin.get();
                    cin.getline(game_name, 100);

                    cin>>game_price>>game_on_sale;

                    cin>>sub_game_monthly_fee;
                    cin>>sub_game_month>>sub_game_year;
                    g = new SubscriptionGame(game_name, game_price, game_on_sale, sub_game_monthly_fee, sub_game_month, sub_game_year);
                }

                u+=(*g);
            }

            cout<<u;

            cout<<"Total money spent: $"<<u.total_spent()<<endl;
        }
        return 0;
    }
