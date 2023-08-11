default: Cavity

LidDrivenCavitySolver.o: LidDrivenCavitySolver.cpp
	g++ -std=c++11 -Wall -O2 -o LidDrivenCavitySolver.o -c LidDrivenCavitySolver.cpp

LidDrivenCavity.o: LidDrivenCavity.cpp LidDrivenCavity.h
	g++ -std=c++11 -Wall -O2 -o LidDrivenCavity.o -c LidDrivenCavity.cpp

Poisson_Solver.o: Poisson_Solver.cpp LidDrivenCavity.h
	g++ -std=c++11 -Wall -O2 -o Poisson_Solver.o -c Poisson_Solver.cpp

Cavity: LidDrivenCavitySolver.o LidDrivenCavity.o Poisson_Solver.o
	g++ -o Cavity LidDrivenCavitySolver.o LidDrivenCavity.o Poisson_Solver.o -llapack -lblas

Clean:
	rm *.o Cavity
