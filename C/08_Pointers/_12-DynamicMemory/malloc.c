/**
 * This program serves as a review for dynamically allocating memory
 * using the function malloc().
 * 
 * In this program, we will simulate a car dealership that stores a list
 * of the cars they have in their store.
 */

#include <stdio.h>
#include <stdlib.h>

// Start by creating a struct to represent one car, and use typedef to
// create our own name for it

typedef struct {
    char make[20];
    char model[20];
    char year[5];
} Car;

int main(){
    // Store the number of cars currently in the array
    int numCars;
    // Create a pointer that will point to the array of cars
    Car *cars;

    // Prompt user to enter the initial number of cars stored
    printf("\nEnter the number of cars in the dealership: ");
    scanf("%d", &numCars);

    // Dynamically allocate memory to store "numCars" amount of "Car" structs
    // Assign the memory location to the pointer we created earlier
    cars = (Car *)malloc(numCars * sizeof(Car));

    // If memory could not be allocated, display an error and exit;
    if (cars == NULL){
        printf("Memory allocation failed.");
        return 1;
    }

    // Accept data about the cars stored from the user
    for (int index = 0; index < numCars; index++){
        printf("\nEnter details for Car #%d:\n", (index+1));
        printf("Car Make: ");
        scanf("%s", cars[index].make);
        printf("Car Model: ");
        scanf("%s", cars[index].model);
        printf("Car Release Year: ");
        scanf("%s", cars[index].year);
    }

    printf("\n%s\n", cars[0].year);

    // Display the details of every car currently stored
    printf("\n\nCurrently, these are the cars we offer:");
    for (int index = 0; index < numCars; index++){
        printf("\n\tCar #%d: %s %s %s", (index+1), cars[index].year,
            cars[index].make, cars[index].model);
    }

    // Always free allocated memory
    free(cars);
    
    return 0;
}