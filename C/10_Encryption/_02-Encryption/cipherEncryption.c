/**
 * Practice with Encrypting a string using OpenSSL
 * 
 * Run this program using the following command:
 *      gcc cipherEncryption.c -lssl -lcrypto
 */

#include <stdio.h>
#include <string.h>
#include <openssl/evp.h>
#include <openssl/err.h>

#define KEY_SIZE 32   // AES-256
#define IV_SIZE 16    // AES block size
#define LINE_LENGTH 32

int encrypt(unsigned char *plainText, int plainTextLen, unsigned char *key, unsigned char *iv, unsigned char *cipherText);
int decrypt(unsigned char *cipherText, int cipherTextLen, unsigned char *key, unsigned char *iv, unsigned char *plainText);

int main(){
    unsigned char key[KEY_SIZE] = "01234567890123456789012345678901";
    unsigned char iv[IV_SIZE]  = "0123456789012345";

    unsigned char plainText[LINE_LENGTH];
    unsigned char cipherText[LINE_LENGTH];
    unsigned char decrypted[LINE_LENGTH];

    printf("\nEnter text to encrypt: ");
    // Read an entire line of text, including spaces and the newline
    fgets(plainText, LINE_LENGTH, stdin);
    // Remove the newline at the end of the string
    plainText[strcspn(plainText, "\n")] = '\0';

    int cipherTextLen = encrypt(plainText, strlen((char *)plainText), key, iv, cipherText);

    int decryptedLen = decrypt(cipherText, cipherTextLen, key, iv, decrypted);

    decrypted[decryptedLen] = '\0';

    printf("Original: %s\n", plainText);
    printf("Encrypted: %s\n", cipherText);
    printf("Decrypted: %s\n", decrypted);

    return 0;
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