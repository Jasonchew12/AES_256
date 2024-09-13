#include "FileEncryption.h"
#include "AESCore.h"
#include <omp.h>

bool EncryptFile(const std::string& inFile, const std::string& outFile, unsigned char* key, enum keySize size) {
    const int blockSize = 16;  // AES block size is 128 bits (16 bytes)
    std::ifstream input(inFile, std::ios::binary);
    std::ofstream output(outFile, std::ios::binary);

    if (!input.is_open() || !output.is_open()) {
        std::cerr << "Failed to open files!" << std::endl;
        return false;
    }

    const int bufferBlocks = 8192;  // Number of blocks to read into memory at once
    unsigned char buffer[bufferBlocks * blockSize];
    unsigned char encrypted[bufferBlocks * blockSize];

    while (input.read(reinterpret_cast<char*>(buffer), bufferBlocks * blockSize) || input.gcount() > 0) {
        std::streamsize bytesRead = input.gcount();
        int blocksRead = static_cast<int>(bytesRead / blockSize);

        // Handle any partial blocks by padding
        if (bytesRead % blockSize != 0) {
            std::memset(buffer + bytesRead, 0, (blockSize - (bytesRead % blockSize)));
            blocksRead++;
        }

        // Parallel block encryption
#pragma omp parallel for
        for (int i = 0; i < blocksRead; ++i) {
            AES_Encrypt(buffer + (i * blockSize), encrypted + (i * blockSize), key, size);
        }

        // Write the encrypted blocks to the output file
        output.write(reinterpret_cast<char*>(encrypted), blocksRead * blockSize);
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

    const int bufferBlocks = 8192;  // Number of blocks to read into memory at once
    unsigned char buffer[bufferBlocks * blockSize];
    unsigned char decrypted[bufferBlocks * blockSize];

    while (input.read(reinterpret_cast<char*>(buffer), bufferBlocks * blockSize) || input.gcount() > 0) {
        std::streamsize bytesRead = input.gcount();
        int blocksRead = static_cast<int>(bytesRead / blockSize);

        // Handle any partial blocks by padding
        if (bytesRead % blockSize != 0) {
            std::memset(buffer + bytesRead, 0, (blockSize - (bytesRead % blockSize)));
            blocksRead++;
        }

        // Parallel block decryption
#pragma omp parallel for
        for (int i = 0; i < blocksRead; ++i) {
            AES_Decrypt(buffer + (i * blockSize), decrypted + (i * blockSize), key, size);
        }

        // Write the decrypted blocks to the output file
        output.write(reinterpret_cast<char*>(decrypted), blocksRead * blockSize);
    }

    input.close();
    output.close();
    return true;
}