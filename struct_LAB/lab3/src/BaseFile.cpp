#include "BaseFile.hpp"
#include <cstring>
#include <iostream>

using namespace std;


BaseFile::BaseFile():file(nullptr){
    mode[0]='\0';
    //cout << "BaseFile Конструктор по умолчанию" << '\n';
};
BaseFile::BaseFile(const char* path, const char* md){
    file = fopen(path, md);
    if (md) {
        strncpy(mode, md, 7);
        mode[7] = '\0';
    } else {
        mode[0] = '\0';
    }
    //cout << "BaseFile Конструктор (открытие файла)" <<'\n';

}
BaseFile::BaseFile(FILE* f): file(f){
    strcpy(mode,"rb+");
    //cout << "BaseFile Конструктор из FILE*" << '\n';
}
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
bool BaseFile::can_read() {
    if (!file) {
        return false;
    }
    if (strchr(mode, 'r') != nullptr || strchr(mode, '+') != nullptr) {
        int ch = fgetc(file);
        if (ch == EOF) {
            return false;
        }
        ungetc(ch, file);
        return true;
    }
    return false;
}


bool BaseFile::can_write(){// не учел этот момент с режимом, добавил поле mode
    if (!file)
        return false;
    return (strchr(mode, 'w') != nullptr || 
            strchr(mode, 'a') != nullptr || 
            strchr(mode, '+') != nullptr);
}

size_t BaseFile::write_raw(const void* buf, size_t n_bytes) {
    if (!file || !can_write()) return 0;
    return fwrite(buf, 1, n_bytes, file);
}
size_t BaseFile::read_raw(void* buf, size_t max_bytes) {
    if (!file || !can_read()) return 0;
    return fread(buf, 1, max_bytes, file);
}
long BaseFile::tell(){
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

BaseFile::BaseFile(BaseFile&& other) : file(other.file) {
    strncpy(this->mode, other.mode, 8);
    other.file = nullptr;// зануляем файл, чтобы деструктор не закрыл действующий 
    other.mode[0] = '\0';
}

BaseFile& BaseFile::operator=(BaseFile&& other) {
    if (this != &other) {
        if (file) fclose(file);
        this->file = other.file;
        strncpy(this->mode, other.mode, 8);

        other.file = nullptr;
        other.mode[0] = '\0';
    }
    return *this;
}