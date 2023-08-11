// overloading class constructors
#include <iostream>
using namespace std;

class CRectangle {
int width, height;
public:
    CRectangle ();                               // 1) Constructor without input
    CRectangle (int,int);                        // 2) Constructor with 2 inputs
int area (void) {return (width*height);}
};

CRectangle::CRectangle () {                      // Defining constructor 1)
width = 5;
height = 5;
}
CRectangle::CRectangle (int a, int b) {          //Defining constructor 2)
width = a;
height = b;
}
int main () {
CRectangle rect (3,4);                           // object which corresponds to constructor 2)    ***** Compilre recognises by the input the usage of the constructor.
CRectangle rectb;                                // object which corresponds to constructor 1)
cout << "rect area: " << rect.area() << endl;
cout << "rectb area: " << rectb.area() << endl;
return 0;
}
