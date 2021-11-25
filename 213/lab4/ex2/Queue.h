#ifndef _QUEUE
#define _QUEUE

#include "QueueException.h"
const int MAX_QUEUE = 100;

template <class T>
class Queue {
public:
    Queue();  // default constructor
    bool isEmpty() const;
    void enqueue(const T& newItem) throw(QueueException);
    T dequeue() throw(QueueException);
    T peek() const throw(QueueException);
private:
    T items[MAX_QUEUE];
    int front;
    int back;
    int count;
};
template<class T>
Queue<T>::Queue():front(0), back(MAX_QUEUE-1), count(0) {}


template<class T>
bool Queue<T>::isEmpty() const
{
    return count == 0;
}
template<class T>
void Queue<T>::enqueue(const T& newItem) throw(QueueException) {
    if (count == MAX_QUEUE)
        throw QueueException("QueueException: queue full on enqueue");
    else {  	// queue is not full; insert item
        back = (back+1) % MAX_QUEUE;
        items[back] = newItem;
        ++count;
    }
}
template<class T>
T Queue<T>::dequeue() throw(QueueException) {
    if (isEmpty())
        throw QueueException("QueueException: empty queue, cannot dequeue");
    else {  // queue is not empty; remove front
        T val = items[front];
        front = (front+1) % MAX_QUEUE;
        --count;
        return val;
    }
}

template <class T>
T Queue<T>::peek () const throw(QueueException)
{
    if (isEmpty())
        throw QueueException("QueueException: empty queue, cannot getFront");
    else
        // queue is not empty; retrieve front
        return(items[front]);
}

#endif // _QUEUE

