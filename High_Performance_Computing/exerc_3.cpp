
#include <iostream>
#include <limits>
#include <string>
#include <sstream>

using namespace std;
int main() 
{
string vStr;                 // String for storing input
int vNum;                   // Target variable for input
getline(cin,vStr);                 // Read input from the user
stringstream S(vStr);       // Initialise stringstream with user input
S >> vNum;                   // Extract to the target variable
cout<<vNum<<endl;
return 0;
}
