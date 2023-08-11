default: Cavity

LidDrivenCavitySolver.o: LidDrivenCavitySolver.cpp
	mpicxx -std=c++11 -Wall -O2 -o LidDrivenCavitySolver.o -c LidDrivenCavitySolver.cpp -llapack -lblas

LidDrivenCavity.o: LidDrivenCavity.cpp LidDrivenCavity.h
	g++ -std=c++11 -Wall -O2 -o LidDrivenCavity.o -c LidDrivenCavity.cpp

Cavity: LidDrivenCavitySolver.o LidDrivenCavity.o
	mpicxx -o Cavity LidDrivenCavitySolver.o LidDrivenCavity.o

Clean:
	rm *.o Cavity
