#ifndef RLEFILE2_HPP
#define RLEFILE2_HPP

#include "IFile.hpp"

class RleFile2 : public IFile {
private:
    IFile* inner;

public:
    RleFile2(IFile* file);
    virtual ~RleFile2();

    bool can_read() override;
    bool can_write() override;

    size_t write(const void* buf, size_t n_bytes) override;
    size_t read(void* buf, size_t max_bytes) override;
};

#endif