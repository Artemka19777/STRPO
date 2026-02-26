#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>

#include "IFile.hpp"
#include "BaseFile.hpp"
#include "Base32File2.hpp"
#include "RleFile2.hpp"

using namespace std;

const size_t DATA_SIZE = 50 * 1024;
const size_t BUF_SIZE = 256;

bool test_file(IFile* file) {
    unsigned char* data = new unsigned char[DATA_SIZE];
    srand((unsigned int)time(nullptr));
    for (size_t i = 0; i < DATA_SIZE; i++)
        data[i] = rand() % 256;// случайные данные

    for (size_t i = 0; i < DATA_SIZE; i += BUF_SIZE) {
        size_t chunk = min(BUF_SIZE, DATA_SIZE - i);
        file->write(&data[i], chunk);//записываем данные по 256, либо меньше, если не влезает
    }

    unsigned char* read_data = new unsigned char[DATA_SIZE];
    memset(read_data, 0, DATA_SIZE);

    BaseFile* bf_ptr = dynamic_cast<BaseFile*>(file);
    if (bf_ptr)
        bf_ptr->seek(0);

    size_t total_read = 0;
    while (total_read < DATA_SIZE) {
        size_t chunk = min(BUF_SIZE, DATA_SIZE - total_read);
        size_t read_bytes = file->read(&read_data[total_read], chunk);
        if (read_bytes == 0) break;
        total_read += read_bytes;
    }

    bool ok = (total_read == DATA_SIZE) && (memcmp(data, read_data, DATA_SIZE) == 0);//проверка

    delete[] data;
    delete[] read_data;

    return ok;
}

int main() {
    const char* table = "ABCDEFGHIJKLMNOPQRSTUVWXYZ123456";
    {
        BaseFile bf("data/test_base.bin", "wb+");
        if (test_file(&bf))
            cout << "BaseFile: PASS\n";
        else
            cout << "BaseFile: FAIL\n";
    }
    {
        Base32File2 b32f(new BaseFile("data/test_b32.bin", "wb+"), table);
        if (test_file(&b32f))
            cout << "Base32File2: PASS\n";
        else
            cout << "Base32File2: FAIL\n";
    }
    {
        RleFile2 rf(new BaseFile("data/test_rle.bin", "wb+"));
        if (test_file(&rf))
            cout << "RleFile2: PASS\n";
        else
            cout << "RleFile2: FAIL\n";
    }
    {
        RleFile2 combo(
            new Base32File2(
                new Base32File2(new BaseFile("data/test_combo.bin", "wb+"), table),
                table
            )
        );
        if (test_file(&combo))
            cout << "Combo Base32 Base32 RLE: PASS\n";
        else
            cout << "Combo Base32 Base32 RLE: FAIL\n";
    }

    return 0;
}