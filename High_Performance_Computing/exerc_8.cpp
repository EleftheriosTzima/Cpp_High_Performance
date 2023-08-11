#include <iostream>
#include <math.h>
#include <limits>
#include <fstream>
#include <iomanip>
/* 
   Simpson Numerical Integration of x^2*exp(x^2)
*/
using namespace std;

int main()
{
    double a,b,h,integral,sum1=0,sum2=0;
    unsigned int n;


    cout<<"Define the start and the of the integral: ";
    cin>>a>>b;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout<<"The number of points : ";
    cin>>n;

    h=(b-a)/n;

    for(int i=1;i<=n/2;i++)
    {
        sum1=sum1+pow(a+(2.0*i-1)*h,2)*exp(pow(a+(2.0*i-1)*h,2));
    }
    for(int i=1;i<=n/2-1;i++)
    {
        sum2=sum2+pow(a+2.0*i*h,2)*exp(pow(a+2.0*i*h,2));
    }

    integral=((b-a)/(3.0*n))*(pow(a,2)*exp(pow(a,2))+pow(b,2)*exp(pow(b,2))+4.0*sum1+2.0*sum2);

    cout<<"Result is equal to: "<<integral<<endl;


return 0;

}