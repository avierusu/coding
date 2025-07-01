/**
 * This program uses the function calloc
 * to allocate memory for an array of pointers,
 * each of which point to an array, creating
 * a 2D array
 */

#include <stdio.h>
#include <stdlib.h>

// Function prototypes
int **allocate(int rows, int columns);
void readData(int **ptr, int rows, int columns);
void printData(int **ptr, int rows, int columns);

int main(){
    // Initialize a pointer to an array of pointers (2D array)
    // as well as a height and width for our 2D array
    int **pointer, height, width;

    // Prompt for and store number of rows and columns
    printf("Enter the number of rows and columns, separated by a space:\n");
    scanf("%d %d", &height, &width);
    
    // Allocate memory for the 2D array
    pointer = allocate(height, width);
    // Read data from the user
    printf("\nEnter data:\n");
    readData(pointer, height, width);
    // Display the data
    printf("\nThe array read as:\n");
    printData(pointer, height, width);

    // Free the allocated memory
    free(pointer);

    return 0;
}

// Allocate enough memory for a 2D array with
// dimensions: rows x columns
int **allocate(int rows, int columns){
    // Declare a pointer to a pointer
    int **ptr;

    // Allocate enough memory to contain 'rows' number
    // of int pointers (Array of pointers)
    ptr = (int**) calloc(rows, sizeof(int*));

    // Allocate memory to contain 'columns' number of
    // integers (array of integers)
    for (int currRow = 0; currRow < rows; currRow++){
        ptr[currRow] = (int*) calloc(columns, sizeof(int));
    }

    return ptr;
}

// Store data provided by the user
void readData(int **ptr, int rows, int columns){
    // Loop through each row
    for (int currRow = 0; currRow < rows; currRow++){
        // Loop through each column
        for (int currColumn = 0; currColumn < columns; currColumn++){
            // Store user input
            scanf("%d", &ptr[currRow][currColumn]);
        }
    }
}

// Display the data to the console in a grid
void printData(int **ptr, int rows, int columns){
    // Loop through each row
    for (int currRow = 0; currRow < rows; currRow++){
        // Loop through each column
        for (int currColumn = 0; currColumn < columns; currColumn++){
            // Display data
            printf("%5d ", ptr[currRow][currColumn]);
        }
        printf("\n");
    }
}