#ifndef TREENODE_H
#define TREENODE_H

#include <iostream> 
#include <string> 

using namespace std; 

class TreeNode {
public:
    string data;        // data stored at this node
    TreeNode *left;     // reference to left subtree
    TreeNode *right;    // reference to right subtree

    // Constructs a leaf node with the given data.
    TreeNode(string val="") {
        data = val;
        left = NULL;
        right = NULL;
    }

    // Constructs a branch node with the given data and links.
    TreeNode(string val, TreeNode *lft, TreeNode *rght) {
        data = val;
        left = lft;
        right = rght;
    }
};

#endif //TREENODE_H