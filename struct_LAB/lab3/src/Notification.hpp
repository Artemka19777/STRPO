#ifndef NOTIFICATION_H
#define NOTIFICATION_H
#include "MyString.hpp"

enum NotType{
    System,
    Message,
    App
};
enum Attetion{
    Normal, 
    SOS
};

struct SystemD{
    MyString text;
    Attetion lvl;
};
struct ChatD{
    MyString name;
    MyString text;
};
struct AppD{
    MyString name;
    MyString title;
    MyString body;
};

struct Notification{
    int timestamp;
    NotType type;

    union DataUnion{
        SystemD system;
        ChatD chat;
        AppD app;

        DataUnion(){};
        ~DataUnion(){};
    } data;//объявляем и создаем объект

    Notification();
    ~Notification();
    Notification(const Notification& other);
    Notification& operator=(const Notification& other);

    void print() const;
};

Notification createSystem(int ts, MyString text, Attetion lvl);
Notification createMessege(int ts, MyString name, MyString text);
Notification createApp(int ts, MyString name, MyString title, MyString body);

int countType(Notification* arr, int size, NotType type);

class NotificationQueue{
    protected:
        Notification* data;
        int capacity;
        int Nsize;

        void reserve(int newCapacity);// метод для расширения памяти;
    public:
        NotificationQueue();
        ~NotificationQueue();
        void push(const Notification& note);
        int size() const;
        Notification pop();
        Notification* begin();
        Notification* end();
};
class NotificationPriorityQueue : public NotificationQueue {//наследуем от прошлого класса, чтобы не переписывать методы
    private:
        bool better(const Notification& a, const Notification& b) const;
        bool isUrgentSystem(const Notification& n) const;
        int typePriority(NotType t) const;
    public:
        Notification pop();

};
#endif