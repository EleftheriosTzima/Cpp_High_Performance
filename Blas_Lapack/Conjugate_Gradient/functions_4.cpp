# include <iostream>
# include <math.h>
# include "declare_4.h"

// Definition of various functions

double fRand(double fMin, double fMax)      //random number function generator
{
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}

void vectRand(double* vect,int n)
{
   srand(time(0));

   for (int i=0;i<n; ++i){

    vect[i]=fRand(-1,1);

   }

}

void symRand(double* array,int n)         // creates a random symmetric matrix
{

  srand(time(0));           // modifies the rand() function to start by taking into account the clock
  int k=1,j=0;
  for (int i=0; i < n*n; ++i) {

        array[i]=fRand(-1,1);
        array[i+j*(n-1)]=array[i];
        j=j+1;

          if ((i+1)%n==0){
           j=0;
           i=i+k;
           k=k+1;
          }
      }
}

void coppy(const double* str1,double* str2,int n)
{
  for(int i=0;i<n;++i)
  {
    str2[i]=str1[i];
  }
}
