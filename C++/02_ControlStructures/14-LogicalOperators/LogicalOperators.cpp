// Logical operators

#include <iostream>
using namespace std;

int main(void){
    cout << boolalpha << "Logical AND (&&)"
        << "\nfalse && false: " << (false && false)
        << "\nfalse && true: " << (false && true)
        << "\ntrue && false: " << (true && false)
        << "\ntrue && true: " << (true && true) << "\n\n";
    
    cout << "Logical OR (||)"
        << "\nfalse || false: " << (false || false)
        << "\nfalse || true: " << (false || true)
        << "\ntrue || false: " << (true || false)
        << "\ntrue || true: " << (true || true) << "\n\n";
    
    cout << boolalpha << "Logical negation (!)"
        << "\n!false: " << (!false)
        << "\n!true: " << (!true) << endl;
}