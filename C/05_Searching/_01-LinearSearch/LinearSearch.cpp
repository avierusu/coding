/**
 * Linear search is the simplest search; it searches through
 * the entire array from the beginning until the target is found
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <iostream>
#include <chrono>
using namespace std;

#define ARR_SIZE 10

int searchUnsorted(int* inArray, size_t size, int target);
int searchSorted(int* inArray, size_t size, int target);

int main(){
    // Create an unsorted array and sorted array that we will search through
    int unsortedNums[ARR_SIZE] = {2, 6, 4, 8, 10, 12, 89, 68, 45, 37};
    int sortedNums[ARR_SIZE] = {2, 4, 6, 8, 10, 12, 37, 45, 68, 89};

    // Define the target value and declare its location
    int target = 11;
    int location;

    // Check how long the search takes
    // Record the start time
    auto start = chrono::high_resolution_clock::now();

    // Search the array for the target value
    // location = searchUnsorted(unsortedNums, ARR_SIZE, target);
    location = searchSorted(sortedNums, ARR_SIZE, target);

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

// Search through the entire array from the beginning until the target is found
int searchUnsorted(int* inArray, size_t size, int target){
    int location = 0;
    bool isFound = false;

    while (!isFound && location < size){
        if (inArray[location] == target){
            isFound = true;
        } else {
            location++;
        }
    }

    if (isFound){
        return location;
    } else {
        return -1;
    }
}

// Search through the array from the beginning until target is found
// Exit early once checking values larger than target
int searchSorted(int* inArray, size_t size, int target){
    int location = 0;

    while (location < size){
        if (inArray[location] == target){
            return location;
        } else {
            location++;
        }

        // Check if we passed where target would be, meaning
        // it is not in the array
        if (inArray[location] > target){
            return -1;
        }
    }

    return -1;
}