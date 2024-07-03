/**
 * Function Template
 * Whereas Overloaded Functions are used to perform similar operations involving different logic
 * on different data types,
 * Function Templates are used when program logic and operations are identical for data types
 */

#include <iostream>
#include "maximum.h"
using namespace std;

int main(){
    // maximum with int values
    cout << "Input three integer values: ";
    int int1, int2, int3;
    cin >> int1 >> int2 >> int3;

    // invoke int version of maximum
    cout << "the maximum integer value is: " << maximum(int1, int2, int3);

    // maximum with double values
    cout << "\n\nInput three double values: ";
    double double1, double2, double3;
    cin >> double1 >> double2 >> double3;

    // invoke int version of maximum
    cout << "the maximum double value is: " << maximum(double1, double2, double3);

    // maximum with char values
    cout << "\n\nInput three characters: ";
    char char1, char2, char3;
    cin >> char1 >> char2 >> char3;

    // invoke int version of maximum
    cout << "the maximum character value is: " << maximum(char1, char2, char3);
}