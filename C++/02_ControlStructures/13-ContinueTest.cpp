// Using continue to terminate an iteration of a for loop

#include <iostream>
using namespace std;

int main(){
    for(unsigned int count{1}; count <= 10; count++){
        if(count == 5){
            continue;
        }

        cout << count << " ";
    }

    cout << "\nUsed continue to skip printing 5" << endl;
}