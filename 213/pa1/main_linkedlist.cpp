#include <iostream>
#include <string>

#include "LinkedList.h"


void print_size(LinkedList<int> &llist) {
    llist.print();
    std::cout << "============== size: " << llist.getSize() << " ================" << std::endl;
}

void randomFill(LinkedList<int> &llist) {
    llist.removeAllNodes();
    llist.insertAtTheFront(2);
    llist.insertAtTheEnd(4);
    llist.insertAtTheFront(1);
    llist.insertAtTheEnd(5);
    llist.insertAfterNode(3, llist.getNode(2));
}


void test_insertion() {
    std::cout << ">> Testing insertion.." << std::endl;
    LinkedList<int> llist;
    print_size(llist);
    llist.insertAtTheFront(1);
    llist.insertAtTheEnd(2);
    llist.insertAtTheEnd(4);
    llist.insertAtTheEnd(5);
    llist.insertAfterNode(3, llist.getNode(2));
    print_size(llist);
}

void test_remove_every_kth_node() {
    std::cout << ">> Testing delete every 2nd node.." << std::endl;
    LinkedList<int> llist;
    randomFill(llist);
    
    print_size(llist);
    llist.removeEveryKthNode(2);
    print_size(llist);
}

void test_remove_all() {
    std::cout << ">> Testing delete all.." << std::endl;
    LinkedList<int> llist;
    randomFill(llist);
    
    print_size(llist);
    llist.removeAllNodes();
    print_size(llist);
}

void test_remove_data() {
    std::cout << ">> Testing remove data 1,4.." << std::endl;
    LinkedList<int> llist;
    randomFill(llist);
   
    print_size(llist);
    llist.removeNode(1);
    llist.removeNode(4);
    print_size(llist);
}

void test_get_node() {
    std::cout << ">> Testing get node.." << std::endl;
    LinkedList<int> llist;
    randomFill(llist);
    Node<int> *current_node = llist.getFirstNode();
    print_size(llist);
    int data;
    do {
        data = llist.getNode(current_node->data)->data;
        std::cout << "data: " << data << std::endl;
        current_node = current_node->next;
    }
    while (current_node != llist.getFirstNode());
    print_size(llist);
}


void test_copy_constructor() {
    std::cout << ">> Testing copy constructor.." << std::endl;
    LinkedList<int> llist;
    randomFill(llist);
    print_size(llist);
    LinkedList<int> llist2(llist);
    print_size(llist2);
}

void test_assignment_operator() {
    std::cout << ">> Testing operator=.." << std::endl;
    LinkedList<int> llist;
    randomFill(llist);
    print_size(llist);
    LinkedList<int> llist2;
    llist2 = llist;
    print_size(llist2);
}

void test_copy_constructor_update() {
    std::cout << ">> Testing copy constructor update (construct llist2 form llist).." << std::endl;
    LinkedList<int> llist;
    randomFill(llist);
    LinkedList<int> llist2;
    llist2 = llist;
    std::cout << "#### llist2.." << std::endl;
    print_size(llist2);
    std::cout << "## Removing node with data 2 from llist2.." << std::endl;
    llist2.removeNode(2);
    std::cout << "#### llist2.." << std::endl;
    print_size(llist2);
    std::cout << "#### llist.." << std::endl;
    print_size(llist);

    std::cout << "## Removing all nodes from llist2.." << std::endl;
    llist2.removeAllNodes();
    std::cout << "#### llist2.." << std::endl;
    print_size(llist2);
    std::cout << "#### llist.." << std::endl;
    print_size(llist);

    std::cout << "head of llist: " << llist.getFirstNode()->data << std::endl;
}

int main() {
    test_insertion();

    test_remove_every_kth_node();
    test_remove_all();
    test_remove_data();
    test_get_node();
    test_copy_constructor();
    test_assignment_operator();
    test_copy_constructor_update();

    return 0;
}
