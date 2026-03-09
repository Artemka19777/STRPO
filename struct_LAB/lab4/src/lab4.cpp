#include "Circle.hpp"
#include <iostream>

int main() {

    List l;

    Circle c1(Point(0,0), 2);
    Circle c2(Point(1,1), 3);
    Circle c3(Point(2,2), 1);
    Circle c4(Point(5,5), 4);

    l.push_front(c1);
    l.push_back(c2);
    l.push_back(c3);
    l.push_front(c4);

    std::cout << "list:\n";
    std::cout << l << '\n';

    // сортировка
    l.sort();
    std::cout << "After sorting: \n";
    std::cout << l << '\n';

    std::cout << "Removing circle (1,1,r=3)\n";
    if (l.remove(c2))
        std::cout << "Removed successfully\n";
    else
        std::cout << "Element not found\n";

    std::cout << "List after remove:\n";
    std::cout << l << '\n';

    // добавим несколько одинаковых элементов
    l.push_back(c1);
    l.push_back(c1);

    std::cout << "List after adding:\n";
    std::cout << l << '\n';

    // удаление всех
    int removed = l.removeAll(c1);
    std::cout << "Removed " << removed << " elements equal to c1\n";

    std::cout << "List after removeAll:\n";
    std::cout << l << '\n';

    // сохранение в файл
    l.saveListToFile(l);

    // очистка
    std::cout << "Clearing list\n";
    l.clear();
    std::cout << "List after clear:\n";
    std::cout << l << '\n';

    // загрузка из файла
    std::string filename;
    std::cout << "Enter file name to load: ";
    std::cin >> filename;

    l.load_from_file(filename);

    std::cout << "List after loading from file:\n";
    std::cout << l << std::endl;

    return 0;
}
