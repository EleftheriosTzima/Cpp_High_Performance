#include <iostream>
#include <mpi.h>
#include "declarations.h"

using namespace std;

int main(int argc,char* argv[]){

  int my_rank, p;

  MPI_Init(&argc,&argv);
  MPI_Comm_rank(MPI_COMM_WORLD,&my_rank);   //Get rank
  MPI_Comm_size(MPI_COMM_WORLD,&p);

  int intervals=0;

  if(my_rank==0){

      while((intervals+1)%p!=0){
      cout<<"Enter the number of intervals (n+1 devisivle by np): ";
      cin>>intervals;
      }
    }

    MPI_Bcast(&intervals,1,MPI_DOUBLE,0,MPI_COMM_WORLD);        // Broadcast the interval value

    double* x=new double[intervals+1]{};
    double* local_x=new double[(intervals+1)/p]{};
    double sum=1/(double)intervals;


  if(my_rank==0){
    for(int i=0;i<intervals+1;++i){
      x[i]=x[i]+sum*i;
      }
   }

  MPI_Scatter(x,(intervals+1)/p,MPI_DOUBLE,local_x,(intervals+1)/p,MPI_DOUBLE,0,MPI_COMM_WORLD);

   double res=0;
   double result;

   for(int i=0;i<(intervals+1)/p;++i){
        res=res+2/(1+local_x[i]*local_x[i]);
        }


  MPI_Reduce(&res,&result,1,MPI_DOUBLE,MPI_SUM,0,MPI_COMM_WORLD);

  if(my_rank==0){

      result=0.5/(double)intervals*(result-1.5);
      cout<<"Integral is equal to: "<<result<<endl;
   }

    MPI_Finalize();

}
