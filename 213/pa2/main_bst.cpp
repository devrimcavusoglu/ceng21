#include <iostream>

#include "BST.h"

void print_test_begin(std::string test_name) {
    std::cout << "===== BEGIN " << test_name << " =====\n";
}

void print_test_end() {
    std::cout << "===== END OF TEST ======\n";
}

template <class T>
void test_case_3(BST<T> tree) {
    print_test_begin("Test functions on empty tree..");
    /*BSTNode<T> *s_node = tree.search(5);
    tree.remove(5);
    tree.insert(5);*/
    tree.print(inorder);
    print_test_end();
}

template <class T>
void test_case_4(BST<T> &tree) {
    print_test_begin("Test insertion, deletion, printing..");
    tree.insert(4.5);
    tree.insert(2);
    tree.insert(6);
    tree.insert(1);
    tree.insert(3);
    tree.insert(5);
    tree.insert(7);
    tree.print(inorder);
    tree.removeAllNodes();
    tree.print(inorder);
    print_test_end();
}

int main() {
    BST<int> tree;

    tree.print(inorder);
    tree.print(preorder);
    tree.print(postorder);

    test_case_3(tree);
    test_case_4(tree);

    return 0;
}
