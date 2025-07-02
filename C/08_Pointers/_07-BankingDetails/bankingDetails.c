/**
 * This program will use a struct to define a customer account
 * We will use this to create details for two customers,
 * as well as a combined joint account
 */

#include <stdio.h>
#include <string.h>

// Define customer account struct type
struct customerAccount{
    char accHolder[50];
    int accNum;
    float checkingBalance;
    float savingsBalance;
};

// Use typedef to creat a new name for struct customerAccount
typedef struct customerAccount custAcc;

// Function prototype
void createJoint(custAcc *acc1, custAcc *acc2, custAcc *joint);

int main(){
    // Declare three customerAccounts, two for customers and one for the joint account
    custAcc customer1, customer2, jointAcc;

    // Set the account number for the new accounts
    customer1.accNum = 1111;
    customer2.accNum = 2222;
    jointAcc.accNum = 3333;

    // Prompt for and store the names and balances of the two accounts
    printf("\nEnter the name of Account1: ");
    scanf("%s", customer1.accHolder);
    printf("Enter %s's Checking Account balance: ", customer1.accHolder);
    scanf("%f", &customer1.checkingBalance);
    printf("Enter %s's Savings Account balance: ", customer1.accHolder);
    scanf("%f", &customer1.savingsBalance);
    printf("-----------------------------------------------------");
    printf("\nEnter the name of Account2: ");
    scanf("%s", customer2.accHolder);
    printf("Enter %s's Checking Account balance: ", customer2.accHolder);
    scanf("%f", &customer2.checkingBalance);
    printf("Enter %s's Savings Account balance: ", customer2.accHolder);
    scanf("%f", &customer2.savingsBalance);

    // Create a joint account that combines customer1's and customer2's names and balances
    createJoint(&customer1, &customer2, &jointAcc);

    // Display the new joint account information
    printf("\n\nYour joint account \"%s\" has the following balances:", jointAcc.accHolder);
    printf("\nJoint Checking Account: $%.2f", jointAcc.checkingBalance);
    printf("\nJoint Savings Account: $%.2f\n", jointAcc.savingsBalance);

    return 0;
}

// Combine the names and balances of acc1 and acc2 into the joint account
void createJoint(custAcc *acc1, custAcc *acc2, custAcc *joint){
    // Combine the names of acc1 and acc2 into joint
    strcpy(joint -> accHolder, acc1 -> accHolder);
    strcat(joint -> accHolder, " + ");
    strcat(joint -> accHolder, acc2 -> accHolder);

    // Combine the checking and savings balances into joint
    joint -> checkingBalance = acc1 -> checkingBalance + acc2 -> checkingBalance;
    joint -> savingsBalance = acc1 -> savingsBalance + acc2 -> savingsBalance;
}