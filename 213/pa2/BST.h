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
        node = new BSTNode<T>();
        node->data = data;
    }
    else if (data < node->data)
        insert(node->left, data);
    else
        insert(node->right, data);
}

template<class T>
void BST<T>::remove(BSTNode<T> *&node, const T &data) {
    if (node == NULL or !contains(node, data))
        return;
    else if (node->data == data) {
        BSTNode<T> *parent = getParent(node);
        bool is_left_child;
        if (parent != NULL) 
            is_left_child = (parent->left == node) ? true : false;

        if (isLeaf(node)) {
            if (node == root) {
                root = NULL;
                return;
            }
            else if (is_left_child)
                parent->left = NULL;
            else
                parent->right = NULL;
            delete node;
        }
        else if (node->left != NULL and node->right != NULL) {
            // Node has two children
            BSTNode<T> *successor = minNode(node->right);
            T val = successor->data;
            remove(successor, val);
            node->data = val;
        }
        else {
            // Node has one child
            BSTNode<T> *child = (node->left != NULL) ? node->left : node->right;
            
            if (parent == NULL) {
                root = child;
                delete node;
                return;
            }
            else if (is_left_child)
                parent->left = child;
            else
                parent->right = child;
            delete node;
        }
    }
    else {
        remove(node->left, data);
        remove(node->right, data);
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
    while (current->left != NULL)
    {
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
    while (current->right != NULL)
    {
        current = current->right;
    }
    return current;
}

template<class T>
BSTNode<T> *BST<T>::maxNode() const {
    return minNode(root);
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
    if (tp == inorder) {
        /*
        if right node exists
            return min of root->right
        else if node is max of root->right
            return NULL
        else
            return parent
        */
        if (node == NULL)
            return minNode();
        else if (node->right != NULL)
            return minNode(node->right);
        else if (node == maxNode(root->right))
            return NULL;
        else if (node == maxNode(root->left))
            return root;
        else {
            return parent;
        }
    } else if (tp == preorder) {
        /*
        if left node exists, 
            return left node.
        else if right node exists
            return right node.
        else if node is max of root->left
            return root->right
        else if node is min of root->right
            return NULL
        else
            return parent's right node.
        */
        std::cout << "1\n";
        if (node == NULL)
            return root;
        else if (node->left != NULL)
            return node->left;
        else if (node->right != NULL)
            return node->right;
        else if (parent && parent->right)
            return parent->right;
        else if (node == maxNode(root->left))
            return root->right;
        else if (node == maxNode())
            return NULL;
        else
            return NULL;
    } else if (tp == postorder) {
        /*
        if node is root node
            return NULL (stopping cond)
        else if node is root->right
            return root
        else if node->parent->right exists
            return min(node->parent->right)
        else
            return parent
        */
        if (node == NULL)
            return minNode();
        if (node == root)
            return NULL;
        else if (parent->right != NULL and parent->right != node)
            return minNode(parent->right);
        else {
            return parent;
        }
        return node->right;
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
        BSTNode<T> *rhs_current = rhs.getRoot();
        while (rhs_current != NULL) {
            std::cout << rhs_current->data << " ###############\n";
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
