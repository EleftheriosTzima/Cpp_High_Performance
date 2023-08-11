#include <iostream>
#include <math.h>
#include <fstream>
#include <iomanip>

using namespace std;

int main()
{
 const double pi=4*atan(1);
 double result;

  ofstream LoL("sin.txt", ios::out | ios::trunc);  // opens a file called data for output only. If it exists it is deleted
  if(LoL.good())                                   // test if the file can open
  {
    for(int n=0;n<=99;n++)
    {
        
        result=sin(2*pi*n/100);
        LoL.precision(5);                          // set the precision
        LoL<<setw(3)<<n<<"  "<<setw(10)<<result<<endl;

    }
    LoL.close();                                  // Closes the file
  }
else
{
    cout<<"Could not open the file";
}

return 0;
}