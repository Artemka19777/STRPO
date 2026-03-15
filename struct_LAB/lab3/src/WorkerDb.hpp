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
            Entry* next; //добавляем поле, которое указвает на следующий элемент, нужно из-за возникновение коллизий
        };
        Entry** db;// массив указателей на списки
        int count;
        int capacity;
        unsigned int hash(const MyString& surname) const;
    public:
        class Iterator{//не стал делать через дружественный класс в целях инкапсуляции и простоты
            private:
                Entry** db;
                int capacity;
                int bucket;
                Entry* ptr;//указатель на текущего работника

                void move_next(); // сейчас элементы лежат не подряд, поэтому для перехода нужно реализовать вспомогательную функцию
            public:
                Iterator(Entry** d, int cap, int b, Entry* p);//напрмяую не будем пользоваться, только в методах WorkerDb
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