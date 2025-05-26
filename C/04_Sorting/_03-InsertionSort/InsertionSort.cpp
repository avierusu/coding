/**
 * Insertion sort:
 * On the first iteration, if the array's second element is less than the first,
 * they are swapped.
 * The second iteration looks at the third element and inserts it into the
 * correct position with respect to the first two elements, so all three
 * are in order.
 * So on and so forth
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
void insertionSort(int* inArray, size_t size);

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
    insertionSort(nums, ARR_SIZE);

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

// Sorts the array using the Selection Sort method
void insertionSort(int* inArray, size_t size){
    // Loop over size - 1 elements
    for (size_t index = 1; index < size; index++){
        // Initialize location to place element
        size_t moveItem = index;
        // Hold element to insert
        int insert = inArray[index];

        // Search for a place to put the current element
        while (moveItem > 0 && inArray[moveItem - 1] > insert){
            // shift element right one slot
            inArray[moveItem] = inArray[moveItem - 1];
            moveItem--;
        }

        // Place inserted element
        inArray[moveItem] = insert;
    }
}