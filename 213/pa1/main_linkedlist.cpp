#include <iostream>

#include "LinkedList.h"

int main() {
    LinkedList<int> llist;

    llist.print();

    llist.insertAtTheEnd(3);
    llist.insertAtTheFront(2);
    llist.insertAfterNode(1, llist.getNode(2));

    llist.print();
    
    return 0;
}
