// Create and manipulate an Account object

#include <iostream>
#include <string>
#include "Account.h"
// #include "AnotherAccount.h"

using namespace std;

int main(){
    Account acc1{"Jane Green"};
    Account acc2{"John Blue"};

    cout << "account1 name is: " << acc1.getName() << endl;
    cout << "account2 name is: " << acc2.getName() << endl;
}