/**
 * Practice with Obfuscating a string
 */

#include <stdio.h>
#include <string.h>

#define LINE_LENGTH 100
#define SHIFT_VALUE 3

void obfuscate(char *str);
void deobfuscate(char *str);

int main(){
    char text[LINE_LENGTH];

    printf("\nEnter some text: ");
    // Read an entire line of text, including spaces and the newline
    fgets(text, LINE_LENGTH, stdin);
    // Remove the newline at the end of the string
    text[strcspn(text, "\n")] = '\0';

    printf("\n\nOriginal: %s\n", text);
    obfuscate(text);
    printf("Obfuscated: %s\n", text);
    deobfuscate(text);
    printf("Deobfuscated: %s\n", text);

    return 0;
}

// This function obfuscates a string by shifting characters
void obfuscate(char *str){
    for (int index = 0; str[index] != '\0'; index++){
        str[index] += SHIFT_VALUE;
    }
}

// This function deobfuscates a string by shifting characters back
void deobfuscate(char *str){
    for (int index = 0; str[index] != '\0'; index++){
        str[index] -= SHIFT_VALUE;
    }
}