/**
 * Quick Sort is the currently best sorting algorithm
 * Quick sort selects a value to act as a pivot and
 * partitions the values around it;
 * all values greater than the pivot are placed after,
 * and all values less are placed before. The pivot value
 * will be placed in its correct position.
 * The array is split into subarrays by the position and 
 * is recursively sorted
 */

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
#include <iostream>
#include <chrono>
using namespace std;

#define ARR_SIZE 1000
#define RANGE 9999

void printArray(int arr[], size_t size);
void populateArray(int* inArray, size_t size, int min, int max);

void quickSort(int* inArray, size_t size);
void sortSubArray(int* inArray, size_t left, size_t right);
void swap(int& first, int& second);

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
    quickSort(nums, ARR_SIZE);

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

// Sorts the array using the Quick Sort method
void quickSort(int* inArray, size_t size){
    sortSubArray(inArray, 0, size - 1);
}

// Sorts the a piece of the array
void sortSubArray(int* inArray, size_t left, size_t right){
    int leftSwap = left;
    int rightSwap = right;
    int middle = inArray[ (left + right) / 2 ];

    // printf("left: %d, right: %d, middle: %d\n", left, right, middle);

    do {
        while ( (inArray[leftSwap] < middle) && (leftSwap < right) ){
            leftSwap++;
        }
        while ( (inArray[rightSwap] > middle) && (rightSwap > left) ){
            rightSwap--;
        }

        if (leftSwap <= rightSwap){
            swap(inArray[leftSwap], inArray[rightSwap]);

            leftSwap++;
            rightSwap--;
        }
        // printArray(inArray, ARR_SIZE);

    } while (leftSwap <= rightSwap);

    if (left < rightSwap){
        sortSubArray(inArray, left, rightSwap);
    }
    if (leftSwap < right){
        sortSubArray(inArray, leftSwap, right);
    }
}

void swap(int& first, int& second){
    int temp = first;
    first = second;
    second = temp;
}