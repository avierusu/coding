// Function overloading
// Define multiple functions of the same name but different signatures

#include <iostream>
using namespace std;

// function square for int values
int square(int x){
    cout << "square of integer " << x << " is ";
    return x * x;
}

// function square for double values
double square(double y){
    cout << "square of double " << y << " is ";
    return y * y;
}

int main(){
    cout << square(7);      // calls int version
    cout << endl;
    cout << square(7.5);    // calls double version
    cout << endl;
}