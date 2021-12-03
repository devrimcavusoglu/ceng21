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

    void updateNode(Node<T> *node);

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
    head = NULL;
    size = 0;
    *this = obj;
}

template<class T>
LinkedList<T>::~LinkedList() {
    removeAllNodes();
    delete head;
}

template<class T>
int LinkedList<T>::getSize() const {
    return size;
}

template<class T>
bool LinkedList<T>::isEmpty() const {
    return (size == 0) ? true : false;
}

template<class T>
bool LinkedList<T>::contains(Node<T> *node) const {
    if (isEmpty())
        return false;
    Node<T> *current = head;
    do {
        if (current == node){
            return true;
        }
        current = current->next;
    } while (current != head);

    return false;
}

template<class T>
Node<T> *LinkedList<T>::getFirstNode() const {
    if (isEmpty())
        return NULL;
    return head;
}

template<class T>
Node<T> *LinkedList<T>::getLastNode() const {
    if (isEmpty())
        return NULL;
    return head->prev;
}

template<class T>
Node<T> *LinkedList<T>::getNode(const T &data) const {
    if (isEmpty())
        return NULL;
    Node<T> *current = head;
    do {
        if (current->data == data)
            return current;
        current = current->next;
    } while (current != head);
    return NULL;
}

template<class T>
Node<T> *LinkedList<T>::getNodeAtIndex(int index) const {
    if (index >= size or index < 0)
        return NULL;
    Node<T> *current = head;
    int i = 0;
    do {
        if (i == index)
            return current;
        current = current->next;
        i++;
    } while (current != head);
    return NULL;
}

template<class T>
void LinkedList<T>::insertAtTheFront(const T &data) {
    Node<T> *new_node = new Node<T>(data);
    if (!head) {
        new_node->prev = new_node;
        new_node->next = new_node;
    }
    else {
        new_node->prev = head->prev;
        new_node->next = head;
    }
    head = new_node;
    updateNode(head);
    size++;
}

template<class T>
void LinkedList<T>::insertAtTheEnd(const T &data) {
    if (!head) {
        insertAtTheFront(data);
        return;
    }
    else {
        Node<T> *last_node = getLastNode();
        Node<T> *new_node = new Node<T>(data, last_node, head);
        updateNode(new_node);
    }
    size++;
}

template<class T>
void LinkedList<T>::insertAfterNode(const T &data, Node<T> *node) {
    if (!contains(node)) 
        return;
    Node<T> *next_node = node->next;
    Node<T> *new_node = new Node<T>(data, node, next_node);
    updateNode(new_node);
    size++;
}

template<class T>
void LinkedList<T>::insertAsEveryKthNode(const T &data, int k) {
    if (k < 2 or k > (size+1))
        return;
    Node<T> *current = head;
    int i = 1;
    do {
        if (i % (k-1) == 0) {
            insertAfterNode(data, current);
            current = current->next;
        }
        current = current->next;
        i++;
    } while (current != head);
}

template<class T>
void LinkedList<T>::removeNode(Node<T> *node) {
    if (!contains(node)) 
        return;

    if (size == 1) {
        delete node;
        head = NULL;
        size = 0;
        return;
    }
    else if (node == getFirstNode()) {
        Node<T> *prev_node = head->prev;
        head = head->next;
        head->prev = prev_node;
        prev_node->next = head;
    }
    else if (node == getLastNode()) {
        Node<T> *prev_node = node->prev;
        prev_node->next = head;
        head->prev = prev_node;
    }
    else {
        Node<T> *tmp_prev = node->prev;
        Node<T> *tmp_next = node->next;
        tmp_prev->next = tmp_next;
        tmp_next->prev = tmp_prev;
    }
    delete node;
    size--;
}

template<class T>
void LinkedList<T>::removeNode(const T &data) {
    if (isEmpty()) 
        return;

    Node<T> *tmp = getNode(data);
    while (tmp != NULL) {
        removeNode(tmp);
        tmp = getNode(data);
    } 
}

template<class T>
void LinkedList<T>::removeAllNodes() {
    while (!isEmpty()){
        removeNode(head);
    }
}

template<class T>
void LinkedList<T>::removeEveryKthNode(int k) {
    if (k < 2 or k > (size+1))
        return;
    Node<T> *current = head;
    int i = 0;
    do {
        if ((i+1) % k == 0) {
            Node<T> *next_node = current->next;
            removeNode(current);
            current = next_node;
        }
        else 
            current = current->next;
        i++;
    } while (current != head);
}

template<class T>
void LinkedList<T>::updateNode(Node<T> *node) {
    node->prev->next = node;
    node->next->prev = node;
}


template<class T>
void LinkedList<T>::swap(Node<T> *node1, Node<T> *node2) {
    if (!contains(node1) or !contains(node2)) 
        return;

    if (node1 == node2)
        return;
    
    if (node2->next == node1) {
        Node<T> *temp = node1;
        node1 = node2;
        node2 = temp;
    }

    if (node2->next != node1) { // More than 2 nodes in the list
        Node<T> *n1_prev = node1->prev;
        Node<T> *n2_next = node2->next;

        if (node1->next == node2) {
            node1->prev = node1->next;
            node2->next = node2->prev;
        } else {
            node1->prev = node2->prev;
            node2->next = node1->next;
        }
        node2->prev = n1_prev;
        node1->next = n2_next;

        updateNode(node1);
        updateNode(node2);
    }
    // If head was swapped, it should reference the other one now
    if (head == node1)
        head = node2;
    else if (head == node2)
        head = node1;
}

template<class T>
void LinkedList<T>::shuffle(int seed) {
    //for "i=0" to "i=size-1":
    //swap the node at index i with the node at index (i*i+seed)%size
    for (int i = 0; i<size; i++) {
        int swap_index = (i*i+seed)%size;
        swap(getNodeAtIndex(i), getNodeAtIndex(swap_index));
    }
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
    Node<T> *rhs_current = rhs.getFirstNode();
    if (rhs_current == NULL) {
        this->head = NULL;
        this->size = rhs.getSize();
    }
    else {
        do {
            insertAtTheEnd(rhs_current->data);
            rhs_current = rhs_current->next;
        } while(rhs_current != rhs.getFirstNode());
    }
    return *this;
}

#endif //LINKEDLIST_H
