#include "cassert"
#include "../src/rect.hpp"
#include <iostream>

using namespace std;

int main(){
    Rect r1;
    assert(r1.get_left() == 0);
    assert(r1.get_right() == 0);
    assert(r1.get_top() == 0);
    assert(r1.get_bottom() == 0);

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

    cout<<"Все basic тесты rect пройдены\n";
    return 0;
}