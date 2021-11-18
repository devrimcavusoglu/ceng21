#ifndef LISTNODE_H
#define LISTNODE_H

#include <cstddef>

class ListNode {
public:
    int data;
    ListNode *next;

    ListNode(int x) {
        data = x;
        next = NULL;
    }

    ListNode(int x, ListNode *p) {
        data = x;
        next = p;
    }
};

#endif //LISTNODE_H
