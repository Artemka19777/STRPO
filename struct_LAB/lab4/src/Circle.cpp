#include "Circle.hpp"
#include <cmath>
#include <fstream>

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

const Point& Circle:: getCenter() const { return center; }
double Circle::getRadius() const { return radius;}

List::Node:: Node(): pPrev(nullptr), pNext(nullptr){}

List::Node:: Node(Node* prev, Node* next, const Circle* item):pPrev(prev), pNext(next), m_Data(*item){
    if (prev)//теперь нужно соединить элементы с действующим объектом, обновить указатели для них
        prev->pNext = this;
    if (next)
        next->pPrev = this;
}
List::Node:: ~Node(){
    if (pPrev) pPrev->pNext = pNext;// соединяем предыдущий и следующий
    if (pNext) pNext->pPrev = pPrev;//условия для HEAD и Tail 
}
List:: List(): m_size(0){
    Head.pNext = &Tail;
    Tail.pPrev = &Head;
}
List:: ~List(){clear();}

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
    Node* i = Head.pNext;
    while (i != &Tail) {// через for нельзя, т.к. при удалении удалится указатель на следующий элемент, к которому нужно перейти
        Node* nextNode = i->pNext;
        if (i->m_Data == item) {
            delete i;
            m_size--;
            ans++;
        }
        i = nextNode; 
    }
    return ans;
}

void List::clear() {
    Node* i = Head.pNext;
    while (i != &Tail) {
        Node* nextNode = i->pNext;
        delete i;
        i = nextNode;
    }
    Head.pNext = &Tail;//восстанавливаем связи 
    Tail.pPrev = &Head;
    m_size = 0;
}
std::ostream& operator<<(std::ostream& os, const List& l){
    List::Node* curr = l.Head.pNext;
    while (curr != &l.Tail) {
        os << "Circle: Center(" << curr->m_Data.getCenter().getX() << "," 
            << curr->m_Data.getCenter().getY() << "), R=" 
            << curr->m_Data.getRadius() << ", S=" << curr->m_Data.S() << "\n";
        curr = curr->pNext;
    }
    return os;
}
void List::saveListToFile(std::ostream& os) const{
    for (Node* curr = Head.pNext; curr != &Tail; curr = curr->pNext) {
        os << curr->m_Data.getCenter().getX() << " "
             << curr->m_Data.getCenter().getY() << " "
             << curr->m_Data.getRadius() << "\n";// не стал использовать перегруженный оператор << т.к. в таком формате можно загружать и считывать информацию из одного файла

    }
}
void List::load_from_file(std::istream& is) {
    clear();

    double x, y, r;

    while (is >> x >> y >> r) {
        push_back(Circle(Point(x, y), r));
    }
}
List::List(const List& other){
    for(Node* i = other.Head.pNext; i!= &other.Tail; i=i->pNext){
        push_back(i->m_Data);
    }
}

List& List::operator=(const List& other){
    if (this == &other)
        return *this;
    
    clear();

    for(Node* i = other.Head.pNext; i!= &other.Tail; i=i->pNext){
        push_back(i->m_Data);
    }
    return *this;
}
//сортировка
List::Node* List::split(Node* head){
    //левая граница идет с шагом 1, правая с шагом 2
    Node* l = head;
    Node* r = head;
    while(r->pNext!=&Tail && r->pNext->pNext!=&Tail){
        r = r->pNext->pNext;
        l= l->pNext;
    }
    Node* mid = l->pNext;
    l->pNext=&Tail;
    return mid;
}
List::Node* List::merge(Node* left, Node* right){
    Node merged;
    Node* tail = &merged;//указывает на последний отсортированный элемент
    while (left != &Tail && right != &Tail){
        if(left->m_Data.S()<=right->m_Data.S()){
            tail->pNext = left;
            left->pPrev = tail;
            left = left->pNext;
            //связали последний отсортированный элемент с только что добавленным и переместили left на следуюших элемент
        } else{
            tail->pNext = right;
            right->pPrev = tail;
            right = right -> pNext;
        }
        tail= tail->pNext;
    }
    if (left != &Tail) tail->pNext = left;
    if (right != &Tail) tail->pNext = right;
    return merged.pNext;
}
List::Node* List::mergeSort(Node* head) {
    if (head == &Tail || head->pNext == &Tail)
        return head;
    Node* mid = split(head);
    Node* left = mergeSort(head);
    Node* right = mergeSort(mid);

    return merge(left, right);
}
void List::sort(){
    if (m_size < 2) return;

    Head.pNext->pPrev = &Head;
    Node* newHead = mergeSort(Head.pNext);
    
    Head.pNext = newHead;
    Node* curr = Head.pNext;
    curr->pPrev = &Head;

    while (curr->pNext != &Tail)
    {
        curr->pNext->pPrev = curr;
        curr = curr->pNext;
    }
    Tail.pPrev = curr;
}