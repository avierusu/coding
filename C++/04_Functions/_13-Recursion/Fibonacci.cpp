/**
 * Recursive function fibonacci
 * 
 * The Fibonacci sequence is a sequence in which each number is the sum of the two preceding ones.
 * For example:
 * 0, 1, 1, 2, 3, 5, 8, 13, ...
 */

#include <iostream>
using namespace std;

unsigned long fibonacci(unsigned long); // function prototype

int main(){
    // calculate fibonacci values of 0 through 10
    for(unsigned int counter = 0; counter <= 10; counter++){
        cout << "fibonacci(" << counter << ") = " << fibonacci(counter) << endl;
    }

    cout << "\nfibonacci(20) = " << fibonacci(20) << endl;
    cout << "fibonacci(30) = " << fibonacci(30) << endl;
    cout << "fibonacci(35) = " << fibonacci(35) << endl;
}

// This function accepts an integer n and calculates the
// nth fibonacci number by recursively calling itself
unsigned long fibonacci(unsigned long number){
    if ( (number == 0) || (number == 1) ){
        return number;
    } else {
        return fibonacci(number - 1) + fibonacci(number - 2);
    }
}