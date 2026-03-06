// tests/test_priority_queue.cpp
#include "cassert"
#include "../src/Notification.hpp"
#include <iostream>

using namespace std;

int main() {
    NotificationPriorityQueue pq;

    Notification n1 = createSystem(10, MyString("normal system"), Normal);
    Notification n2 = createSystem(12, MyString("urgent system"), SOS);
    Notification n3 = createMessege(9, MyString("Alice"), MyString("Hi"));
    Notification n4 = createApp(11, MyString("App1"), MyString("Title"), MyString("Body"));
    Notification n5 = createMessege(10, MyString("Bob"), MyString("Hello"));

    pq.push(n1);
    pq.push(n2);
    pq.push(n3);
    pq.push(n4);
    pq.push(n5);

    Notification top = pq.pop();
    assert(top.type == System && top.data.system.lvl == SOS); // SOS системное должно быть первым

    top = pq.pop();
    assert(top.type == Message && top.data.chat.name.get_data() == string("Alice")); // сообщение раньше по времени

    top = pq.pop();
    assert(top.type == Message && top.data.chat.name.get_data() == string("Bob")); // следующее сообщение

    top = pq.pop();
    assert(top.type == System && top.data.system.text.get_data() == string("normal system")); // обычное системное

    top = pq.pop();
    assert(top.type == App && top.data.app.name.get_data() == string("App1")); // приложение последним

    cout << "Все тесты NotificationPriorityQueue пройдены!" << '\n';
    return 0;
}