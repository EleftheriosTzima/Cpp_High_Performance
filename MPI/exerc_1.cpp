#include <iostream>
#include <mpi.h>

using namespace std;

int main(int argc,char* argv[]){

int my_rank, p;

MPI_Init(&argc,&argv);
MPI_Comm_rank(MPI_COMM_WORLD,&my_rank);   //Get rank
MPI_Comm_size(MPI_COMM_WORLD,&p);

double value;

if(my_rank==0){
  cout<<"Enter a value: ";
  cin>>value;
  cout<<"My rank is: "<<my_rank<<"and the value distributed is: "<<value<<endl;
}


MPI_Bcast(&value,1,MPI_DOUBLE,0,MPI_COMM_WORLD);

if(my_rank!=0){
cout<<"My rank is "<<my_rank<<" and the value received is: "<<value<<endl;
}

MPI_Finalize();

return 0;


}
