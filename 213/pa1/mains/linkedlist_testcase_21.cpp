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
 * Case 21 : Default constructor; various inserts; various swaps; print.
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

    for (int i = 0 ; i < 4 ; ++i) {
        std::cout << "-> Swapping nodes at index " << i << " and index " << (i + 1) << "." << std::endl;

        Node<int> *node1 = llist.getNodeAtIndex(i);
        Node<int> *node2 = llist.getNodeAtIndex(i+1);

        int node1Data = node1->data;
        int node2Data = node2->data;

        llist.swap(node1, node2);

        if (node1Data != node1->data || node2Data != node2->data) {
            std::cout << "you are not allowed to just swap the data in nodes!" << std::endl;
            return 0;
        }

        bool node1ExistsInTheList = false;
        bool node2ExistsInTheList = false;
        Node<int> *temp = llist.getFirstNode();
        do {
            if (temp == node1) node1ExistsInTheList = true;
            else if (temp == node2) node2ExistsInTheList = true;
            temp = temp->next;
        } while (temp != llist.getFirstNode());

        if (node1ExistsInTheList == false || node2ExistsInTheList == false) {
            std::cout << "you are not allowed to create new nodes!" << std::endl;
            return 0;
        }

        std::cout << "-> Printing the list." << std::endl;

        llist.print();

        std::cout << "-> Printing the list in reverse order." << std::endl;

        llist.print(true);

        checkIfCircular(&llist);
    }

    return 0;
}
