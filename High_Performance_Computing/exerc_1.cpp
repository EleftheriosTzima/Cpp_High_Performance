#include <iostream>
#include <math.h>
using namespace std;

int main()
{
const double pi=3.1415926;
double volume;
double area;
double r=-1;

/* C++ comments can also
   * span multiple lines
   * like this
*/
while (r<=0)                         // promt the user to insert a positive radius
{
cout<<"Enter radius r: ";   
cin>>r;
}

volume=4./3.*pi*pow(r,3.);
area=pi*pow(r,2.);


cout<<"Volume is "<<volume<<endl;
cout<<"Area is "<<area<<endl;


}