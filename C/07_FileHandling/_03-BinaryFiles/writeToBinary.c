/**
 * This program shows how to write data
 * to a binary file
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

// Declare constant variables
#define BUFFER_SIZE 50

// Transaction structure definition
struct transaction{
    int transactionType;
    char payeeMemo[BUFFER_SIZE];
    float amount;
    unsigned taxDeduct:1;   // bitfield of 1 bit
    unsigned cleared:1;
};

// Function prototypes
int getType();
void getTransaction(struct transaction *transactionPtr);
void putTransaction(struct transaction *transactionPtr, FILE *filePointer);

int main(){
    struct transaction transact;
    FILE *filePtr;

    // Open a file and check if it could be opened
    if ((filePtr = fopen("transact", "a+")) == NULL){
        // If the file could not be opened/created
        // Display error message and exit
        printf("Transaction file couldn't be opened.\n");
        exit(1);
    }

    // Repeat until the user wants to exit
    while ((transact.transactionType = getType()) != 'Q'){
        getTransaction(&transact);
        putTransaction(&transact, filePtr);
    }
    
    // Close the file and exit
    fclose(filePtr);
    return 0;
}

// Prompts for and stores transaction type
int getType(){
    char buffer[80];
    int transactionType;
    bool exit = false;

    // Continue to prompt the user for a valid transaction type
    while (!exit){
        printf("\nD)eposit, W)ithdrawal, or Check #");
        printf("\nEnter transaction type or Q)uit: ");
        gets(buffer);

        // If the user entered an integer (for check #)
        // Convert it to an int
        if (isdigit(*buffer)){
            // Exit the loop
            exit = true;
            // Convert to int and store it
            transactionType = atoi(buffer);
        } else {
            // Convert the users input to uppercase and test
            transactionType = toupper((int) *buffer);
            
            // Check if the input is one of the valid options
            if ((transactionType != 'D') && (transactionType != 'W') &&
                (transactionType != 'Q') ){
                
                printf("Incorrect, try again\n");
            } else {
                // If the user entered a valid option, exit loop
                exit = true;
            }
        }
    }

    return transactionType;
}

// Prompt the user for transaction information and store it
void getTransaction(struct transaction *transactionPtr){
    char inputBuffer[80];

    printf("Amount: $");
    // Store transaction amount
    transactionPtr->amount = atof(gets(inputBuffer));

    // Perform different functions depending on the transaction type
    switch (transactionPtr->transactionType){
        case 'W':
        case 'D':
            printf("Memo: ");
            fgets(transactionPtr->payeeMemo, BUFFER_SIZE, stdin);
            break;
        default:
            printf("Payee: ");
            fgets(transactionPtr->payeeMemo, BUFFER_SIZE, stdin);
            
            // Prompt the user if the transaction is tax-deductible
            printf("Tax deductible? (y/n): ");
            gets(inputBuffer);
            if ( (*inputBuffer == 'y') || (*inputBuffer == 'Y')){
                transactionPtr->taxDeduct = 1;
            } else {
                transactionPtr->taxDeduct = 0;
            }

            // Prompt the user if the transaction is cleared
            printf("Cleared? (y/n): ");
            gets(inputBuffer);
            if ( (*inputBuffer == 'y') || (*inputBuffer == 'Y')){
                transactionPtr->cleared = 1;
            } else {
                transactionPtr->cleared = 0;
            }
    }
}

// Writes a record to a binary file
void putTransaction(struct transaction *transactionPtr, FILE *filePointer){
    fwrite(transactionPtr, sizeof(struct transaction), 1, filePointer);
}