/* Serial Code for the Lid-Driven Cavity Problem
Eleftherios Tzima
CID:01807292
*/

#include "LidDrivenCavity.h"
#include <iostream>

// This is a Constructor which initialises its own variables by accessing the variables of the friend class LidDrivenCavity.
Poisson_Solver::Poisson_Solver(LidDrivenCavity Integrator){

dx=Integrator.dx;         // Spatial step in x direction
dy=Integrator.dy;         // Spatial step in y direction
xdim=Integrator.xdim;    //  total number of nodes in x direction
ydim=Integrator.ydim;    // total number of nodes in y direction
}

/* The goal of this function is to create a vector which contains the coefficients of the Poisson problem (Matrix as output).
   First step: Create vector A wich contains the coefficients in an order given by page 208. Horizontal ordering.
   Second step: Reordering vector A in a columnwise pattern in order to be readable by the LAPACK function dgbtrs. The output is the vector M.
   Xdim=Nx-2 and Ydim=Ny-2
*/
void Poisson_Solver::Matrix_A(double*A,double*Matrix,int Xdim,int Ydim){

          // Top coefficients
          for(int i=Xdim*Xdim*Ydim+Xdim;i<(Xdim+1)*Xdim*Ydim;++i){
                 A[i]=-1/(dy*dy);
               }

          // Right Coefficients. The count identifies the boundaries of the problem and substitutes with zero the appropriate indice of the vector A.
          int count=0;
          for(int i=(2*Xdim-1)*Xdim*Ydim+1;i<(2*Xdim)*Xdim*Ydim;++i){
           if (count!=Xdim-1)
                  {A[i]=-1/(dx*dx); count++;}
            else {count=0;}
          }

          // Centre Coefficients.
          for(int i=(2*Xdim)*Xdim*Ydim;i<(2*Xdim+1)*Xdim*Ydim;++i)
                 A[i]=2*(1/(dy*dy)+1/(dx*dx));

         // Left Coefficients. The count identifies the boundaries of the problem and substitutes with zero the appropriate indices of the vector A.
          count=0;
          for(int i=(2*Xdim+1)*Xdim*Ydim;i<(2*Xdim+2)*Xdim*Ydim-1;++i){
              if (count!=Xdim-1)
                      {A[i]=-1/(dx*dx); count++;}
              else {count=0;}
            }

          // Bottom coefficients
          for(int i=3*Xdim*Xdim*Ydim;i<(3*Xdim+1)*Xdim*Ydim-Xdim;++i)
                  A[i]=-1/(dy*dy);

          // This procedure reads the created A vector in a columnwise way and stores the values into Matrix which is the output vector to be used.
          int num=0; int k=0;
          for(int i=0;i<(3*Xdim+1)*Xdim*Ydim;++i){
          Matrix[i]=A[k+num*Xdim*Ydim];
          num++;

            if(num==3*Xdim+1){num=0; k++;}

          }

}

// This function creates the Force vector (to be used in the poisson solver or dgbtrs LAPACK) which contains the interal points of the vortex field (vort_new).
void Poisson_Solver::Force(double* Force,double* vort_new){

int Xdim=xdim-2;  int Ydim=ydim-2;  int j=0;

        for(int i=0;i<Xdim*Ydim;++i){
              Force[i]=vort_new[xdim+1+i+j];
              if((i+1)%Xdim==0){j+=2;}
            }
}

// This function assembles the Global stream function (internal domain+boundaries) by substituting its interior wirh the sub_stream matrix (contains interior points)
void Poisson_Solver::Assembly_stream(double* stream, double* stream_sub){

  int j=0;
      for(int i=0;i<xdim*ydim;++i){
        if((i>xdim)&&(i<xdim*(ydim-1))&&(i%xdim!=0)&&((i+1)%xdim!=0)){
          stream[i]=stream_sub[j];
          j++;
        }
    }
}
