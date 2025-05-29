/**
 * Binary search splits the array in half about a midpoint
 * and checks which subarray the the target value is on (or
 * if it is the midpoint). This process is repeated, narrowing
 * search down each time the array is split.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <iostream>
#include <chrono>
using namespace std;

#define ARR_SIZE 10

int binarySearch(int* inArray, size_t size, int target);

int main(){
    // Create a sorted array that we will search through
    int nums[ARR_SIZE] = {2, 4, 6, 8, 10, 12, 37, 45, 68, 89};

    // Define the target value and declare its location
    int target = 37;
    int location;

    // Check how long the search takes
    // Record the start time
    auto start = chrono::high_resolution_clock::now();

    // Search the array for the target value
    location = binarySearch(nums, ARR_SIZE, target);

    // Record the end time
    auto end = chrono::high_resolution_clock::now();
    // Calculate the time taken in seconds (since clock() returns clock ticks)
    chrono::duration<double> duration = end - start;

    // Display Results
    if (location != -1){
        printf("\n%d was found at index %d.", target, location);
    } else {
        printf("\n%d was not found in the array.", target);
    }
    

    // Display execution time
    printf("\n");
    printf("\n\nExcecution time: %.5f nanoseconds\n", duration.count() * 1000 * 1000);
    cout << "Excecution time: " << duration.count() * 1000 * 1000 << " nanoseconds" << endl;

    return 0;
}

// Search an array using binary search
int binarySearch(int* inArray, size_t size, int target){
    int first = 0, last = size - 1;
    
    while (first <= last){
        int middle = (first + last) / 2;

        if (target < inArray[middle]){
            last = middle - 1;
        } else if (target > inArray[middle]) {
            first = middle + 1;
        } else {
            return middle;
        }
    }

    return -1;
}