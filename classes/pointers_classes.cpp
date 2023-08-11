// pointer to classes example
#include <iostream>
using namespace std;

class CRectangle {
int width, height;
public:
    void set_values (int, int);                       // define the void that will pass tje values to the private sector
    int area (void) {return (width * height);}
};


void CRectangle::set_values (int a, int b) {          // void
width = a;
height = b;
}


int main () {
CRectangle a, *b, *c;                              // declare objects a as variable and b,c as pointers.
CRectangle * d = new CRectangle[2];                // d vector object with 2 entries !!!.
b= new CRectangle;
c= &a;                                             // c address points to a address

a.set_values (1,2);
b->set_values (3,4);                              // for pointes we use -> to dereference. In this case denotes at the first element
d->set_values (5,6);
d[1].set_values (7,8);                            // d[1] is a pointer but treated as variable, so we use the dot (.). (Property of vectors)
cout << "a area: " << a.area() << endl;
cout << "*b area: " << b->area() << endl;
cout << "*c area: " << c->area() << endl;
cout << "d[0] area: " << d[0].area() << endl;
cout << "d[1] area: " << d[1].area() << endl;

delete[] d;                                        // Destroy the objects. If we had used pointers in the private sector of the class, a destructor must be used if we use a constructor.
delete b;
return 0;
}
