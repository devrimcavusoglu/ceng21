#ifndef HEAPPRIORITYQUEUE_H
#define HEAPPRIORITYQUEUE_H

#include <iostream>
#include <vector>

#include "UnderflowException.h"

using namespace std;

template <class T>
class HeapPriorityQueue {
public:
    // Public member functions:
    
    HeapPriorityQueue(int capacity=100);
    
    bool isEmpty() const;
    
    const T& peek() const;
    
    void add(const T &x);
    
    T remove();
    
    void print();
    
    /* TODO : Q4 */
    /* Accepts two elements oldVal and newVal as its parameters and changes 
     * the occurrence of oldVal to newVal. The method should make sure that 
     * the heap ordering property is satisfied after this update.
     */
    void changePriority(T oldVal, T newVal);
    
private:
    // Private member variables:
    
    int theSize;    // Number of elements in heap.
    vector<T> arr;  // The heap array.
    
    // Private member functions:
    
    void buildHeap();
    
    void bubbleDown(int hole);
    
    // YOU MAY ADD YOUR OWN UTILITY MEMBER FUNCTIONS HERE.

    void bubbleUp(int hole);
};

template <class T>
HeapPriorityQueue<T>::HeapPriorityQueue(int c) {
    theSize = 0;
    arr.push_back(0);
}

template <class T>
bool HeapPriorityQueue<T>::isEmpty() const {
    return (theSize == 0);
}

template <class T>
const T& HeapPriorityQueue<T>::peek() const {
    return arr[1];
}

template <class T>
void HeapPriorityQueue<T>::add(const T &x) {
    arr[0] = x; // initialize sentinel
    
    if((theSize + 1) == ((int) arr.size()))
        arr.resize(arr.size( )*2 + 1);
    
    // Percolate up
    int hole = ++theSize;
    for( ; x < arr[hole/2]; hole /= 2 )
        arr[hole] = arr[hole/2];
    arr[hole] = x;
}

template <class T>
T HeapPriorityQueue<T>::remove() {
    // Remove the smallest item from the priority queue.
    if(isEmpty())
        throw UnderflowException(); // Throw UnderflowException if empty.
    
    T tmp = arr[1];
    arr[1] = arr[theSize--];
    bubbleDown(1);
    return tmp;
}

template <class T>
void HeapPriorityQueue<T>::bubbleDown(int hole) {
    // Internal method to percolate down in the heap.
    // hole is the index at which the percolate begins.
    int child;
    T tmp = arr[hole];
    
    for( ; hole*2 <= theSize; hole = child) {
        child = hole * 2;
        if(child != theSize && arr[child + 1] < arr[child])
            child++;
        if(arr[child] < tmp)
            arr[hole] = arr[child];
        else
            break;
    }
    arr[hole] = tmp;
}

template <class T>
void HeapPriorityQueue<T>::buildHeap() {
    // Establish heap-order property from an arbitrary
    // arrangement of items. Runs in linear time.
    for(int i = theSize/2; i > 0; i-- )
        bubbleDown(i);
}

template <class T>
void HeapPriorityQueue<T>::print() {
    for(int i = 1; i <= theSize; i++)
        cout << arr[i] << " ";
    cout << endl;
}

template <class T>
void HeapPriorityQueue<T>::bubbleUp(int hole)
{
    if (hole == 1)
        return;

    int parentIndex = hole/2;
    if(arr[parentIndex] > arr[hole])
    {
        T temp = arr[parentIndex];
        arr[parentIndex] = arr[hole];
        arr[hole] = temp;
        bubbleUp(parentIndex);
    }
}

/* TODO : Q4 */
/* Accepts two elements oldVal and newVal as its parameters and changes 
 * the occurrence of oldVal to newVal. The method should make sure that 
 * the heap ordering property is satisfied after this update.
 */
template <class T>
void HeapPriorityQueue<T>::changePriority(T oldVal, T newVal) {
    if (oldVal == newVal)
        return;
    int idx = 0;
    for (; idx < arr.size(); idx++) {
        if (arr[idx] == oldVal)
            break;
    }
    arr[idx] = newVal;
    if (oldVal < newVal)
        bubbleDown(idx);
    else
        bubbleUp(idx);
}

#endif //HEAPPRIORITYQUEUE_H


