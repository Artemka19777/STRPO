#include <cassert>
#include <iostream>
#include "../src/rect.hpp"

using namespace std;

int main() {
    Rect r(0, 10, 10, 0);

    r.move(5, 3);
    assert(r.get_left() == 5);
    assert(r.get_right() == 15);
    assert(r.get_top() == 13);
    assert(r.get_bottom() == 3);

    r.move(2);
    assert(r.get_left() == 7);
    assert(r.get_right() == 17);

    r.inflate(1);
    assert(r.get_left() == 6);
    assert(r.get_right() == 18);
    assert(r.get_top() == 14);
    assert(r.get_bottom() == 2);

    r.inflate(2, 3);
    assert(r.get_left() == 4);
    assert(r.get_right() == 20);
    assert(r.get_top() == 17);
    assert(r.get_bottom() == -1);

    r.inflate(1, 2, 3, 4);
    assert(r.get_left() == 3);
    assert(r.get_right() == 22);
    assert(r.get_top() == 20);
    assert(r.get_bottom() == -5);

    cout << "Все operations тесты Rect пройдены\n";
    return 0;
}
