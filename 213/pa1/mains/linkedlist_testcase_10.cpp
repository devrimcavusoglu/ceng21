#include <iostream>

#include "../LinkedList.h"


template <class T>
void checkIfCircular(LinkedList<T> *llist) {
    std::cout << "-> Checking if the linked list is circular?" << std::endl;

    if (llist == NULL || llist->isEmpty()) {
        std::cout << "yes. it is circular." << std::endl;
    } else {
        Node<T> *firstNode = llist->getFirstNode();
        Node<T> *lastNode = llist->getLastNode();

        if (firstNode->prev != lastNode || lastNode->next != firstNode) {
            std::cout << "no. it is not circular." << std::endl;
        } else {
            std::cout << "yes. it is circular." << std::endl;
        }
    }
}

/*
 * Case 10 : Default constructor; various inserts; remove last node; getSize and isEmpty; print.
 */
int main() {
    std::cout << "-> Creating a linked list with default constructor." << std::endl;

    LinkedList<int> llist;

    std::cout << "-> Making some insertions to the list." << std::endl;

    llist.insertAtTheFront(62);
    llist.insertAtTheEnd(64);
    llist.insertAtTheFront(61);
    llist.insertAtTheEnd(65);
    llist.insertAfterNode(63, llist.getNode(62));

    std::cout << "-> Printing the list." << std::endl;

    llist.print();

    std::cout << "-> Printing the list in reverse order." << std::endl;

    llist.print(true);

    checkIfCircular(&llist);

    std::cout << "-> Removing the last node from the list." << std::endl;

    llist.removeNode(llist.getLastNode());

    std::cout << "-> Printing the list." << std::endl;

    llist.print();

    std::cout << "-> Printing the list in reverse order." << std::endl;

    llist.print(true);

    checkIfCircular(&llist);

    std::cout << "-> Calculating the size." << std::endl;

    std::cout << "size is " << llist.getSize() << std::endl;

    std::cout << "-> Checking if the list is empty or not." << std::endl;

    if (llist.isEmpty()) {
        std::cout << "linked list is empty" << std::endl;
    } else {
        std::cout << "linked list is not empty" << std::endl;
    }

    return 0;
}
