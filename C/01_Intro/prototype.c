/*
A function prototype in C is a function declaration specifying the function's return type,
name, and the number and types of its parameters.
*/
#include <stdio.h>  // Must be included for all C files
#include <iostream> // Must be included for any C++ style input and output character streams (cin cout)
                    // When this header is included, compile code using g++

int sum(int num1, int num2);

int main(){
    std::cout << sum(1, 2);

    return 0;
}

int sum(int num1, int num2){
    return num1 + num2;
}