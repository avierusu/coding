/**
 * This program uses pointers to pointers to
 * count the amount of unnecessary extra spaces
 * in a full line of text
 */

#include <stdio.h>

// Function signatures
void processLine(char *input, int *extraSpaces);
int countSpaces(char **currentChar);

int main(){
    char inputBuffer[512], *inputPtr;
    int spaceCounter = 0;

    printf("Enter text. Signal end of file when done.\n> ");

    // Accept input until the user enters the end-of-file character
    while ((inputPtr = gets(inputBuffer)) != NULL){
        processLine(inputPtr, &spaceCounter);
        printf("> ");
    }

    // Display results
    printf("There were %d unnecessary spaces.\n", spaceCounter);

    return 0;
}

// Looks through a full line of string text and count
// the number of extra spaces
void processLine(char *input, int *extraSpaces){
    int count;

    // Loop until the end-of-file character
    while (*input != '\0'){
        // Check if the current character is a space
        if (*input == ' '){
            // Count the number of back-to-back spaces
            count = countSpaces(&input);
            // Only increment the extra space counter if there are
            // more than 2 spaces (not just a space between words)
            if (count >= 2){
                *extraSpaces += count - 1;
            }
        } else {
            input++;
        }
    }
}

// Count the number of back-to-back spaces
int countSpaces(char **currentChar){
    int counter = 0;

    // Count each back-to-back space at once
    while (**currentChar == ' '){
        counter++;
        // Move to the next character
        (*currentChar)++;
    }

    return counter;
}