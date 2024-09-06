#include "FileEncryption.h"
#include "AESCore.h"


bool EncryptFile(const std::string& inFile, const std::string& outFile, unsigned char* key, enum keySize size) {
    const int blockSize = 16;  // AES block size is 128 bits (16 bytes)
    std::ifstream input(inFile, std::ios::binary);
    std::ofstream output(outFile, std::ios::binary);

    if (!input.is_open() || !output.is_open()) {
        std::cerr << "Failed to open files!" << std::endl;
        return false;
    }

    unsigned char buffer[blockSize];
    unsigned char encrypted[blockSize];

    while (input.read(reinterpret_cast<char*>(buffer), blockSize)) {
        AES_Encrypt(buffer, encrypted, key, size);
        output.write(reinterpret_cast<char*>(encrypted), blockSize);
    }

    // Handle any remaining bytes (padding if necessary)
    std::streamsize bytesRead = input.gcount();
    if (bytesRead > 0) {
        // Padding with 0s to make it up to the block size
        std::memset(buffer + bytesRead, 0, blockSize - bytesRead);
        AES_Encrypt(buffer, encrypted, key, size);
        output.write(reinterpret_cast<char*>(encrypted), blockSize);
    }

    input.close();
    output.close();
    return true;
}

bool DecryptFile(const std::string& inFile, const std::string& outFile, unsigned char* key, enum keySize size) {
    const int blockSize = 16;  // AES block size is 128 bits (16 bytes)
    std::ifstream input(inFile, std::ios::binary);
    std::ofstream output(outFile, std::ios::binary);

    if (!input.is_open() || !output.is_open()) {
        std::cerr << "Failed to open files!" << std::endl;
        return false;
    }

    unsigned char buffer[blockSize];
    unsigned char decrypted[blockSize];

    while (input.read(reinterpret_cast<char*>(buffer), blockSize)) {
        AES_Decrypt(buffer, decrypted, key, size);
        output.write(reinterpret_cast<char*>(decrypted), blockSize);
    }

    // Handle any remaining bytes (padding if necessary)
    std::streamsize bytesRead = input.gcount();
    if (bytesRead > 0) {
        // Padding with 0s to make it up to the block size
        std::memset(buffer + bytesRead, 0, blockSize - bytesRead);
        AES_Decrypt(buffer, decrypted, key, size);
        output.write(reinterpret_cast<char*>(decrypted), blockSize);
    }

    input.close();
    output.close();
    return true;
}