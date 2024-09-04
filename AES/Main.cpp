// main.cpp
#include "AES.h"
#include <chrono>

void BasicAES()
{
    const int expandedKeySize = 240;

    // the expanded key
    unsigned char expandedKey[expandedKeySize];

    // the cipher key
    unsigned char key[32] = { "Hallo World" };

    // the cipher key size
    enum keySize size = SIZE_32;

    // the plaintext
    unsigned char plaintext[16] = { 'a', 'b', 'c', 'd', 'e', 'f', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0' };

    // the ciphertext
    unsigned char ciphertext[16];

    // the decrypted text
    unsigned char decryptedtext[16];

    expandKey(expandedKey, key, size, expandedKeySize);

    std::cout << "Expanded Key:\n";
    for (int i = 0; i < expandedKeySize; i++) {
        // Print the block number at the beginning of each new line
        if (i % 16 == 0) {
            std::cout << (i / 16 + 1) << ": ";  // Block number starts from 1
        }

        std::cout << std::hex << std::setw(2) << std::setfill('0')
            << static_cast<int>(expandedKey[i]);

        // Insert a space after each byte for readability
        if ((i + 1) % 16 == 0) {
            std::cout << std::endl;  // Print a newline after every 16 bytes
        }
        else {
            std::cout << " ";  // Print a space otherwise
        }
    }

    aes_encrypt(plaintext, ciphertext, key, size);
    printf("\n");

    for (int i = 0; i < 16; i++) {

        std::cout << std::hex << std::setw(2) << std::setfill('0')
            << static_cast<int>(plaintext[i]);

        // Insert a space after each byte for readability
        if ((i + 1) % 16 == 0) {
            std::cout << std::endl;  // Print a newline after every 16 bytes
        }
        else {
            std::cout << " ";  // Print a space otherwise
        }
    }

    printf("\n");
    for (int i = 0; i < 16; i++)
    {
        std::cout << std::hex << std::setw(2) << std::setfill('0')
            << static_cast<int>(ciphertext[i]);

        // Insert a space after each byte for readability
        if ((i + 1) % 16 == 0) {
            std::cout << std::endl;  // Print a newline after every 16 bytes
        }
        else {
            std::cout << " ";  // Print a space otherwise
        }
    }

}

void FileAES()
{

    unsigned char key[32] = { "Hallo World" };
    enum keySize size = SIZE_32;


    std::string inFile = "10mb.txt";
    std::string outFile = "encrypted_input.bin";


    std::ifstream input(inFile, std::ios::binary);
    if (!input.is_open()) {
        std::cerr << "Failed to open input file: " << inFile << std::endl;
        return;
    }
    else {
        std::cout << "Input file opened successfully: " << inFile << std::endl;
    }


    std::ofstream output(outFile, std::ios::binary);
    if (!output.is_open()) {
        std::cerr << "Failed to open output file: " << outFile << std::endl;
        return;
    }
    else {
        std::cout << "Output file created/opened successfully: " << outFile << std::endl;
    }


    input.close();
    output.close();

    auto start = std::chrono::high_resolution_clock::now();

    // Encrypt the file
    if (encryptFile(inFile, outFile, key, size)) {
        std::cout << "File encryption completed successfully!" << std::endl;
    }
    else {
        std::cerr << "File encryption failed!" << std::endl;
    }

    auto end = std::chrono::high_resolution_clock::now();

    // Calculate the duration
    std::chrono::duration<double> duration = end - start;

    // Output the duration
    std::cout << "Time taken for encryption: " << duration.count() << " seconds" << std::endl;


}
int main(int argc, char* argv[])
{
    FileAES();
    return 0;
}