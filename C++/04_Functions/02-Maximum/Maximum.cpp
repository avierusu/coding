// Findint the maximum of three integers

#include <iostream>
#include <iomanip>
using namespace std;

int maximum(int x, int y, int z);

int main(){
    cout << "Enter three integer values:" ;
    int num1, num2, num3;
    cin >> num1 >> num2 >> num3;

    cout << "The maximum integer value is: " << maximum(num1, num2, num3) << endl;
}

int maximum(int x, int y, int z){
    int max{x};

    if(y > max){
        max = y;
    }
    if(z > max){
        max = z;
    }

    return max;
}