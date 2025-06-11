/**
 * This program creates a simple sequential-access file
 * that could be used in an accounts receivable system to
 * track the amounts owed by a company’s credit clients.
 * For each client, the program obtains the client’s account
 * number, name and balance owed.
 * This program assumes the user enters the records in 
 * account-number order.
 */

#include <stdio.h>

int main(){
    // clients.txt file pointer
    FILE *filePtr;

    // fopen opens the file. Exit the program if unable to create the file
    if ((filePtr = fopen("clients.txt", "w")) == NULL){
        printf("File could not be opened\n");
    } else {
        // Prompt for input
        printf("Enter the account, name, and balance.\nEnter EOF to end input,\n? ");

        // Account number, name, and balance
        int account;
        char name[30];
        double balance;
        // Store user input
        scanf("%d%29s%lf", &account, &name, &balance);

        // Write account number, name, and balance into file with fprintf
        while (!feof(stdin)){
            fprintf(filePtr, "%d %s %.2f\n", account, name, balance);
            printf("? ");
            scanf("%d%29s%lf", &account, &name, &balance);
        }
    }

    // Close file
    fclose(filePtr);

    return 0;
}