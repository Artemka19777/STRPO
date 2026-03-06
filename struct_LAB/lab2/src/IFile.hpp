#ifndef IFILE
#define IFILE
#include <cstdio> 
#include <cstddef>
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
#endif