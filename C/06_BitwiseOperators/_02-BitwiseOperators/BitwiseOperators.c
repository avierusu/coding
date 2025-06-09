// Using the bitwise AND, bitwise inclusive OR, bitwise
// exclusive OR, and bitwise complement operators

#include <stdio.h>

// Function prototype
void displayBits(unsigned int value);

int main(){
    // Demonstrate bitwise AND (&)
    unsigned int num = 65535;
    unsigned int mask = 1;
    printf("The result of combining the following\n");
    displayBits(num);
    displayBits(mask);
    printf("using the bitwise AND operator & is\n");
    displayBits(num & mask);
    printf("\n");

    // Demonstrate bitwise inclusive OR (|)
    num = 15;
    unsigned int setBits = 241;
    printf("The result of combining the following\n");
    displayBits(num);
    displayBits(setBits);
    printf("using the bitwise inclusive OR operator | is\n");
    displayBits(num | setBits);
    printf("\n");

    // Demonstrate bitwise exclusive OR (^)
    num = 139;
    unsigned int num2 = 199;
    printf("The result of combining the following\n");
    displayBits(num);
    displayBits(num2);
    printf("using the bitwise exclusive OR operator ^ is\n");
    displayBits(num ^ num2);
    printf("\n");

    // Demonstrate bitwise compliment (~)
    num = 21845;
    printf("The one\n");
    displayBits(num);
    printf("is\n");
    displayBits(~num);
    printf("\n");

    return 0;
}

// Display bits of an unsigned int value
void displayBits(unsigned int value){
    // Define displayMask and left shift 31 bits
    unsigned int displayMask = 1 << 31;

    printf("%10u = ", value);

    // Loop through bits
    for (unsigned int character = 1; character <= 32; character++){
        putchar(value & displayMask ? '1' : '0');
        value <<= 1;    // Shift value left by 1

        // Output a space after 8 bits
        if (character % 8 == 0){
            putchar(' ');
        }
    }

    putchar('\n');
}