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
 * Case 3 : Default constructor; various functions on empty linked list; print.
 */
int main() {
    std::cout << "-> Creating a linked list with default constructor." << std::endl;

    LinkedList<int> llist;

    std::cout << "-> Creating a node with data 63. Node is not in the list." << std::endl;

    Node<int> *tempNode = new Node<int>(63, NULL, NULL);

    std::cout << "-> Trying to remove that node from the list and then printing the list." << std::endl;

    llist.removeNode(tempNode);
    llist.print();

    std::cout << "-> Trying to remove a node with data 63 from the list and then printing the list." << std::endl;

    llist.removeNode(63);
    llist.print();

    std::cout << "-> Trying to remove all nodes from the list and then printing the list." << std::endl;

    llist.removeAllNodes();
    llist.print();

    std::cout << "-> Trying to get a node with data 63 from the list." << std::endl;

    if (llist.getNode(63) == NULL) {
        std::cout << "no node with data 63 exists" << std::endl;
    }

    std::cout << "-> Checking if the list contains the previously created node or not." << std::endl;

    if (llist.contains(tempNode) == false) {
        std::cout << "linked list does not contain that node" << std::endl;
    }

    std::cout << "-> Printing the list." << std::endl;

    llist.print();

    std::cout << "-> Printing the list in reverse order." << std::endl;

    llist.print(true);

    checkIfCircular(&llist);

    delete tempNode;

    return 0;
}
