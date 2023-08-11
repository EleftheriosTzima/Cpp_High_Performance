# include <iostream>
# include <math.h>
# include "declare_5.h"

void coppy(const double* str1,double* str2,int n)
{
  for(int i=0;i<n;++i)
  {
    str2[i]=str1[i];
  }
}

void matr(double* array,int n,double Dx,double l){      // creates A stiffness symmetric matrix
  double a,b;

  a=-2/(Dx*Dx)-l;
  b=1/(Dx*Dx);

  int k=1;
  for (int i=0; i < n; ++i) {

        if(i==0){
        array[i]=a;
        array[i+1]=b;
        continue;
        }
        if(i==n-1){
        array[n*n-1]=a;
        array[n*n-2]=b;
        continue;
        }
        array[i*n+k]=a;
        array[i*n+k+1]=b;
        array[i*n+k-1]=b;
        k=k+1;
      }
}
// Creates the force vector by giving an empty vector.

void x_force(double* array,int n,double Dx,double l,double bound_a,double bound_b)
{
  const double pi=4*atan(1);

   for (int i=0;i<n;++i){
    array[i]=(i+1)*Dx;
    array[i]=-(l+pi*pi)*sin(pi*array[i]);
    }

    array[0]=array[0]-bound_a/(Dx*Dx);
    array[n-1]=array[n-1]-bound_b/(Dx*Dx);
}
