#include <iostream>
#include <math.h>
#include <iomanip>
#include <limits>


using namespace std;

namespace fact
{

unsigned long long int factorial(unsigned long int fact)
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

    void binomial(unsigned long int k,unsigned long int n)
    {
        unsigned long long int result;
        if(n<k)
        {
            throw logic_error("Number must be k<=n");
        }
        else if (k<0||n<0)
        {
            throw logic_error("Number must be k and n must be positive");
        }
            
            result=factorial(n)/(factorial(k)*factorial(n-k));

            cout<<"The binomial factorization is equal to: "<<result<<endl;
        
    }
}

int main()
{

  unsigned long int n,k;

  cout<<"Give k for factorization: ";
  cin>>k;
  cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
  cout<<"Give n for factorization: ";
  cin>>n;
  cin.ignore(numeric_limits<streamsize>::max(), '\n'); 


    try {
    fact::binomial(k,n);
        }
    catch (const logic_error& e) {
    cout << "An error occured: " << e.what() << std::endl;
        }

return 0;

}
