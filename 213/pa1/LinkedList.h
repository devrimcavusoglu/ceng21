#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>

#include "Node.h"

template<class T>
class LinkedList {
public: // DO NOT CHANGE THIS PART.
    LinkedList();
    LinkedList(const LinkedList<T> &obj);

    ~LinkedList();

    int getSize() const;
    bool isEmpty() const;
    bool contains(Node<T> *node) const;

    Node<T> *getFirstNode() const;
    Node<T> *getLastNode() const;
    Node<T> *getNode(const T &data) const;
    Node<T> *getNodeAtIndex(int index) const;

    void insertAtTheFront(const T &data);
    void insertAtTheEnd(const T &data);
    void insertAfterNode(const T &data, Node<T> *node);
    void insertAsEveryKthNode(const T &data, int k);

    void removeNode(Node<T> *node);
    void removeNode(const T &data);
    void removeAllNodes();
    void removeEveryKthNode(int k);

    void swap(Node<T> *node1, Node<T> *node2);
    void shuffle(int seed);

    void print(bool reverse=false) const;

    LinkedList<T> &operator=(const LinkedList<T> &rhs);

private: // YOU MAY ADD YOUR OWN UTILITY MEMBER FUNCTIONS HERE.

private: // DO NOT CHANGE THIS PART.
    Node<T> *head;

    int size;
};

template<class T>
LinkedList<T>::LinkedList() {
    head = NULL;
    size = 0;
}

template<class T>
LinkedList<T>::LinkedList(const LinkedList<T> &obj) {
    size = 0;
    while (obj.head->next != NULL) {
        T current = obj.head->data;
        insertAtTheEnd(current);
        obj = obj.head;
        size++;
   }
}

template<class T>
LinkedList<T>::~LinkedList() {
    while (!isEmpty()){
        T next_ptr = obj.head->next;
        delete head;
    }
}

template<class T>
int LinkedList<T>::getSize() const {
    return size
}

template<class T>
bool LinkedList<T>::isEmpty() const {
    return (size == 0) ? true : false;
}

template<class T>
bool LinkedList<T>::contains(Node<T> *node) const {
    Node<T> *current = head;
    while (current != NULL){
        if (current->data == node->data){
            return true;
        }
        current = current->next;
    }
    return false;
}

template<class T>
Node<T> *LinkedList<T>::getFirstNode() const {
    return head;
}

template<class T>
Node<T> *LinkedList<T>::getLastNode() const {
    while (head->next != NULL){
        head = head->next;
    }
    return head;
}

template<class T>
Node<T> *LinkedList<T>::getNode(const T &data) const {
    while (head->next != NULL){
        if (head->data == data){
            return head;
        }
    }
    return nullptr;
}

template<class T>
Node<T> *LinkedList<T>::getNodeAtIndex(int index) const {
    /* TODO */
}

template<class T>
void LinkedList<T>::insertAtTheFront(const T &data) {
    /* TODO */
}

template<class T>
void LinkedList<T>::insertAtTheEnd(const T &data) {
    /* TODO */
}

template<class T>
void LinkedList<T>::insertAfterNode(const T &data, Node<T> *node) {
    /* TODO */
}

template<class T>
void LinkedList<T>::insertAsEveryKthNode(const T &data, int k) {
    /* TODO */
}

template<class T>
void LinkedList<T>::removeNode(Node<T> *node) {
    /* TODO */
}

template<class T>
void LinkedList<T>::removeNode(const T &data) {
    /* TODO */
}

template<class T>
void LinkedList<T>::removeAllNodes() {
    /* TODO */
}

template<class T>
void LinkedList<T>::removeEveryKthNode(int k) {
    /* TODO */
}

template<class T>
void LinkedList<T>::swap(Node<T> *node1, Node<T> *node2) {
    /* TODO */
}

template<class T>
void LinkedList<T>::shuffle(int seed) {
    /* TODO */
}

template<class T>
void LinkedList<T>::print(bool reverse) const {
    if (this->isEmpty()) {
        std::cout << "The list is empty." << std::endl;
        return;
    }

    if (reverse) {
        // traverse in reverse order (last node to first node).

        Node<T> *node = this->getLastNode();

        do {
            std::cout << *node << std::endl;
            node = node->prev;
        }
        while (node != this->getLastNode());
    } else {
        // traverse in normal order (first node to last node).

        Node<T> *node = this->getFirstNode();

        do {
            std::cout << *node << std::endl;
            node = node->next;
        }
        while (node != this->getFirstNode());
    }
}

template<class T>
LinkedList<T> &LinkedList<T>::operator=(const LinkedList<T> &rhs) {
    /* TODO */
}

#endif //LINKEDLIST_H