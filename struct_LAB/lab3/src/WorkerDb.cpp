#include "WorkerDb.hpp"
#include "MyString.hpp"
#include <iostream>

WorkerData:: WorkerData():name(""), age(0){};
WorkerData:: WorkerData(const MyString& n, int a):name(n), age(a){};
WorkerDb::WorkerDb() {}
WorkerDb::~WorkerDb(){
    delete[] db;
}
WorkerData& WorkerDb::operator[](const MyString& surname){
    for(int i = 0; i<count;i++){
        if(db[i].surname == surname){
            return db[i].data;
        }
    }
    Entry* new_db = new Entry[count+1];//если в базе данных не оказалось работника, нужно создать объект
    for(int i = 0; i<count;i++){
        new_db[i]=std::move(db[i]);//пользуемся move семантикой, чтобы не тратить ресурсы на копирование
    }
    new_db[count].surname=surname;
    delete[] db;
    db=new_db;
    count++;
    return db[count-1].data;//возваращем структуру  
}

WorkerDb::Iterator:: Iterator(Entry* p): ptr(p){} 

WorkerDb::Iterator WorkerDb::begin(){//WorkerDb::Iterator - тип возвращаемого значенияЮ обхект класса итератор, но сам метод нахожится не внутри Iterator
    return Iterator(db);//db - тип Entry - указатель на динамический массив работников
}
WorkerDb::Iterator WorkerDb::end(){//нужно чтобы указывала на элемент после последнего, т.е. который не вхожит в массив
    return Iterator(db+count);
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
    ptr++; // Просто сдвигаем указатель на следующий Entry
    return *this;
}
WorkerDb::Iterator WorkerDb::Iterator::operator++(int) {
    Iterator temp = *this; //запоминаем старое состояние
    ptr++;      
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