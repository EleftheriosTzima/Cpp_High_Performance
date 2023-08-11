# include <iostream>
# include <math.h>
# include <fstream>
# include <iomanip>
# include "declare_4.h"

using namespace std;


int main(){

  const int n=10000;
  double* M=new double[n*n]{};
  double* A=new double[n*n]{};
  double* x_old=new double[n]{};
  double* y=new double[n]{};
  double* b=new double[n]{};
  double* p_old=new double[n]{};
  double* p_new=new double[n]{};
  double* r_new=new double[n]{};
  double* r_old=new double[n]{};
  double* mult=new double[n]{};
  double ak,bk;
  double error=1.0;


  symRand(M,n);
  vectRand(y,n);
  F77NAME(dgemm)('t','n',n,n,n,1.0,M,n,M,n,0.0,A,n);  // Creates the A matrix
  F77NAME(dsymv)('l',n,1.0,A,n,y,1,0.0,b,1);        // Creates the b vector


// Conjugate gradient

  F77NAME(dsymv)('l',n,-1.0,A,n,x_old,1,1.0,b,1);      // calculates r_0
  coppy(b,r_old,n);      //r_old=b
  coppy(r_old,p_old,n);  //p_old=r_old

  while(error>1.e-6){

  F77NAME(dsymv)('l',n,1.0,A,n,p_old,1,0,mult,1); // Calculates A*p_k
  ak=F77NAME(ddot)(n, r_old, 1, r_old, 1) / F77NAME(ddot)(n, p_old, 1, mult, 1);


  F77NAME(daxpy)(n,ak,p_old,1.0,x_old,1.0); // calculates x_new to x_old

  coppy(r_old,r_new,n);  // r_new=r_old
  F77NAME(dsymv)('l',n,-ak,A,n,p_old,1,1,r_new,1); // Calculates A*p_k

  error=F77NAME(idamax)(n,r_new,1);

  bk=F77NAME(ddot)(n, r_new, 1, r_new, 1)/F77NAME(ddot)(n, r_old, 1, r_old, 1);

  coppy(r_new,p_new,n);
  F77NAME(daxpy)(n,bk,p_old,1.0,p_new,1.0);

  coppy(p_new,p_old,n);
  coppy(r_new,r_old,n);

  }

// Output
/*
ofstream LoL("b_vector.txt", ios::out | ios::trunc);  // opens a file called data for output only. If it exists it is deleted

  for(int i=0;i<n;i++)
  {

      LoL.precision(5);                          // set the precision
      LoL<<setw(3)<<y[i]<<" ";

  }

  LoL<<endl;

  for(int i=0;i<n;i++)
  {

      LoL.precision(5);                          // set the precision
      LoL<<setw(3)<<x_old[i]<<" ";

  }
  LoL.close();                                  // Closes the file

*/
 delete[] M,x_old,p_old,p_new,r_old,r_new,b,A,y;
}
