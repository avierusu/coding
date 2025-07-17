/**
 * This program shows how to read data
 * from a binary file
 */

#include <stdio.h>
#include <stdlib.h>

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
int readTransaction(struct transaction *transactionPtr, FILE *filePointer);
void printTransaction(struct transaction *outTransaction);

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

    // Print all transactions
    while (readTransaction(&transact, filePtr)){
        printTransaction(&transact);
    }

    // Close the file and exit
    fclose(filePtr);
    return 0;
}

// Reads a record from a binary file
int readTransaction(struct transaction *transactionPtr, FILE *filePointer){
    int returnValue;
    returnValue = fread(transactionPtr, sizeof(*transactionPtr), 1, filePointer);
    return returnValue;
}

// Prints fields of a transaction
void printTransaction(struct transaction *outTransaction){
    // Display if the transaction is cleared
    if (outTransaction->cleared){
        printf("C | ");
    } else {
        printf("  | ");
    }

    // Display transaction type
    if ((outTransaction->transactionType == 'D') ||
        (outTransaction->transactionType == 'W') ||
        (outTransaction->transactionType == 'I')){
        
        printf("%4c | ", outTransaction->transactionType);
    } else {
        printf("%4d | ", outTransaction->transactionType);
    }

    // Display if transaction is tax deductable
    if (outTransaction->taxDeduct){
        printf(" T | ");
    } else {
        printf("   | ");
    }

    // Display transaction amount and memo
    printf("%10.2f  | ", outTransaction->amount);
    printf("%s", outTransaction->payeeMemo);
}