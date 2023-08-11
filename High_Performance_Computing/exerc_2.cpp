#include <iostream>
#include <math.h>
using namespace std;

int main()
{
const double g=9.81;
double y_in;
double time;
double r;
double vel,height;

cout<<"Enter the time: ";
cin>>time;
cout<<"Enter the initial height: ";
cin>>y_in;

vel=-g*time;
height=y_in-0.5*g*pow(time,2.);

cout<<"height is: "<<height<<endl;
cout<<"velocity is:  "<<vel<<endl;

}