#include <iostream>

#include "TreeNode.h"

using namespace std;


/*
 * Given a binary tree, prints its nodes in preorder.
 */
void printPreorder(TreeNode *node) {
    if (node == NULL) return; 
  
    // First print the data of the node.
    cout << node->data << " "; 
  
    // Then recur on the left subtree.
    printPreorder(node->left);  
  
    // Finally recur on the right subtree.
    printPreorder(node->right); 
}  


/*
 * Q1
 * Write a function called countLeftNodes that returns the number of left children in the tree.
 * A left child is a node that appears as the root of the left-hand subtree of another node. 
 */
int countLeftNodes(TreeNode *node) {
    if (node->left == NULL)
        return 0;
    return 1 + countLeftNodes(node->left);
}



bool isLeaf(TreeNode *node) {
    if (node == NULL)
        return true;
    if (node->left == NULL and node->right == NULL)
        return true;
    return false;
}


/*
 * Q2
 * Write a function called isFull that returns true if a binary tree is full and false if it is not. 
 * A full binary tree is one in which every node has 0 or 2 children.
 * By definition an empty tree is considered full.
 */
bool isFull(TreeNode *node) {
    if (isLeaf(node))
        return true;
    else if ((node->left != NULL and node->right == NULL) or (node->left == NULL and node->right != NULL))
        return false;
    return isFull(node->left) && isFull(node->right);
}


int main() {
    /******************/
    /* countLeftNodes */
    /******************/
    
    cout << "Creating a binary tree named tree1 with preorder traversal: A B C D E" << std::endl;
    /*  Current tree..
    /*            A
    /*        B       D
    /*    C               E
    */
    TreeNode *tree1 = new TreeNode("A");
    tree1->left = new TreeNode("B");
    tree1->left->left = new TreeNode("C");
    tree1->right = new TreeNode("D");
    tree1->right->right = new TreeNode("E");
    
    cout << "Preorder traversal of tree1 is "; 
    printPreorder(tree1); 
    cout << endl;
    
    cout << "Count of left nodes of tree1 is " << countLeftNodes(tree1) << endl;
    
    cout << endl;
    
    /**********/
    /* isFull */
    /**********/
    
    cout << "Creating an empty binary tree named tree2" << std::endl;
    TreeNode *tree2 = NULL;
    
    cout << "Preorder traversal of tree2 is "; 
    printPreorder(tree2);
    cout << endl;
    
    cout << "Is tree2 full? " << (isFull(tree2) ? "yes" : "no") << endl;
    
    cout << "Creating a binary tree named tree3 with preorder traversal: A B D" << std::endl;
    TreeNode *tree3 = new TreeNode("A");
    tree3->left = new TreeNode("B");
    tree3->right = new TreeNode("D");
    
    cout << "Preorder traversal of tree3 is ";
    printPreorder(tree3);
    cout << endl;
    
    cout << "Is tree3 full? " << (isFull(tree3) ? "yes" : "no") << endl;
    
    cout << "Is tree1 full? " << (isFull(tree1) ? "yes" : "no") << endl;
    
    return 0; 
}