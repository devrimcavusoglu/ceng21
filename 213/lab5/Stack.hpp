#ifndef _STACK
#define _STACK

#include "StackException.hpp"

const int MAX_STACK = 100;

template <class T>
class Stack {
public:
    Stack();                        // Default constructor; copy constructor and destructor are supplied by the compiler.

    bool isEmpty() const;	        // Determines if stack is empty.
    void push(const T& newItem);    // Adds an item to the top of a stack.
    T pop();		                // Removes and returns the top of a stack.
    T peek() const;                 // Retrieves top of stack.

private:
    T items[MAX_STACK];  	        // array of stack items
    int top;         		        // index to top of stack
};

template <class T>
Stack<T>::Stack() { // Default constructor.

    top = -1;
}

template <class T>
bool Stack<T>::isEmpty() const { // Determines if stack is empty.

    return top < 0;
}

template <class T>
void Stack<T>::push(const T& newItem) { // Adds an item to the top of a stack.

    if (top >= MAX_STACK-1)
        throw StackException("StackException: stack full on push");
    else
        items[++top] = newItem;
}

template <class T>
T Stack<T>::pop() { // Removes and returns the top of a stack.

    if (isEmpty())
        throw StackException("StackException: stack empty on pop");
    else // stack is not empty; return top
        return (items[top--]);
}

template <class T>
T Stack<T>::peek() const { // Retrieves top of stack.

    if (isEmpty())
        throw StackException("StackException: stack empty on getTop");
    else
        return (items[top]);
}

#endif //_STACK
