// Using the Unary Scope Resolution Operator "::" to refer to a global variable

#include <iostream>
using namespace std;

int number = 7;

int main(){
    double number = 10.5;

    cout << "Local double value of number = " << number
         << "\nGlobal int value of number = " << ::number << endl;
}