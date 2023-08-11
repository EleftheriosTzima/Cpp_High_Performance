#include <iostream>
#include <math.h>
using namespace std;

int main()
{

double sum=0, sum_save_new=0,sum_save_old=0; 
double mult=0,mult_save=1;
double diff=1;
int iterations=0;

for (int n=0;diff>1e-5;n++)
{
    sum=pow(-1.,n)/(2.*n+1);
    sum_save_new=sum_save_old+sum;
    diff=abs(sum_save_new-sum_save_old);
    sum_save_old=sum_save_new;
    iterations++;
}
cout<<"pi/4 is equal to: "<<sum_save_new<<endl;
cout<<"number of iterations : "<<iterations<<endl<<endl;

diff=1;
iterations=0;
for (int n=1;diff>1e-5;n++)
{
    mult=4*pow(n,2)/(4*pow(n,2)-1);
    mult_save=mult_save*mult;
    diff=abs(mult_save-mult_save/mult);
    iterations++;
    
}
cout<<"pi/2 is equal to: "<<mult_save<<endl;
cout<<"number of iterations : "<<iterations<<endl<<endl;

return 0;
}