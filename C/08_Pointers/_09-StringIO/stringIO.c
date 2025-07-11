/**
 * This program shows how to handle a read and
 * display a full line using pointers using pointers
 * to strings
 */

#include <stdio.h>

int main(){
    char *prompt = "Enter a line of text:\n> ";
    char *inputPointer, *inputBuffer;

    printf(prompt);
    inputPointer = gets(inputBuffer);

    // Check if a line was read
    // If so, print it back out; otherwise, display an error message
    if (inputPointer != NULL){
        puts(inputPointer);
    } else {
        puts("Error in input\n");
    }

    return 0;
}