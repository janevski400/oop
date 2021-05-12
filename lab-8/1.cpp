#include <iostream>

using namespace std;

class Shape {
public:
    virtual void draw() {
        cout << "Drawing a shape.\n";
    }
};
class Rectangle : public Shape {
    void draw () {
        cout<<"Drawing a rectangle.\n";
    }
};
int main() {
    Shape* shape;
    Shape shape1;
    shape = &shape1;
    shape->draw();
    Rectangle rect;
    shape = &rect;
    shape->draw();
    return 0;
}
