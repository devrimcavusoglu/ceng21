#include <iostream>
#include <string>

#include "LinkedList.h"

int main() {
    LinkedList<int> llist;

    llist.print();

    llist.insertAtTheEnd(1);
    llist.insertAtTheEnd(2);
    llist.insertAtTheEnd(3);
    llist.insertAtTheEnd(4);
    llist.insertAtTheEnd(5);
    llist.insertAtTheEnd(7);

    llist.print();

    llist.swap(llist.getFirstNode(), llist.getNodeAtIndex(3));
    std::cout << "==============================" << std::endl;
    llist.print();
    return 0;
}
