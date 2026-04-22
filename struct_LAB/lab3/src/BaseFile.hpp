#ifndef BASE
#define BASE
#include <cstdio>
class IFile {
    public:
        virtual bool can_read()=0;
        virtual bool can_write()=0;
        virtual size_t write(const void* buf, size_t n_bytes)=0;
        virtual size_t read(void* buf, size_t max_bytes)=0;
        virtual ~IFile()=0;
        virtual bool seek(long offset)=0; 
        virtual long tell()=0; 
};
inline IFile::~IFile() {}
class BaseFile: public IFile{
    private:
        FILE* file;
        char mode[8];
    public:
        BaseFile();
        BaseFile(const char* path, const char* md);
        BaseFile(FILE* f);
        virtual ~BaseFile();/*Рекомендуется делать виртуальными деструкторы для того, чтобы гарантировать
правильное освобождение памяти из-под динамического объекта,*/
        BaseFile(const BaseFile& other) = delete;
        BaseFile& operator=(const BaseFile& other) = delete;

        BaseFile(BaseFile&& other);//move конструктор
        BaseFile& operator=(BaseFile&& other); //move оператор присваивания

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



#endif