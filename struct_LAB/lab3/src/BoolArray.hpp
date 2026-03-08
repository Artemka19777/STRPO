#ifndef BOOL_ARRAY_HPP
#define BOOL_ARRAY_HPP

#include <iostream>
class BoolArray{
    private:
        unsigned char* data;// массив байтов
        int n_bits;  
        class Bit{
            private:
                unsigned char& byte;
                int bit_pos;
            public:
                Bit(unsigned char& b, int pos);
                Bit& operator=(bool val);//для записи: ar[i] = true
                Bit& operator=(const Bit& cp);// для копирования значения
                operator bool() const;// для чтения: if(ar[i])

        };
    public:
        BoolArray(int size, bool default_val = false);
        BoolArray(const BoolArray& other);
        ~BoolArray();
        BoolArray& operator=(const BoolArray& other);
        Bit operator[](int i);
        bool operator[](int i) const;
        int size() const;
        void resize(int new_size, bool fill_val = false);
};

#endif