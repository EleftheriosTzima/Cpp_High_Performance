#include <iostream>
#include <math.h>
#include <iomanip>


using namespace std;

int main()
{
  unsigned long long int number=1;
  int fact;

  cout<<"Give n for factorization: ";
  cin>>fact;

    if (fact>0)
    {
        for (int n=1;n<=fact;n++)
        {
            number=number*n;
        }

         cout<<"Factorization= "<<setprecision(4)<<number<<endl;

    }
    else if (fact==1)
    {
        cout<<"Factorization=1"<<endl;
    }
    else 
    {
        cout<<"Need a positive variable, operation failed."<<endl;
    }


return 0;

}
