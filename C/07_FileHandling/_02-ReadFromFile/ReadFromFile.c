// Reading and printing information from a file

#include <stdio.h>

int main(){
    // Define the name of the file
    char file[] = "clients.txt";
    // Define a file pointer and open the file
    FILE *filePtr;
    filePtr = fopen(file, "r");
    
    // exit the program if the file cannot be opened
    if (filePtr == NULL){
        printf("File could not be opened.\n");
        return 1;
    }

    // Create variables to store account number, name, and balance from file
    int account;
    char name[30];
    double balance;

    printf("%-10s%-13s%s\n", "Account", "Name", "Balance");
    // Read and display account number, name, and balance from file
    fscanf(filePtr, "%d%29s%lf", &account, name, &balance);

    // While not end of file
    while (!feof(filePtr)){
        printf("%-10d%-13s%7.2f\n", account, name, balance);
        fscanf(filePtr, "%d%29s%lf", &account, name, &balance);
    }

    fclose(file);
    
    return 0;
}