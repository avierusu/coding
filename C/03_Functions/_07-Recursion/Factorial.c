// Recursive function factorial

#include <stdio.h>

unsigned long long int factorial(int number);

int main(void){
    // calculate factorials of 0 through 21
    for(int i = 0; i <= 21; i++){
        printf("%d! = %llu\n", i, factorial(i));
    }
}

unsigned long long int factorial(int number){
    if(number <= 1){
        return 1;                                   // base cases: 0! = 1 and 1! = 1
    } else {
        return (number * factorial(number - 1));    // recursive step
    }
}