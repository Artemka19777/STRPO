#include "Notification.hpp"
#include <iostream>
#include <cstring>

using namespace std;

Notification::Notification(): timestamp(0), type(NotType::System) {
    new (&data.system) SystemD{};
}
Notification:: ~Notification(){
    //на данном этапе непоняно какой тип уведомления хранится в uinon, поэтому нужно проверить и вызвать нужный деструктор
   if (type == NotType::System) {
        data.system.text.~MyString();
    } else if (type == NotType::Message) {
        data.chat.name.~MyString();
        data.chat.text.~MyString();
    } else if (type == NotType::App) {
        data.app.name.~MyString();
        data.app.title.~MyString();
        data.app.body.~MyString();
    }
}
Notification createSystem(int ts, MyString text, Attetion lvl){
    Notification n;
    n.timestamp = ts;
    n.type = NotType::System;    
    new (&n.data.system) SystemD{ text, lvl };// без new объект в union не создается и происходит присваивание неинециализированному объекту

    return n;
}
Notification createMessege(int ts, MyString name, MyString text) {
    Notification n;
    n.timestamp = ts;
    n.type = NotType::Message;
    new (&n.data.chat) ChatD{ name, text };

    return n;
}
Notification createApp(int ts, MyString name, MyString title, MyString body){
    Notification n;
    n.timestamp=ts;
    n.type= NotType::App;
    new (&n.data.app) AppD{ name, title, body };
    return n;
}
void Notification::print() const{
    int m = (timestamp / 60) % 60;
    int h = (timestamp / 3600) % 24;

    cout<<"(" << h<<":"<<m<< ")";
    if (type == NotType::System) {
        cout << "SYSTEM: " << data.system.text.get_data() <<'\n';
    } else if (type == NotType::Message) {
        cout << "MESSAGE from " << data.chat.name.get_data() << ": " << data.chat.text.get_data() <<'\n';
    } else{
        cout << "App "<<data.app.name.get_data()<<data.app.title.get_data()<<": "<<data.app.body.get_data()<<'\n';
    }
}
int countType(Notification* arr, int size, NotType type){
    int count = 0;
    for (int i = 0; i < size; ++i) {
        if (arr[i].type == type) 
            count++;
    }
    return count;
}
Notification::Notification(const Notification& other) {
    timestamp = other.timestamp;
    type = other.type;

    switch (type) {
        case NotType::System:
            new (&data.system) SystemD{other.data.system.text,
                                       other.data.system.lvl};
            break;

        case NotType::Message:
            new (&data.chat) ChatD{other.data.chat.name,
                                   other.data.chat.text};
            break;

        case NotType::App:
            new (&data.app) AppD{other.data.app.name,
                                 other.data.app.title,
                                 other.data.app.body};
            break;
    }
}
Notification& Notification::operator=(const Notification& other) {
    if (this == &other)
        return *this;

    this->~Notification();

    timestamp = other.timestamp;
    type = other.type;

    switch (type) {
        case NotType::System:
            new (&data.system) SystemD{other.data.system.text,
                                       other.data.system.lvl};
            break;

        case NotType::Message:
            new (&data.chat) ChatD{other.data.chat.name,
                                   other.data.chat.text};
            break;

        case NotType::App:
            new (&data.app) AppD{other.data.app.name,
                                 other.data.app.title,
                                 other.data.app.body};
            break;
    }

    return *this;
}
NotificationQueue:: NotificationQueue():data(nullptr), capacity(0), Nsize(0), head(0), tail(0){};
NotificationQueue::~NotificationQueue() {
    delete[] data; 
}
int NotificationQueue::size() const{
    return Nsize;
}
Notification* NotificationQueue::begin(){
    return data+head;//нужно поменять относительно чего ведется отсчет
}
Notification* NotificationQueue::end(){
    return data + Nsize+head;
}
void NotificationQueue::reserve(int newCapacity) {
    if (newCapacity <= capacity) 
        return;
    Notification* newData = new Notification[newCapacity];
    for (int i = 0; i < Nsize; ++i) {
        newData[i] = data[(head+i)%capacity]; 
    }

    delete[] data;
    data = newData;
    capacity = newCapacity;
    head=0;
    tail=Nsize;
}

void NotificationQueue::push(const Notification& note) {
    if (Nsize == capacity) {//если количество элементов сравнялось с памятью, выделяем новую
        reserve(capacity == 0 ? 4 : capacity * 2);// проверка на случай, если память не выделяли
    }
    data[tail] = note; // ставим на свободное место элемент
    tail = (tail + 1)%capacity;
    Nsize++;
}
Notification NotificationQueue::pop() {
    if (Nsize == 0) 
        return Notification(); 

    Notification front = data[head]; //копируем первый элемент
    head = (head + 1) %capacity;// передвигаем начало, тем самымй освобождая элемент и teil теперь сможет встать на это место, так как реализован с %
    Nsize--;
    return front;
}


bool NotificationPriorityQueue::isUrgentSystem(const Notification& n) const {
    return n.type == NotType::System && n.data.system.lvl==SOS; //проверка на самое срочное
}int NotificationPriorityQueue::typePriority(NotType t) const {
    if (t == Message) return 3;
    if (t == System) return 2;
    return 1; // App
}

bool NotificationPriorityQueue::better(const Notification& a, const Notification& b) const {

    bool aUrg = isUrgentSystem(a);
    bool bUrg = isUrgentSystem(b);

    // 1
    if (aUrg != bUrg)
        return aUrg;

    // 2
    if (a.timestamp != b.timestamp)
        return a.timestamp < b.timestamp;

    // 3
    int pa = typePriority(a.type);
    int pb = typePriority(b.type);

    if (pa != pb)
        return pa > pb;

    // (FIFO)
    return false;
}
Notification NotificationPriorityQueue::pop() {
    //реализовал кучу(heap), теперь поиск за O(log n), был за O(n)
    if (Nsize == 0)
        return Notification();
    Notification res = data[0]; // запоминаем вершину, чтобы вернуть
    data[0] = data[Nsize-1];
    Nsize--;
    if(Nsize>0)
        siftdown(0);// продвигаем вниз последний элемент, который мы поставили в вершину
    return res;
}
//NotificationPriorityQueue
void NotificationPriorityQueue::reserve(int newCapacity) {
    if (newCapacity <= capacity) 
        return;
    Notification* newData = new Notification[newCapacity];
    for (int i = 0; i < Nsize; ++i) {
        newData[i] = data[i]; 
    }

    delete[] data;
    data = newData;
    capacity = newCapacity;
}
void NotificationPriorityQueue::siftdown(int i){
    while(2*i+1< Nsize){ // пока есть потомок
        int l = 2*i + 1;
        int r = 2*i + 2;
        int best = i;
        //нужно сравнить двух потомков с лучшим вариантом, нельзя поставить первый попавшийся элемент
        if (l<Nsize && better(data[l], data[i])){
            best = l;
        }
        if (r<Nsize && better(data[r], data[best])){
            best = r;
        }
        if (best == i)
            break;
        swap(data[i], data[best]);
        i = best;// продолжаем с позиции, в которую переместился элемент
    }
}
void NotificationPriorityQueue::siftup(int i){
    while(i>0){  // в вершине самое приоритетное уведомление
        int p = (i - 1)/2;
        if (better(data[i], data[p])){
            swap(data[i], data[p]);
            i=p;//ставим элемент на место родителя
        } else
            break;
    }
}

void NotificationPriorityQueue::push(const Notification& note){
    if (Nsize == capacity) //если количество элементов сравнялось с памятью, выделяем новую
        reserve(capacity == 0 ? 4 : capacity * 2);// проверка на случай, если память не выделяли
    data[Nsize] = note;
    siftup(Nsize);//продвигаем вверх новый элемент
    Nsize++;    
}

NotificationPriorityQueue::NotificationPriorityQueue():data(nullptr), capacity(0),Nsize(0){}
NotificationPriorityQueue::~NotificationPriorityQueue(){delete[] data;}