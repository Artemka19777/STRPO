#include "BaseFile.hpp"
#include <cstring>
#include <iostream>

using namespace std;

BaseFile::BaseFile():file(nullptr){
    //cout << "BaseFile Конструктор по умолчанию" << '\n';
};
BaseFile::BaseFile(const char* path, const char* mode){
    file = fopen(path, mode);
    //cout << "BaseFile Конструктор (открытие файла)" <<'\n';

}
BaseFile::BaseFile(FILE* f): file(f){
    //cout << "BaseFile Конструктор из FILE*" << '\n';
};
BaseFile::~BaseFile(){//нужно прописать деструктор, т.к. без закрытия файла, память не осовбождается
    if (file){
        fclose(file);
        file = nullptr;
    }
    //cout << "BaseFile деструктор" << '\n';
}
bool BaseFile::is_open(){
    return file != nullptr;
}
bool BaseFile::can_read(){
    if (!file) {
        return false;
    }
    int ch = fgetc(file);
    if (ch == EOF) {
        return false;
    }
    ungetc(ch, file);
    return true;
}

bool BaseFile::can_write(){
    return file != nullptr;
}

size_t BaseFile::write_raw(const void* buf, size_t n_bytes) {
    if (!file) return 0;
    return fwrite(buf, 1, n_bytes, file);
}
size_t BaseFile::read_raw(void* buf, size_t max_bytes) {
    if (!file) return 0;
    return fread(buf, 1, max_bytes, file);
}
long BaseFile::tell() const{
    if (!file) return -1;
    return ftell(file);
}

bool BaseFile::seek(long offset) {
    if (!file) return false;
    return fseek(file, offset, SEEK_SET) == 0;
}

size_t BaseFile::write(const void* buf, size_t n_bytes) {
    return write_raw(buf, n_bytes);
}

size_t BaseFile::read(void* buf, size_t max_bytes) {
    return read_raw(buf, max_bytes);
}

//BASE32

Base32File:: Base32File(): BaseFile(){//вызываем конструктор по умолчанию родительского класса(необходимо)
    strcpy(encode_table, "ABCDEFGHIJKLMNOPQRSTUVWXYZ123456");
    //cout << "Base32File Конструктор по умолчанию" <<'\n';
}

Base32File::Base32File(const char* path, const char* mode, const char* custom_table) 
    : BaseFile(path, mode) {
    strncpy(encode_table, custom_table, 32);
    encode_table[32] = '\0';
    //cout << "Base32File Конструктор с параметрами" <<'\n';
}

Base32File::Base32File(FILE* f, const char* custom_table) : BaseFile(f) {
    strncpy(encode_table, custom_table, 32);
    encode_table[32] = '\0';
    //cout << "Base32File Конструктор из FILE" <<'\n';
}

int Base32File::get_index(char c){
    for (int i = 0; i < 32; i++) {
        if (encode_table[i] == c) return i;
    }
    return -1;
}

size_t Base32File::write(const void* buf, size_t n_bytes) {
    if (!is_open() || n_bytes == 0) return 0;

    const unsigned char* raw_data = static_cast<const unsigned char*>(buf);
    
    size_t encoded_len = (n_bytes * 8 + 4) / 5;
    char* encoded_buf = new char[encoded_len];

    unsigned int bit_buffer = 0;
    int bits_in_count = 0;
    size_t out_pos = 0;

    for (size_t i = 0; i < n_bytes; i++) {
        bit_buffer = (bit_buffer << 8) | raw_data[i];
        bits_in_count += 8;
        while (bits_in_count >= 5) {
            encoded_buf[out_pos++] = encode_table[(bit_buffer >> (bits_in_count - 5)) & 0x1F];
            bits_in_count -= 5;
        }
    }

    if (bits_in_count > 0) {
        encoded_buf[out_pos++] = encode_table[(bit_buffer << (5 - bits_in_count)) & 0x1F];
    }

    size_t written_raw = write_raw(encoded_buf, out_pos);//записываем закоидрованные данные в файл с помощью переопределенного метода write
    
    delete[] encoded_buf;
    
    // Возвращаем кол-во успешно обработанных исходных байт
    
    if(written_raw == out_pos)
        return n_bytes;
    return 0; 
}

size_t Base32File::read(void* buf, size_t max_bytes) {
    if (!is_open() || max_bytes == 0) return 0;

    size_t bytes_to_read = (max_bytes * 8) / 5;
    char* read_buf = new char[bytes_to_read];
    size_t actual_read = read_raw(read_buf, bytes_to_read);

    unsigned char* dst = static_cast<unsigned char*>(buf);
    unsigned int bit_buffer = 0;
    int bits_in_count = 0;
    size_t out_pos = 0;

    for (size_t i = 0; i < actual_read; i++) {
        int val = get_index(read_buf[i]);
        if (val == -1) break;

        bit_buffer = (bit_buffer << 5) | (val & 0x1F);
        bits_in_count += 5;

        while (bits_in_count >= 8 && out_pos < max_bytes) {
            dst[out_pos++] = (bit_buffer >> (bits_in_count - 8)) & 0xFF;
            bits_in_count -= 8;
        }
    }

    delete[] read_buf;
    return out_pos;
}

Base32File::~Base32File() {
    //cout << "Base32File Деструктор"<<'\n';
}

//RLE

RleFile:: RleFile() : BaseFile() {
    //cout << "RleFile Конструктор по умолчанию" << '\n';

}
RleFile:: RleFile(const char* path, const char* mode) : BaseFile(path, mode) {
    //cout << "RleFile Конструктор c параметрами" << '\n';
}
RleFile:: RleFile(FILE* f) : BaseFile(f) {
    //cout << "RleFile Конструктор из FILE" << '\n';
}

size_t RleFile::write(const void* buf, size_t n_bytes) {
    if (!is_open() || n_bytes == 0) return 0;
    const unsigned char* src = (const unsigned char*)buf;
    
    size_t i = 0;
    size_t total = 0;

    while (i < n_bytes) {
        unsigned char current_char = src[i];
        unsigned char count = 0;

        while (i < n_bytes && src[i] == current_char && count < 255) {//идем пока символ поворяется и считаем количество
            count++;
            i++;
        }
        //как только закончились повторяющиеся символы записываем результат 
        unsigned char pair[2] = { count, current_char };
        total += write_raw(pair, 2);
    }
    return n_bytes;
}

size_t RleFile::read(void* buf, size_t max_bytes) {
    if (!is_open() || max_bytes == 0) return 0;
    unsigned char* dst = (unsigned char*)buf;
    size_t total = 0;

    while (total< max_bytes) {
        unsigned char header[2];
        if (read_raw(header, 2) < 2) break; 

        unsigned char count = header[0];
        unsigned char val = header[1];

        for (int i = 0; i < count && total < max_bytes; i++) {
            dst[total++] = val;
        }
    }
    return total;
}

RleFile::~RleFile() {
    //cout << "RleFile деструктор" << '\n';
}


void write_int(IFile& f, int n){
    if (n == 0)
        f.write("0", 1);
    if (n < 0){
        f.write("-", 1);
        n = -n;
    }
    char buf[20]; // Буфер для числа
    int i = 0;
    while (n > 0) {
        buf[i++] = (n % 10) + '0'; // т.к. int более точный тип '0' приводится к типу int = 48, далее число приводится к char 
        n /= 10;
    }
    while (i > 0) {
        f.write(&buf[--i], 1);// меняем порядок цифр 
    }
}