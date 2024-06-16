// Create and test Student objects

#include <iostream>
#include "Student.h"
using namespace std;

int main(){
    Student student1{"Jane Green", 93};
    Student student2{"John Blue", 72};

    cout << student1.getName() << "'s letter grade equivalent of "
         << student1.getAverage() << " is: "
         << student1.getLetterGrade() << "\n";
    cout << student2.getName() << "'s letter grade equivalent of "
         << student2.getAverage() << " is: "
         << student2.getLetterGrade();
}