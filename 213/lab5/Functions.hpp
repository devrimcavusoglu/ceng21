#ifndef _FUNCTIONS
#define _FUNCTIONS

#include "Stack.hpp"

// Write a function called isSorted that accepts a stack of integers as a parameter and returns true if the
// elements in the stack is in ascending (nondecreasing) order from top to bottom. That is the smallest
// element should be on top, growing larger toward the bottom. For example if the stack stores 
// [20,20,17,11,8,8,3,2] your function should return true. An empty, or one-element stack is considered to
// be sorted. Your function must restore the parameter stack to its original state before returning. Use a
// stack as auxiliary storage.
bool isSorted(Stack<int>& s1);

// Write a method called equals that accepts two stacks of integers as parameters and
// returns true if the two stacks are exactly the same sequence of integer values in the same order.
// Your method must restore the two stacks to their original state before returning.
// Use one stack as auxiliary storage.
bool equals(Stack<int>& s1, Stack<int>& s2);

#endif //_FUNCTIONS
