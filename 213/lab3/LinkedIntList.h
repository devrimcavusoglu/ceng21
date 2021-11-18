#ifndef LINKEDINTLIST_H
#define LINKEDINTLIST_H

#include "ListNode.h"
#include "NoSuchElementException.h"

class LinkedIntList {
public:
    LinkedIntList() {
        front = NULL;
    }

    ~LinkedIntList();

    LinkedIntList(const LinkedIntList &rhs);

    LinkedIntList &operator=(const LinkedIntList rhs);

    void add(int value);

    void add(int index, int value);

    void addSorted(int value);

    int get(int index);

    int remove(); // throws NoSuchElementException

    void remove(int index);

    void print();

    // TODO
    // Write a method called "set" that accepts an index and a value and
    // sets the list’s element at that index to have the given value.
    // You may assume that the index is between 0 (inclusive) and the size of the list (exclusive).
    void set(int index, int value);

    // TODO
    // Write a method called "min" that returns the minimum value in a list of integers.
    // If the list is empty, it should throw a NoSuchElementException.
    int min();

    // TODO
    // Write a method called "lastIndexOf" that accepts an integer value as a parameter and
    // that returns the index in the list of the last occurrence of that value or -1 if the value is not found in the list.
    // For example if a variable list stores values [1, 18, 2, 7, 18, 39, 18, 40] then the call of list.lastIndexOf(18)
    // should return 6. If the call instead is list.lastIndexOf(3), the method returns -1.
    int lastIndexOf(int value);

    // TODO
    // Write a method called "deleteBack" that deletes the last value (the value at the back of the list) and
    // returns the deleted value. If the list is empty, throw a NoSuchElementException.
    int deleteBack();

    // TODO
    // Write a method called "removeAdjacentDuplicates" that remove adjacent duplicate elements
    // on the linked list.
    // For example if list is currently [18, 7, 7, 7, 4, 4, 24, 11, 11]
    // then it becomes [18, 7, 4, 24, 11]
    void removeAdjacentDuplicates();

    // TODO
    // Write a method called "removeAll" that removes all occurrences of a particular value.
    // For example if a variable list stores the values [3, 9, 4, 2, 3, 8, 17, 4, 3, 18], the call list.removeAll(3);
    // would change the list to store [9, 4, 2, 8, 17, 4, 18].
    void removeAll(int value);

    // TODO
    // Write a method called "equals" that accepts a second list as a parameter,
    // returns true if the two lists are equal, and returns false otherwise.
    // Two lists are considered equal if they store exactly the same values in exactly the same order and
    // have exactly the same length.
    bool equals(const LinkedIntList &L);

    // TODO
    // Write a method called "invert" that inverts the linked list.
    // For example if list is currently [4, 5, 9, 22, 8, 33]
    // then it becomes [33, 8, 22, 9, 5, 4]
    void invert();
    
    //TODO
    //Write a method called "numberOfOccurences" that accepts an integer value as parameter
    //This method returns number of occurences of a value in the list
    //For example if a variable list stores the values [5, 5, 5, 10, 15, 5], the call list.numberOfOccurences(5);
    // would return 4.
    int numberOfOccurences(int value);
    
    //TODO
    //Write a method called "isSorted" that do not accept any parameter
    //This method returns true if the list is sorted; it returns false if the list is unsorted
    //For example if a variable list stores the values [5, 5, 5, 10, 15, 5], the call list.isSorted();
    // would return false
    //For example if a variable list stores the values [5, 5, 5, 10, 15], the call list.isSorted();
    // would return true
    bool isSorted();

    

private:
    ListNode *front;

    bool isEmpty();
};

#endif //LINKEDINTLIST_H
