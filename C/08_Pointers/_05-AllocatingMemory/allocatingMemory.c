/**
 * This program showcases dynamic memory allocation
 * using the function malloc
 * We will take the average of students heights.
 * The user will specify how many students and their heights
 */

#include <stdio.h>
#include <stdlib.h>

int main(){
    // Declare variables
    int numStudents;
    float *height, sum = 0, average;

    // Prompt for and store the number of students
    printf("Enter the number of students to average the heights of: ");
    scanf("%d", &numStudents);

    // Allocate enough memory to store numStudents
    // amount of float variables and store the address
    // into height
    height = (float *) malloc(numStudents * sizeof(float));

    // Prompt for the height of numStudents students
    printf("Enter heights for %d students:\n", numStudents);
    for (int count = 0; count < numStudents; count++){
        printf("> ");
        scanf("%f", &height[count]);
        // Add each height to the sum
        sum += height[count];
    }

    // Calculate the average
    average = sum / (float) numStudents;

    // Display results
    printf("Average height = %f\n", average);

    // Free the memory previously allocated
    free(height);

    return 0;
}