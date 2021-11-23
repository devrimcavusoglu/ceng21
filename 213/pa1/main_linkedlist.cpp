#include <iostream>
#include <string>

#include "LinkedList.h"

int main() {
    LinkedList<int> llist;

    llist.print();

    llist.insertAtTheEnd(1);
    //llist.insertAtTheEnd(2);
    //llist.insertAtTheEnd(3);
    //llist.print();

    llist.print();

    llist.removeNode(llist.getFirstNode());
    llist.print();
    return 0;
}
