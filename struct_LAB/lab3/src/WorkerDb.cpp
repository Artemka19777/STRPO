#include "WorkerDb.hpp"
#include "MyString.hpp"
#include <iostream>

WorkerData:: WorkerData():name(""), age(0){};
WorkerData:: WorkerData(const MyString& n, int a):name(n), age(a){};
WorkerDb::WorkerDb() {
    capacity = 101;
    count = 0;
    db = new Entry* [capacity];
    for(int i = 0; i<capacity; i++)
        db[i] = nullptr;
}
WorkerDb::~WorkerDb(){
    for(int i = 0; i<capacity; i++){
        Entry* cur = db[i];// проходимся по каждому связанному списку
        while(cur){
            Entry* tmp = cur;
            cur= cur->next;
            delete tmp;
        }    
    }
    delete[] db;
}
unsigned int WorkerDb::hash(const MyString& surname) const{
    const char* str = surname.get_data();
    unsigned int h = 0;
    while(*str){
        h = h*31+static_cast<unsigned int>(*str);
        str++;
    }
    return h;
}
WorkerData& WorkerDb::operator[](const MyString& surname){ 
    //реализовал хэш таблицу, теперь поиск выполняется за O(1), было за O(n)
    if (count > capacity * 0.75)
        rehash();
    unsigned int h = hash(surname)%capacity;
    Entry* cur = db[h];
    while(cur){
        if(cur->surname == surname)
            return cur->data;
        cur = cur->next;
    }
    //если на нашли элемент, нужно создать новый
    Entry* e = new Entry;
    e->surname= surname;
    e->data=WorkerData();
    e->next = db[h];// фактически ставим новый элемент в начало спсика, и говорим, что следующий элемент для него это первый

    db[h] = e;// обновляем значение, теперь значение хэша указывает на 1 элемент

    count++;
    return e->data;
}

WorkerDb::Iterator:: Iterator(Entry** d, int cap, int b, Entry* p){
    db=d;
    capacity = cap;
    bucket = b;
    ptr= p;

} 


WorkerDb::Iterator WorkerDb::begin(){//WorkerDb::Iterator - тип возвращаемого значенияЮ обхект класса итератор, но сам метод нахожится не внутри Iterator
    int b = 0;
    Entry* p = nullptr;
    while(b<capacity && db[b] == nullptr){
        b++;
    }// идем до первого связанного списка
    if(b<capacity)
        p=db[b];
    return Iterator(db, capacity, b, p);//db - тип Entry - указатель на динамический массив работников
}
WorkerDb::Iterator WorkerDb::end(){//нужно чтобы указывала на элемент после последнего, т.е. который не вхожит в массив
    return Iterator(db, capacity, capacity, nullptr);
}
MyString WorkerDb::Iterator::key() const{
    return ptr->surname;
}
WorkerData* WorkerDb::Iterator::operator->() {//умный указатель, должно вернуть именно адрес, а не объект, иначе ошибка, т.к. -> работает только с указателями
    return &(ptr->data); // Возвращаем адрес данных
}
WorkerData& WorkerDb::Iterator::operator*() {
    return ptr->data;
}
WorkerDb::Iterator& WorkerDb::Iterator::operator++() {
    if (ptr)
        ptr = ptr->next; // есил в связанном списке есть еще элементы то переходим на них
    if (ptr == nullptr){
        bucket++;
        move_next();
    }
    
    return *this;
}
WorkerDb::Iterator WorkerDb::Iterator::operator++(int) {
    Iterator temp = *this; //запоминаем старое состояние
    ++(*this);      
    return temp;// возвращаем старое состояние
}
bool WorkerDb::Iterator::operator!=(const Iterator& other) const {
    return ptr != other.ptr;
}

bool WorkerDb::Iterator::operator==(const Iterator& other) const {
    return ptr == other.ptr;
}
void print_db(WorkerDb& db){
    for(WorkerDb::Iterator it = db.begin(); it!=db.end();it++){
        std::cout<<it.key()<<" - "<< it->name<<", "<< it->age<<'\n'; //т.к. я перегрузил ->так, чтобы она возвращала поле data типа структуры WorkerData, не нужно писать it->data.name
    }
}
double get_avg_age(WorkerDb& db){
    double ans = 0.0;
    int count = 0;
    for(WorkerDb::Iterator it = db.begin(); it!=db.end();it++){
        ans += it->age;
        count++;
    }
    if (!count)
        return 0.0;
    return ans/count;
}

void WorkerDb::Iterator:: move_next(){
    while(bucket<capacity && ptr == nullptr){// идем по связанным спискам пока не найдем первый ненулевой указатель
        ptr = db[bucket];
        if (ptr == nullptr)
            bucket++;
    }
}
void WorkerDb::rehash(){
    int new_capacity = capacity * 2;
    Entry ** new_db = new Entry*[new_capacity];
     for (int i = 0; i < new_capacity; i++) {
        new_db[i] = nullptr;
    }
    for(int i = 0; i <capacity;i++){
        Entry* cur = db[i];
        while(cur){
            Entry* next  = cur->next;

            int new_index = hash(cur->surname)%new_capacity;
            cur->next = new_db[new_index];
            new_db[new_index] = cur;
            cur = next;
        }
    }
    delete[] db;
    db = new_db;
    capacity = new_capacity;
}