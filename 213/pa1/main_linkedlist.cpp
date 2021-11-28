#include <iostream>
#include <string>

#include "LinkedList.h"


void print_size(LinkedList<int> &llist) {
    llist.print();
    std::cout << "============== size: " << llist.getSize() << " ================" << std::endl;
}

void randomFill(LinkedList<int> &llist) {
    llist.removeAllNodes();
    llist.insertAtTheEnd(1);
    llist.insertAtTheEnd(2);
    llist.insertAtTheEnd(3);
    llist.insertAtTheEnd(4);
    llist.insertAtTheEnd(5);
}


void test_insertion() {
    LinkedList<int> llist;
    std::cout << ">> Testing insertion.." << std::endl;
    llist.insertAtTheFront(1);
    llist.insertAtTheEnd(2);
    //llist.insertAsEveryKthNode(3, 3);
    llist.insertAtTheEnd(4);
    llist.insertAtTheEnd(5);
    llist.insertAfterNode(3, llist.getNode(2));
    print_size(llist);
}

void test_remove_every_kth_node() {
    LinkedList<int> llist;
    randomFill(llist);
    
    std::cout << ">> Testing delete every 2nd node.." << std::endl;
    print_size(llist);
    llist.removeEveryKthNode(2);
    print_size(llist);
}

void test_remove_all() {
    LinkedList<int> llist;
    randomFill(llist);
    std::cout << ">> Testing delete all.." << std::endl;
    print_size(llist);
    llist.removeAllNodes();
    print_size(llist);
}

void test_remove_data() {
    LinkedList<int> llist;
    randomFill(llist);
    std::cout << ">> Testing remove data 1,4.." << std::endl;
    print_size(llist);
    llist.removeNode(1);
    llist.removeNode(4);
    print_size(llist);
}

void test_get_node() {
    LinkedList<int> llist;
    randomFill(llist);
    Node<int> *current_node = llist.getFirstNode();
    std::cout << ">> Testing get node.." << std::endl;
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

int main() {
    test_insertion();

    test_remove_every_kth_node();
    test_remove_all();
    test_remove_data();
    
    test_get_node();
    //llist.removeEveryKthNode(2);
    /*llist.print();
    std::cout << "============== size: " << llist.getSize() << " ================" << std::endl;*/
    return 0;
}
