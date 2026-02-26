#ifndef BASE
#define BASE
#include <cstdio> 
#include "IFile.hpp"

class BaseFile: public IFile{
    private:
        FILE* file;
    public:
        BaseFile();
        BaseFile(const char* path, const char* mode);
        BaseFile(FILE* f);
        virtual ~BaseFile();/*Рекомендуется делать виртуальными деструкторы для того, чтобы гарантировать
правильное освобождение памяти из-под динамического объекта,*/

        bool is_open();
        bool can_read();
        bool can_write();
        size_t write_raw(const void *buf, size_t n_bytes);
        size_t read_raw(void *buf, size_t max_bytes);
        long tell();
        bool seek(long offset);
        virtual size_t write(const void* buf, size_t n_bytes);
        virtual size_t read(void* buf, size_t max_bytes);//делаем виртуальными, чтобы переопределить

};

class Base32File: public BaseFile{//используем ключ доступа public, который фактически не вносит изменения в область видимости.
    private:
        char encode_table[33];
    public:
        Base32File();
        Base32File(const char* path, const char* mode, const char* custom_table = "ABCDEFGHIJKLMNOPQRSTUVWXYZ123456");
        Base32File(FILE* f, const char* custom_table = "ABCDEFGHIJKLMNOPQRSTUVWXYZ123456");
        
        int get_index(char c);
        size_t write(const void* buf, size_t n_bytes);
        size_t read(void* buf, size_t max_bytes);
        virtual ~Base32File();
};


class RleFile: public BaseFile{
    public:
        RleFile();
        RleFile(const char* path, const char* mode);
        RleFile(FILE* f);
        virtual ~RleFile();

        size_t write(const void* buf, size_t n_bytes);//опять переопределяем относительно BasicFile
        size_t read(void* buf, size_t max_bytes);
};


void write_int(IFile& f, int n);

#endif