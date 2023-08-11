/* Serial Code for the Lid-Driven Cavity Problem
Eleftherios Tzima
CID:01807292
*/

#pragma once

#include <string>
#include <math.h>
using namespace std;

#define F77NAME(x) x##_
extern "C" {


  void F77NAME(dgbtrf)(const int& M, const int& N, const int& KL, const int& KU, double * A,
                      const int& lda, int* ipiv, int& info);

  void F77NAME(dgbtrs)(const char& trans, const int& n, const int& KL, const int& KU, const int& nhrs,const double * A,
                      const int& lda,const int* ipiv, double* B, const int& ldb, int& info);

}


class LidDrivenCavity{

friend class Poisson_Solver;

private:
    int Nx,Ny,Px,Py;                            // For non-parallel Px=Py=0
    double Lx,Ly,Re;
    double U=1;
    double dx,dy,dt,T;

public:

    int xdim,ydim;                             // xdim: number of nodes in x direction. ydim: number of nodes in y direction,
    int chronos;                               // amount of time steps required to reach T

    //Constructor which initialises the above varialbes
    LidDrivenCavity(double a, double b, int c, int d, int e,int f, double g, double j, double k);

    // Defines the variables in the public section
    void initialise();
    // Coppy function. Coppies vector str1 to str2
    void coppy_vort(const double* str1,double* str2,int& xdim,int& ydim);
    // Applies the boundary conditions to the vortex vector.
    void Boundary_Vort(double* vort,double* stream);
    // Calculates interior vorticity at time t.
    void Vort_n(double* vort_sub_old,double* stream);
    // Calculates interior vorticity at time t+1.
    void Vort_n_new(double* vort_new,double* vort_old,double* stream);

};


class Poisson_Solver{

private:
  double dx,dy;
  int xdim, ydim;

public:
  // This is a Constructor which initialises its own variables by accessing the variables of the friend class LidDrivenCavity.
  Poisson_Solver(LidDrivenCavity Integrator);
  // The goal of this function is to create a vector which contains the coefficients of the Poisson problem (Matrix as output).
  void Matrix_A(double*A,double*Matrix,int Xdim,int Ydim);
  // This function creates the Force vector (to be used in the poisson solver or dgbtrs LAPACK) which contains the interal points of the vortex field (vort_new).
  void Force(double* Force,double* vort_new);
  // This function assembles the Global stream functin (internal domain+boundaries) by substituting its interior wirh the sub_stream matrix (contains interior points)
  void Assembly_stream(double* stream, double* stream_sub);

};
