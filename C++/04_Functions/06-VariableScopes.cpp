// Testing variables' scopes within functions

#include <iostream>
using namespace std;

// function prototypes
void useLocal();
void useStaticLocal();
void useGlobal();

int x = 1;  // global variable

int main(){
    cout << "global x in main is " << x << endl;

    int x = 5;
    cout << "local x in outer scope of main is " << x << endl;

    {   // start new scope
        int x = 7;
        cout << "local x in inner scope of main is" << x << endl;
    }   // end new scope

    cout << "local x in outer scope of main is " << x << endl;

    useLocal();         // useLocal has automatic local x
    useStaticLocal();   // useStaticLocal has static local x
    useGlobal();        // useGlobal uses global x
    useLocal();         // useLocal reinitializes automatic local x
    useStaticLocal();   // static local x retains its prior value
    useGlobal();        // global x also retains its value

    cout << "\nlocal x in outer scope of main is " << x << endl;
}


// Reinstates local variable x during each call
void useLocal(void){
    int x = 25;             // initialized each time useLocal is called
    cout << "\nlocal x is" << x << "after entering useLocal" << endl;
    x++;
    cout << "local x is" << x << "before exiting useLocal" << endl;
}

// Initializes static local variable x  only the first time the function is called;
// value of x is saved between calls
void useStaticLocal(void){
    static int x = 50;      // initialized once
    cout << "\nlocal static x is" << x << "after entering useStaticLocal" << endl;
    x++;
    cout << "local static x is" << x << "before exiting useStaticLocal" << endl;
}

// modifies global variable x during each call
void useGlobal(void){
    cout << "\nglobal x is" << x << "after entering useGlobal" << endl;
    x *= 10;
    cout << "global x is" << x << "before exiting useGlobal" << endl;
}