#pragma once

#include <string>
using namespace std;

struct LidDrivenCavity{

    int Nx,Ny,Px,Py;
    double Lx,Ly,Re;
    double U=1;
    double dx,dy,dt,T;

    int xdim,ydim;
    int chronos;

    LidDrivenCavity(double a,double b,int c,int d,int e,int f,double g,double j,double k);
    void Boundary_Vort(double* vort_sub,double* stream_sub,int* coord);
    void Initialise();
    void Boundary(double* dummy,double* domain);
    void Vort_n(double* vort_sub_old,double* stream_sub,double* bottom_stream_rec, double* top_stream_rec, double* right_stream_rec, double* left_stream_rec);
    void Vort_n_plus(double* vort_sub_new,double* vort_sub_old,double* stream_sub,double* bottom_stream_rec_rec, double* top_stream_rec_rec, double* right_stream_rec_rec, double* left_stream_rec_rec,
                                 double* bottom_vort_rec,double* top_vort_rec,double* right_vort_rec,double* left_vort_rec,int* coord);

    void Send_Vort(double* vort_sub_old,double* bottom_sen,double* top_sen,double* right_sen, double* left_sen);

    void reshape_global (double* dummy,double* domain);



};


void coppy(const double* str1,double* str2,int n);





/*  Matrix visualisation
for(int i=0;i<gr_poin;++i){
        cout<<result[i]<<" ";
        if((i+1)%Solver.Nx==0)
    cout<<endl;
  }

    delete[] result;
}
*/
