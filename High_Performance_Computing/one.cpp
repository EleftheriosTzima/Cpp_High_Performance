//Code Implemented by Eleftherios Tzima
//CID: 01807292


#include <iostream>
#include <math.h>
#include <limits>
#include <fstream>
#include <iomanip>

using namespace std;

unsigned long long int factorial(unsigned long int fact)      // Calculates the factorial
{
        long long int number=1;

        if (fact==1)
        {
            number=1;
        }
        else{
         for (int n=1;n<=fact;n++)
            {
                number=number*n;
            }
        }

        return number;

 }

double sinus(long int k,double x)                 //Function for approximating sin(x)
{
    double sum1=0;

    for(int i=0;i<=k;i++)
        {
            sum1=sum1+pow(-1.0,i)*pow(x,2*i+1)/factorial(2*i+1);
        }

        return sum1;

}

double cosinus(long int k,double x)           //Function for approximating cos(x)
{
    double sum1=0;

    for(int i=0;i<=k;i++)
        {   
            sum1=sum1+pow(-1.0,i)*pow(x,2*i)/factorial(2*i);
        }

    return sum1;
}



int main()
{
long int k=5;
double x;

double cos_res,sin_res;

cout<<"Enter x in radians: ";
cin>>x;
cin.ignore(numeric_limits<streamsize>::max(), '\n'); 

if (x<=-4*atan(1)||x>=4*atan(1))                             // Statement that the imput must be -pi<x<pi
   {
       throw logic_error("x must be pi<x<pi.");
   }

try                                                         // If it is satisfied the execute
{
    sin_res=sinus(k,x);
    cos_res=cosinus(k,x);

    cout<<"True values for sin(x)= "<<sin(x)<<endl;
    cout<<"True values for cos(x)= "<<cos(x)<<endl;

    cout<<"Approximation sin(x)= "<<sin_res<<endl;
    cout<<"Approximation cos(x)= "<<cos_res<<endl;

    cout<<"Absolute Error is y= "<<pow(sin_res,2)+pow(cos_res,2)<<endl;
}

catch (const logic_error& e)                               // If it is not satisfied
    {
    cout<<"An error occured: "<<e.what()<<endl;
    }

}