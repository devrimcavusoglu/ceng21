#ifndef INTTREE_H
#define INTTREE_H

#include <iostream>
#include <string>

#include "IntTreeNode.h"

using namespace std;

class IntTree {
public:
    // PUBLIC MEMBER FUNCTIONS:
    
    // Default constructor.
    IntTree(IntTreeNode *r=NULL);
    
    // Constructor that creates a full binary tree of a given height.
    IntTree(int height=-1);
    
    // Constructor that creates a full binary tree of a given integer array.
    IntTree(int *arr, int length);
    
    // Destructor.
    ~IntTree();
    
    // Copy constructor.
    IntTree(const IntTree &t);
    
    // Assignment operator.
    IntTree& operator=(const IntTree &t);
    
    // Prints this tree in inorder.
    void print();
    
    // Prints this tree sideways.
    void printSideways();
    
    // Returns the maximum value in this binary tree.
    int getMax();
    
    // Finds the sum of all values in this tree.
    int find_sum();

    /* Q1 */
    /* Returns the height of the tree.
     */
    int height();
    
    /* Q2 */
    /* Returns if the tree contains the value val or not.
     */
    bool contains(int val);

    /* Q3 */
    /* Prints the leaves of the tree from right to left 
     * (i.e. the leaves must be printed in the reverse order that 
     * they would be printed using a standard traversal). 
     * If the tree is empty your method should produce the output "no leaves”.
     */
    void printLeaves();
    
    /* Q4 */
    /* Changes the data stored in the tree, assigning sequential integers 
     * starting with 1 to each node so that preorder traversal will produce 
     * the numbers in order (1, 2, 3, etc.).
     */
    void numberNodes();
    
    /* Q5 */
    /* Removes the leaves from the tree. 
     * A leaf node is a node that has empty left and right subtrees. 
     * If method is called on an empty tree, it does not change the tree. 
     */
    void removeLeaves();
    
    /* Q6 */
    /* Accepts an integer n and prints the values at level n 
     * from left to right on one line. 
     * (Root of the tree is at level 1, its children are at level 2 and so on). 
     * If there are no values at the level, method should produce no output. 
     * The method should throw an IllegalArgumentException if 
     * it is passed a value for a level that is less than 1.
     */
    void printLevel(int n);

private:
    bool isLeaf(IntTreeNode *node);
    bool isEmpty();
    void updateData(IntTreeNode *&node, int value);
    int depth(IntTreeNode *target_node);
    int depth(IntTreeNode *source_node, IntTreeNode *target_node);

private:
    // PRIVATE MEMBER VARIABLES:
    
    // The overall root of the tree. It is null for an empty tree.
    IntTreeNode *root;

    // PRIVATE MEMBER FUNCTIONS:

    // Helper method to construct a binary tree with a given height.
    void construct(IntTreeNode *&r, int h);
    
    // Helper method to construct a binary tree with a given integer array.
    void constructWithArray(IntTreeNode *&r, int *arr, int ind, int length);
    
    // Helper method to delete all nodes in a tree.
    void deleteTree(IntTreeNode *&r);
    
    // Make a deep copy of a given tree.
    void make_copy(IntTreeNode *&t1, IntTreeNode *t2);
    
    // Helper method to print the nodes in inorder.
    void printInOrder(IntTreeNode *r);
    
    // Helper method to print the nodes sideways.
    void printSideways(IntTreeNode *r, string str);
    
    // Helper method to find the maximum value in this binary tree.
    int getMax(IntTreeNode *r);
    
    // Helper method to find the overall sum of  values.
    int find_sum(IntTreeNode *r);
    
    /* Q1 : helper function */
    int height(IntTreeNode *r);

    /* Q2 : helper function */
    bool contains(IntTreeNode *r, int val);

    /* Q3 : helper function */
    void printLeaves(IntTreeNode *r);
    
    /* Q4 : helper function */
    void numberNodes(IntTreeNode *r, int &n);
    
    /* Q5 : helper function */
    void removeLeaves(IntTreeNode *&r);
    
    /* Q6 : helper function */
    void printLevel(IntTreeNode *r, int n);
};

#endif //INTTREE_H
