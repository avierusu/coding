// Display an unsigned int in bits

#include <stdio.h>
#include <limits.h>

// Function prototype
void displayBits(unsigned int value);

int main(){
    // Variable to hold user intput
    unsigned int num = 0;

    printf("Enter a non-negative int: ");
    scanf("%u", &num);
    displayBits(num);

    return 0;
}

// Display bits of an unsigned int value
void displayBits(unsigned int value){
    // Define displayMask and left shift 31 bits
    unsigned int displayMask = 1 << (CHAR_BIT * sizeof(unsigned int) - 1);

    printf("%10u = ", value);

    // Loop through bits
    for (unsigned int character = 1; character <= (CHAR_BIT * sizeof(unsigned int)); character++){
        putchar(value & displayMask ? '1' : '0');
        value <<= 1;    // Shift value left by 1

        // Output a space after 8 bits
        if (character % 8 == 0){
            putchar(' ');
        }
    }

    putchar('\n');
}