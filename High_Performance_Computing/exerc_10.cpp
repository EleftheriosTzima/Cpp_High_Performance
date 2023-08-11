#include <iostream>
#include <math.h>
#include <limits>

using namespace std;

void exchange(double& a,double& b,double& c)         // Sorting algorithm for three numbers
{
    double cef,bef,aef;
    cef=c;
    bef=b;
    aef=a;

      for(int n=0;n<3;n++)
      {
        if (b>a)
        {
            b=aef;
            a=bef;
            bef=b;
            aef=a;
        }
     
        else if (c>a)
        {
            c=aef;
            a=cef;
            aef=a;
            cef=c;
        }
    
        else if (c>b)
        {
            c=bef;
            b=cef;
            cef=c;
            bef=b;
        }
      }

}

int main()
{
  double a,b,c;
  cout<<"Insert a, b and c: ";
  cin>>a>>b>>c;

  exchange(a,b,c);

  cout<<"a b c: "<<a<<" "<<b<<" "<<c<<endl;
   
   return 0;
}