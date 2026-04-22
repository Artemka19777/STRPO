#include "BoolArray.hpp"
#include <cstring>
#include <algorithm>

BoolArray::Bit::Bit(unsigned char& b, int pos) : byte(b), bit_pos(pos) {}
BoolArray::Bit& BoolArray::Bit::operator=(bool val) {
    if (val) byte |= (1 << bit_pos);// если аргумент true то ставим 1, иначе 0
    else byte &= ~(1 << bit_pos);
    return *this;
}
BoolArray::Bit& BoolArray::Bit::operator=(const Bit& cp) {
    return *this = (bool)cp; //пользуемся оператором = предыдущим
}
BoolArray::Bit::operator bool() const {
    return (byte >> bit_pos) & 1; //сдвигаем нужный бит в начало и проверяем его
}
BoolArray::BoolArray(int size, bool default_val) : n_bits(size) {
    int n_bytes = (n_bits + 7) / 8;// формула для подсчета байт
    data = new unsigned char[n_bytes];
    std::memset(data, default_val ? 0xFF : 0x00, n_bytes);// заполняем либо 0, либо 1
}
BoolArray::BoolArray(const BoolArray& other) : n_bits(other.n_bits) {
    int n_bytes = (n_bits + 7) / 8;
    data = new unsigned char[n_bytes];
    std::memcpy(data, other.data, n_bytes);
}
BoolArray::~BoolArray() {
    delete[] data;
}
BoolArray& BoolArray::operator=(const BoolArray& other) {
    if (this != &other) {
        delete[] data;
        n_bits = other.n_bits;
        int n_bytes = (n_bits + 7) / 8;
        data = new unsigned char[n_bytes];
        std::memcpy(data, other.data, n_bytes);
    }
    return *this;
}
int BoolArray::size() const { 
    return n_bits; 
}

BoolArray::Bit BoolArray::operator[](int i) {
    return Bit(data[i / 8], i % 8); // находим нужный бит в байте
}
bool BoolArray::operator[](int i) const {
    return (data[i / 8] >> (i % 8)) & 1;// для получения значения
}
void BoolArray::resize(int new_size, bool fill_val) {
    int old_bytes = (n_bits + 7) / 8;
    int new_bytes = (new_size + 7) / 8;

    unsigned char* new_data = new unsigned char[new_bytes];
    int copy_bytes = std::min(old_bytes, new_bytes);
    
    std::memcpy(new_data, data, copy_bytes);

    if (new_bytes > old_bytes) {// если новый размер больше, то нужно добавить 0
        std::memset(new_data + old_bytes, fill_val ? 0xFF : 0x00, new_bytes - old_bytes);
    }

    delete[] data;
    data = new_data;
    n_bits = new_size;
}