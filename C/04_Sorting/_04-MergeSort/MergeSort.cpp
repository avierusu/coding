/**
 * Merge Sort recursively splits the array into two subarrays
 * of equal size, sorts the array, and merges them
 * (if the array is odd in size, one array is bigger)
 * 
 * The subarrays are split until they contain one value
 * When merging, the smallest element of each subarray are compared,
 * and the smallest gets placed in the first position. Then, the
 * larger gets compared with the next smallest in the other subarray,
 * and so on.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <iostream>
#include <chrono>
using namespace std;

#define ARR_SIZE 1000
#define RANGE 9999
// for debugging/demonstrating
#define IS_DEBUG false

void printArray(int arr[], size_t size);
void populateArray(int* inArray, size_t size, int min, int max);

void mergeSort(int* inArray, size_t size);
void sortSubArray(int* inArray, size_t low, size_t high);
void merge(int* inArray, size_t left, size_t middle1, size_t middle2, size_t right);
void displaySubArray(int* inArray, size_t left, size_t right);

int main(){
    // Create an unsorted array that will be sorted
    // int nums[ARR_SIZE] = {2, 6, 4, 8, 10, 12, 89, 68, 45, 37};
    int nums[ARR_SIZE] = {0};
    populateArray(nums, ARR_SIZE, -RANGE, RANGE);

    // Display the original order of the array
    printf("\nData items in original order:\n");
    printArray(nums, ARR_SIZE);

    // Check how long the sort takes
    // Record the start time
    auto start = chrono::high_resolution_clock::now();

    // Sort
    mergeSort(nums, ARR_SIZE);

    // Record the end time
    auto end = chrono::high_resolution_clock::now();
    // Calculate the time taken in seconds (since clock() returns clock ticks)
    chrono::duration<double> duration = end - start;
    
    // Display the sorted array
    printf("\n\nData items in ascending order:\n");
    printArray(nums, ARR_SIZE);

    // Display execution time
    printf("\nExcecution time: %.5f nanoseconds\n", duration.count() * 1000 * 1000);
    cout << "Excecution time: " << duration.count() * 1000 * 1000 << " nanoseconds" << endl;
    
    return 0;
}

// Prints the contents of the array with 4 spaces for each number
void printArray(int arr[], size_t size){
    for (size_t index = 0; index < size; index++){
        printf("%6d", arr[index]);
    }
    printf("\n\n");
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

// Sorts the array using the Merge Sort method
void mergeSort(int* inArray, size_t size){
    sortSubArray(inArray, 0, size - 1);
}

// Sorts a piece of the array
void sortSubArray(int* inArray, size_t low, size_t high){
    // Test base case: size of array = 1
    if ((high - low) >= 1){
        // If not base case:
        size_t middle1 = (low + high) / 2;
        size_t middle2 = middle1 + 1;

        // Output split step (for debugging/demonstrating)
        if (IS_DEBUG){
            printf("%s", "split:   ");
            displaySubArray(inArray, low, high);
            printf("%s", "\n         ");
            displaySubArray(inArray, low, middle1);
            printf("%s", "\n         ");
            displaySubArray(inArray, middle2, high);
            printf("\n");
        }

        // Split the array in half and sort each half recursively
        sortSubArray(inArray, low, middle1);
        sortSubArray(inArray, middle2, high);

        // Merge the two sorted arrays
        merge(inArray, low, middle1, middle2, high);
    }
}

// Merges two sorted subarrays into one sorted subarray
void merge(int* inArray, size_t left, size_t middle1, size_t middle2, size_t right){
    // Index into left subarray
    size_t leftIndex = left;
    // Index into right subarray
    size_t rightIndex = middle2;
    // Index into temporary array
    size_t combinedIndex = left;
    // Temporary array
    int tempArray[ARR_SIZE] = {0};

    // Output two subarrays before merging (for debugging/demonstrating)
    if (IS_DEBUG){
        printf("%s", "merge:   ");
        displaySubArray(inArray, left, middle1);
        printf("%s", "\n         ");
        displaySubArray(inArray, middle2, right);
        printf("\n");
    }

    // Merge the subarrays until the end of one is reached
    while (leftIndex <= middle1 && rightIndex <= right){
        // Place the smaller of the two current elements in result
        // and move to the next space in the subarray
        if (inArray[leftIndex] <= inArray[rightIndex]){
            tempArray[combinedIndex++] = inArray[leftIndex++];
        } else {
            tempArray[combinedIndex++] = inArray[rightIndex++];
        }
    }

    if (leftIndex == middle2){
        // If at the end of the left array
        // Copy the right array
        while (rightIndex <= right){
            tempArray[combinedIndex++] = inArray[rightIndex++];
        }
    } else {
        // If at the end of the right array
        // Copy the left array
        while (leftIndex <= middle2){
            tempArray[combinedIndex++] = inArray[leftIndex++];
        }
    }

    // Copy the values back into the original array
    for (size_t index = left; index <= right; index++){
        inArray[index] = tempArray[index];
    }

    // Output merged subarray (for debugging/demonstrating)
    if (IS_DEBUG){
        printf("%s", "         ");
        displaySubArray(inArray, left, right);
        printf("\n");
    }
}

// Displays the current sub array (for debug/demonstrating)
void displaySubArray(int* inArray, size_t left, size_t right){
    // Output spaces for alignment
    for (size_t index = 0; index < left; index++){
        printf("%s", "      ");
    }

    // Output elements in array
    for (size_t index = left; index <= right; index++){
        printf("%6d", inArray[index]);
    }
}