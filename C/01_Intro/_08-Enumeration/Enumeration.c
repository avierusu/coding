// Using an enumeration constant

#include <stdio.h>

// Enumeration constants represent months of the year
enum months{
    JAN = 1, FEB, MAR, APR, MAY, JUN, JUL, AUG, SEP, OCT, NOV, DEC
};

int main(){
    // Initialize array of pointers
    const char *monthName[] = {"", "January", "February", "March", "April", "May",
        "June", "July", "August", "September", "October", "November", "December"};

    // Loop through the months
    for (enum months month = JAN; month <= DEC; month++){
        printf("%2d%11s\n", month, monthName[month]);
    }
    
    return 0;
}