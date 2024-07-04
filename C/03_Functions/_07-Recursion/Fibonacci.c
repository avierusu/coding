/**
 * Recursive function fibonacci
 * 
 * The Fibonacci sequence is a sequence in which each number is the sum of the two preceding ones.
 * For example:
 * 0, 1, 1, 2, 3, 5, 8, 13, ...
 */

#include <stdio.h>

unsigned long long int fibonacci(int n);    // function prototype

int main(void){
    // calculate fibonacci values of 0 through 10
    for(int number = 0; number <= 10; number++){
        printf("Fibonacci(%d) = %llu\n", number, fibonacci(number));
    }

    printf("Fibonacci(20) = %llu\n", fibonacci(20));
    printf("Fibonacci(30) = %llu\n", fibonacci(30));
    printf("Fibonacci(40) = %llu\n", fibonacci(40));
}

unsigned long long int fibonacci(int n){
    if(n == 0 || n == 1){
        return n;                                       // base case
    } else {
        return fibonacci (n - 1) + fibonacci (n - 2);   // recursive step
    }
}