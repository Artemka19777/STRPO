#include "../src/BaseFile.hpp"
#include <ctime>
#include <iostream>

int main() {
    const char* filename = "data/test_rle_temp.txt";
    const size_t DATA_SIZE = 1024;
    char* originalData = new char[DATA_SIZE];
    char* readData = new char[DATA_SIZE];
    
    srand(static_cast<unsigned>(time(nullptr)));
    
    size_t pos = 0;
    int series_lengths[] = {1, 2, 5, 10, 20, 50, 100, 200, 255, 100, 50, 20, 10, 5, 2, 1};
    int num_series = sizeof(series_lengths) / sizeof(series_lengths[0]);
    int series_index = 0;
    //добавил подряд идущие символы
    while (pos < DATA_SIZE) {
        int len = series_lengths[series_index % num_series];
        series_index++;
        
        if (pos + len > DATA_SIZE) {
            len = DATA_SIZE - pos;
        }
        
        char c = 'A' + (rand() % 26);
        
        for (int i = 0; i < len; i++) {
            originalData[pos++] = c;
        }
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