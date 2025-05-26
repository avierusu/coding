/**
 * A Bubble Sort requires multiple passes through the array.
 * On each pass, pairs of elements are compared with each other.
 * If they are in ascending order or equal, they are left as is.
 * If they are in descending order, they are swapped
 */

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <chrono>
using namespace std;

#define ARR_SIZE 1000
#define RANGE 9999

void printArray(int arr[], size_t size);
void populateArray(int* inArray, size_t size, int min, int max);
void bubbleSort(int* inArray, size_t size);

int main(){
    // Create an unsorted array that will be sorted
    // int nums[ARR_SIZE] = {2, 6, 4, 8, 10, 12, 89, 68, 45, 37};
    int nums[ARR_SIZE] = {0};
    populateArray(nums, ARR_SIZE, -RANGE, RANGE);

    // Display the original order of the array
    printf("\nData items in original order:\n");
    printArray(nums, ARR_SIZE);

    // Check how long the bubble sort takes
    // Record the start time
    auto start = chrono::high_resolution_clock::now();

    // Sort with bubble sort
    bubbleSort(nums, ARR_SIZE);

    // Record the end time
    auto end = chrono::high_resolution_clock::now();
    // Calculate the time taken in seconds (since clock() returns clock ticks)
    chrono::duration<double> duration = end - start;
    
    // Display the sorted array
    printf("\n\n\nData items in ascending order:\n");
    printArray(nums, ARR_SIZE);

    // Display execution time
    printf("\n");
    printf("\n\nExcecution time: %.5f nanoseconds\n", duration.count() * 1000 * 1000);
    cout << "Excecution time: " << duration.count() * 1000 * 1000 << " nanoseconds" << endl;

    return 0;
}

// Prints the contents of the array with 4 spaces for each number
void printArray(int arr[], size_t size){
    for (size_t index = 0; index < size; index++){
        printf("%6d", arr[index]);
    }
}

// Populates the array with random values
void populateArray(int* inArray, size_t size, int min, int max){
    // Set the seed of rand to be random
    srand(time(NULL));
    
    // Generate values
    for (size_t index = 0; index < size; index++){
        inArray[index] = rand() % (max - min + 1) + min;
    }
}

// Sorts the array using the Bubble Sort method
void bubbleSort(int* inArray, size_t size){
    // Bubble sort
    // Loop to control the number of passes
    for (int pass = 1; pass < size; pass++){
        // Print how many times the loop passes through the array (for debug mode)
        // printf("\nPass %d:\n", pass);

        // Loop to control the number of comparisons per pass
        for (size_t index = 0; index < (size - 1); index++){
            // Compare adjacent elements and swap if necessary
            if (inArray[index] > inArray[index + 1]){
                // Swap values
                int hold = inArray[index];
                inArray[index] = inArray[index + 1];
                inArray[index + 1] = hold;
                

                // Print after each swap (for debug mode)
                // for (size_t counter = 0; counter < ARR_SIZE; counter++){
                //     printf("%4d", nums[counter]);
                // }
                // printf("\n");
            }
        }
    }
}