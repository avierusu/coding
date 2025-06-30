/**
 * This program shows how to use the arrow operator "->"
 * when accessing members of a structure from its pointer
 * For example:
 * student.member
 * vs
 * pointer->member
 */

#include <stdio.h>

// Define our struct type "complex"
struct complex {
    float real;
    float imaginary;
};

// Use typedef to create a new type name for struct complex
typedef struct complex complexNum;

// Function prototype
void add(complexNum *num1, complexNum *num2, complexNum *result);

int main(){
    // Declare three complex numbers; two to add and one containing the sum
    complexNum complex1, complex2, sum;

    // Prompt for and store the two complex numbers
    printf("\nEnter the first complex number (in the form \"#.# #.#\"): ");
    scanf("%f %f", &complex1.real, &complex1.imaginary);
    printf("Enter the second complex number (in the form \"#.# #.#\"): ");
    scanf("%f %f", &complex2.real, &complex2.imaginary);

    // Add the two complex numbers
    add(&complex1, &complex2, &sum);

    // Display the result
    printf("\nThe sum is: %f %fi\n", sum.real, sum.imaginary);

    return 0;
}

// Add two complex numbers
void add(complexNum *num1, complexNum *num2, complexNum *result){
    // Add the two parts of the complex numbers
    result->real = num1->real + num2->real;
    result->imaginary = num1->imaginary + num2->imaginary;
}