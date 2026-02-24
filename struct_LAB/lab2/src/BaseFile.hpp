#ifndef BASE
#define BASE
#include <cstdio> 
class BaseFile{
    private:
        FILE* file;
    public:
        BaseFile();
        BaseFile(const char* path, const char* mode);
        BaseFile(FILE* f);
        ~BaseFile();

        bool is_open();
        bool can_read();
        bool can_write();
        size_t write_raw(const void *buf, size_t n_bytes);
        size_t read_raw(void *buf, size_t max_bytes);
        long tell() const;
        bool seek(long offset);
        size_t write(const void* buf, size_t n_bytes);
        size_t read(void* buf, size_t max_bytes);


};

#endif