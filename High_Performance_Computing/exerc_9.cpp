#include <iostream>
#include <math.h>
#include <limits>


using namespace std;

double cel_far(double temp)         // Function which converts the temperatures from Celsius to Fahrenheit
{
  return 9./5.*temp+32;
}

double far_cel(double temp)         // Function which converts the temperatures from Fahrenheit to Celsius
{
  return 5./9.*(temp-32);
}

int main()
{
    int option;
    double init_temp,temperature;

    while (true)
    {
        cout<<"Press 1 for Celsius to Fahrenheit, 2 for Fahrenheit to Celsius: ";
        cin>>option;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');                              // Clears whatever is after the first input

        if (option==1)
        {
            try
            {
            cout<<"Insert the value of temperature to be converted: ";
            cin>>init_temp;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if(init_temp<-273.15)                                                         // We have a logic error
            {
                throw logic_error("Temperature in Celsius must be > -273.15");            // throw 99 or logic_error("Temperature in Celsius must be > -273.15")
            }
            temperature=cel_far(init_temp);                                               // These commands are executed if the logic above is correct
            cout<<"The temperature in Fahrenheit is : "<<temperature<<endl;
            break;
            }
            catch(const logic_error& e)                                                   // if the logic is incorrect then assign logic_error to e or catch(double x)
            {
                cout<<"Error: "<<e.what()<<endl;                                          // displays e or cout<<x
                continue;
            }
            
        }
        else if (option==2)
        {
            try
            {
            cout<<"Insert the value of temperature to be converted: ";
            cin>>init_temp;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if(init_temp<-459.67)
            {
                throw logic_error("Temperature in Fahrenheit must be > -459.67");
            }
            temperature=far_cel(init_temp);
            cout<<"The temperature in Celsius is : "<<temperature<<endl;
            break;
            }
            catch(const logic_error& e)
            {
                cout<<"Error: "<<e.what()<<endl;
                continue;
            }
        }
        
    }
    return 0;
}