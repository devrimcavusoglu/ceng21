#ifndef _DEQUE
#define _DEQUE

#include "DequeException.h"
#include <iostream>
using namespace std;

/*
A deque is a data structure consisting of a list of items, on which the following operations are possible:

push(x): Insert item x on the front end of the deque.
pop(): remove the front item from the deque and return it.
inject(x): Insert item x on the back end of the deque.
eject(): Remove the back item from the deque and return it.

Write the implementation of deque using a circular array.
*/


const int MAX_DEQUE = 100;

class Deque {
public:
    Deque();  // default constructor; copy constructor and destructor are supplied by the compiler

    bool isEmpty() const;	// Determines if deque is empty.
    void push(const int& newItem) throw(DequeException); // Adds an item to the front of a deque.
    int pop() throw(DequeException);		   // Removes and returns the front item of a deque.
    void inject(const int& newItem) throw(DequeException); // Adds an item to the back of a deque.
    int eject() throw(DequeException);      // Removes and returns the back item from the deque.

    bool isFull(); // Determines if deque is full.
    int getFront(); // Return front element of Deque
    int getBack(); // Return rear element of Deque

private:
    int items[MAX_DEQUE];  	// array of items
    int front;         		// index to front of deque
    int back;                // index to back of deque
    int count;
};


Deque::Deque(){// default constructor
   front = 0;
   back = MAX_DEQUE - 1;
   count = 0;
}

bool Deque::isFull() {
    return count == MAX_DEQUE;
}

bool Deque::isEmpty() const {
    return count == 0;
}

int Deque::getFront() {
    return items[front];
}

int Deque::getBack() {
    return items[back];
}

int Deque::pop() throw(DequeException) {
    if (isEmpty())
        throw DequeException("Deque is empty.");
    front = (front + 1) % MAX_DEQUE;
    count--;
    return items[front];
}

void Deque::push(const int& newItem) throw(DequeException) {
    if (isFull())
        throw DequeException("Deque is full.");
    front = (front - 1) % MAX_DEQUE;
    count++;
}

int Deque::eject() throw(DequeException) {
    if (isEmpty())
        throw DequeException("Deque is empty.");
    back = (back - 1) % MAX_DEQUE;
    count--;
    return items[back];
 }

void Deque::inject(const int& newItem) throw(DequeException) {
    if (isFull())
        throw DequeException("Deque is full.");
    back = (back + 1) % MAX_DEQUE;
    count++;
    items[back] = newItem;
}
#endif // _EXCEPTION

