/**
 * Practice with Encrypting a string using OpenSSL
 * 
 * Run this program using the following command:
 *      gcc cipherFileEncryption.c -lssl -lcrypto
 *      a original.txt encrypted.bin decrypted.txt
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>

#define KEY_SIZE 32   // AES-256
#define IV_SIZE 16    // AES block size
#define BUFFER_SIZE 4096

void encrypt_file(const char *input, const char *output, unsigned char *key, unsigned char *iv);
void decrypt_file(const char *input, const char *output, unsigned char *key, unsigned char *iv);

int main(int argc, char *argv[]){
    if (argc != 4) {
        printf("Usage: %s <input> <encrypted> <decrypted>\n", argv[0]);
        return 1;
    }

    unsigned char key[KEY_SIZE] = "01234567890123456789012345678901";
    unsigned char iv[IV_SIZE]  = "0123456789012345";

    encrypt_file(argv[1], argv[2], key, iv);
    decrypt_file(argv[2], argv[3], key, iv);

    printf("Encryption and decryption complete.\n");
    return 0;

    return 0;
}

// This function encrypts an input file with a given key
void encrypt_file(const char *input, const char *output, unsigned char *key, unsigned char *iv){
    FILE *fin = fopen(input, "rb");
    FILE *fout = fopen(output, "wb");

    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();

    unsigned char inbuf[BUFFER_SIZE];
    unsigned char outbuf[BUFFER_SIZE + EVP_MAX_BLOCK_LENGTH];
    int inlen, outlen;

    EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv);

    while ((inlen = fread(inbuf, 1, BUFFER_SIZE, fin)) > 0) {
        EVP_EncryptUpdate(ctx, outbuf, &outlen, inbuf, inlen);
        fwrite(outbuf, 1, outlen, fout);
    }

    EVP_EncryptFinal_ex(ctx, outbuf, &outlen);
    fwrite(outbuf, 1, outlen, fout);

    EVP_CIPHER_CTX_free(ctx);
    fclose(fin);
    fclose(fout);
}

// This function decrypts an encrypted file with a given key
void decrypt_file(const char *input, const char *output, unsigned char *key, unsigned char *iv){
    FILE *fin = fopen(input, "rb");
    FILE *fout = fopen(output, "wb");

    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();

    unsigned char inbuf[BUFFER_SIZE];
    unsigned char outbuf[BUFFER_SIZE];
    int inlen, outlen;

    EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv);

    while ((inlen = fread(inbuf, 1, BUFFER_SIZE, fin)) > 0) {
        EVP_DecryptUpdate(ctx, outbuf, &outlen, inbuf, inlen);
        fwrite(outbuf, 1, outlen, fout);
    }

    EVP_DecryptFinal_ex(ctx, outbuf, &outlen);
    fwrite(outbuf, 1, outlen, fout);

    EVP_CIPHER_CTX_free(ctx);
    fclose(fin);
    fclose(fout);
}