/* Serial Code for the Lid-Driven Cavity Problem
Eleftherios Tzima
CID:01807292
*/

#include "LidDrivenCavity.h"
#include <iostream>
#include <math.h>

// Creating a Constructor
LidDrivenCavity::LidDrivenCavity(double a, double b, int c, int d, int e,int f, double g, double j, double k){
  Lx=a;
  Ly=b;
  Nx=c;
  Ny=d;
  Px=e;
  Py=f;
  dt=g;
  T=j;
  Re=k;
}

// Initialises the below variables by accsessing those of the constructor above.
void LidDrivenCavity::initialise(){

  xdim=Nx;
  ydim=Ny;
  dx=Lx/(Nx-1);
  dy=Ly/(Ny-1);
  chronos=(int)(T/dt);

}


// Apply Boundary Conditions for the vorticity field to the boundary subdomains
void LidDrivenCavity::Boundary_Vort(double* vort,double* stream){

    // Bottom B.C
    for(int i=0;i<xdim;++i){
      vort[i]=-2*stream[i+xdim]/(dy*dy);
    }
    // Left B.C
    for(int i=1;i<ydim-1;++i){
      vort[i*xdim]=-2*stream[i*xdim+1]/(dx*dx);
    }
    // Right B.C
    for(int i=1;i<ydim-1;++i){
      vort[(i+1)*xdim-1]=-2*stream[(i+1)*xdim-2]/(dx*dx);
    }

    // Top B.C
    for(int i=xdim*ydim-1;i>=xdim*(ydim-1);--i){
      vort[i]=-2*stream[i-xdim]/(dy*dy)-2*U/dy;
    }
}

// Calculates interior vorticity at time t.
void LidDrivenCavity::Vort_n(double* vort_old,double* stream){

  for(int i=0;i<xdim*ydim;++i){
          if( (i>xdim) && (i%xdim!=0) && ((i+1)%xdim!=0) && (i<(ydim-1)*xdim)  ){

           vort_old[i]=-(stream[i+1]-2*stream[i]+stream[i-1])/(dx*dx)-(stream[i+xdim]-2*stream[i]+stream[i-xdim])/(dy*dy);

           }
        }
      }

// Calculates interior vorticity at time t+1.
void LidDrivenCavity::Vort_n_new(double* vort_new,double* vort_old,double* stream){

  for(int i=0;i<xdim*ydim;++i){
      if( (i>xdim) && (i%xdim!=0) && ((i+1)%xdim!=0) && (i<(ydim-1)*xdim)  ){

        vort_new[i]=vort_old[i]+dt/Re*((vort_old[i+1]-2*vort_old[i]+vort_old[i-1])/(dx*dx)+(vort_old[i+xdim]-2*vort_old[i]+vort_old[i-xdim])/(dy*dy))
          +dt/(4*dx*dy)*(stream[i+1]-stream[i-1])*(vort_old[i+xdim]-vort_old[i-xdim])
          -dt/(4*dx*dy)*(stream[i+xdim]-stream[i-xdim])*(vort_old[i+1]-vort_old[i-1]);

        }
      }

}

  // Coppy function. Coppies vector str1 to str2
void LidDrivenCavity::coppy_vort(const double* str1,double* str2,int& xdim,int& ydim){

  for(int i=0;i<xdim*ydim;++i)
  {
      if((i>xdim)&&(i<xdim*(ydim-1))&&(i%xdim!=0)&&((i+1)%xdim!=0)){
      str2[i]=str1[i];
      }
  }
}
