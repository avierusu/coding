// Rolling a six-sided die using random

#include <iostream>
#include <iomanip>
#include <cstdlib>
using namespace std;

int main(){
    unsigned int freq1{0};
    unsigned int freq2{0};
    unsigned int freq3{0};
    unsigned int freq4{0};
    unsigned int freq5{0};
    unsigned int freq6{0};
    int face;

    for(unsigned int roll{1}; roll <= 60000000; roll++){
        face = 1 + rand() % 6;

        switch(face){
            case 1:
                freq1++;
                break;
            case 2:
                freq2++;
                break;
            case 3:
                freq3++;
                break;
            case 4:
                freq4++;
                break;
            case 5:
                freq5++;
                break;
            case 6:
                freq6++;
                break;
        }
    }

    cout << "Face" << setw(13) << "Frequency" << endl;
    cout << "   1" << setw(13) << freq1
       << "\n   2" << setw(13) << freq2
       << "\n   3" << setw(13) << freq3
       << "\n   4" << setw(13) << freq4
       << "\n   5" << setw(13) << freq5
       << "\n   6" << setw(13) << freq6 << endl;
}