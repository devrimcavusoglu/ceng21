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
 * Case 20 : Default constructor; various inserts; various removals (removeNode(const T &data)); print.
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

    std::cout << "-> Making some removals from the list and printing it after each removal." << std::endl;

    std::cout << "-> remove node with data 61 ..." << std::endl;

    llist.removeNode(61);
    llist.print();

    std::cout << "-> remove node with data 62 ..." << std::endl;

    llist.removeNode(62);
    llist.print();

    std::cout << "-> remove node with data 64 ..." << std::endl;

    llist.removeNode(64);
    llist.print();

    std::cout << "-> remove node with data 65 ..." << std::endl;

    llist.removeNode(65);
    llist.print();

    std::cout << "-> remove all nodes ..." << std::endl;

    llist.removeAllNodes();
    llist.print();

    return 0;
}
