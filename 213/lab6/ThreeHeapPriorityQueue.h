#ifndef THREEHEAPPRIORITYQUEUE_H
#define THREEHEAPPRIORITYQUEUE_H

#include <iostream>
#include <vector>

#include "UnderflowException.h"

using namespace std;

/* TODO : Q5 */
/* Modify the HeapPriorityQueue class to make it into a three-heap. 
 * A three-heap is similar to a binary heap, except that each node is 
 * considered to have three children rather than two children. 
 * A three-heap is a wider tree though not as tall as a binary heap. 
 * The heap can still be represented as an array, but the algorithms for 
 * traversing it must be modified to consider all three children 
 * when bubbling as appropriate.
 */

template <class T>
class ThreeHeapPriorityQueue {
public:
    // Public member functions:
    
    ThreeHeapPriorityQueue(int capacity=100);
    
    bool isEmpty() const;
    
    const T& peek() const;
    
    void add(const T &x);
    
    T remove();
    
    void print();

private:
    // Private member variables:
    
    int theSize;    // Number of elements in heap.
    vector<T> arr;  // The heap array.
    
    // Private member functions:
    
    void buildHeap();
    
    void bubbleDown(int hole);
    
    // YOU MAY ADD YOUR OWN UTILITY MEMBER FUNCTIONS HERE.
};

/* TODO : Q5 */
template <class T>
ThreeHeapPriorityQueue<T>::ThreeHeapPriorityQueue(int c) {
    
}

/* TODO : Q5 */
template <class T>
bool ThreeHeapPriorityQueue<T>::isEmpty() const {
    
}

/* TODO : Q5 */
template <class T>
const T& ThreeHeapPriorityQueue<T>::peek() const {
    
}

/* TODO : Q5 */
template <class T>
void ThreeHeapPriorityQueue<T>::add(const T &x) {
    
}

/* TODO : Q5 */
template <class T>
T ThreeHeapPriorityQueue<T>::remove() {
    
}

/* TODO : Q5 */
template <class T>
void ThreeHeapPriorityQueue<T>::bubbleDown(int hole) {
    
}

/* TODO : Q5 */
template <class T>
void ThreeHeapPriorityQueue<T>::buildHeap() {
    
}

/* TODO : Q5 */
template <class T>
void ThreeHeapPriorityQueue<T>::print() {
    
}

#endif //THREEHEAPPRIORITYQUEUE_H
