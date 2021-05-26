#include <cstring>
#include <iostream>
using namespace std;

enum Size
{
    Small,
    Large,
    Family
};

class Pizza
{
protected:
    char name[21];
    char ingredients[49];
    float basePrice;
public:
    Pizza(char *name = nullptr, char *ingredients = nullptr, float basePrice = 0)
    {
        strcpy(this->name,name);
        strcpy(this->ingredients,ingredients);
        this->basePrice = basePrice;
    }
    virtual float price () = 0;
    char *getName () {
        return name;
    }
    char *getIngredients () {
        return ingredients;
    }
};


class FlatPizza : public Pizza
{
private:
    Size size;
public:
    FlatPizza (char *_name = nullptr, char *_ingredients = nullptr, int _price = 0, Size _size = (Size)0): Pizza(_name,_ingredients,_price)
    {
        size = _size;
    }
    float price ()
    {
        if(size == 0)
            return basePrice+(basePrice/100.0*10);
        else if (size==1)
            return basePrice+(basePrice/100.0*30);
        else if (size == 2)
            return basePrice+(basePrice/100.0*30);
    }
    int getSize () {
        return (int)size;
    }
};

class FoldedPizza : public Pizza {
private:
    bool wf;
public:
    FoldedPizza (char *_name=nullptr, char *_ingredients = nullptr, float _price=0): Pizza(_name,_ingredients,_price) {
        wf=true;
    }
    float price (){
        if(wf)
            return basePrice+basePrice*0.10;
        else
            return basePrice+basePrice*0.30;
    }
    void setWhiteFlour (bool value) {
        wf = value;
    }
    bool getWhiteFlour () {
        return wf;
    }
};

ostream &operator << (ostream &out, Pizza &a)
{
    if(dynamic_cast<FlatPizza*>(&a)) {
        FlatPizza temp = dynamic_cast<FlatPizza&>(a);
        out<<temp.getName()<<": "<<temp.getIngredients();
        if(temp.getSize()==0)
            out<<", small - ";
        else if (temp.getSize()==1)
            out<<", large - ";
        else
            out<<", family - ";
        out<<temp.price()<<endl;
    }
    else {
        FoldedPizza temp = dynamic_cast<FoldedPizza&>(a);
        out<<temp.getName()<<": "<<temp.getIngredients();
        if(temp.getWhiteFlour())
            out<<", wf - ";
        else
            out<<", nwf - ";
        out<<temp.price()<<endl;
    }
}

bool operator < (Pizza &a, Pizza &b) {
    if(a.price()>b.price())
        return false;
    return true;
}

void expensivePizza (Pizza **pizzas, int n) {
    int index;
    float price = 0;
    for(int i=0;i<n;i++) {
        if(pizzas[i]->price()>price){
            price = pizzas[i]->price();
            index = i;
        }
    }
    cout<<*pizzas[index]<<endl;
}

int main() {
  int test_case;
  char name[20];
  char ingredients[100];
  float inPrice;
  Size size;
  bool whiteFlour;

  cin >> test_case;
  if (test_case == 1) {
    // Test Case FlatPizza - Constructor, operator <<, price
    cin.get();
    cin.getline(name,20);
    cin.getline(ingredients,100);
    cin >> inPrice;
    FlatPizza fp(name, ingredients, inPrice);
    cout << fp;
  } else if (test_case == 2) {
    // Test Case FlatPizza - Constructor, operator <<, price
    cin.get();
    cin.getline(name,20);
    cin.getline(ingredients,100);
    cin >> inPrice;
    int s;
    cin>>s;
    FlatPizza fp(name, ingredients, inPrice, (Size)s);
    cout << fp;

  } else if (test_case == 3) {
    // Test Case FoldedPizza - Constructor, operator <<, price
    cin.get();
    cin.getline(name,20);
    cin.getline(ingredients,100);
    cin >> inPrice;
    FoldedPizza fp(name, ingredients, inPrice);
    cout << fp;
  } else if (test_case == 4) {
    // Test Case FoldedPizza - Constructor, operator <<, price
    cin.get();
    cin.getline(name,20);
    cin.getline(ingredients,100);
    cin >> inPrice;
    FoldedPizza fp(name, ingredients, inPrice);
    fp.setWhiteFlour(false);
    cout << fp;

  } else if (test_case == 5) {
	// Test Cast - operator <, price
    int s;

    cin.get();
    cin.getline(name,20);
    cin.getline(ingredients,100);
    cin >> inPrice;
    cin>>s;
    FlatPizza *fp1 = new FlatPizza(name, ingredients, inPrice, (Size)s);
    cout << *fp1;

    cin.get();
    cin.getline(name,20);
    cin.getline(ingredients,100);
    cin >> inPrice;
    cin>>s;
    FlatPizza *fp2 = new FlatPizza(name, ingredients, inPrice, (Size)s);
    cout << *fp2;

    cin.get();
    cin.getline(name,20);
    cin.getline(ingredients,100);
    cin >> inPrice;
    FoldedPizza *fp3 = new FoldedPizza(name, ingredients, inPrice);
    cout << *fp3;

    cin.get();
    cin.getline(name,20);
    cin.getline(ingredients,100);
    cin >> inPrice;
    FoldedPizza *fp4 = new FoldedPizza(name, ingredients, inPrice);
    fp4->setWhiteFlour(false);
    cout << *fp4;

    cout<<"Lower price: "<<endl;
    if(*fp1<*fp2)
        cout<<fp1->price()<<endl;
    else cout<<fp2->price()<<endl;

    if(*fp1<*fp3)
        cout<<fp1->price()<<endl;
    else cout<<fp3->price()<<endl;

    if(*fp4<*fp2)
        cout<<fp4->price()<<endl;
    else cout<<fp2->price()<<endl;

    if(*fp3<*fp4)
        cout<<fp3->price()<<endl;
    else cout<<fp4->price()<<endl;

  } else if (test_case == 6) {
	// Test Cast - expensivePizza
    int num_p;
    int pizza_type;

    cin >> num_p;
    Pizza **pi = new Pizza *[num_p];
    for (int j = 0; j < num_p; ++j) {

      cin >> pizza_type;
      if (pizza_type == 1) {
        cin.get();
        cin.getline(name,20);

        cin.getline(ingredients,100);
        cin >> inPrice;
        int s;
        cin>>s;
        FlatPizza *fp = new FlatPizza(name, ingredients, inPrice, (Size)s);
        cout << (*fp);
        pi[j] = fp;
      }
      if (pizza_type == 2) {

        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        FoldedPizza *fp =
            new FoldedPizza (name, ingredients, inPrice);
        if(j%2)
          (*fp).setWhiteFlour(false);
        cout << (*fp);
        pi[j] = fp;

      }
    }

    cout << endl;
    cout << "The most expensive pizza:\n";
    expensivePizza(pi,num_p);


  }
  return 0;
}
