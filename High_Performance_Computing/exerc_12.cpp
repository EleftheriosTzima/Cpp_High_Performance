#include <iostream>
#include <math.h>
#include <iomanip>
#include <limits>

using namespace std;

unsigned long long int fibonacci(unsigned long int n)
{
   if (n<2)
   {
       throw logic_error("n must be >=2.");
   }
   
   unsigned long long int x0=1, x1=1,result;

    for (unsigned long int i=2;i<n;i++)
        {
            result=x1+x0;
            x0=x1;
            x1=result;
        }
return result;
}

int main()
{
    unsigned long int n;
    unsigned long int result;

    cout<<"Insert number n for Fibonacci sequence: ";
    cin>>n;
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); 

    try{
    result=fibonacci(n);
    cout<<"The Fibonacci result is: "<<result<<endl;
    }
    catch (const logic_error& e){
    cout<<"An error occured: "<<e.what()<<endl;
    }
}


