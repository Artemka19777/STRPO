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
        pNext->pPrev = this;
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
void List::sort(){
    for(size_t j = 0; j<m_size-1;j++){
        for(Node* i = Head.pNext; i->pNext!=&Tail; i=i->pNext){
            if (i->m_Data.S()> i->pNext->m_Data.S()){
                Circle temp = i->m_Data;
                i->m_Data=i->pNext->m_Data;
                i->pNext->m_Data = temp;
            }
        }
    }
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
void List::saveListToFile(const List& l) {
    char ar[80];
    std::cout << "Enter Output File Name - ";
    std::cin >> ar;

    std::ofstream fout(ar);

    if (!fout.is_open()) {
        std::cerr << "Error\n";
        return;
    }

    for (Node* curr = l.Head.pNext; curr != &l.Tail; curr = curr->pNext) {
        fout << curr->m_Data.getCenter().getX() << " "
             << curr->m_Data.getCenter().getY() << " "
             << curr->m_Data.getRadius() << "\n";// не стал использовать перегруженный оператор << т.к. в таком формате можно загружать и считывать информацию из одного файла

    }

    fout.close();
    std::cout << "Saved to file: " << ar << '\n';
}
void List::load_from_file(const std::string& filename) {
    std::ifstream fin(filename);
    
    if (!fin.is_open()) {
        std::cerr << "Error" << filename << '\n';
        return;
    }
    clear(); 
    double x, y, r;
    while (fin >> x >> y >> r) {
        push_back(Circle(Point(x, y), r));
    }

    fin.close();
}