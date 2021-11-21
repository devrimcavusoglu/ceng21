#include <iostream>

#include "Functions.hpp"

using namespace std;

int main() {
    /************/
    /* isSorted */
    /************/
    
    cout << "Creating an empty stack named s1." << std::endl;
    Stack<int> s1;
    
    cout << "Creating a stack named s2 with values (top to bottom): 9" << std::endl;
    Stack<int> s2;
    s2.push(9);
    
    cout << "Creating a stack named s3 with values (top to bottom): 3, 4, 5, 5" << std::endl;
    Stack<int> s3;
    s3.push(5);
    s3.push(5);
    s3.push(4);
    s3.push(3);
    
    cout << "Creating a stack named s4 with values (top to bottom): 6, 7, 7, 5, 8" << std::endl;
    Stack<int> s4;
    s4.push(8);
    s4.push(5);
    s4.push(7);
    s4.push(7);
    s4.push(6);
    
    cout << "Is s1 sorted? " << (isSorted(s1) ? "yes" : "no") << endl;
    cout << "Is s2 sorted? " << (isSorted(s2) ? "yes" : "no") << endl;
    cout << "Is s3 sorted? " << (isSorted(s3) ? "yes" : "no") << endl;
    cout << "Is s4 sorted? " << (isSorted(s4) ? "yes" : "no") << endl;
    
    cout << "\"isSorted\" function must restore the parameter stack to its original state before returning." << std::endl;

    cout << "Stack s1 (after isSorted):" << endl;
    while (!s1.isEmpty()) {
        cout << s1.pop() << endl;
    }
    cout << "Stack s2 (after isSorted):" << endl;
    while (!s2.isEmpty()) {
        cout << s2.pop() << endl;
    }
    cout << "Stack s3 (after isSorted):" << endl;
    while (!s3.isEmpty()) {
        cout << s3.pop() << endl;
    }
    cout << "Stack s4 (after isSorted):" << endl;
    while (!s4.isEmpty()) {
        cout << s4.pop() << endl;
    }

    /**********/
    /* equals */
    /**********/
    
    cout << "Testing equals" << endl;

    cout << "Creating a stack named s5 with values (top to bottom): 8, 2, 7" << std::endl;
    Stack<int> s5;
    s5.push(7);
    s5.push(2);
    s5.push(8);

    cout << "Creating a stack named s6 with values (top to bottom): 8, 2, 7" << std::endl;
    Stack<int> s6;
    s6.push(7);
    s6.push(2);
    s6.push(8);

    cout << "Creating a stack named s7 with values (top to bottom): 2, 7" << std::endl;
    Stack<int> s7;
    s7.push(7);
    s7.push(2);

    bool equals_s5_s6 = equals(s5, s6);
    bool equals_s5_s7 = equals(s5, s7);

    cout << "Is s5 equal to s6 : " << (equals_s5_s6 ? "yes" : "no") << endl;
    cout << "Is s5 equal to s7 : " << (equals_s5_s7 ? "yes" : "no") << endl;

    std::cout << "Your method must restore the two stacks to their original state before returning." << std::endl;
    
    cout << "Stack s5 (after equals):" << endl;
    while (!s5.isEmpty()) {
        cout << s5.pop() << endl;
    }
    cout << "Stack s6 (after equals):" << endl;
    while (!s6.isEmpty()) {
        cout << s6.pop() << endl;
    }
    cout << "Stack s7 (after equals):" << endl;
    while (!s7.isEmpty()) {
        cout << s7.pop() << endl;
    }

    return 0;
}