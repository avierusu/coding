// Creating and using a function to square a number

#include <iostream>
using namespace std;

int square(int number); // function prototype

int main(){
    for(unsigned int x{1}; x <= 10; x++){
        cout << square(x) << "  ";
    }

    cout << endl;
}

int square(int number){
    return number * number;
}