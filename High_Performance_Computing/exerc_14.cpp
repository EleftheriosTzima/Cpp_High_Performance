#include <iostream>
#include <math.h>
#include <cstdlib>
#include <ctime>

using namespace std;

float minimum (float pArray[],int n)    // Minimum of an array
{
    float mini=pArray[0];

  for(int i=0;i<n-1;i++)
    {
        if(pArray[i]<=mini)
        {
            mini=pArray[i];
        }
        
    }

    return mini;
}

float maximum (float pArray[],int n)      // Maximum of an array
{
    float maxi=pArray[0];


  for(int i=0;i<n-1;i++)
    {
        if(pArray[i]>=maxi)
        {
            maxi=pArray[i];
        }
        
    }

    return maxi;
}


float mean (float pArray[],int n)          // Mean of an array
{
    float sum=0;
    float mean;

  for(int i=0;i<n-1;i++)
    {
        sum=sum+pArray[i];
        
    }

    mean=sum/n;

    return mean;
}

float insert(float pArray[],int p,float val)
{




}


int main()
{
    const int n=20;               // How many values we desire

    float* Array=new float[n];    // Request memory from the heap


 
    srand(time(0));           // modifies the rand() function to start by taking into account the clock
    for(int i=0;i<n;i++)
    {
        Array[i]=(float)rand()/(float)(RAND_MAX)*100;     //Generating random floating point 
        
        cout<<Array[i]<<endl;

    }


    cout<<"The minimum value is: "<<minimum(Array,n)<<endl;
    cout<<"The maximum value is: "<<maximum(Array,n)<<endl;
    cout<<"The mean value is: "<<mean(Array,n)<<endl;

    // Sorting algorithm of the array until p

    float val=10;
    int p=5;                // It should be less than n


delete [] Array;            // Discharge the memory

return 0;
}