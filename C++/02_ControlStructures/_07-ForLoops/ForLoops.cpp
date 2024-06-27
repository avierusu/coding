// Counter-controlled iteration with a for loop

#include <iostream>
using namespace std;

int main(){
    for(unsigned int counter{1}; counter <= 10; ++counter){
        cout << counter << "   ";
    }

    cout << endl;
}