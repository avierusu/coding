/**
 * This program will accept multiple lines from the
 * user and display the amount of lines and characters
 * that the user entered
 */

#include <stdio.h>
#include <string.h>

int main(){
    char inputBuffer[512], *inputPtr;
    int numLines = 0, numChars = 0;

    // Prompt the user for text
    printf("Enter your text now. Signal end-of-file when done.\n> ");

    // Read line by line
    // Each line is read up to a newline character or EOF
    // Exit loop when ^Z is entered
    while((inputPtr = gets(inputBuffer)) != NULL){
        numLines++;
        numChars += strlen(inputPtr) + 1;
        printf("> ");
    }

    // Display results
    printf("\n%d lines, %d characters\n", numLines, numChars);

    return 0;
}