#include "Base32File2.hpp"
#include <cstring>
#include "IFile.hpp"

Base32File2::Base32File2(IFile* file, const char* table): inner(file){
    strncpy(encode_table, table, 32);
    encode_table[32] = '\0';
}

Base32File2::~Base32File2() {
    delete inner;
}

bool Base32File2::can_read() {
    return inner->can_read();
}

bool Base32File2::can_write() {
    return inner->can_write();
}

int Base32File2::get_index(char c) {
    for (int i = 0; i < 32; i++)
        if (encode_table[i] == c)
            return i;
    return -1;
}

size_t Base32File2::write(const void* buf, size_t n_bytes) {
    if (!inner->can_write() || n_bytes == 0)
        return 0;

    const unsigned char* raw = (const unsigned char*)buf;

    unsigned int bit_buffer = 0;
    int bits = 0;

    char encoded[2048];
    size_t out = 0;

    for (size_t i = 0; i < n_bytes; i++) {
        bit_buffer = (bit_buffer << 8) | raw[i];
        bits += 8;

        while (bits >= 5) {
            encoded[out++] =
                encode_table[(bit_buffer >> (bits - 5)) & 0x1F];
            bits -= 5;
        }
    }

    if (bits > 0) {
        encoded[out++] =
            encode_table[(bit_buffer << (5 - bits)) & 0x1F];
    }

    inner->write(encoded, out);
    return n_bytes;
}

size_t Base32File2::read(void* buf, size_t max_bytes) {
    if (!inner->can_read() || max_bytes == 0)
        return 0;

    char encoded[2048];
    size_t read_bytes = inner->read(encoded, sizeof(encoded));

    unsigned char* dst = (unsigned char*)buf;

    unsigned int bit_buffer = 0;
    int bits = 0;
    size_t out = 0;

    for (size_t i = 0; i < read_bytes; i++) {
        int val = get_index(encoded[i]);
        if (val == -1)
            break;

        bit_buffer = (bit_buffer << 5) | val;
        bits += 5;

        while (bits >= 8 && out < max_bytes) {
            dst[out++] =
                (bit_buffer >> (bits - 8)) & 0xFF;
            bits -= 8;
        }
    }

    return out;
}