#include <cassert>
#include <iostream>
#include "../src/WorkerDb.hpp"

using namespace std;

int main() {
    WorkerDb db;

    db["Aa"] = WorkerData("Ivan", 20);
    db["BB"] = WorkerData("Petr", 30);
    db["Ca"] = WorkerData("Sidor", 40);

    assert(db["Aa"].name == MyString("Ivan"));
    assert(db["Aa"].age == 20);

    assert(db["BB"].name == MyString("Petr"));
    assert(db["BB"].age == 30);

    assert(db["Ca"].name == MyString("Sidor"));
    assert(db["Ca"].age == 40);

    db["Aa"] = WorkerData("Ivan_new", 99);
    assert(db["Aa"].age == 99);

    int count = 0;
    for (WorkerDb::Iterator it = db.begin(); it != db.end(); ++it) {
        count++;
    }

    assert(count == 3);

    cout << "COLLISION TEST PASSED" << '\n';

    return 0;
}