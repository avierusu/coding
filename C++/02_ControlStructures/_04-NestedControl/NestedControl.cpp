// Analysis of exam results

#include <iostream>
using namespace std;

int main(){
    unsigned int passes{0};
    unsigned int failures{0};
    unsigned int studentCounter{1};

    while(studentCounter <= 10){
        cout << "Enter result (1 = pass, 2 = fail): ";
        int result;
        cin >> result;

        if(result == 1){
            passes++;
        } else {
            failures++;
        }

        studentCounter++;
    }

    cout << "Passed: " << passes << "\nFailed: " << failures << endl;

    if (passes > 8){
        cout << "Bonus to instructor!" << endl;
    }
}