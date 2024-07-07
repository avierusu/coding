// Round numbers to various digits without using math functions like round(), floor(), and ceil()

#include <iostream>
#include <iomanip>
using namespace std;

// Function prototypes
double roundToDigit(double, int);
int roundToInteger(double);
double roundToTenths(double);
double roundToHundreths(double);
double roundToThousandths(double);

int main(){
    double number;
    cout << "Enter a number to round: ";
    cin >> number;

    cout << number << "rounded to:" << endl;
    cout << "Nearest Integer:\t" << roundToInteger(number) << endl;
    cout << "Nearest Tenth:\t\t" << fixed << setprecision(1) << roundToTenths(number) << endl;
    cout << "Nearest Hundreth:\t" << fixed << setprecision(2) << roundToHundreths(number) << endl;
    cout << "Nearest Thousandth:\t" << fixed << setprecision(3) << roundToThousandths(number) << endl;
}


// General function to round to any decimal point
double roundToDigit(double num, int decimals){
    double power = 1;
    for(int i = 0; i < decimals; i++){
        power *= 10;
    }

    int number = (int) (num * power * 10);

    if(number % 10 >= 5){           // Determine whether to round up or down
        number = number / 10 + 1;
    } else {
        number /= 10;
    }

    return number / power;          // Return the rounded number
}


// Round to a whole number
int roundToInteger(double num){
    return (int) roundToDigit(num, 0);
}

// Round to the tenths place
double roundToTenths(double num){
    return roundToDigit(num, 1);
}

// Round to the hundreths place
double roundToHundreths(double num){
    return roundToDigit(num, 2);
}

// Rount to the thousandths place
double roundToThousandths(double num){
    return roundToDigit(num, 3);
}