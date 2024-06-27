// Using default arguments

#include <iostream>
using namespace std;

unsigned int boxVolume(unsigned int length = 1, unsigned int width = 1, unsigned int height = 1);

int main(){
    // no argumetns - use default values for all dimensions
    cout << "The default box volume is: " << boxVolume();

    // specify length; default width and height
    cout << "\n\nThe volume of a box with a length 10,\n"
         << "width 1, and height 1 is: " << boxVolume(10);
    
    // specify length and width; default height
    cout << "\n\nThe volume of a box with a length 10,\n"
         << "width 5, and height 1 is: " << boxVolume(10, 5);
    
    // specify all arguments
    cout << "\n\nThe volume of a box with a length 10,\n"
         << "width 5, and height 2 is: " << boxVolume(10, 5, 2) << endl;
}

unsigned int boxVolume(unsigned int length, unsigned int width, unsigned int height){
    return length * width * height;
}