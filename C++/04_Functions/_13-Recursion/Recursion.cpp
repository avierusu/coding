// Recursive function factorial

#include <iostream>
#include <iomanip>
using namespace std;

unsigned long factorial(unsigned long);

int main(){
    // calculate factorials of 0 through 10
    for(unsigned int counter = 0; counter <= 10; counter++){
        cout << setw(2) << counter << "! = " << factorial(counter) << endl;
    }
}

unsigned long factorial(unsigned long number){
    if(number <= 1){
        return 1;       // base cases: 0! = 1 and 1! = 1
    } else {
        return number * factorial(number - 1);
    }
}