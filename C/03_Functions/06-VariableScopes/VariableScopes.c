// Testing variables' scopes within functions

#include <stdio.h>

// function prototypes
void useLocal(void);
void useStaticLocal(void);
void useGlobal(void);

int x = 1;  // global variable

int main(void){
    int x = 5;  // local variable to main

    printf("local x in outer scope of main is %d\n", x);

    {   // start new scope
        int x = 7;
        printf("local x in inner scope of main is %d\n", x);
    }   // end new scope

    printf("local x in outer scope of main is %d\n", x);

    useLocal();         // useLocal has automatic local x
    useStaticLocal();   // useStaticLocal has static local x
    useGlobal();        // useGlobal uses global x
    useLocal();         // useLocal reinitializes automatic local x
    useStaticLocal();   // static local x retains its prior value
    useGlobal();        // global x also retains its value

    printf("\nlocal x in main is %d\n", x);
}


// Reinstates local variable x during each call
void useLocal(void){
    int x = 25;             // initialized each time useLocal is called
    printf("\nlocal x in useLocal is %d after entering useLocal\n", x);
    x++;
    printf("local x in useLocal is %d before exiting useLocal\n", x);
}

// Initializes static local variable x  only the first time the function is called;
// value of x is saved between calls
void useStaticLocal(void){
    static int x = 50;      // initialized once
    printf("\nlocal static x is %d after entering useStaticLocal\n", x);
    x++;
    printf("local static x is %d before exiting useStaticLocal\n", x);
}

// modifies global variable x during each call
void useGlobal(void){
    printf("\nglobal x is %d after entering useGlobal\n", x);
    x *= 10;
    printf("global x is %d before exiting useGlobal\n", x);
}