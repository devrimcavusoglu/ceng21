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
 * Case 18 : Default constructor; various inserts; copy constructor; print.
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

    std::cout << "-> Creating a duplicate linked list with copy constructor." << std::endl;

    LinkedList<int> duplicatedLList(llist);

    std::cout << "-> Printing the duplicate list." << std::endl;

    duplicatedLList.print();

    std::cout << "-> Printing the duplicate list in reverse order." << std::endl;

    duplicatedLList.print(true);

    checkIfCircular(&duplicatedLList);

    std::cout << "-> Printing the original list." << std::endl;

    llist.print();

    std::cout << "-> Printing the original list in reverse order." << std::endl;

    llist.print(true);

    checkIfCircular(&llist);

    std::cout << "-> Removing the middle node from the original list." << std::endl;

    llist.removeNode(llist.getNode(63));

    std::cout << "-> Printing the duplicate list." << std::endl;

    duplicatedLList.print();

    std::cout << "-> Printing the duplicate list in reverse order." << std::endl;

    duplicatedLList.print(true);

    checkIfCircular(&duplicatedLList);

    std::cout << "-> Printing the original list." << std::endl;

    llist.print();

    std::cout << "-> Printing the original list in reverse order." << std::endl;

    llist.print(true);

    checkIfCircular(&llist);

    return 0;
}
