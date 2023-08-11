# ifndef DECLARE_5_H_
# define DECLARE_5_H_

#define F77NAME(x) x##_
extern "C" {
  void F77NAME(dgemm)(const char& trans, const char& transb,
                      const int& m, const int& n, const int& k,
                      const double& alpha,
                      const double* A, const int& lda,
                      const double* B, const int& ldb,
                      const double& beta, double* C, const int& ldc);

  double F77NAME(ddot) (const int& n,                              // dot of vectors
                        const double *x, const int& incx,
                        const double *y, const int& incy);


  void F77NAME(dgemv)(const char& trans, const int& m,
                      const int& n, const double& alpha,
                      const double* A, const int& lda,
                      const double* x, const int& incx,
                      const double& beta, double* y,
                      const int& incy);

  void F77NAME(dsymv)(const char& uplo,
                      const int& n, const double& alpha,
                      const double* A, const int& lda,
                      const double* x, const int& incx,
                      const double& beta, double* y,
                      const int& incy);

  void F77NAME(daxpy)(const int& n, const double& alpha,
                      const double* x, const int& incx,
                      const double* y, const int& incy);

  double F77NAME(idamax)(const int& n,
                        const double* x, const int& incx);

  double F77NAME(dasum)(const int& n,
                        const double* x, const int& incx);

}



# endif
