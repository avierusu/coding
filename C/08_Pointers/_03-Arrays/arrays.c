/**
 * An array name is a constant address (or pointer)
 * that always points to the first element of the array
 */

#include <stdio.h>

// Function prototype
float avg(int array[], int size);

int main(){
    // Declare a variable to store the total number of grades and their average
    int gradeCount;
    float average;

    // Prompt and store number of grades
    printf("Enter how many grades to find the average of: ");
    scanf("%d", &gradeCount);

    // Declare an array to store all the grades
    int grades[gradeCount];

    printf("\n");
    // Prompt and store each grade
    for (int index = 0; index < gradeCount; index++){
        printf("Enter grade (%d/%d): ", (index + 1), gradeCount);
        scanf("%d", &grades[index]);
    }

    // Calculate average
    average = avg(grades, gradeCount);

    printf("\nThe average is %f\n", average);

    return 0;
}

// Find the average of an integer of arrays
float avg(int array[], int size){
    // Declare the pointer to the array and the sum of the ints
    int *arrPointer, sum = 0;
    arrPointer = array;

    // Find the sum of all ints
    for (int index = 0; index < size; index++){
        sum += *(arrPointer + index);
    }

    // Find the average and return it
    return ((float) sum / size);
}