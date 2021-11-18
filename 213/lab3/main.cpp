#include <iostream>

#include "LinkedIntList.h"
#include "NoSuchElementException.h"

using namespace std;

int main() {
    LinkedIntList list;

    list.add(5);
    list.add(10);
    list.add(15);

    bool is_sorted = list.isSorted();
    std::cout << is_sorted << "\n";
    list.print();

    return 0;
}