// Reading and printing information from a file

#include <stdio.h>

int main(){
    // Define the name of the file
    const char fileName[] = "clients.txt";
    // Define a file pointer and open the file
    FILE *filePtr;
    filePtr = fopen(fileName, "r");
    
    // exit the program if the file cannot be opened
    if (filePtr == NULL){
        printf("File could not be opened.\n");
    } else {
        // Read account number, name, and balance from file
        int account;
        char name[30];
        double balance;

        printf("%-10s%-13s%s\n", "Account", "Name", "Balance");
        fscanf(filePtr, "%d%29s%lf", &account, name, &balance);

        // While not end of file
        while (!feof(filePtr)){
            printf("%-10d%-13s%7.2f\n", account, name, balance);
            fscanf(filePtr, "%d%29s%lf", &account, name, &balance);
        }
    }

    return 0;
}