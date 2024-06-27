// Using if statements, relational operators, and equality operators

#include <iostream>

using std::cout;
using std::cin;
using std::endl;

int main(){
    int num1{0};
    int num2{0};

    cout << "Enter two integers to compare: ";
    cin >> num1 >> num2;

    if(num1 == num2){
        cout << num1 << " == " << num2 << endl;
    }
    if(num1 != num2){
        cout << num1 << " != " << num2 << endl;
    }
    if(num1 < num2){
        cout << num1 << " < " << num2 << endl;
    }
    if(num1 > num2){
        cout << num1 << " > " << num2 << endl;
    }
    if(num1 <= num2){
        cout << num1 << " <= " << num2 << endl;
    }
    if(num1 >= num2){
        cout << num1 << " >= " << num2 << endl;
    }
}