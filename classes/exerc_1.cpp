# include <iostream>
# include <string>
using namespace std;

class Complex {

  double x,y;                           // private members

public:

     Complex (){                        // Constructor for default initialisation
       x=0;
       y=0;
    }
     Complex (double a,double b){      // Constructor for assiging values
       x=a;
       y=b;
    }
    ~Complex (){ }                     // Destructor not used for this class


    double get_real(void){
      return x;
    }
    double get_imag(void){
      return y;
    }

    Complex operator+ (const Complex& bara){   // Complex operator ... c=a+b   where c=temp, this refers to operator+ which is a and bara is the object b.
    Complex temp;
    temp.x=x+bara.x;
    temp.y=y+bara.y;
    return(temp);
    }

    Complex operator* (const Complex& bara){  // const is used to prevent inadvrtently changes of the class bara when it is called by reference. Avoid copying the class.
    Complex temp;
    temp.x=x*bara.x-y*bara.y;
    temp.y=y*bara.x+x*bara.y;
    return(temp);
    }

    friend ostream& operator<< (ostream& out, const Complex& bara){
    out<<bara.x<<"+"<<bara.y<<"i"<<endl;
      return out;
    }


    void add () {
      cout<<"Multiplication is equal to: "<<x<<"+"<<y<<"i"<<endl;
    }

    void mult() {
      cout<<"Multiplication is equal to: "<<x<<"+"<<y<<"i"<<endl;
    }

};

int main(){

Complex a (1.0,2.0);
Complex b (2.0,3.0);
Complex addition,multiplication;

addition=a+b;
multiplication=a*b;

cout<<addition;
cout<<multiplication;

cout<<"Imaginary part of multiplication is: "<<multiplication.get_imag()<<endl;
}
