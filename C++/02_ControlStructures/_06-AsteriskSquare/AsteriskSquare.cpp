#include <iostream>
using namespace std;

int main(){
    cout << "Enter a size: ";
    int size;
    cin >> size;

    int vertCounter = 0;
    int horzCounter = 0;

    while(vertCounter < size){
        while(horzCounter < size){
            cout << "*";
            horzCounter++;
        }
        cout << endl;
        vertCounter++;
        horzCounter = 0;
    }

    cout << "Enter a size: ";
    size;
    cin >> size;

    vertCounter = 1;
    horzCounter = 1;

    while(vertCounter <= size){
        while(horzCounter <= size){
            if(horzCounter == 1){
                cout << "*";
            } else if(horzCounter == size){
                cout << "*";
            } else {
                if(vertCounter == 1){
                    cout << "*";
                } else if(vertCounter == size){
                    cout << "*";
                } else {
                    cout << " ";
                }
            }
            
            horzCounter++;
        }
        cout << endl;
        vertCounter++;
        horzCounter = 1;
    }
}