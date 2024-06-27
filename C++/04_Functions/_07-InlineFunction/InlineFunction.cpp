#include <iostream>
using namespace std;

/**
 * Definition of the inline function. Definition appears before the function is called, so a
 * function prototype is not required. First line of the function definition acts as a prototype
 */
inline double cube(const double side){
    return side * side * side;  // calculate cube
}

int main(){
    double sideValue;
    cout << "Enter the side length of your cube: ";
    cin >> sideValue;

    // Calculate cube of sideValue and display result
    cout << "Volume of cube with side " << sideValue << " is " << cube(sideValue) << endl;
}