#include <iostream>

#include "LinkedList.h"

int main() {
    LinkedList<int> llist;

    llist.print();

    
    llist.insertAtTheFront(2);
    llist.insertAtTheFront(3);
    llist.insertAtTheEnd(4);
    //llist.insertAtTheFront(4);
    //llist.insertAfterNode(1, llist.getNode(2));

    llist.print();
    
    return 0;
}
