#include <iostream>
#include <mpi.h>
#include "declarations.h"

using namespace std;

double fRand(double fMin, double fMax)      //random number function generator
{
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}

int main(int argc,char* argv[]){

  int my_rank, p;

  MPI_Init(&argc,&argv);
  MPI_Comm_rank(MPI_COMM_WORLD,&my_rank);   //Get rank
  MPI_Comm_size(MPI_COMM_WORLD,&p);


  int n=4;                              // Dimension of the matrix-vector 2^n

  double* A=new double[n*n]{};
  double* x=new double[n]{};
  double* A_local=new double[n*n/p]{};
  double* res_local=new double[n/p]{};

    if(my_rank==0){

        srand(time(0));           // modifies the rand() function to start by taking into account the clock
        for(int i=0;i<n*n;++i)
        {
            A[i]=fRand(0,1);     //Generating random A matrix row-wise
        }
        for(int i=0;i<n;++i)
        {
            x[i]=fRand(0,1);     //Generating random floating point
        }

     cout<<"A is equal to: "<<endl;
       for(int i=0;i<n*n;++i){
         cout<<A[i]<<" ";
         if((i+1)%n==0)
         cout<<endl;
         }

       cout<<"x is equal to: "<<endl;

       for(int i=0;i<n;++i){
         cout<<x[i]<<endl;
         }
      }


    MPI_Bcast(x,n,MPI_DOUBLE,0,MPI_COMM_WORLD);
    MPI_Scatter(A,n*n/p,MPI_DOUBLE,A_local,n*n/p,MPI_DOUBLE,0,MPI_COMM_WORLD);

    int k=0;
    for (int j=0;j<n/p;++j){
      k=n*j;
      for (int i=0;i<n;++i){

       res_local[j]=res_local[j]+A_local[i+k]*x[i];         //submatrix A x vector multiplication

      }
    }


   MPI_Gather(res_local,n/p,MPI_DOUBLE,x,n/p,MPI_DOUBLE,0,MPI_COMM_WORLD);


   if(my_rank==0){
     cout<<"Matr_Vect_Mult is equal to: "<<endl;
     for(int i=0;i<n;++i){
       cout<<x[i]<<endl;
       }
     }


    MPI_Finalize();

}
