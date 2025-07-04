/**
 * A pointer to void is a general-purpose pointer used
 * to hold references to any data type.
 * 
 * - A pointer to void will have the same representation
 * as a pointer to char
 * - A pointer to void will never be equal to another pointer.
 * However, two void pointers assigned a NULL value will
 * be equal
 * 
 * This program will showcase that any pointer can be assigned
 * to a pointer to void, and can then be cast back to its original
 * pointer type, keeping the original pointer value.
 */

#include <stdio.h>

int main(){
    // Initialize an integer to create a pointer for
    int age;
    // Initialize an int pointer and assign the address of age to it
    int *intPtr = &age;
    // Display the contents of intPtr before
    printf("Value of intPtr: %p\n", intPtr);
    
    // Initialize a void pointer and assign the address in intPtr to it
    void *voidPtr = intPtr;
    // Typecast and assign voidPtr to intPtr
    intPtr = (int*) voidPtr;
    // Display the contents of intPtr after
    printf("Value of intPtr: %p\n", intPtr);

    return 0;
}