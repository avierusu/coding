#include <iostream>
using namespace std;

int main(){
    cout << "Enter a number: ";
    int n;
    cin >> n;

    cout << "N\t10*N\t100*N\t1000*N\n\n";
    unsigned int counter = 1;

    while(counter <= n){
        cout << counter << "\t"
             << counter*10 << "\t"
             << counter*100 << "\t"
             << counter*1000
             << endl;
        counter++;
    }
}