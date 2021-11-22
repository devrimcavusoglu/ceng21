#include <iostream>

#include "Functions.hpp"

using namespace std;


void print_stack(Stack<int> s){
    while (!s.isEmpty()){
        cout << s.pop() << " ";
    }
    cout << "\n";
}

void mystery(Stack<int> s){
    Stack<int> s1;
    while (!s.isEmpty()){
        int n = s.pop();
        s1.push(n);
        s1.push(n);
    }
    while(!s1.isEmpty()){
        s.push(s1.pop());
    }
    while(!s.isEmpty()){
        cout << s.pop() << "#";
    }
}

int main() {
    Stack<int> s;
    int n1, n2, n3;
    s.push(17);
    s.push(143);
    s.push(42);
    print_stack(s);
    n1 = s.pop();
    n2 = s.peek();
    s.push(n1);
    n3 = s.pop();
    n1 = s.peek();

    print_stack(s);
    cout << "n1 & n2 & n3: " << n1 << " " << n2 << " " << n3 << "\n";
}