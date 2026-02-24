#include "MyString.hpp"
#include <iostream>
#include <cstring>

using namespace std;

MyString::MyString() : data(nullptr), len(0) {}

MyString::MyString(const char* str) {
    if (!str) {
        data = nullptr;
        len = 0;
        return;
    }
    len = strlen(str);
    data = new char[len + 1];
    strcpy(data, str);
}
MyString::MyString(const MyString& other) {
    len = other.len;
    if (len > 0) {
        data = new char[len + 1];
        strcpy(data, other.data);
    } else {
        data = nullptr;
    }
}
MyString::~MyString() {
    delete[] data;
}
char MyString::get(int i) const{
    return data[i];
}
void MyString::set(int i, char c) {
    data[i] = c;
}
int MyString::size(){
    return len;
}
void MyString::set_new_string(const char* str){
    delete[] data;
    if (!str) {
        data = nullptr;
        len = 0;
        return;
    }
    len =strlen(str);
    data = new char[strlen(str)+1];
    strcpy(data, str); 
}
void MyString::print(){
    if (data) cout << data;
}
void MyString::read_line() {
    delete[] data;

    const int BUF_SIZE = 1024;
    char buffer[BUF_SIZE];

    cin.getline(buffer, BUF_SIZE);
    len = strlen(buffer);
    data = new char[len + 1];
    strcpy(data, buffer);
}
int MyString::get_size() const{
    return len;
}
MyString& MyString::operator=(const MyString& other) {
    if (this != &other) {       
        delete[] data;         
        len = other.len;
        if (other.data) {
            data = new char[len + 1];
            strcpy(data, other.data);
        } else {
            data = nullptr;
        }
    }
    return *this;
}
