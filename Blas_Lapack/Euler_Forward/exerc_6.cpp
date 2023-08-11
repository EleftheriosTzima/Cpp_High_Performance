# include <iostream>
# include <math.h>
# include <fstream>
# include <iomanip>
# include "declare_6.h"

using namespace std;

int main()
{
  int nodes=20;
  int Nt=1000;        // number of repetitions
  double a=0;        // Starting Point
  double b=1;        // Ending point

  double bound_a=0;  // B.C Conditions
  double bound_b=0;

  int n=nodes-2;     // Dimensions of the banded matrix
  int m=3;
  int dimension=n*m;

  double Dx=(b-a)/(nodes-1);
  double Dt=0.001;
  double v=Dt/(Dx*Dx);
  double* A=new double[m*n]{};
  double* force=new double[n]{};
  double* u_old=new double[n]{};
  double* u_new=new double[n]{};
  double* solution=new double[nodes]{};


  matr_bounded(A,dimension);
  initial(u_old,n,Dx,bound_a,bound_b);
  coppy(u_old,force,n);

   for(int i=0;i<Nt;++i){
    F77NAME(dsbmv)('u',n,1,1.0,A,3,u_old,1,0,u_new,1);      // leading order of banded matrix A is 3 with 1 super-diagona;.
    coppy(u_new,u_old,n);
    }


    ofstream LoL("u_vector.txt", ios::out | ios::trunc);  // opens a file called data for output only. If it exists it is deleted

      LoL.precision(5);
      LoL<<solution[0]<<endl;
      for(int i=1;i<n+1;++i)
      {                 // set the precision
          LoL<<setw(3)<<u_new[i-1]<<endl;

      }
      LoL<<endl;
      for(int i=0;i<n;++i)
      {                 // set the precision
          LoL<<setw(3)<<force[i]<<endl;

      }


}
