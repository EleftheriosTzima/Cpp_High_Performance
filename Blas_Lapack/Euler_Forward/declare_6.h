# ifndef DECLARE_6_H_
# define DECLARE_6_H_

#define F77NAME(x) x##_
extern "C" {
  void F77NAME(dsbmv)(const char& uplo, const int& n,
                      const int& k, const double& alpha,
                      const double* A, const int& lda,
                      const double* x, const int& incx,
                      const double& beta, double* y,
                      const int& incy);
}

// Functions Declarations

void coppy(const double* str1,double* str2,int n);
void matr_bounded(double* array,int dimension);
void initial(double* u_old,int n,double Dx,double bound_a,double bound_b);


# endif
