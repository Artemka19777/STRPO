#ifndef BASE32FILE2_HPP
#define BASE32FILE2_HPP

#include "IFile.hpp"

class Base32File2 : public IFile {
private:
    IFile* inner;
    char encode_table[33];
    int get_index(char c);

public:
    Base32File2(IFile* file, const char* table = "ABCDEFGHIJKLMNOPQRSTUVWXYZ123456");
    virtual ~Base32File2();

    bool can_read();
    bool can_write();

    size_t write(const void* buf, size_t n_bytes);
    size_t read(void* buf, size_t max_bytes);
};

#endif