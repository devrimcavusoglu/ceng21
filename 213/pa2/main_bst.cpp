#include <iostream>

#include "BST.h"

int main() {
    BST<int> tree;

    tree.print(inorder);
    tree.print(preorder);
    tree.print(postorder);

    tree.insert(4);
    tree.insert(2);
    tree.insert(6);
    tree.insert(1);
    tree.insert(3);
    tree.insert(5);
    tree.insert(7);

    tree.print(inorder);
    tree.print(preorder);
    tree.print(postorder);

    return 0;
}
