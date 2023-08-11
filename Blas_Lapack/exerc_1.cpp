# include <iostream>
# include <math.h>
#include <fstream>
#include <iomanip>

using namespace std;

#define F77NAME(x) x##_
extern "C" {
  void F77NAME(dgemv)(const char& trans, const int& m,
                      const int& n, const double& alpha,
                      const double* A, const int& lda,
                      const double* x, const int& incx,
                      const double& beta, double* y,
                      const int& incy);


  double F77NAME(ddot) (const int& n,                              // dot of vectors
                      const double *x, const int& incx,
                      const double *y, const int& incy);

  double F77NAME(dnrm2) (const int& n,                             // Norm 2 of a vector
                         const double *x, const int& incx);

   double F77NAME(dnrm2) (const int& n,                             // Norm 2 of a vector
                          const double *x, const int& incx);

   double F77NAME(idamax) (const int& n,                           // maximum of a vector
                          const double *x, const int& incx);

   double F77NAME(dasum) (const int& n,                           // maximum of a vector
                          const double *x, const int& incx);
}

int main(){

  const int n=10;
  double* x=new double[n];
  double z;

  srand(time(0));           // modifies the rand() function to start by taking into account the clock
  for(int i=0;i<n;i++)
  {
      x[i]=(float)rand()/(float)(RAND_MAX);     //Generating random floating point
      cout<<x[i]<<endl;
  }

  z = F77NAME(ddot)(n, x, 1, x, 1);

  cout<<"the square root of the ddot(x) is equal to: "<<sqrt(z)<<endl;
  cout<<"sum of the real absolute component is equal to: "<<F77NAME(dasum)(n, x, 1)<<endl;
  cout<<"maximum value of x vector is equal to: "<<F77NAME(idamax)(n, x, 1)<<endl;


/////////// Output file for matlab
  ofstream LoL("output.txt", ios::out | ios::trunc);  // opens a file called data for output only. If it exists it is deleted
  if(LoL.good())                                   // test if the file can open
  {
    for(int i=0;i<n;i++)
    {

        LoL.precision(5);                          // set the precision
        LoL<<setw(3)<<x[i]<<endl;

    }
    LoL.close();                                  // Closes the file
  }
else
{
    cout<<"Could not open the file";
}
///////////////////*****************//////////////////////
  delete[] x;
}
