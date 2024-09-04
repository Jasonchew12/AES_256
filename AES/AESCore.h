

#ifndef AESCORE_H
#define AESCORE_H

#include <iostream>
#include <cstddef>

enum errorCode
{
    SUCCESS = 0,
    UNKNOWN_KEYSIZE,
    MEMORY_ALLOCATION_PROBLEM,
};

enum keySize {
    SIZE_16 = 16,
    SIZE_24 = 24,
    SIZE_32 = 32
};

void expandKey(unsigned char* expandedKey, unsigned char* key, enum keySize, size_t expandedKeySize);

// Implementation: AES Encryption
// Implementation: subBytes
void subBytes(unsigned char* state);
// Implementation: shiftRows
void shiftRows(unsigned char* state);
void shiftRow(unsigned char* state, unsigned char nbr);
// Implementation: addRoundKey
void addRoundKey(unsigned char* state, unsigned char* roundKey);
// Implementation: mixColumns
unsigned char galois_multiplication(unsigned char a, unsigned char b);
void mixColumns(unsigned char* state);
void mixColumn(unsigned char* column);

// Implementation: AES Decryption
// Implementation: Inverse Sub Bytes
void invSubBytes(unsigned char* state);
// Implementation: Inverse Shift Row
void invShiftRows(unsigned char* state);
void invShiftRow(unsigned char* state, unsigned char nbr);
// Implementation: Inverse MixColumn
void invMixColumns(unsigned char* state);
void invMixColumn(unsigned char* column);


// Implementation: AES round
void aes_round(unsigned char* state, unsigned char* roundKey);
void aes_invRound(unsigned char* state, unsigned char* roundKey);
void createRoundKey(unsigned char* expandedKey, unsigned char* roundKey);
void aes_main(unsigned char* state, unsigned char* expandedKey, int nbrRounds);


char aes_encrypt(unsigned char* input, unsigned char* output, unsigned char* key, enum keySize size);
#endif 