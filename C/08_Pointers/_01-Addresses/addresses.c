#include <stdio.h>

int main(){
    int num;

    printf("The address of num before assigning a value is: %p\n", &num);

    num = 10;

    int *numPtr;
    numPtr = &num;

    // %p is used to display memory address in hex format
    printf("\nThe value in the variable num is: %d\n", num);
    printf("The address of the variable num using &num is: %p\n", &num);
    printf("The value in the variable numPtr is: %p\n", numPtr);
    printf("The address of the variable numPtr using &numPtr is: %p\n", &numPtr);
    printf("The value that numPtr points to using *numPtr is: %d\n", *numPtr);
    printf("The value that numPtr points to using *&num is: %d\n", *&num);

    // Changing value of num using its pointer
    *numPtr = 20;
    printf("\nThe value in the variable num is: %d\n", num);

    return 0;
}