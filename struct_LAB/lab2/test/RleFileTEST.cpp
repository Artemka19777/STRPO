#include "../src/BaseFile.hpp"
#include <ctime>
#include <iostream>

int main() {
    const char* filename = "data/test_rle_temp.txt";
    const size_t DATA_SIZE = 50 * 1024;
    char* originalData = new char[DATA_SIZE];
    char* readData = new char[DATA_SIZE];

    std::srand(static_cast<unsigned>(std::time(nullptr)));

    for (size_t i = 0; i < DATA_SIZE; ++i) {
        originalData[i] = static_cast<char>(65 + (std::rand() % 26));
    }
    std::cout << "Generated " << DATA_SIZE << " bytes of random data" << std::endl;

    {
        RleFile reader(filename, "w+");
        size_t totalWritten = 0;
        
        while (totalWritten < DATA_SIZE) {            
            size_t written = reader.write(originalData + totalWritten, 256);
            totalWritten += written;
        }

        std::cout << "Total written: " << totalWritten << " bytes" << std::endl;
    }

    {
        RleFile reader(filename, "r+");
        size_t totalRead = 0;
        
        while (totalRead < DATA_SIZE) {
            size_t read = reader.read(readData + totalRead, 256);
            totalRead += read;
        }
        std::cout << "Total read: " << totalRead << " bytes" << std::endl;

        bool match = true;
        for (size_t i = 0; i < totalRead; ++i) {
            if (originalData[i] != readData[i]) {
                match = false;
                std::cout << "Mismatch at position " << i << ": " << originalData[i] << " - " << readData[i] << std::endl;
                break;
            }
        }

        if (match) {std::cout << "Bytes match successfully!" << std::endl;}
    }
    
    delete[] originalData;
    delete[] readData;
    
}