// classes example
#include <iostream>
using namespace std;

class CRectangle {
  int x, y;
  public:
        void set_values (int,int);                 // Declearation of a function inside the class
        int area () {return (x*y);}
  };

void CRectangle::set_values (int a, int b) {      // Defining the void function of the class. If we ommit CRectangle:: then it becomes a simple function without refering to the class.
  x = a;
  y = b;
}

int main () {

CRectangle rect;
rect.set_values (3,4);                              // x=3 and y=4 by set values function
cout << "area: " << rect.area()<<endl;

return 0;
}
