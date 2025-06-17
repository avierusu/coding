/**
 * This program shows the difference between
 * passing arguments by value vs by reference
 * to a function, using pointers.
 * 
 * By passing arguments to a function by reference,
 * we can change the values of the variables themselves.
 * 
 * 
 * 
 * A practical example of a function that accepts arguments by value
 * (instead of by reference) is a function that calculates something
 * without modifying the original data
 * 
 * Why this makes sense: For small types like float, passing by value is cheap
 * (in terms of performance) and avoids accidental modification of the original data.
 * Practicality: This is common in functions that do not need to alter the input
 * and when the input type is inexpensive to copy.
 * 
 */

#include <stdio.h>

// Function signatures
void swapByValue(int num1, int num2);
void swapByReference(int *addr1, int *addr2);

int main(){
    // Define two integers to be swapped
    int score1 = 10, score2 = 53;
    printf("\nBefore swapping:\nScore 1 = %d\nScore 2 = %d\n", score1, score2);

    // Swap the values by passing them to a swap function by value
    // This will not swap the values
    swapByValue(score1, score2);
    printf("\nAfter swapping by passing variables to a function by value:");
    printf("\nScore 1 = %d\nScore 2 = %d\n", score1, score2);

    // Swap the values by passing them to a swap function by reference
    // This will swap the values
    swapByReference(&score1, &score2);
    printf("\nAfter swapping by passing variables to a function by reference:");
    printf("\nScore 1 = %d\nScore 2 = %d\n", score1, score2);

    return 0;
}

// This function is supposed to swap two integers,
// but since we pass arguments by value, the actual
// variables are unchanged
void swapByValue(int num1, int num2){
    int temp;
    temp = num1;
    num1 = num2;
    num2 = temp;
}

// This function swaps two integers. Since we pass
// arguments by reference, the original variables
// will also be swapped
void swapByReference(int *addr1, int *addr2){
    int temp;
    temp = *addr1;
    *addr1 = *addr2;
    *addr2 = temp;
}