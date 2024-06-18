// Summation using a for loop

#include <iostream>
using namespace std;

int main(){
    unsigned int total{0};

    for(unsigned int num{2}; num <= 20; num += 2){
        total += num;
    }

    cout << "Sum is " << total << endl;
}