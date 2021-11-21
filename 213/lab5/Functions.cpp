#include <iostream>

#include "Functions.hpp"

using namespace std;

// Write a function called isSorted that accepts a stack of integers as a parameter and returns true if the
// elements in the stack is in ascending (nondecreasing) order from top to bottom. That is the smallest
// element should be on top, growing larger toward the bottom. For example if the stack stores 
// [20,20,17,11,8,8,3,2] your function should return true. An empty, or one-element stack is considered to
// be sorted. Your function must restore the parameter stack to its original state before returning. Use a
// stack as auxiliary storage.
bool isSorted(Stack<int>& s1) {
    bool is_sorted = true;
    if (!s1.isEmpty()){
        int max = s1.peek();
        Stack<int> aux;
        while (!s1.isEmpty() and is_sorted){
            int item;
            item = s1.pop();
            aux.push(item);
            if (item >= max)
                max = item;
            else
                is_sorted = false;
        }
        while (!aux.isEmpty()){
            int item;
            item = aux.pop();
            s1.push(item);
        }
    }
    return is_sorted;
}


// Write a method called equals that accepts two stacks of integers as parameters and
// returns true if the two stacks are exactly the same sequence of integer values in the same order.
// Your method must restore the two stacks to their original state before returning.
// Use one stack as auxiliary storage.
bool equals(Stack<int>& s1, Stack<int>& s2) {
    bool is_equal = true;
    Stack<int> s3;

    if (s1.isEmpty() and s2.isEmpty())
        is_equal = true;
    else if (s1.isEmpty() and !s2.isEmpty())
        is_equal = false;
    else if (!s1.isEmpty() and s2.isEmpty())
        is_equal = false;
    else {
        if (s1.peek() != s2.peek())
            return false;
        else {
            int tmp;
            tmp = s1.pop();
            tmp = s2.pop();
            s3.push(tmp);
        }
        is_equal = equals(s1, s2);
        int tmp = s3.pop();
        s1.push(tmp);
        s2.push(tmp);
    }
    return is_equal;
}
