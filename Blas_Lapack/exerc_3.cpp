#include <iostream>
#include <cstdlib>
using namespace std;

// For BLAS ONLY (i.e. not LAPACK):
// Rather than declare the F77NAME macro and extern "C" declarations, we can use
// the cblas.h header which includes this for us.
#include <cblas.h>

int main() {
    const int N = 64;                       // Size of vectors
    double* x = new double[N];              // Allocate vectors
    double* y = new double[N];
    double z = 0.0;

    srand(time(0));                         // Initialise random numbers
    for (int i = 0; i < N; ++i) {           // Populate vectors
        x[i] = (double)(rand()) / RAND_MAX; //   with numbers in [0,1]
        y[i] = (double)(rand()) / RAND_MAX;
    }

    // Wrapper routines are prefixed with "cblas_" to distinguish them from
    // the native BLAS routines.
    z = cblas_ddot(N, x, 1, y, 1);          // Compute dot-product using CBLAS

    cout << "Dot product result: " << z << endl;

    delete[] x;                             // Deallocate memory!
    delete[] y;
}
