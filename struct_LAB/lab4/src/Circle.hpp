#ifndef CIRCLE_H
#define CIRCLE_H
#include <cstddef>
#include <iostream>
class Point{
    private:
        double x;
        double y;
    public:
        Point();
        Point(double x, double y);
        ~Point();
        double getX() const;
        double getY() const;
};

class Circle{
    private:
        Point center;
        double radius;
    public:
        Circle();
        Circle(const Point& c, double radius);
        ~Circle();
        bool operator==(const Circle& item);// перегружаем оператор для сравнения, нужен для поиска элементов, удаления

        double S() const;
        double getRadius() const;
        const Point& getCenter() const;
};
class List{
    private:
        class Node{
            public:
                Node* pPrev;// нет смысла писать private, т.к. поля защищены внешним классом, т.к. класс находится в private, инкапсуляция соблюдена
                Node* pNext;
                Circle m_Data;

                Node();
                Node(Node* prev, Node* next, const Circle* item);
                ~Node();
        };
        Node Head;
        Node Tail;
        size_t m_size;
    public:
        List();
        ~List();

        void push_front(const Circle& item);
        void push_back(const Circle& item);
        bool remove(const Circle& item);
        int removeAll(const Circle& item);
        void clear();

        void sort();
        friend std::ostream& operator<<(std::ostream& os, const List& l);

        void saveListToFile(const List& l);
        void load_from_file(const std::string& filename);
};
#endif