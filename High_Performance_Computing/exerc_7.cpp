#include <iostream>
#include <math.h>
#include <fstream>
#include <iomanip>

using namespace std;

int main()
{
    ifstream LoL("sin.txt");
    float n,data;

    if(LoL.good())
    {
        while(true)
        {
            LoL>>n>>data;                   // the first value of column is stored in n and the second in data
            if(LoL.eof())                  // if the end of the file is reached
            break;
            cout<<n<<"  "<<data<<endl;    // print the output on the screen
        }
    }


}