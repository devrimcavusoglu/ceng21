#ifndef BST_H
#define BST_H

#include <iostream>

#include "BSTNode.h"

enum TraversalPlan {preorder, inorder, postorder};

template<class T>
class BST {
public: // DO NOT CHANGE THIS PART.
    BST();
    BST(const BST<T> &obj);

    ~BST();

    BSTNode<T> *getRoot() const;
    bool isEmpty() const;
    bool contains(BSTNode<T> *node) const;

    void insert(const T &data);

    void remove(const T &data);
    void removeAllNodes();

    BSTNode<T> *search(const T &data) const;
    BSTNode<T> *getSuccessor(BSTNode<T> *node, TraversalPlan tp) const;

    void print(TraversalPlan tp=inorder) const;

    BST<T> &operator=(const BST<T> &rhs);

private: // YOU MAY ADD YOUR OWN UTILITY MEMBER FUNCTIONS HERE.
    void print(BSTNode<T> *node, TraversalPlan tp) const;
    bool isLeaf(BSTNode<T> *node);
    int height();
    int height(BSTNode<T> *node);
    bool contains(BSTNode<T> *node, const T &data) const;
    void insert(BSTNode<T> *&node, const T &data);
    void remove(BSTNode<T> *&node, const T &data);
    void removeAllNodes(BSTNode<T> *&node);
    BSTNode<T> *search(BSTNode<T> *node, const T &data) const;
    BSTNode<T> *minNode(BSTNode<T> *node) const;
    BSTNode<T> *minNode() const;
    BSTNode<T> *maxNode(BSTNode<T> *node) const;
    BSTNode<T> *maxNode() const;
    BSTNode<T> *getParent(BSTNode<T> *node) const;
    

private: // DO NOT CHANGE THIS PART.
    BSTNode<T> *root;
};

#endif //BST_H

// UDF

template<class T>
bool BST<T>::isLeaf(BSTNode<T> *node) {
    return (node->left == NULL and node->right == NULL) ? true : false;
}

template<class T>
int BST<T>::height() {
    return height(root);
}

template<class T>
int BST<T>::height(BSTNode<T> *node) {
    if (node == NULL)
        return -1;
    if (isLeaf(node))
        return 0;
    int l_height = height(node->left);
    int r_height = height(node->right);
    if (l_height < r_height)
        return r_height + 1;
    return l_height + 1;
}

template<class T>
bool BST<T>::contains(BSTNode<T> *node, const T &data) const {
    if (node == NULL)
        return false;
    if (node->data == data)
        return true;
    else 
        return contains(node->left, data) or contains(node->right, data);
}

template<class T>
void BST<T>::insert(BSTNode<T> *&node, const T &data) {
    if (contains(node, data))
        return;
    if (node == NULL) {
        node = new BSTNode<T>(data, NULL, NULL);
    }
    else if (data < node->data)
        insert(node->left, data);
    else
        insert(node->right, data);
}

template<class T>
void BST<T>::remove(BSTNode<T> *&node, const T &data) {
    if (!node or !contains(node, data))
        return;
    if (data < node->data)
        remove(node->left, data);
    else if (data > node->data)
        remove(node->right, data);
    else if (node->left && node->right) {
        node->data = minNode(node->right)->data;
        remove(node->right, node->data);
    }
    else {
        BSTNode<T> *oldNode = node;
        node = (node->left) ? node->left : node->right;
        delete oldNode;
    }
}

template<class T>
void BST<T>::removeAllNodes(BSTNode<T> *&node) {
    if (node == NULL) 
        return;
    removeAllNodes(node->left);
    removeAllNodes(node->right);
    if (node == root) {
        delete node;
        root = NULL;
    }
    else
        delete node;
}

template<class T>
BSTNode<T> *BST<T>::search(BSTNode<T> *node, const T &data) const {
    if (node == NULL or !contains(node, data))
        return NULL;
    if (node->data == data)
        return node;
    else if (data < node->data)
        return search(node->left, data);
    else
        return search(node->right, data);
}

template<class T>
BSTNode<T> *BST<T>::minNode(BSTNode<T> *node) const {
    if (!node)
        return NULL;
    BSTNode<T> *current = node;
    while (current->left != NULL) {
        current = current->left;
    }
    return current;
}

template<class T>
BSTNode<T> *BST<T>::minNode() const {
    return minNode(root);
}

template<class T>
BSTNode<T> *BST<T>::maxNode(BSTNode<T> *node) const {
    if (!node)
        return NULL;
    BSTNode<T> *current = node;
    while (current->right != NULL) {
        current = current->right;
    }
    return current;
}

template<class T>
BSTNode<T> *BST<T>::maxNode() const {
    return maxNode(root);
}

template<class T>
BSTNode<T> *BST<T>::getParent(BSTNode<T> *node) const {
    if (node == NULL or node == root)
        return NULL;
    BSTNode<T> *parent = root;
    while (true) {
        if (parent->left == node or parent->right == node) 
            break;
        if (node->data < parent->data)
            parent = parent->left;
        else
            parent = parent->right;
    }
    return parent;
}

// UDF END

template<class T>
BST<T>::BST() {
    root = NULL;
}

template<class T>
BST<T>::BST(const BST<T> &obj) {
    *this = obj;
}

template<class T>
BST<T>::~BST() {
    removeAllNodes();
    delete root;
}

template<class T>
BSTNode<T> *BST<T>::getRoot() const {
    return root;
}

template<class T>
bool BST<T>::isEmpty() const {
    return (root == NULL) ? true : false;
}

template<class T>
bool BST<T>::contains(BSTNode<T> *node) const {
    return contains(root, node->data);
}

template<class T>
void BST<T>::insert(const T &data) {
    insert(root, data);
}

template<class T>
void BST<T>::remove(const T &data) {
    remove(root, data);
}

template<class T>
void BST<T>::removeAllNodes() {
    removeAllNodes(root);
}

template<class T>
BSTNode<T> *BST<T>::search(const T &data) const {
    return search(root, data);
}

template<class T>
BSTNode<T> *BST<T>::getSuccessor(BSTNode<T> *node, TraversalPlan tp) const {
    if (isEmpty())
        return NULL;

    BSTNode<T> *parent = getParent(node);
    bool is_left_child;
    if (parent != NULL) 
        is_left_child = (parent->left == node) ? true : false;
    if (tp == inorder) {
        if (!node)
            return minNode();
        else if (node->right)
            return minNode(node->right);
        else {
            while (parent) {
                if (parent->data > node->data)
                    return parent;
                parent = getParent(parent);
            }
            return parent;
        }
    } else if (tp == preorder) {
        /*
        1. If left child of given node exists, then the left child is preorder 
        successor.
        2. If left child does not exist, however right child exists, then 
        the preorder successor is the right child.
        3. If left child and right child does not exist and given node is left 
        child of its parent, then its sibling is its preorder successor.
        4. If none of above conditions are satisfied (left child does not exist 
        and given node is not left child of its parent), then we move up using 
        parent pointers until one of the following happens. 
            a. We reach root. In this case, preorder successor does not exist.
            b. Current node (one of the ancestors of given node) is left child 
            of its parent, in this case preorder successor is sibling of current 
            node.
        */
        if (!node) 
            return root;
        else if (node->left) 
            return node->left;
        else if (node->right) 
            return node->right;
        else if (is_left_child && parent->right) 
            return parent->right;
        else {
            BSTNode<T> *ancestor = parent;
            bool ancestor_is_left_child;
            while (getParent(ancestor)) {
                BSTNode<T> *ancestor_parent = getParent(ancestor);
                ancestor_is_left_child = (ancestor_parent->left == ancestor) ? true : false;
                //std::cout << "ancestor: " << ancestor->data << " ancestor_parent: " << ancestor_parent->data << " ancestor_is_left_child: " << ancestor_is_left_child <<std::endl;
                if (ancestor_is_left_child)
                    return ancestor_parent->right;
                ancestor = ancestor_parent; 
            }
        }
    } else if (tp == postorder) {
        /*
        1. If given node is root then postorder successor is NULL, since root is 
        the last node print in a postorder traversal
        2. If given node is right child of parent or right child of parent is 
        NULL, then parent is postorder successor.
        3. If given node is left child of parent and right child of parent is 
        not NULL, then postorder successor is the leftmost node of parent’s right subtree.
        */
        if (!node) {
            if (!root->left->left && root->left->right)
                return minNode(root->left->right);
            return minNode();
        }
        else if (node == root)
            return NULL;
        else if (!parent->right || parent->right == node)
            return parent;
        else
            return maxNode(minNode(parent->right));
    }
    else
        return NULL;
}

template<class T>
void BST<T>::print(TraversalPlan tp) const {

    if (tp == inorder) {
        // check if the tree is empty?
        if (isEmpty()) {
            // the tree is empty.
            std::cout << "BST_inorder{}" << std::endl;
            return;
        }

        // the tree is not empty.

        // recursively output the tree.
        std::cout << "BST_inorder{" << std::endl;
        print(root, inorder);
        std::cout << std::endl << "}" << std::endl;
    } else if (tp == preorder) {
        // check if the tree is empty?
        if (isEmpty()) {
            // the tree is empty.
            std::cout << "BST_preorder{}" << std::endl;
            return;
        }

        // the tree is not empty.

        // recursively output the tree.
        std::cout << "BST_preorder{" << std::endl;
        print(root, preorder);
        std::cout << std::endl << "}" << std::endl;
    } else if (tp == postorder) {
        // check if the tree is empty?
        if (isEmpty()) {
            // the tree is empty.
            std::cout << "BST_postorder{}" << std::endl;
            return;
        }

        // the tree is not empty.

        // recursively output the tree.
        std::cout << "BST_postorder{" << std::endl;
        print(root, postorder);
        std::cout << std::endl << "}" << std::endl;
    }
}

template<class T>
BST<T> &BST<T>::operator=(const BST<T> &rhs) {
    root = NULL;
    removeAllNodes();
    if (!rhs.isEmpty() or this != &rhs) {
        BSTNode<T> *rhs_current = rhs.getSuccessor(NULL, preorder);
        while (rhs_current != NULL) {
            insert(rhs_current->data);
            rhs_current = rhs.getSuccessor(rhs_current, preorder);
        }
    }
    return *this;
}

template<class T>
void BST<T>::print(BSTNode<T> *node, TraversalPlan tp) const {

    // check if the node is NULL?
    if (node == NULL)
        return;

    if (tp == inorder) {
        // first, output left subtree and comma (if needed).
        print(node->left, inorder);
        if (node->left) {
            std::cout << "," << std::endl;
        }

        // then, output the node.
        std::cout << "\t" << node->data;

        // finally, output comma (if needed) and the right subtree.
        if (node->right) {
            std::cout << "," << std::endl;
        }
        print(node->right, inorder);
    } else if (tp == preorder) {
        // first, output the node.
        std::cout << "\t" << node->data;

        // then, output left subtree and comma (if needed).
        if (node->left) {
            std::cout << "," << std::endl;
        }
        print(node->left, preorder);
        

        // finally, output comma (if needed) and the right subtree.
        if (node->right) {
            std::cout << "," << std::endl;
        }
        print(node->right, preorder);
    } else if (tp == postorder) {
        // then, output left subtree and comma (if needed).
        print(node->left, postorder);
        print(node->right, postorder);

        // first, output the node.
        std::cout << "\t" << node->data;
        if (node != root)
            std::cout << "," << std::endl;
    }
}
