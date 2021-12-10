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
    void deleteNode(BSTNode<T> *node);
    void insert(BSTNode<T> *node, const T &data);
    void remove(BSTNode<T> *node, const T &data);
    BSTNode<T> *search(BSTNode<T> *node, const T &data);

private: // DO NOT CHANGE THIS PART.
    BSTNode<T> *root;
};

#endif //BST_H

template<class T>
void BST<T>::deleteNode(BSTNode<T> *node) {
    if (node == NULL)
        return;
    this->deleteNode(node->left);
    this->deleteNode(node->right);
    delete node;
    node = NULL;
}

template<class T>
void BST<T>::insert(BSTNode<T> *&node, const T &data) {
    if (this->contains(node, data))
        return;
    if (node == NULL)
        node = new BSTNode<T>();
        node->data = data;
    else if (data < node->data)
        insert(node->left, data);
    else
        insert(node->right, data);
}

template<class T>
void BST<T>::remove(BSTNode<T> *node, const T &data) {
    if (node == NULL or !this->contains(node, data))
        return;
    else if (node->data == data)
        this->deleteNode(node);
    else {
        this->remove(node->left, data);
        this->remove(node->right, data);
    }
}

template<class T>
BSTNode<T> *BST<T>::search(BSTNode<T> *node, const T &data) const {
    if (node == NULL or !this->contains(node, data))
        return NULL;
    if (node->data == data)
        return node;
    else if (data < node->data)
        return search(node->left, data);
    else
        return search(node->right, data);
}


template<class T>
BST<T>::BST() {
    this->root = NULL;
}

template<class T>
BST<T>::BST(const BST<T> &obj) {
    *this = obj;
}

template<class T>
BST<T>::~BST() {
    deleteNode(this->root);
    delete this->root;
}

template<class T>
BSTNode<T> *BST<T>::getRoot() const {
    return this->root;
}

template<class T>
bool BST<T>::isEmpty() const {
    return (this->root == NULL) ? true : false;
}

template<class T>
bool BST<T>::contains(BSTNode<T> *node) const {
    if (node == NULL)
        return false;
    if (node->data == val)
        return true;
    else 
        return contains(node->left, val) or contains(node->right, val);
}

template<class T>
void BST<T>::insert(const T &data) {
    this->insert(this->root, data);
}

template<class T>
void BST<T>::remove(const T &data) {
    this->remove(this->root, data);
}

template<class T>
void BST<T>::removeAllNodes() {
    this->deleteNode(this->root);
}

template<class T>
BSTNode<T> *BST<T>::search(const T &data) const {
    this->search(this->root, data);
}

template<class T>
BSTNode<T> *BST<T>::getSuccessor(BSTNode<T> *node, TraversalPlan tp) const {

    if (tp == inorder) {
        return node;
    } else if (tp == preorder) {
        return node->left;
    } else if (tp == postorder) {
        return node->right;
    }
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
            std::cout << "BST_inorder{}" << std::endl;
            return;
        }

        // the tree is not empty.

        // recursively output the tree.
        std::cout << "BST_inorder{" << std::endl;
        print(root, preorder);
        std::cout << std::endl << "}" << std::endl;
    } else if (tp == postorder) {
        // check if the tree is empty?
        if (isEmpty()) {
            // the tree is empty.
            std::cout << "BST_inorder{}" << std::endl;
            return;
        }

        // the tree is not empty.

        // recursively output the tree.
        std::cout << "BST_inorder{" << std::endl;
        print(root, postorder);
        std::cout << std::endl << "}" << std::endl;
    }
}

template<class T>
BST<T> &BST<T>::operator=(const BST<T> &rhs) {
    this->removeAllNodes();
    
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
        /* TODO */
    } else if (tp == postorder) {
        /* TODO */
    }
}
