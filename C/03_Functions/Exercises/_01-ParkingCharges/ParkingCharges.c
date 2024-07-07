/**
 * Parking garage charges $2.00 minimum fee to park up to 3 hours
 * and $0.50 every hour past 3 hours.
 * Maximum charge for any 24-hour period is $10.00
 */

#include <stdio.h>
#include <math.h>

double calculateCharges(double);    // Function prototype

// Constant variables
const double BASE_CHARGE = 2.00;
const double CHARGE_PER_HOUR = 0.50;
const double BASE_CHARGE_CUTOFF = 3.0;
const double CHARGE_CUTOFF = 10.00;

int main(void){
    // Get parking hours for all three cars
    double carOneHours, carTwoHours, carThreeHours;
    printf("Enter the amount of hours Car 1 parked for: ");
    scanf("%lf", &carOneHours);
    printf("Enter the amount of hours Car 2 parked for: ");
    scanf("%lf", &carTwoHours);
    printf("Enter the amount of hours Car 3 parked for: ");
    scanf("%lf", &carThreeHours);

    // Calculate charges for each car
    double carOneCharge = calculateCharges(carOneHours);
    double carTwoCharge = calculateCharges(carTwoHours);
    double carThreeCharge = calculateCharges(carThreeHours);

    // Calculate totals
    double totalHours = carOneHours + carTwoHours + carThreeHours;
    double totalCharge = carOneCharge + carTwoCharge + carThreeCharge;

    // Display a table of costs and totals
    printf("Car\tHours\tCharge\n");
    printf("1\t%5.1f\t%5.2f\n", carOneHours, carOneCharge);
    printf("2\t%5.1f\t%5.2f\n", carTwoHours, carTwoCharge);
    printf("3\t%5.1f\t%5.2f\n", carThreeHours, carThreeCharge);
    printf("TOTAL\t%5.1f\t%5.2f", totalHours, totalCharge);
}

// Calculate the charge for each customer
double calculateCharges(double hours){
    double charge = BASE_CHARGE;

    if(hours > BASE_CHARGE_CUTOFF){                                         // Car is parked for more than 3 hours
        charge += (ceil(hours - BASE_CHARGE_CUTOFF) * CHARGE_PER_HOUR);     // Calculate additional price per hour
        if(charge >= CHARGE_CUTOFF){                                        // Implement hard cap of $10
            return CHARGE_CUTOFF;
        } else {
            return charge;
        }
    } else {                                                                // Car is parked for 3 hours or less
        return charge;
    }
}