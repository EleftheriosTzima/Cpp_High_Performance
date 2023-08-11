#include "LidDrivenCavity.h"
#include <iostream>


LidDrivenCavity::LidDrivenCavity(double a,double b,int c,int d,int e,int f,double g,double j,double k){    // Creating a Constructor
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


void LidDrivenCavity::Initialise(){

xdim=Nx/Px;
ydim=Ny/Py;
dx=Lx/(Nx-1);
dy=Ly/(Ny-1);
chronos=(int)(T/dt);


}

// Apply Boundary Conditions for the vorticity field to the boundary subdomains
void LidDrivenCavity::Boundary_Vort(double* vort_sub,double* stream_sub,int* coord){

  if (coord[0]==0){                                      //Bottom subdomains
    for(int i=0;i<xdim;++i){
      vort_sub[i]=-2*stream_sub[i+xdim]/(dy*dy);
    }
  }

  if (coord[1]==0){                                      //Left subdomains
    for(int i=0;i<ydim;++i){
      vort_sub[i*xdim]=-2*stream_sub[i*xdim+1]/(dx*dx);
    }
  }


  if (coord[1]==Px-1){                                    //Right subdomains
    for(int i=0;i<ydim;++i){
      vort_sub[(i+1)*xdim-1]=-2*stream_sub[(i+1)*xdim-2]/(dx*dx);
    }
  }

  if (coord[0]==Py-1){                                   //North subdomains
    for(int i=xdim*ydim;i>=xdim*(ydim-1);--i){
      vort_sub[i]=-2*stream_sub[i-xdim]/(dy*dy)-2*U/dy;
    }
  }
}


void LidDrivenCavity::Vort_n(double* vort_sub_old,double* stream_sub,double* bottom_stream_rec, double* top_stream_rec, double* right_stream_rec, double* left_stream_rec){

/// Calculate vort_n of the subgrid
  int left=0; int right=0; int top=0;  int bottom=0;

  for(int i=0;i<xdim*ydim;++i){

          if( (i>xdim) && (i%xdim!=0) && ((i+1)%xdim!=0) && (i<(ydim-1)*xdim) ){
           vort_sub_old[i]=-(stream_sub[i+1]-2*stream_sub[i]+stream_sub[i-1])/(dx*dx)-(stream_sub[i+xdim]-2*stream_sub[i]+stream_sub[i-xdim])/(dy*dy);
           }

          else if(i==0){
           vort_sub_old[i]=-(stream_sub[i+1]-2*stream_sub[i]+left_stream_rec[left])/(dx*dx)-(stream_sub[i+xdim]-2*stream_sub[i]+bottom_stream_rec[bottom])/(dy*dy);
           bottom++; left++;
           }


          else if(i==(xdim-1)){
          vort_sub_old[i]=-(right_stream_rec[right]-2*stream_sub[i]+stream_sub[i-1])/(dx*dx)-(stream_sub[i+xdim]-2*stream_sub[i]+bottom_stream_rec[bottom])/(dy*dy);
          right++; bottom++;
          }


           else if(i==xdim*(ydim-1)){
            vort_sub_old[i]=-(stream_sub[i+1]-2*stream_sub[i]+left_stream_rec[left])/(dx*dx)-(top_stream_rec[top]-2*stream_sub[i]+stream_sub[i-xdim])/(dy*dy);
            top++;
            }

            else if((i>0)&&(i<(xdim-1))){
             vort_sub_old[i]=-(stream_sub[i+1]-2*stream_sub[i]+stream_sub[i-1])/(dx*dx)-(stream_sub[i+xdim]-2*stream_sub[i]+bottom_stream_rec[bottom])/(dy*dy);
             bottom++;
             }


          else if(i==xdim*ydim-1){
          vort_sub_old[i]=-(right_stream_rec[right]-2*stream_sub[i]+stream_sub[i-1])/(dx*dx)-(top_stream_rec[top]-2*stream_sub[i]+stream_sub[i-xdim])/(dy*dy);
           }


          else if ((i>xdim*(ydim-1))&&(i<xdim*ydim-1)){
            vort_sub_old[i]=-(stream_sub[i+1]-2*stream_sub[i]+stream_sub[i-1])/(dx*dx)-(top_stream_rec[top]-2*stream_sub[i]+stream_sub[i-xdim])/(dy*dy);
            top++;
           }

          else if((i%xdim==0)&&(i>0)&&(i<(ydim-1)*xdim)){
           vort_sub_old[i]=-(stream_sub[i+1]-2*stream_sub[i]+left_stream_rec[left])/(dx*dx)-(stream_sub[i+xdim]-2*stream_sub[i]+stream_sub[i-xdim])/(dy*dy);
           left++;
           }

          else if(((i+1)%xdim==0)&&(i>xdim)&&(i<ydim*xdim-1)){
           vort_sub_old[i]=-(right_stream_rec[right]-2*stream_sub[i]+stream_sub[i-1])/(dx*dx)-(stream_sub[i+xdim]-2*stream_sub[i]+stream_sub[i-xdim])/(dy*dy);
           right++;
          }
      }
}

void LidDrivenCavity::Vort_n_plus(double* vort_sub_new,double* vort_sub_old,double* stream_sub,double* bottom_stream_rec, double* top_stream_rec, double* right_stream_rec, double* left_stream_rec,
                             double* bottom_vort_rec,double* top_vort_rec,double* right_vort_rec,double* left_vort_rec,int* coord){

/// Calculate vort_n of the subgrid
  int left=0; int right=0; int top=0;  int bottom=0;

  for(int i=0;i<xdim*ydim;++i){

          if( (i>xdim) && (i%xdim!=0) && (i%(xdim-1)!=0) && (i<(ydim-1)*xdim)  ){

            vort_sub_new[i]=vort_sub_old[i]+dt/Re*((vort_sub_old[i+1]-2*vort_sub_old[i]+vort_sub_old[i-1])/(dx*dx)+(vort_sub_old[i+xdim]-2*vort_sub_old[i]+vort_sub_old[i-xdim])/(dy*dy))
              +dt/(4*dx*dy)*(stream_sub[i+1]-stream_sub[i-1])*(vort_sub_old[i+xdim]-vort_sub_old[i-xdim])
              -dt/(4*dx*dy)*(stream_sub[i+xdim]-stream_sub[i-xdim])*(vort_sub_old[i+1]-vort_sub_old[i-1]);
           }

          else if((i==0)&&(coord[0]!=0)){

            vort_sub_new[i]=vort_sub_old[i]+dt/Re*((vort_sub_old[i+1]-2*vort_sub_old[i]+left_vort_rec[left])/(dx*dx)+(vort_sub_old[i+xdim]-2*vort_sub_old[i]+bottom_vort_rec[bottom])/(dy*dy))
              +dt/(4*dx*dy)*(stream_sub[i+1]-left_vort_rec[left])*(vort_sub_old[i+xdim]-bottom_vort_rec[bottom])
              -dt/(4*dx*dy)*(stream_sub[i+xdim]-bottom_stream_rec[bottom])*(vort_sub_old[i+1]-left_vort_rec[left]);
           bottom++; left++;
           }

          else if(((i>0)&&(i<(xdim-1)))&&(coord[0]!=0)){

            vort_sub_new[i]=vort_sub_old[i]+dt/Re*((vort_sub_old[i+1]-2*vort_sub_old[i]+vort_sub_old[i-1])/(dx*dx)+(vort_sub_old[i+xdim]-2*vort_sub_old[i]+bottom_vort_rec[bottom])/(dy*dy))
              +dt/(4*dx*dy)*(stream_sub[i+1]-stream_sub[i-1])*(vort_sub_old[i+xdim]-bottom_vort_rec[bottom])
              -dt/(4*dx*dy)*(stream_sub[i+xdim]-bottom_stream_rec[bottom])*(vort_sub_old[i+1]-vort_sub_old[i-1]);
           bottom++;
           }

          else if((i==(xdim-1))&&(coord[0]!=0)){

            vort_sub_new[i]=vort_sub_old[i]+dt/Re*((right_vort_rec[right]-2*vort_sub_old[i]+vort_sub_old[i-1])/(dx*dx)+(vort_sub_old[i+xdim]-2*vort_sub_old[i]+bottom_vort_rec[bottom])/(dy*dy))
              +dt/(4*dx*dy)*(right_stream_rec[right]-stream_sub[i-1])*(vort_sub_old[i+xdim]-bottom_vort_rec[bottom])
              -dt/(4*dx*dy)*(stream_sub[i+xdim]-bottom_stream_rec[bottom])*(right_vort_rec[right]-vort_sub_old[i-1]);
           right++; bottom++;
           }

          else if((i==xdim*ydim-1)&&(coord[0]!=Py-1)){

            vort_sub_new[i]=vort_sub_old[i]+dt/Re*((right_vort_rec[right]-2*vort_sub_old[i]+vort_sub_old[i-1])/(dx*dx)+(top_vort_rec[top]-2*vort_sub_old[i]+vort_sub_old[i-xdim])/(dy*dy))
              +dt/(4*dx*dy)*(right_stream_rec[right]-stream_sub[i-1])*(top_vort_rec[top]-vort_sub_old[i-xdim])
              -dt/(4*dx*dy)*(top_stream_rec[top]-stream_sub[i-xdim])*(right_vort_rec[right]-vort_sub_old[i-1]);
           }

          else if((i==xdim*(ydim-1))&&(coord[0]!=Py-1)){

            vort_sub_new[i]=vort_sub_old[i]+dt/Re*((vort_sub_old[i+1]-2*vort_sub_old[i]+left_vort_rec[left])/(dx*dx)+(top_vort_rec[top]-2*vort_sub_old[i]+vort_sub_old[i-xdim])/(dy*dy))
              +dt/(4*dx*dy)*(stream_sub[i+1]-left_stream_rec[left])*(top_vort_rec[top]-vort_sub_old[i-xdim])
              -dt/(4*dx*dy)*(top_stream_rec[top]-stream_sub[i-xdim])*(vort_sub_old[i+1]-left_vort_rec[left]);
            left++; top++;
            }

          else if (((i>xdim*(ydim-1))&&(i<xdim*ydim-1))&&(coord[0]!=Py-1)){

            vort_sub_new[i]=vort_sub_old[i]+dt/Re*((vort_sub_old[i+1]-2*vort_sub_old[i]+vort_sub_old[i-1])/(dx*dx)+(top_vort_rec[top]-2*vort_sub_old[i]+vort_sub_old[i-xdim])/(dy*dy))
              +dt/(4*dx*dy)*(stream_sub[i+1]-stream_sub[i-1])*(top_vort_rec[top]-vort_sub_old[i-xdim])
              -dt/(4*dx*dy)*(top_stream_rec[top]-stream_sub[i-xdim])*(vort_sub_old[i+1]-vort_sub_old[i-1]);
            top++;
           }

          else if((i%xdim==0)&&(coord[1]!=0)){

            vort_sub_new[i]=vort_sub_old[i]+dt/Re*((vort_sub_old[i+1]-2*vort_sub_old[i]+left_vort_rec[left])/(dx*dx)+(vort_sub_old[i+xdim]-2*vort_sub_old[i]+vort_sub_old[i-xdim])/(dy*dy))
              +dt/(4*dx*dy)*(stream_sub[i+1]-left_stream_rec[left])*(vort_sub_old[i+xdim]-vort_sub_old[i-xdim])
              -dt/(4*dx*dy)*(stream_sub[i+xdim]-stream_sub[i-xdim])*(vort_sub_old[i+1]-left_vort_rec[left]);
           left++;
           }

          else if((i%(xdim-1)==0)&&(coord[1]!=Px-1)){

            vort_sub_new[i]=vort_sub_old[i]+dt/Re*((right_vort_rec[right]-2*vort_sub_old[i]+vort_sub_old[i-1])/(dx*dx)-(vort_sub_old[i+xdim]-2*vort_sub_old[i]+vort_sub_old[i-xdim])/(dy*dy))
              +dt/(4*dx*dy)*(right_stream_rec[right]-stream_sub[i-1])*(vort_sub_old[i+xdim]-vort_sub_old[i-xdim])
              -dt/(4*dx*dy)*(stream_sub[i+xdim]-stream_sub[i-xdim])*(right_vort_rec[right]-vort_sub_old[i-1]);
           right++;
          }
      }
}



// Sending the Buffer Array
void LidDrivenCavity::Send_Vort(double* vort_sub_old,double* bottom_sen,double* top_sen,double* right_sen, double* left_sen){

   for(int i=0;i<xdim*ydim;++i){
      if(i<xdim)
      {bottom_sen[i]=vort_sub_old[i];}
      if(i>=(ydim-1)*xdim)
      {top_sen[i]=vort_sub_old[i];}
      if(i%(xdim-1)!=0)
      {right_sen[i]=vort_sub_old[i];}
      if(i%xdim!=0)
      {left_sen[i]=vort_sub_old[i];}
    }

}



// This function reshapes the Gathered matrix to a global one.
void LidDrivenCavity::reshape_global (double* dummy,double* domain){

int j=0; int k=0; int m=0;

     for(int i=0;i<Nx*Ny;++i){
       dummy[j]=domain[i];

       if((i+1)%xdim==0){
       j+=(Px-1)*xdim;
       }

       if((i+1)%(xdim*ydim)==0){
       k++;
       j=(k*xdim-1);
       }

       if((i+1)%(xdim*ydim*Px)==0){
       m++;
       j=xdim*ydim*Px*m-1;
       k=m*Px*ydim;
       }
       j++;
     }

}
