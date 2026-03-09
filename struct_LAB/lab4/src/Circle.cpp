#include "Circle.hpp"
#include <cmath>

Point:: Point():x(0), y(0){}
Point:: Point(double x, double y):x(x), y(y) {}
Point::~Point(){}

double Point::getX() const { return x; }
double Point:: getY() const { return y; }

Circle:: Circle():radius(0){}
Circle:: Circle(const Point& p, double r): center(p), radius(r){}
double Circle::S() const{
    return M_PI *radius*radius;
}

Circle:: ~Circle(){}


List::Node:: Node(): pPrev(nullptr), pNext(nullptr){}

List::Node:: Node(Node* prev, Node* next, const Circle* item):pPrev(prev), pNext(next), m_Data(*item){
    if (prev)//теперь нужно соединить элементы с действующим объектом, обновить указатели для них
        prev->pNext = this;
    if (next)
        pNext->pPrev = this;
}
List::Node:: ~Node(){
    pPrev->pNext = pNext;// соединяем предыдущий и следующий
    pNext->pPrev = pPrev;
}
List:: List(): m_size(0){
    Head.pNext = &Tail;
    Tail.pPrev = &Head;
}
List:: ~List(){}

bool Circle::operator==(const Circle& other){
    return (center.getX()==other.center.getX())
    && (center.getY() == other.center.getY()) && (radius == other.radius);

}

void List::push_front(const Circle& item){
    new Node(&Head, Head.pNext, &item);
    m_size++;
}
void List::push_back(const Circle& item){
    new Node(Tail.pPrev,&Tail, &item);
    m_size++;
}
bool List:: remove(const Circle& item){
    for(Node* i = Head.pNext;i!=&Tail; i = i->pNext)//начинаем с Head.pNext т.к. сам head не является элементом списка
        if (i->m_Data == item){
            delete i;
            m_size--;
            return true; 
        }
    return false;
}

int List:: removeAll(const Circle& item){
    int ans = 0;
    for(Node* i = Head.pPrev; i!=&Tail; i=i->pNext){
        if (i->m_Data == item){
            delete i;
            m_size--;
            ans++;
        }
    }
    return ans;
}

void List::clear(){
    for(Node* i = Head.pPrev; i!=&Tail; i=i->pNext){
        delete i;
    }
    m_size=0;
}
void List::sort(){
    for(size_t i = 0; i<m_size-1;i++){
        for(Node* i = Head.pPrev; i!=&Tail; i=i->pNext){
            if (i->m_Data.S()> i->pNext->m_Data.S()){
                Circle temp = i->m_Data;
                i->m_Data=i->pNext->m_Data;
                i->pNext->m_Data = temp;
            }
        }
    }
}
std::ofstream& operator<<(std::ostream& os, const List& l){
    
}