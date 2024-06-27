// Passing arguments by value and by reference

#include <iostream>
using namespace std;

int squareByValue(int);
void squareByReference(int&);

int main(){
    int x = 2;
    int z = 4;

    cout << "x = " << x << " before squareByValue\n";
    cout << "Value returned by squareByValue: " << squareByValue(x) << endl;
    cout << "x = " << x << " after squareByValue\n" << endl;

    cout << "z = " << z << " before squareByReference" << endl;
    squareByReference(z);
    cout << "z = " << z << " after squareByReference" << endl;
}

int squareByValue(int number){
    return number *= number;    // caller's argument not modified
}

void squareByReference(int& numberRef){
    numberRef *= numberRef;     // caller's argument modified
}