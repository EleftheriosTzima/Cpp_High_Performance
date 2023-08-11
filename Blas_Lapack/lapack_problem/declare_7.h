# ifndef DECLARE_7_H_
# define DECLARE_7_H_

#define F77NAME(x) x##_
extern "C" {

  // BLAS SECTION
  // Banded Matrix Vector Multiplication.
  void F77NAME(dsbmv)(const char& uplo, const int& n,
                      const int& k, const double& alpha,
                      const double* A, const int& lda,
                      const double* x, const int& incx,
                      const double& beta, double* y,
                      const int& incy);

   // LAPACK SECTION
  // Calculates the eigenvalues of a general symmetric matrix.
  void F77NAME(dsyev)(const char& v, const char& ul, const int& n,
                      double* a, const int& lda, double* w,
                      double* work, const int& lwork, int* info );


  // Calculates the LU Decomposition of A Matrix with partial pivoting of a banded matrix
  void F77NAME(dgbtrf) (const int& m, const int& n, const int& kl,
                        const int& ku, double* A, const int& lda,
                        int* ipiv, int& info);

  // Repetitive Ax=b after calling the previous one
  void F77NAME(dgbtrs) (const char& trans, const int& n, const int& kl,
                      const int &ku, const int& nrhs,
                      const double* A,
                      const int& lda, const int* ipiv, double* b,
                      const int& ldb, int& info);
}

// Functions Declarations

void coppy(const double* str1,double* str2,int n);
void matr(double* array,int n,double Dx,double v);
void initial(double* u_old,int n,double Dx,double bound_a,double bound_b);
void matr_bounded(double* array,int dimension,double Dx,double v);

# endif
