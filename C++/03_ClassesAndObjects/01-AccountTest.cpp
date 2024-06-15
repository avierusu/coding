// Create and manipulate an Account object

#include <iostream>
#include <string>
// #include "Account.h"
#include "AnotherAccount.h"

using namespace std;

int main(){
    AnotherAccount myAccount;

    cout << "Initial account name is: " << myAccount.getName();

    cout << "\nPlease enter the account name: ";
    string name;
    getline(cin, name);
    myAccount.setName(name);

    cout << "Name in object myAccount is: " << myAccount.getName() << endl;
}