// example: class constructor
#include <iostream>
using namespace std;

class CRectangle {
  int width, height;
  public:
  CRectangle (int,int);                         // Constructor definition. It playse the role of assigning values to the private members width and height. Like void.
  int area () {return (width*height);}
};

CRectangle::CRectangle (int a, int b) {        // Defining the constroctur.
width = a;
height = b;
}

int main () {
CRectangle rect(7,3);                        // Objects are created mandately by using arguments e.g (7,3). This helps the initilasation of private members.
CRectangle rectb(6,5);
cout << "rect area: " << rect.area() << endl;
cout << "rectb area: " << rectb.area() << endl;
return 0;
}
