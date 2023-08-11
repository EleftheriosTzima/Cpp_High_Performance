// example on constructors and destructors
#include <iostream>
using namespace std;

class CRectangle {
int *width, *height;                         // Pointers width and height.
public:
        CRectangle (int,int);                // Constructor allocates the values to the private members
        ~CRectangle ();                      // Destructor  Definition.
int area () {return (*width * *height);}     // Deferncing the pointers and then do the multiplication.
};

CRectangle::CRectangle (int a, int b) {
width = new int;
height = new int;
*width = a;                                // Dereferencing objects and assigning values.
*height = b;
}
                                           // Defining the destructor. It releases the heap memory when the object created is destroyed.
CRectangle::~CRectangle () {
delete width;
delete height;
}

int main () {
CRectangle rect (3,4), rectb (5,6);       // Definging the objects by initialising with the constructors.

cout << "rect area: " << rect.area() << endl;
cout << "rectb area: " << rectb.area() << endl;
return 0;
}
