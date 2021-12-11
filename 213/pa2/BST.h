#ifndef BST_H
#define BST_H

#include <iostream>

#include "BSTNode.h"

enum TraversalPlan {preorder, inorder, postorder};

template<class T>
class BST {
public: // DO NOT CHANGE THIS PART.
    BST();
    BST(const BST<T> &obj);

    ~BST();

    BSTNode<T> *getRoot() const;
    bool isEmpty() const;
    bool contains(BSTNode<T> *node) const;

    void insert(const T &data);

    void remove(const T &data);
    void removeAllNodes();

    BSTNode<T> *search(const T &data) const;
    BSTNode<T> *getSuccessor(BSTNode<T> *node, TraversalPlan tp) const;

    void print(TraversalPlan tp=inorder) const;

    BST<T> &operator=(const BST<T> &rhs);

private: // YOU MAY ADD YOUR OWN UTILITY MEMBER FUNCTIONS HERE.
    void print(BSTNode<T> *node, TraversalPlan tp) const;
    bool isLeaf(BSTNode<T> *node);
    int height();
    int height(BSTNode<T> *node);
    bool contains(BSTNode<T> *node, const T &data);
    void deleteNode(BSTNode<T> *node);
    void insert(BSTNode<T> *&node, const T &data);
    void remove(BSTNode<T> *node, const T &data);
    BSTNode<T> *search(BSTNode<T> *node, const T &data) const;
    BSTNode<T> *minNode(BSTNode<T> *node);

private: // DO NOT CHANGE THIS PART.
    BSTNode<T> *root;
};

#endif //BST_H

// UDF

template<class T>
bool BST<T>::isLeaf(BSTNode<T> *node) {
    return (node->left == NULL and node->right == NULL) ? true : false;
}

template<class T>
int BST<T>::height() {
    return height(root);
}

template<class T>
int BST<T>::height(BSTNode<T> *node) {
    if (node == NULL)
        return -1;
    if (isLeaf(node))
        return 0;
    int l_height = height(node->left);
    int r_height = height(node->right);
    if (l_height < r_height)
        return r_height + 1;
    return l_height + 1;
}

template<class T>
bool BST<T>::contains(BSTNode<T> *node, const T &data) {
    if (node == NULL)
        return false;
    if (node->data == data)
        return true;
    else 
        return contains(node->left, data) or contains(node->right, data);
}

template<class T>
void BST<T>::deleteNode(BSTNode<T> *node) {
    if (node == NULL)
        return;
    deleteNode(node->left);
    deleteNode(node->right);
    delete node;
    node = NULL;
}

template<class T>
void BST<T>::insert(BSTNode<T> *&node, const T &data) {
    if (contains(node, data))
        return;
    if (node == NULL) {
        node = new BSTNode<T>();
        node->data = data;
    }
    else if (data < node->data)
        insert(node->left, data);
    else
        insert(node->right, data);
}

template<class T>
void BST<T>::remove(BSTNode<T> *node, const T &data) {
    if (node == NULL or !contains(node, data))
        return;
    else if (node->data == data)
        deleteNode(node);
    else {
        remove(node->left, data);
        remove(node->right, data);
    }
}

template<class T>
BSTNode<T> *BST<T>::search(BSTNode<T> *node, const T &data) const {
    if (node == NULL or !contains(node, data))
        return NULL;
    if (node->data == data)
        return node;
    else if (data < node->data)
        return search(node->left, data);
    else
        return search(node->right, data);
}

template<class T>
BSTNode<T> *BST<T>::minNode(BSTNode<T> *node) {
    BSTNode<T> *current = node;
    while (current->left != NULL)
    {
        current = current->left;
    }
    return current;
}

// UDF END

template<class T>
BST<T>::BST() {
    root = NULL;
}

template<class T>
BST<T>::BST(const BST<T> &obj) {
    *this = obj;
}

template<class T>
BST<T>::~BST() {
    deleteNode(root);
}

template<class T>
BSTNode<T> *BST<T>::getRoot() const {
    return root;
}

template<class T>
bool BST<T>::isEmpty() const {
    return (root == NULL) ? true : false;
}

template<class T>
bool BST<T>::contains(BSTNode<T> *node) const {
    return contains(root, node->data);
}

template<class T>
void BST<T>::insert(const T &data) {
    insert(root, data);
}

template<class T>
void BST<T>::remove(const T &data) {
    remove(root, data);
}

template<class T>
void BST<T>::removeAllNodes() {
    deleteNode(root);
}

template<class T>
BSTNode<T> *BST<T>::search(const T &data) const {
    return search(root, data);
}

template<class T>
BSTNode<T> *BST<T>::getSuccessor(BSTNode<T> *node, TraversalPlan tp) const {
    BSTNode<T> *successor = root;
    if (tp == inorder) {
        if (node->right != NULL)
            return minNode(node->right);
        while (successor != NULL) {
            if (node->data < successor->data)
                successor = successor->left;
            else if (successor->data < node->data)
                successor = successor->right;
            else
                break;
        }
        return successor;
    } else if (tp == preorder) {
        return node->left;
    } else if (tp == postorder) {
        return node->right;
    }
    else
        return NULL;
}

template<class T>
void BST<T>::print(TraversalPlan tp) const {

    if (tp == inorder) {
        // check if the tree is empty?
        if (isEmpty()) {
            // the tree is empty.
            std::cout << "BST_inorder{}" << std::endl;
            return;
        }

        // the tree is not empty.

        // recursively output the tree.
        std::cout << "BST_inorder{" << std::endl;
        print(root, inorder);
        std::cout << std::endl << "}" << std::endl;
    } else if (tp == preorder) {
        // check if the tree is empty?
        if (isEmpty()) {
            // the tree is empty.
            std::cout << "BST_preorder{}" << std::endl;
            return;
        }

        // the tree is not empty.

        // recursively output the tree.
        std::cout << "BST_preorder{" << std::endl;
        print(root, preorder);
        std::cout << std::endl << "}" << std::endl;
    } else if (tp == postorder) {
        // check if the tree is empty?
        if (isEmpty()) {
            // the tree is empty.
            std::cout << "BST_postorder{}" << std::endl;
            return;
        }

        // the tree is not empty.

        // recursively output the tree.
        std::cout << "BST_postorder{" << std::endl;
        print(root, postorder);
        std::cout << std::endl << "}" << std::endl;
    }
}

template<class T>
BST<T> &BST<T>::operator=(const BST<T> &rhs) {
    removeAllNodes();
    if (rhs.isEmpty())
        return *this;

    BSTNode<T> *rhs_current = rhs.getSuccessor(rhs.getRoot(), inorder);
    while (rhs_current != NULL) {
        insert(rhs_current->data);
    }
    return *this;
}

template<class T>
void BST<T>::print(BSTNode<T> *node, TraversalPlan tp) const {

    // check if the node is NULL?
    if (node == NULL)
        return;

    if (tp == inorder) {
        // first, output left subtree and comma (if needed).
        print(node->left, inorder);
        if (node->left) {
            std::cout << "," << std::endl;
        }

        // then, output the node.
        std::cout << "\t" << node->data;

        // finally, output comma (if needed) and the right subtree.
        if (node->right) {
            std::cout << "," << std::endl;
        }
        print(node->right, inorder);
    } else if (tp == preorder) {
        // first, output the node.
        std::cout << "\t" << node->data;

        // then, output left subtree and comma (if needed).
        if (node->left) {
            std::cout << "," << std::endl;
        }
        print(node->left, preorder);
        

        // finally, output comma (if needed) and the right subtree.
        if (node->right) {
            std::cout << "," << std::endl;
        }
        print(node->right, preorder);
    } else if (tp == postorder) {
        // then, output left subtree and comma (if needed).
        print(node->left, postorder);
        print(node->right, postorder);

        // first, output the node.
        std::cout << "\t" << node->data;
        if (node != root)
            std::cout << "," << std::endl;
    }
}
