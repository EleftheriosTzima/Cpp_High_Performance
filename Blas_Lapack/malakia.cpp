# include <iostream>
# include <math.h>
# include <fstream>
# include <iomanip>
# include "declarations.h"
using namespace std;

int main()
{
  double* p_old=new double[3]{0,1,2};
  double* p_new=new double[3]{};

  coppy(p_old,p_new,3);

  p_new[0]=10;

  cout<<p_old[0]<<" "<<p_old[1]<<" "<<p_old[2]<<" "<<endl;
  cout<<p_new[0]<<" "<<p_new[1]<<" "<<p_new[2]<<" "<<endl;
}
