// main.cpp
#include "AES.h"
#include <chrono>
#include <cstdlib>
void DisplayAESExplanationkey(unsigned char* key, enum keySize size)
{
    const int expandedKeySizeDisplay = 240;

    // the expanded key
    unsigned char expandedKeyDisplay[expandedKeySizeDisplay];


    CreateExpandKey(expandedKeyDisplay, key, size, expandedKeySizeDisplay);

    std::cout << "Expanded Key:\n";
    for (int i = 0; i < expandedKeySizeDisplay; i++) {
        // Print the block number at the beginning of each new line
        if (i % 16 == 0) {
            std::cout << (i / 16 + 1) << ": ";  // Block number starts from 1
        }

        std::cout << std::hex << std::setw(2) << std::setfill('0')
            << static_cast<int>(expandedKeyDisplay[i]);

        // Insert a space after each byte for readability
        if ((i + 1) % 16 == 0) {
            std::cout << std::endl;  // Print a newline after every 16 bytes
        }
        else {
            std::cout << " ";  // Print a space otherwise
        }
    }


    printf("\nExpanded Key (HEX format):\n");

    for (int i = 0; i < expandedKeySizeDisplay; i++)
    {
        printf("%2.2x%c", expandedKeyDisplay[i], ((i + 1) % 16) ? ' ' : '\n');
    }



}

void FileAES()
{


    unsigned char key[32] = { "HalloWorldThisIsAStringOfLetter" };
    enum keySize size = SIZE_32;

    
    DisplayAESExplanationkey(key,size);
 
    std::string inFile = "FileToEncrypt/10mb-examplefile-com.txt";
    std::string outFile = "EncryptFile/10mbEncryptedCUDA.bin";
    


    std::ifstream encryptInput(inFile, std::ios::binary);
    if (!encryptInput.is_open()) {
        std::cerr << "Failed to open input file: " << inFile << std::endl;
        return;
    }
    else {
        std::cout << "Input file opened successfully: " << inFile << std::endl;
    }


    std::ofstream encrypOutput(outFile, std::ios::binary);
    if (!encrypOutput.is_open()) {
        std::cerr << "Failed to open output file: " << outFile << std::endl;
        return;
    }
    else {
        std::cout << "Output file created/opened successfully: " << outFile << std::endl;
    }


    encryptInput.close();
    encrypOutput.close();

    auto start = std::chrono::high_resolution_clock::now();

    // Encrypt the file
    if (EncryptFile(inFile, outFile, key, size)) {
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


    std::string DecryptOutputFile = "DecryptFile/10mbText_unencrypted.txt";

    std::ifstream DecryptInput(outFile, std::ios::binary);
    if (!DecryptInput.is_open()) {
        std::cerr << "Failed to open input file: " << outFile << std::endl;
        return;
    }
    else {
        std::cout << "Input file opened successfully: " << outFile << std::endl;
    }


    std::ofstream DecryptOutput(DecryptOutputFile, std::ios::binary);
    if (!DecryptOutput.is_open()) {
        std::cerr << "Failed to open output file: " << DecryptOutputFile << std::endl;
        return;
    }
    else {
        std::cout << "Output file created/opened successfully: " << DecryptOutputFile << std::endl;
    }


    DecryptInput.close();
    DecryptOutput.close();


    auto DecryptStart = std::chrono::high_resolution_clock::now();

    // Encrypt the file
    if (DecryptFile(outFile, DecryptOutputFile, key, size)) {
        std::cout << "File encryption completed successfully!" << std::endl;
    }
    else {
        std::cerr << "File encryption failed!" << std::endl;
    }

    auto DecryptEnd = std::chrono::high_resolution_clock::now();

    // Calculate the duration
    std::chrono::duration<double> decryptDuration = DecryptEnd - DecryptStart;

    // Output the duration
    std::cout << "Time taken for Decryption: " << decryptDuration.count() << " seconds" << std::endl;

    std::string openOriginalFileCommand = "start " + inFile;
    system(openOriginalFileCommand.c_str());

    std::string openDecryptedFileCommand = "start " + DecryptOutputFile;
    system(openDecryptedFileCommand.c_str());

}
int main(int argc, char* argv[])
{
    FileAES();
    return 0;
}