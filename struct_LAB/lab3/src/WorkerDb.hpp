#ifndef WORKER_H
#define WORKER_H
#include "MyString.hpp"

struct WorkerData{//не привязан к базе данных
    public:
        MyString name;
        int age;

        WorkerData();
        WorkerData(const MyString& n, int a);
};


class WorkerDb{
    private:
        struct Entry{
            MyString surname;
            WorkerData data;
        };
        Entry* db = nullptr;
        int count = 0;
    public:
        class Iterator{//не стал делать через дружественный класс в целях инкапсуляции и простоты
            private:
                Entry* ptr;//указатель на текущего работника
            public:
                Iterator(Entry* p);//напрмяую не будем пользоваться, только в методах WorkerDb
                MyString key() const;// выводит фамилию 
                WorkerData* operator->();
                WorkerData& operator*();
                Iterator& operator++();
                Iterator operator++(int);
                bool operator!=(const Iterator& other) const;
                bool operator==(const Iterator& other) const;
                 
        };
        WorkerDb();
        ~WorkerDb();
        WorkerData& operator[](const MyString& surname);

        Iterator begin();
        Iterator end();
        
};

void print_db(WorkerDb& db);
double get_avg_age(WorkerDb& db);
#endif