#include <iostream>
using namespace std;

int main(){
    unsigned int c{5};
    cout << "c before post-increment: " << c << endl;   //prints 5
    cout << "    post-incrementing c: " << c++ << endl; //pritns 5
    cout << " c after post-increment: " << c << endl;   //prints 6

    cout << endl;

    c = 5;
    cout << " c before pre-increment: " << c << endl;   //prints 5
    cout << "     pre-incrementing c: " << ++c << endl; //pritns 6
    cout << "  c after pre-increment: " << c << endl;   //prints 6
}