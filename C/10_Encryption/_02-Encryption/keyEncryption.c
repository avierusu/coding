/**
 * Practice with Encrypting a string using a hex key
 */

#include <stdio.h>
#include <string.h>

#define LINE_LENGTH 100
#define KEY 0x5A

void xorCipher(char *str);
void printHex(char *str);

int main(){
    char text[LINE_LENGTH];

    printf("\nEnter some text: ");
    // Read an entire line of text, including spaces and the newline
    fgets(text, LINE_LENGTH, stdin);
    // Remove the newline at the end of the string
    text[strcspn(text, "\n")] = '\0';

    printf("\nOriginal: %s\n", text);

    xorCipher(text);
    printf("Encrypted: ");
    printHex(text);
    printf("\n");
    printf("test: \n%s\n", text);

    xorCipher(text);
    printf("Unencrypted: %s\n", text);

    return 0;
}

// This function uses a key to encrypt a string of text
void xorCipher(char *str){
    for (int index = 0; str[index] != '\0'; index++) {
        str[index] ^= KEY;
    }
}

// This function prints a string in hex format to prevent
void printHex(char *str){
    for (int index = 0; str[index] != '\0'; index++) {
        printf("%02X ", (unsigned char)str[index]);
    }
}