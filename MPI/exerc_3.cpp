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
int elements=1024;

MPI_Init(&argc,&argv);
MPI_Comm_rank(MPI_COMM_WORLD,&my_rank);   //Get rank
MPI_Comm_size(MPI_COMM_WORLD,&p);

double* local_x=new double[elements/p]{};
double* local_y=new double[elements/p]{};
double result[1];
double* x=new double[elements]{};
double* y=new double[elements]{};

double res;

if(my_rank==0){
    srand(time(0));           // modifies the rand() function to start by taking into account the clock
    for(int i=0;i<elements;++i)
    {
        x[i]=fRand(0,1);     //Generating random floating point
        y[i]=fRand(0,1);
    }
  }

    MPI_Scatter(x,elements/p,MPI_DOUBLE,local_x,elements/p,MPI_DOUBLE,0,MPI_COMM_WORLD);
    MPI_Scatter(y,elements/p,MPI_DOUBLE,local_y,elements/p,MPI_DOUBLE,0,MPI_COMM_WORLD);

    res=F77NAME(ddot) (elements/p, local_x,1,local_y, 1);

    MPI_Reduce(&res,result,1,MPI_DOUBLE,MPI_SUM,0,MPI_COMM_WORLD);
    MPI_Barrier(MPI_COMM_WORLD);


if(my_rank==0){
  cout<<"The result is equal to: "<<result[0]<<endl;
}

    MPI_Finalize();

}
