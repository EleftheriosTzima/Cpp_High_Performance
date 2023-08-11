#include <iostream>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <mpi.h>
#include "LidDrivenCavity.h"


using namespace std;

int main(int argc,char* argv[])
{

int my_rank, p;
MPI_Init(&argc,&argv);
MPI_Comm_rank(MPI_COMM_WORLD,&my_rank);
MPI_Comm_size(MPI_COMM_WORLD,&p);

//LidDrivenCavity Integrator (atof(argv[5]),atof(argv[6]),(int)atof(argv[7]),(int)atof(argv[8]),(int)atof(argv[9]),(int)atof(argv[10]),atof(argv[11]),atof(argv[12]),atof(argv[13]));
LidDrivenCavity Integrator (1,1,20,20,4,4,0.1,1,100);
MPI_Comm subdomain;
MPI_Status stats[8];

int dim[2], period[2], reorder;
int coord[2], id;


dim[0]=Integrator.Px; dim[1]=Integrator.Py;
period[0]=true; period[1]=false; reorder=true;

MPI_Cart_create(MPI_COMM_WORLD,2,dim,period,reorder,&subdomain);    //  Put Ranks into topology

int gr_poin=Integrator.Nx*Integrator.Ny;
int gr_l_poin=Integrator.xdim*Integrator.ydim;

double* vort=new double[gr_poin];                       //Global Vorticity Matrix

double* vort_sub_old=new double[gr_l_poin]{};             //Vorticity Matrix of the subdomain
double* vort_sub_new=new double[gr_l_poin]{};             //Vorticity Matrix of the subdomain
double* stream_sub=new double[gr_l_poin]{};               //Vorticity Matrix of the subdomain


double* bottom_vort_rec= new double[Integrator.xdim]{};  double* bottom_vort_sen= new double[Integrator.xdim]{};
double* top_vort_rec= new double[Integrator.xdim]{};     double* top_vort_sen= new double[Integrator.xdim]{};
double* left_vort_rec= new double[Integrator.ydim]{};    double* left_vort_sen= new double[Integrator.ydim]{};
double* right_vort_rec= new double[Integrator.ydim]{};   double* right_vort_sen= new double[Integrator.ydim]{};

double* bottom_stream_rec= new double[Integrator.xdim]{};  double* bottom_stream_sen= new double[Integrator.xdim]{};
double* top_stream_rec= new double[Integrator.xdim]{};     double* top_stream_sen= new double[Integrator.xdim]{};
double* left_stream_rec= new double[Integrator.ydim]{};    double* left_stream_sen= new double[Integrator.ydim]{};
double* right_stream_rec= new double[Integrator.ydim]{};   double* right_stream_sen= new double[Integrator.ydim]{};


MPI_Cart_coords(subdomain,my_rank,2,coord);                              // Gives the coordinates of the rank


Integrator.Initialise();                                  // Setting Initial Conditions of the vorticity field


for(int i=0;i<1;++i){



        if((coord[0]+coord[1])%2==0){
// Vorticity Communication
            if(coord[0]!=0)
            {MPI_Send(bottom_vort_sen,Integrator.xdim,MPI_DOUBLE,my_rank-Integrator.Px,1,MPI_COMM_WORLD);
            MPI_Send(bottom_stream_sen,Integrator.xdim,MPI_DOUBLE,my_rank-Integrator.Px,1,MPI_COMM_WORLD);}
            if(coord[0]!=Integrator.Py-1)
            {MPI_Send(top_vort_sen,Integrator.xdim,MPI_DOUBLE,my_rank+Integrator.Px,1,MPI_COMM_WORLD);
             MPI_Send(top_stream_sen,Integrator.xdim,MPI_DOUBLE,my_rank+Integrator.Px,1,MPI_COMM_WORLD);}
            if(coord[1]!=Integrator.Px-1)
            {MPI_Send(right_vort_sen,Integrator.ydim,MPI_DOUBLE,my_rank+1,1,MPI_COMM_WORLD);
            MPI_Send(right_stream_sen,Integrator.ydim,MPI_DOUBLE,my_rank+1,1,MPI_COMM_WORLD);}
            if(coord[1]!=0)
            {MPI_Send(left_vort_sen,Integrator.ydim,MPI_DOUBLE,my_rank-1,1,MPI_COMM_WORLD);
            MPI_Send(left_stream_sen,Integrator.ydim,MPI_DOUBLE,my_rank-1,1,MPI_COMM_WORLD);}

            if(coord[0]!=0)
            {MPI_Recv(bottom_vort_rec,Integrator.xdim,MPI_DOUBLE,my_rank-Integrator.Px,1,MPI_COMM_WORLD,&stats[0]);
            MPI_Recv(bottom_stream_rec,Integrator.xdim,MPI_DOUBLE,my_rank-Integrator.Px,1,MPI_COMM_WORLD,&stats[4]);}
            if(coord[0]!=Integrator.Py-1)
            {MPI_Recv(top_vort_rec,Integrator.xdim,MPI_DOUBLE,my_rank+Integrator.Px,1,MPI_COMM_WORLD,&stats[1]);
            MPI_Recv(top_stream_rec,Integrator.xdim,MPI_DOUBLE,my_rank+Integrator.Px,1,MPI_COMM_WORLD,&stats[5]);}
            if(coord[1]!=Integrator.Px-1)
            {MPI_Recv(right_vort_rec,Integrator.ydim,MPI_DOUBLE,my_rank+1,1,MPI_COMM_WORLD,&stats[2]);
            MPI_Recv(right_stream_rec,Integrator.ydim,MPI_DOUBLE,my_rank+1,1,MPI_COMM_WORLD,&stats[6]);}
            if(coord[1]!=0)
            {MPI_Recv(left_vort_rec,Integrator.ydim,MPI_DOUBLE,my_rank-1,1,MPI_COMM_WORLD,&stats[3]);
            MPI_Recv(left_stream_rec,Integrator.ydim,MPI_DOUBLE,my_rank-1,1,MPI_COMM_WORLD,&stats[7]);}


        } else if((coord[0]+coord[1])%2==1){
// Vorticity Communication
            if(coord[0]!=Integrator.Py-1)
            {MPI_Recv(top_vort_rec,Integrator.xdim,MPI_DOUBLE,my_rank+Integrator.Px,1,MPI_COMM_WORLD,&stats[1]);
            MPI_Recv(top_stream_rec,Integrator.xdim,MPI_DOUBLE,my_rank+Integrator.Px,1,MPI_COMM_WORLD,&stats[5]);}
            if(coord[0]!=0)
            {MPI_Recv(bottom_vort_rec,Integrator.xdim,MPI_DOUBLE,my_rank-Integrator.Px,1,MPI_COMM_WORLD,&stats[0]);
            MPI_Recv(bottom_stream_rec,Integrator.xdim,MPI_DOUBLE,my_rank-Integrator.Px,1,MPI_COMM_WORLD,&stats[4]);}
            if(coord[1]!=0)
            {MPI_Recv(left_vort_rec,Integrator.ydim,MPI_DOUBLE,my_rank-1,1,MPI_COMM_WORLD,&stats[3]);
            MPI_Recv(left_stream_rec,Integrator.ydim,MPI_DOUBLE,my_rank-1,1,MPI_COMM_WORLD,&stats[7]);}
            if(coord[1]!=Integrator.Px-1)
            {MPI_Recv(right_vort_rec,Integrator.ydim,MPI_DOUBLE,my_rank+1,1,MPI_COMM_WORLD,&stats[2]);
            MPI_Recv(right_stream_rec,Integrator.ydim,MPI_DOUBLE,my_rank+1,1,MPI_COMM_WORLD,&stats[6]);}

            if(coord[0]!=Integrator.Py-1)
            {MPI_Send(top_vort_sen,Integrator.xdim,MPI_DOUBLE,my_rank+Integrator.Px,1,MPI_COMM_WORLD);
            MPI_Send(top_stream_sen,Integrator.xdim,MPI_DOUBLE,my_rank+Integrator.Px,1,MPI_COMM_WORLD);}
            if(coord[0]!=0)
            {MPI_Send(bottom_vort_sen,Integrator.xdim,MPI_DOUBLE,my_rank-Integrator.Px,1,MPI_COMM_WORLD);
            MPI_Send(bottom_stream_sen,Integrator.xdim,MPI_DOUBLE,my_rank-Integrator.Px,1,MPI_COMM_WORLD);}
            if(coord[1]!=0)
            {MPI_Send(left_vort_sen,Integrator.ydim,MPI_DOUBLE,my_rank-1,1,MPI_COMM_WORLD);
            MPI_Send(left_stream_sen,Integrator.ydim,MPI_DOUBLE,my_rank-1,1,MPI_COMM_WORLD);}
            if(coord[1]!=Integrator.Px-1)
            {MPI_Send(right_vort_sen,Integrator.ydim,MPI_DOUBLE,my_rank+1,1,MPI_COMM_WORLD);
            MPI_Send(right_stream_sen,Integrator.ydim,MPI_DOUBLE,my_rank+1,1,MPI_COMM_WORLD);}

       }


cout<<top_stream_rec[2];
     Integrator.Vort_n(vort_sub_old,stream_sub,bottom_stream_rec, top_stream_rec, right_stream_rec, left_stream_rec);
    //  Integrator.Boundary_Vort(vort_sub_old,stream_sub,coord);
    //  Integrator.Vort_n_plus(vort_sub_new, vort_sub_old, stream_sub, bottom_stream_rec, top_stream_rec, right_stream_rec, left_stream_rec,
              //                      bottom_vort_rec, top_vort_rec, right_vort_rec, left_vort_rec, coord);


 Integrator.Send_Vort(vort_sub_old,bottom_vort_sen,top_vort_sen, right_vort_sen, left_vort_sen);

}



//MPI_Gather(vort_sub_new,gr_l_poin,MPI_DOUBLE,vort,gr_l_poin,MPI_DOUBLE,0,MPI_COMM_WORLD);


MPI_Finalize();

	return 0;
}
