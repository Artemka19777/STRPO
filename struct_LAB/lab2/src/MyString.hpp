#ifndef MYSTRING_HPP
#define MYSTRING_HPP
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
        
        MyString& operator=(const MyString& other);
};
#endif