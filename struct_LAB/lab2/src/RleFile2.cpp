#include "RleFile2.hpp"
#include "IFile.hpp"

RleFile2::RleFile2(IFile* file) : inner(file) {}

RleFile2::~RleFile2() {
    delete inner;
}

bool RleFile2::can_read() {
    return inner->can_read();
}

bool RleFile2::can_write() {
    return inner->can_write();
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
        unsigned char pair[2];
        if (inner->read(pair, 2) < 2)
            break;

        unsigned char count = pair[0];
        unsigned char value = pair[1];

        for (int i = 0; i < count && total < max_bytes; i++) {
            dst[total++] = value;
        }
    }

    return total;
}