#ifndef MYSTRING_HPP
#define MYSTRING_HPP
#include <iostream> 
class MyString{
    private:
        char* data;
        int len;
    public:
        MyString();
        MyString(const char* str);
        MyString(const MyString& other);  

        ~MyString();
        char get(int i) const;
        void set(int i, char c);

        int size();

        void set_new_string(const char* str);
        void print();
        void read_line();
        int get_size() const;
        const char* get_data() const;//добавил для задания, чтобы в глобальных методах был доступ к данным
        
        MyString& operator=(const MyString& other);

        MyString& operator+=(const MyString& other);
        MyString& operator+=(const char* str);
        MyString operator+(const MyString& other) const;
        MyString operator+(const char* str) const;

        MyString(MyString&& other);
        MyString& operator=(MyString&& other);

        bool operator==(const MyString& other) const;
        bool operator<(const MyString& other) const;

        bool operator!=(const MyString& other) const;
        bool operator<=(const MyString& other) const; 

        char& operator[](int n);
};
MyString operator+(const char* str, const MyString& s);

bool operator==(const char* str, const MyString& s);
bool operator<(const char* str, const MyString& s);
bool operator!=(const char* str, const MyString& s);
bool operator<=(const char* str, const MyString& s);


std::ostream& operator<<(std::ostream& os, const MyString& s);
std::istream& operator>>(std::istream& is, MyString& s);

MyString addTxtExtension(const MyString &path);
#endif