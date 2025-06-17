// Reading and printing information from a file

/**
 * In standard C, there is no built-in function to
 * directly read remote files (e.g., over HTTP, FTP).
 * fopen() works only with local file paths, not URLs.
 */

#include <stdio.h>

int main(){
    // Define the name of the file
    char file[] = "C:\\Downloads\\clients.csv";
    // Define a file pointer and open the file
    FILE *filePtr;
    filePtr = fopen(file, "r");
    
    // exit the program if the file cannot be opened
    if (filePtr == NULL){
        printf("File could not be opened.\n");
        return 1;
    }

    char line[256];
    // Read and display account number, name, and balance from file
    fscanf(filePtr, "%s", line);

    // While not end of file
    while (!feof(filePtr)){
        printf("--> %s\n", line);
        fscanf(filePtr, "%s", line);
    }

    fclose(filePtr);
    
    return 0;
}