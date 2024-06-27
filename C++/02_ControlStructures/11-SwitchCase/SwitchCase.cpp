// Counting letter grades with switch

#include <iostream>
#include <iomanip>
using namespace std;

int main(){
    int total{0};
    unsigned int gradeCounter{0};
    unsigned int aCount{0};
    unsigned int bCount{0};
    unsigned int cCount{0};
    unsigned int dCount{0};
    unsigned int fCount{0};

    cout << "Enter the integer grades in the range 0-100\n"
         << "Type the end-of-file indicator to terminate input:\n"
         << "On Windows type <Ctrl> z then press Enter\n"
         << "on UNIX/Linux/Mac OS X type <Ctrl> d then press Enter\n";
    
    int grade;

    while(cin >> grade){
        total += grade;
        gradeCounter++;

        switch(grade / 10){
            case 9:
            case 10:
                ++aCount;
                break;
            case 8:
                ++bCount;
                break;
            case 7:
                ++cCount;
                break;
            case 6:
                ++dCount;
                break;
            default:
                ++fCount;
                break;
        }
    }

    cout << fixed << setprecision(2);
    
    cout << "\nGrade Report:\n";

    if(gradeCounter != 0){
        double average = static_cast<double>(total) / gradeCounter;

        cout << "Total of the " << gradeCounter << " grades entered is "
             << total << "\nClass Average is " << average
             << "\nNumber of students who received each grade:"
             << "\nA: " << aCount
             << "\nB: " << bCount
             << "\nC: " << cCount
             << "\nD: " << dCount
             << "\nF: " << fCount << endl;
    } else {
        cout << "No grades were entered" << endl;
    }
}