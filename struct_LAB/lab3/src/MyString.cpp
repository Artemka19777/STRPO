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
//lab3
MyString& MyString::operator+=(const MyString& other){
    int new_len=len + other.len;
    char* new_data = new char[new_len+1];
    if (data) strcpy(new_data, data);// копируем старое
    if (other.data) strcpy(new_data + len, other.data);// дописываем новое
    delete[] data;
    data=new_data;
    len=new_len;
    return *this;

}
MyString& MyString::operator+=(const char* str){
    return *this +=MyString(str);
}
MyString MyString::operator+(const MyString& other)const{
    MyString res(*this);
    res+=other;
    return res;
}
MyString MyString::operator+(const char* str)const {
    MyString res(*this);
    res+=str;
    return res;
}
MyString operator+(const char* str, const MyString& s){
    MyString res(str);
    res+=s;
    return res;
}

//move
MyString::MyString(MyString&& other):data(other.data),len(other.len){
    other.data=nullptr;//прописываем для того, чтобы деструктор не удалил память временного объекту, которую мы присвоили другому объекту
    other.len=0;
}
MyString& MyString::operator=(MyString&& other) {
    if (this != &other){
        delete[] data;

        data=other.data;//нельзя через список инициализаторов, т.к. сначала стоит освободитт старые данные, чтобы не было утечек
        len=other.len;

        other.data=nullptr; // по той же причине, что и при move-конструкторе
        other.len=0;
    }
    return *this;
}

const char* MyString::get_data() const {
    return data; 
}

bool MyString::operator==(const MyString& other) const {
    if (len != other.len)
        return false;
    if (!data && !other.data)
        return true;
    if (!data || !other.data)
        return false;
    return strcmp(data, other.data) == 0;
}

bool MyString::operator<(const MyString& other) const {
    if (!data && !other.data)
        return false;
    if (!data) 
        return true; 
    if (!other.data)
        return false;
    return strcmp(data, other.data) < 0;
}
bool MyString::operator!=(const MyString& other) const {
    return !(*this==other);// использую уже готовый оператор
}
bool MyString::operator<=(const MyString& other) const {
    return (*this<other) || (*this == other);
}

bool operator==(const char* str, const MyString& s) {
    const char* s_data = s.get_data();
    if (!str && !s_data)
        return true;
    if (!str || !s_data)
        return false;
    return strcmp(str, s_data) == 0;
    // сравниваю через strcmp, нет необходимости создавать объект Mystring, как это было в Matrix
}
bool operator<(const char* str, const MyString& s) {
    const char* s_data = s.get_data();
    if (!str && !s_data)
        return false;
    if (!str)
        return true;
    if (!s_data)
        return false;
    return strcmp(str, s_data) < 0;
}
bool operator!=(const char* str, const MyString& s) {
    return !(str == s);
}

bool operator<=(const char* str, const MyString& s) {
    return (str < s) || (str == s);
}
char& MyString::operator[](int n){
    if (n>=len || n<0)
        throw runtime_error("Не подходит индекс");
    return data[n];
}

std::ostream& operator<<(std::ostream& os, const MyString& s) {//ostream - тип даныых, который описывает вывод, cout - объект 
    if (s.get_data()) {
        os << s.get_data();
    }
    return os; //возвращаем поток
}
std::istream& operator>>(std::istream& is, MyString& s) {
    char buffer[1024]; 
    is.getline(buffer, sizeof(buffer));//читаем в буфер 
    
    // Используем уже написанный оператор присваивания, чтобы обновить s
    s = buffer; 
    
    return is;
}
MyString addTxtExtension(const MyString &path) { return path + ".txt"; };