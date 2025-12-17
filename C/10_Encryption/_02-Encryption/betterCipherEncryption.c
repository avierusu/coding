/**
 * Practice with Encrypting a string using OpenSSL
 * 
 * Run this program using the following command:
 *      gcc betterCipherEncryption.c -lssl -lcrypto
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <openssl/evp.h>
#include <openssl/err.h>

#define KEY_SIZE 32   // AES-256
#define IV_SIZE 16    // AES block size
#define LINE_LENGTH 32

void printKey(unsigned char *key);
void createKey(unsigned char *password, unsigned char *key);
unsigned int hashString(const char *str);
int encrypt(unsigned char *plainText, int plainTextLen, unsigned char *key, unsigned char *iv, unsigned char *cipherText);
int decrypt(unsigned char *cipherText, int cipherTextLen, unsigned char *key, unsigned char *iv, unsigned char *plainText);

int main(){
    unsigned char password[KEY_SIZE] = {0};
    unsigned char key[KEY_SIZE] = {0};
    unsigned char iv[IV_SIZE]  = "0123456789012345";
    unsigned char plainText[LINE_LENGTH];
    unsigned char cipherText[LINE_LENGTH];
    unsigned char decrypted[LINE_LENGTH];

    // Prompt the user for a password
    printf("\nEnter your password: ");
    // Read an entire line of text, including spaces and the newline
    fgets(password, LINE_LENGTH, stdin);
    // Remove the newline at the end of the string
    password[strcspn(password, "\n")] = '\0';

    // Create a key from the password generated
    createKey(password, key);

    printf("\n");
    printKey(key);
    printf("\n");
    
    // Prompt the user for text to encrypt
    printf("\nEnter text to encrypt: ");
    // Read an entire line of text, including spaces and the newline
    fgets(plainText, LINE_LENGTH, stdin);
    // Remove the newline at the end of the string
    plainText[strcspn(plainText, "\n")] = '\0';

    int cipherTextLen = encrypt(plainText, strlen((char *)plainText), key, iv, cipherText);

    int decryptedLen = decrypt(cipherText, cipherTextLen, key, iv, decrypted);

    decrypted[decryptedLen] = '\0';

    printf("Original: %s\n", plainText);
    printf("Encrypted: \n%s\n", cipherText);
    printf("Decrypted: %s\n", decrypted);

    return 0;
}

// This function simply prints out the key
void printKey(unsigned char *key){
    for (int index = 0; index < KEY_SIZE; index++) {
        printf("%c", key[index] ? key[index] : '.');
    }
}

// This function uses the password provided by the user to create a key that will be used
// to encrypt some text. The password is used as a seed, and is placed randomly in the key.
// The remaining empty space in the key is filled with randomly generated characters. As long
// as the user's password is the same, the key will be the same, as the password is the seed
// for all randomly generated data
void createKey(unsigned char *password, unsigned char *key){
    // If the password is already the key limit (32), just set the key to be the password
    if (strlen(password) == KEY_SIZE){
        strcpy(key, password);
        return;
    }

    // Set the seed to the password
    unsigned int hash = hashString(password);
    srand(hash);

    // Calculate the last possible index we can place the password in the key
    int endIndex = KEY_SIZE - strlen(password) - 1;
    // Generate the index to place the password at
    int passIndex = rand() % endIndex;
    // Place password inside the key at index passIndex
    memcpy(key + passIndex, password, strlen(password));
    
    // TODO: randomly generate characters to fill in the empty space i.e. replace
    // all '\0' chars with randomly generated chars
    // Loop through each character in the key
    for (int index = 0; index < KEY_SIZE; index++){
        // Check for characters that are empty
        if (!key[index]){
            key[index] = 33 + rand() % (126 - 33 + 1);  // '!' to '~'
        }
    }
    key[KEY_SIZE-1] = '\0';
}

// This function hashes a string, converting it into an integer that can be used as a
// seed to generate random data
unsigned int hashString(const char *str){
    unsigned int hash = 5381;
    // val is the ascii value of the character
    int val;

    while ((val = *str++)) {
        hash = ((hash << 5) + hash) + val;
    }

    return hash;
}


// This function encrypts plainText with a given key
int encrypt(unsigned char *plainText, int plainTextLen, unsigned char *key, unsigned char *iv, unsigned char *cipherText){
    EVP_CIPHER_CTX *ctx;
    int len;
    int cipherTextLen;

    if (!(ctx = EVP_CIPHER_CTX_new())){
        exit(1);
    }

    if (EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv) != 1){
        exit(1);
    }

    if (EVP_EncryptUpdate(ctx, cipherText, &len, plainText, plainTextLen) != 1){
        exit(1);
    }

    cipherTextLen = len;

    if (EVP_EncryptFinal_ex(ctx, cipherText + len, &len) != 1){
        exit(1);
    }

    cipherTextLen += len;

    EVP_CIPHER_CTX_free(ctx);
    return cipherTextLen;
}

// This function decrypts plainText with a given key
int decrypt(unsigned char *cipherText, int cipherTextLen, unsigned char *key, unsigned char *iv, unsigned char *plainText){
    EVP_CIPHER_CTX *ctx;
    int len;
    int plainTextLen;

    if (!(ctx = EVP_CIPHER_CTX_new())){
        exit(1);
    }

    if (EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv) != 1){
        exit(1);
    }

    if (EVP_DecryptUpdate(ctx, plainText, &len, cipherText, cipherTextLen) != 1){
        exit(1);
    }

    plainTextLen = len;

    if (EVP_DecryptFinal_ex(ctx, plainText + len, &len) != 1){
        exit(1);
    }

    plainTextLen += len;

    EVP_CIPHER_CTX_free(ctx);
    return plainTextLen;
}