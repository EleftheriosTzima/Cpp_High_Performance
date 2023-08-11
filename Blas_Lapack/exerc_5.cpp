# include <iostream>
# include <math.h>
# include <fstream>
# include <iomanip>
# include "declare_5.h"

using namespace std;



int main()
{
  int nodes=41;
  double a=0;        // Starting Point
  double b=2;        // Ending point
  double bound_a=0;  // B.C Conditions
  double bound_b=0;

  int n=nodes-2;
  double l=1;
  double Dx=(b-a)/(nodes-1);

  double* A=new double[n*n]{};
  double* force=new double[n]{};
  double* x_old=new double[n]{};
  double* p_old=new double[n]{};
  double* p_new=new double[n]{};
  double* r_new=new double[n]{};
  double* r_old=new double[n]{};
  double* mult=new double[n]{};
  double ak,bk;
  double error=1.0;

  double* solution=new double[nodes]{};

  matr(A,n,Dx,l);                             // A matrix
  x_force(force,n,Dx,l,bound_a,bound_b);     // Force vector

// Conjugate gradient

  F77NAME(dsymv)('l',n,-1.0,A,n,x_old,1,1.0,force,1);      // calculates r_0
  coppy(force,r_old,n);      //r_old=b
  coppy(r_old,p_old,n);  //p_old=r_old

  while(error>1.e-8){

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

  solution[0]=bound_a;
  solution[nodes-1]=bound_b;

  ofstream LoL("x_vector.txt", ios::out | ios::trunc);  // opens a file called data for output only. If it exists it is deleted

    LoL.precision(5);
    LoL<<solution[0]<<endl;
    for(int i=1;i<n+1;i++)
    {                 // set the precision
        LoL<<setw(3)<<x_old[i-1]<<endl;

    }
    LoL<<solution[n-1]<<endl;

}
