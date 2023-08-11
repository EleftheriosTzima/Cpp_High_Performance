#include <iostream>
#include <mpi.h>

using namespace std;

int main(int argc,char* argv[]){

int my_rank, p;

MPI_Init(&argc,&argv);
MPI_Comm_rank(MPI_COMM_WORLD,&my_rank);   //Get rank
MPI_Comm_size(MPI_COMM_WORLD,&p);


  if(my_rank==0){
    double value;
    cout<<"Enter a value: ";
    cin>>value;
    cout<<"My rank is "<<my_rank<<" and the value distributed is: "<<value<<endl;

        for(int i=0;i<p-1;++i){
        MPI_Ssend(&value,1,MPI_DOUBLE,i+1,5,MPI_COMM_WORLD);
        }
  }

else{
  double buff;
  MPI_Recv(&buff, 1, MPI_DOUBLE,0,5,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
  cout<<"My rank is "<<my_rank<<" and the value distributed is: "<<buff<<endl;
  }

MPI_Finalize();

}
