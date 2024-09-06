
// FileEncryption.h
#ifndef FILEENCRYPTION_H
#define FILEENCRYPTION_H

#include <fstream>
#include <cstring>
#include <string>
bool EncryptFile(const std::string& inFile, const std::string& outFile, unsigned char* key, enum keySize size);
bool DecryptFile(const std::string& inFile, const std::string& outFile, unsigned char* key, enum keySize size);

#endif // FILEENCRYPTION_H
