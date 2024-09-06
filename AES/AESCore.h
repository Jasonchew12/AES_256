

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

void CreateExpandKey(unsigned char* expandedKey, unsigned char* key, enum keySize, size_t expandedKeySize);

// Implementation: AES Encryption
// Implementation: subBytes
void SubBytes(unsigned char* state);
// Implementation: shiftRows
void ShiftRows(unsigned char* state);
void ShiftRow(unsigned char* state, unsigned char nbr);
// Implementation: addRoundKey
void AddRoundKey(unsigned char* state, unsigned char* roundKey);
// Implementation: mixColumns
unsigned char Galois_Multiplication(unsigned char a, unsigned char b);
void MixColumns(unsigned char* state);
void MixColumn(unsigned char* column);

// Implementation: AES Decryption
// Implementation: Inverse Sub Bytes
void InvSubBytes(unsigned char* state);
// Implementation: Inverse Shift Row
void InvShiftRows(unsigned char* state);
void InvShiftRow(unsigned char* state, unsigned char nbr);
// Implementation: Inverse MixColumn
void InvMixColumns(unsigned char* state);
void InvMixColumn(unsigned char* column);


// Implementation: AES round
void AES_Round(unsigned char* state, unsigned char* roundKey);
void AES_InvRound(unsigned char* state, unsigned char* roundKey);
void CreateRoundKey(unsigned char* expandedKey, unsigned char* roundKey);
void AES_Main(unsigned char* state, unsigned char* expandedKey, int nbrRounds);


char AES_Encrypt(unsigned char* input, unsigned char* output, unsigned char* key, enum keySize size);
char AES_Decrypt(unsigned char* input, unsigned char* output, unsigned char* key,enum keySize size);
#endif 