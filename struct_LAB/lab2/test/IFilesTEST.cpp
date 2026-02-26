#include "../src/BaseFile.hpp"
#include "../src/RleFile2.hpp"
#include "../src/Base32File2.hpp"
#include <ctime>
#include <iostream>
#include <cstring>

int main() {

    const char* filename = "data/test_chain_temp.txt";
    const size_t DATA_SIZE = 1 * 1024;

    char* originalData = new char[DATA_SIZE];
    char* readData = new char[DATA_SIZE];

    std::srand(static_cast<unsigned>(std::time(nullptr)));

    for (size_t i = 0; i < DATA_SIZE; ++i) {
        originalData[i] = static_cast<char>(65 + (std::rand() % 26));
    }

    std::cout << "Generated " << DATA_SIZE << " bytes of random data" << std::endl;

    {
        BaseFile* baseFile = new BaseFile(filename, "wb");
        Base32File2* b32_outer = new Base32File2(baseFile);
        RleFile2* rle = new RleFile2(b32_outer);

        size_t total_writeen = 0;
        while (total_writeen < DATA_SIZE)
        {
            size_t written = rle->write(originalData+total_writeen, 256);
            total_writeen += written;
        }

        std::cout << "Total written: " << total_writeen << " bytes" << std::endl;
        delete rle;
    }

    {
        BaseFile* baseFile = new BaseFile(filename, "rb");
        Base32File2* b32_outer = new Base32File2(baseFile);
        RleFile2* rle = new RleFile2(b32_outer);
        
        size_t totalRead = 0;
        
        while (totalRead < DATA_SIZE) {
            size_t read = rle->read(readData + totalRead, 256);
            totalRead += read;
        }
        std::cout << "Total read: " << totalRead << " bytes" << std::endl;
        delete rle;
    }

    bool match = true;
    for (size_t i = 0; i < DATA_SIZE; ++i) {
        if (originalData[i] != readData[i]) {
            match = false;
            std::cout << "Mismatch at position " << i << ": ";
            break;
        }
    }
    
    if (match) {
        std::cout << "Bytes match successfully!" << std::endl;
    }

    delete[] originalData;
    delete[] readData;

    return 0;
}
