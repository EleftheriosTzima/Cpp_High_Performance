/* Serial Code for the Lid-Driven Cavity Problem
Eleftherios Tzima
CID:01807292
*/

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include "LidDrivenCavity.h"


using namespace std;

int main(int argc,char* argv[])
{

// Command Line Input (Lx Ly Nx Ny Px Py dy T Re). Call the constructor to define the private variables of the Integrator object.
LidDrivenCavity Integrator (atof(argv[1]),atof(argv[2]),(int)atof(argv[3]),(int)atof(argv[4]),(int)atof(argv[5]),(int)atof(argv[6]),atof(argv[7]),atof(argv[8]),atof(argv[9]));
// Initialising some variables which will be used below.
Integrator.initialise();
// Call the constructor to define the private variables of the Solver object. As input variables are chosen the public variables of the Integrator object.
Poisson_Solver Solver (Integrator);

int N=Integrator.xdim*Integrator.ydim;                               // Total number of nodes for global domains
int n=(Integrator.ydim-2)*(Integrator.xdim-2);                       // Number of nodes for the interior domains.

double* vort_old=new double[N]{};                                    // Global vorticity matrix for the old time step
double* vort_new=new double[N]{};                                    // Global vorticity matrix for the new time step
double* stream=new double[N]{};                                      // Global stream function matrix

double* stream_sub=new double[n]{};                                  // Interior stream function matrix
double* Coefficient_1=new double[(3*(Integrator.xdim-2)+1)*n]{};     // Dummy matrix used to store horizontally the coefficients of the poisson problem as shown in page 208 of the notes.
double* Coefficient_2=new double[(3*(Integrator.xdim-2)+1)*n]{};     // This matrix is used to store the values of Coefficient_1 columnwise in order to be used in LAPACK function.

double* Force=new double[n]{};                                       // Force vector. Contains the internal values of the global vortex matrix.
int* piv=new int[n]{};                                               // pivot vevtor used for LU decomposition with patrial pivoting. (LAPACK function)
int info=0;

// The goal of this function is to create a vector which contains the coefficients of the Poisson problem (Matrix as output).
Solver.Matrix_A(Coefficient_1,Coefficient_2,Integrator.xdim-2,Integrator.ydim-2);

// Performs LU decomposition and stores the values in the Coefficient_2 matrix.
F77NAME(dgbtrf)(n, n, Integrator.xdim-2, Integrator.xdim-2,Coefficient_2,3*(Integrator.xdim-2)+1, piv, info);

// Progressing the solution through time.
for(int i=0;i<Integrator.chronos;++i){

// Calculates interior vorticity field at time t.
        Integrator. Vort_n(vort_old,stream);
// Apply Boundary Conditions to vorticity field.
        Integrator.Boundary_Vort(vort_old,stream);
// Calculates interior vorticity field at time t+1.
        Integrator.Vort_n_new(vort_new, vort_old, stream);
// Coppies the matrix of the vorticity field, at time t+1, to that of time t.
        Integrator.coppy_vort(vort_new,vort_old,Integrator.xdim,Integrator.ydim);


// ------------------------------------------------ Poisson Section -------------------------------------------------------------//
// This function creates the Force vector (to be used in the poisson solver or dgbtrs LAPACK) which contains the interal points of the vortex field (vort_new).
        Solver.Force(Force, vort_new);

// Solves the linear system of equations of the Poisson problem.
        F77NAME(dgbtrs)('N', n, Integrator.xdim-2, Integrator.xdim-2, 1, Coefficient_2, 3*(Integrator.xdim-2)+1, piv, Force, n, info);

// This function assembles the Global stream function. Force contains the solution of the Poisson problem, which is the internal stream function subamatrix.
        Solver.Assembly_stream(stream, Force);
// ---------------------------------------------------------------------------------------------------------------------------------//
}

//------------------------------------------ Output Section--------------------------------------------------------------------//
ofstream LoL("Stream.txt", ios::out | ios::trunc);  // opens a file called data for output only. If it exists it is deleted
if(LoL.good())                                      // test if the file can open
{
  for(int i=0;i<Integrator.xdim*Integrator.ydim;++i)
  {
      LoL.precision(7);                              // set the precision
      LoL<<setw(10)<<stream[i]<<"  ";
        if((i+1)%(Integrator.xdim)==0)
        LoL<<endl;
  }
  LoL.close();                                      // closes the file
}
else
{
  cout<<"Could not open the file";
}
//----------------------------------------------------------------------------------------------------------------------------//

// Frees the leap
delete[] vort_old; delete[] vort_new; delete[] stream; delete[] stream_sub; delete[] Coefficient_1; delete[] Coefficient_2; delete[] Force; delete[] piv;

	return 0;
}
