# include <iostream>
# include <math.h>
# include <fstream>
# include <iomanip>
# include <cstdlib>



using namespace std;

/*      !!! D=aAB+bC !!!

   transa ("n" "t" "c" == not/traspose/transpose complex)
   m_a: number of rows of matrix A and C
   n_b: number of columns of matrix B and C
   k: number of columns of A and rows of B
   a: constant
   A:
   lda: how long is the column of A == m_a
   B:
   ldb: how long is the column of B == k
   b: const
   C:
   ldc: == m_a


*/

#define F77NAME(x) x##_
extern "C" {
  void F77NAME(dgemm)(const char& trans, const char& transb,
                      const int& m, const int& n, const int& k,
                      const double& alpha,
                      const double* A, const int& lda,
                      const double* B, const int& ldb,
                      const double& beta, double* C, const int& ldc);

}

int main(){


int n=3,N=3;


double* A=new double [N*N];
double* B=new double [N*N];
double* C=new double [N*N];


srand(time(0));

for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      A[i*N+j] = double(rand())/RAND_MAX*100;
      B[i*N+j] = double(rand())/RAND_MAX*100;
      }
  }

  F77NAME(dgemm)('n','n',N,N,N,1.0,A,N,B,N,0.0,C,N);


// Visualisation. Transpose is needed in matlab
  ofstream LoL("A.txt", ios::out | ios::trunc);
  ofstream KoL("B.txt", ios::out | ios::trunc);
  ofstream MoL("Res.txt", ios::out | ios::trunc);  // opens a file called data for output only. If it exists it is deleted

    LoL.precision(6);
    KoL.precision(6);
    MoL.precision(6);

    for (int i = 0; i < N*N; ++i) {

          LoL<<setw(3)<<A[i]<<"  ";        // prints out the A', B' and C'.
          KoL<<setw(3)<<B[i]<<"  ";
          MoL<<setw(3)<<C[i]<<"  ";

          if ((i+1)%N==0){
          LoL<<endl;
          KoL<<endl;
          MoL<<endl;
        }
      }
    LoL.close();
    KoL.close();
    MoL.close();                                   // Closes the file

delete[] A,B,C;
}

///////////////////*****************//////////////////////
