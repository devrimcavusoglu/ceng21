#include <iostream>
#include <string>

#include "LinkedList.h"

int main() {
    LinkedList<int> llist;

    llist.print();

    llist.insertAtTheFront(1);
    llist.insertAtTheEnd(2);
    llist.insertAtTheEnd(3);
    llist.insertAsEveryKthNode(4, 2);
    llist.insertAtTheFront(5);
    llist.insertAtTheEnd(7);
    llist.print();
    
    std::cout << "============== size: " << llist.getSize() << " ================" << std::endl;
    llist.removeEveryKthNode(2);
    llist.print();
    std::cout << "============== size: " << llist.getSize() << " ================" << std::endl;
    return 0;
}
