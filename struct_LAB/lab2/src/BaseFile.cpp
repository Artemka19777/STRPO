#include "BaseFile.hpp"

BaseFile::BaseFile():file(nullptr){};
BaseFile::BaseFile(const char* path, const char* mode){
    file = fopen(path, mode);
}
BaseFile::BaseFile(FILE* f): file(f){};
BaseFile::~BaseFile(){//нужно прописать деструктор, т.к. без закрытия файла, память не осовбождается
    if (file){
        fclose(file);
        file = nullptr;
    }
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