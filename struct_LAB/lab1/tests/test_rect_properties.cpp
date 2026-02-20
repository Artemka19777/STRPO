#include <cassert>
#include <iostream>
#include "../src/rect.hpp"

using namespace std;

int main() {
    Rect r(2, 8, 13, 4); 

    assert(r.get_width() == 6);
    assert(r.get_height() == 9);
    assert(r.get_square() == 54);

    r.set_width(3);
    r.set_height(10);
    assert(r.get_width() == 3);
    assert(r.get_height() == 10);
    assert(r.get_square() == 30);

    cout << "Все property тесты rect пройдены\n";
    return 0;
}