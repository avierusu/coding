// Contains a name and balance and functions to set and update each

#include <string>

class Account {
    public:
        // Account constructor
        explicit Account(std::string accName, int initBalance) : name{accName}{
            if(initBalance > 0){
                balance = initBalance;
            }
        }

        // Deposits a valid amount to the balance
        void deposit(int depositAmount){
            if(depositAmount > 0){
                balance = balance + depositAmount;
            }
        }

        // Return the account balance
        int getBalance() const {
            return balance;
        }

        // Set the name of the account
        void setName(std::string accName){
            name = accName;
        }

        // Return the name of the account
        std::string getName() const {
            return name;
        }
    private:
        std::string name;
        int balance{0};
};