/**
 * Parking garage charges $2.00 minimum fee to park up to 3 hours
 * and $0.50 every hour past 3 hours.
 * Maximum charge for any 24-hour period is $10.00
 */

#include <iostream>
#include <iomanip>
#include <math.h>
using namespace std;

double calculateCharges(double);    // Function prototype

// Constant variables
const double BASE_CHARGE = 2.00;
const double CHARGE_PER_HOUR = 0.50;
const double BASE_CHARGE_CUTOFF = 3.0;
const double CHARGE_CUTOFF = 10.00;

int main(){
    // Get parking hours for all three cars
    double carOneHours, carTwoHours, carThreeHours;
    cout << "Enter the amount of hours Car 1 parked for: ";
    cin >> carOneHours;
    cout << "Enter the amount of hours Car 2 parked for: ";
    cin >> carTwoHours;
    cout << "Enter the amount of hours Car 3 parked for: ";
    cin >> carThreeHours;

    // Calculate charges for each car
    double carOneCharge = calculateCharges(carOneHours);
    double carTwoCharge = calculateCharges(carTwoHours);
    double carThreeCharge = calculateCharges(carThreeHours);

    // Calculate totals
    double totalHours = carOneHours + carTwoHours + carThreeHours;
    double totalCharge = carOneCharge + carTwoCharge + carThreeCharge;

    // Display a table of costs and totals
    cout << "Car\tHours\tCharge" << endl;
    cout << "1\t" << setw(5) << fixed << setprecision(1) << carOneHours << "\t" << setw(5) << setprecision(2) << carOneCharge << endl;
    cout << "2\t" << setw(5) << fixed << setprecision(1) << carTwoHours << "\t" << setw(5) << setprecision(2) << carTwoCharge << endl;
    cout << "3\t" << setw(5) << fixed << setprecision(1) << carThreeHours << "\t" << setw(5) << setprecision(2) << carThreeCharge << endl;
    cout << "TOTAL\t" << setw(5) << fixed << setprecision(1) << totalHours << "\t" << setw(5) << setprecision(2) << totalCharge << endl;
}

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