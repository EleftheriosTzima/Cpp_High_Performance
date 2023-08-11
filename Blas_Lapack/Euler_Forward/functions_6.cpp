# include <iostream>
# include <math.h>
# include "declare_6.h"

void coppy(const double* str1,double* str2,int n)
{
  for(int i=0;i<n;++i)
  {
    str2[i]=str1[i];
  }
}

void matr_bounded(double* array,int dimension){   // creates A stiffness symmetric matrix
  double a,b;
  double v=0.3;
  a=1-2*v;
  b=v;

  for (int i=1; i < dimension-1;) {
      array[i]=a;
      array[i+1]=b;
      array[i-1]=b;
      i=i+3;
      }
}
// Creates the force vector by giving an empty vector.

void initial(double* array,int n,double Dx,double bound_a,double bound_b)
{
  const double pi=4*atan(1);

   for (int i=0;i<n;++i){
    array[i]=(i+1)*Dx;
    array[i]=sin(pi*array[i]);
    }
    array[0]=array[0]-bound_a/(Dx*Dx);
    array[n-1]=array[n-1]-bound_b/(Dx*Dx);
}
