# include <iostream>
# include <math.h>
# include <fstream>
# include <iomanip>
# include "declare_7.h"

using namespace std;

int main()
{
  int nodes=20;
  int Nt=50;        // number of repetitions
  double a=0;        // Starting Point
  double b=1;        // Ending point
  double diffusive=0.1;
  double bound_a=0;  // B.C Conditions
  double bound_b=0;


  int n=nodes-2;     // Dimensions of the banded matrix

  double Dx=(b-a)/(nodes-1);
  double Dt=0.01;
  int dimension=4*n;              // dimension
  double v=diffusive*Dt/(Dx*Dx);
  double* A=new double[dimension]{};
  double* force=new double[n]{};
  double* u_old=new double[n]{};
  int* piv=new int [n]{};          // pivot array


  // Declarations for the eigenvalue problem and solving it
  int info, lwork=-1;
  double wkopt;
  double* w=new double[n];
  double* work;


  ///////////////////////////////////////////////////////////
  matr_bounded(A,dimension,Dx,v);                 // General Symmetric Matrix to Reduced Banded Symmetric
  initial(u_old,n,Dx,bound_a,bound_b);          // Apply the initial conditions



  ofstream LoL("u_vector.txt", ios::out | ios::trunc);  // opens a file called data for output only. If it exists it is deleted

    for(int i=0;i<n;++i)
    {                 // set the precision
        LoL<<setw(3)<<u_old[i]<<endl;;

    }
     LoL<<endl;



  // Lapack Implicit Methodology
  F77NAME(dgbtrf) (n, n, 1, 1, A, 4, piv, info);       // Find the LU Factorization of A(M,N) matrix.


  for (int i=0;i<Nt;++i){

   F77NAME(dgbtrs) ('N', n, 1, 1, 1, A, 4, piv, u_old, n, info);

  }

  /*// Query for optimal workspase
  F77NAME(dsyev)('V', 'U', n, A, n, w, &wkopt, lwork, &info);  // Solves Eigenvalue Problem. int info=0 might be defined


  // Allocates workspace
   lwork = (int)wkopt;
   work = new double[lwork];  // work array is the amount of the space required

   // Computes Eigenvalues
   F77NAME(dsyev)('V', 'U', n, A, n, w, work, lwork, &info);  // Solves Eigenvalue problem
   */

  //  ofstream LoL("u_vector.txt", ios::out | ios::trunc);  // opens a file called data for output only. If it exists it is deleted

      for(int i=0;i<n;++i)
      {                 // set the precision
          LoL<<setw(3)<<u_old[i]<<endl;;

      }

}
