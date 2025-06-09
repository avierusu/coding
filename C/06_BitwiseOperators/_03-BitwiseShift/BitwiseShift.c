// Display an unsigned int in bits

#include <stdio.h>

// Function prototype
void displayBits(unsigned int value);

int main(){
    unsigned int num = 960;

    // Demonstrate bitwise left shift
    printf("\nThe result of left shifting\n");
    displayBits(num);
    printf("8 positions using the left shift operator << is\n");
    displayBits(num << 8);

    // Demonstrate bitwise right shift
    printf("\nThe result of right shifting\n");
    displayBits(num);
    printf("8 positions using the right shift operator >> is\n");
    displayBits(num >> 8);

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