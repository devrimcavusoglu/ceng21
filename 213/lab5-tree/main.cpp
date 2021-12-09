#include <iostream>

#include "IntTree.h"

using namespace std;

int main() {
    
    cout << "Crating a random full tree of height 2." << endl;
    
    //int height = 2;
    int size = 10;
    int arr[] = {10,20,30,40,50,60,70,80,90,100}; 
    IntTree myFullTree(arr, size);
    
    cout << "Inorder traversal: " << endl;
    
    myFullTree.print();
    
    cout << "Full tree sideways: " << endl;
    
    myFullTree.printSideways();

    cout << "Height of the full binary tree is " << myFullTree.height() << endl;

    int value = 80;
    cout << "Does the tree contains the value " << value << "? " << (myFullTree.contains(value) ? "yes" : "no") << endl;

    // You can write code to test other functions ...

    cout << "Testing print leaves (in reverse)\n";
    myFullTree.printLeaves();

    cout << "Testing numberNodes\n";
    myFullTree.numberNodes();
    myFullTree.printSideways();
    cout << "Testing printLevel\n";
    myFullTree.printLevel(3);
    cout << "Testing removeLeaves\n";
    myFullTree.removeLeaves();
    myFullTree.printSideways();


    return 0;
}
