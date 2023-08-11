# include <iostream>
# include <math.h>
# include <fstream>
# include <iomanip>
# include "declare_5.h"

using namespace std;



int main()
{
  int nodes=100000;
  double a=0;        // Starting Point
  double b=2;        // Ending point
  double bound_a=0;  // B.C Conditions
  double bound_b=0;

  int n=nodes-2;
  double l=1;
  double Dx=(b-a)/(nodes-1);

  double* A=new double[n*n]{};
  double* force=new double[n]{};
  int* piv=new int[n]{};
  int info;


  double* solution=new double[nodes]{};

  matr(A,n,Dx,l);                             // A matrix
  x_force(force,n,Dx,l,bound_a,bound_b);     // Force vector


// LU Decomposition method
F77NAME(dgesv)(n, 1, A, n, piv, force, n, info);

/*
  solution[0]=bound_a;
  solution[nodes-1]=bound_b;

  ofstream LoL("x_vector.txt", ios::out | ios::trunc);  // opens a file called data for output only. If it exists it is deleted

    LoL.precision(5);
    LoL<<solution[0]<<endl;
    for(int i=1;i<n+1;i++)
    {                 // set the precision
        LoL<<setw(3)<<force[i-1]<<endl;

    }
    LoL<<solution[n-1]<<endl;
    */

}
