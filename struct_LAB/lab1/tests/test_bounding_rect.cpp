#include "cassert"
#include "../src/rect.hpp"
#include <iostream>

using namespace std;

int main(){
    Rect r1;
    r1.set_all(3, 7, 8, 6);
    assert(r1.get_left() == 3);
    assert(r1.get_right() == 7);
    assert(r1.get_top() == 8);
    assert(r1.get_bottom() == 6);

    Rect r2(3,9,7,1);
    assert(r2.get_left() == 3);
    assert(r2.get_right() == 9);
    assert(r2.get_top() == 7);
    assert(r2.get_bottom() == 1);

    Rect r3 = bounding_rect(r1, r2);
    assert(r3.get_left() == 3);
    assert(r3.get_right() == 9);
    assert(r3.get_top() == 8);
    assert(r3.get_bottom() == 1);

    Rect r5(10, 2, 3, 8);  // перепутаны координаты
    Rect r6(-5, -1, -1, -10);

    Rect r7 = bounding_rect(r5, r6);


    assert(r7.get_left() == -5);
    assert(r7.get_right() == 10);
    assert(r7.get_top() == 8);
    assert(r7.get_bottom() == -10);

    cout<<"Все bounding тесты rect пройдены\n";
    return 0;
}