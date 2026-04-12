#include "RleFile2.hpp"
#include "IFile.hpp"

RleFile2::RleFile2(IFile* file) : inner(file),pending_value(0), pending_count(0) {}

RleFile2::~RleFile2() {
    delete inner;
}

bool RleFile2::can_read() {
    return inner->can_read();
}

bool RleFile2::can_write() {
    return inner->can_write();
}

bool RleFile2::seek(long offset) {
    return inner->seek(offset);
}

long RleFile2::tell(){
    return inner->tell();
}

size_t RleFile2::write(const void* buf, size_t n_bytes) {
    const unsigned char* src = (const unsigned char*)buf;
    size_t i = 0;

    while (i < n_bytes) {
        unsigned char value = src[i];
        unsigned char count = 0;

        while (i < n_bytes && src[i] == value && count < 255) {
            count++;
            i++;
        }

        unsigned char pair[2] = {count, value};
        inner->write(pair, 2);
    }

    return n_bytes;
}

size_t RleFile2::read(void* buf, size_t max_bytes) {
    unsigned char* dst = (unsigned char*)buf;
    size_t total = 0;

    while (total < max_bytes) {
        if (pending_count > 0) {
            dst[total++] = pending_value;
            pending_count--;
            continue;
        }

        unsigned char pair[2];
        if (inner->read(pair, 2) < 2)
            break;

        pending_count = pair[0];
        pending_value = pair[1];
    }

    return total;
}