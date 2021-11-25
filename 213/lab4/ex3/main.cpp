#include "Deque.h"

int main() {
   Deque dq;
    
    for (int i=1; i<11; i++) {
       dq.inject(i);
    }
    cout << "get rear element (10): " << dq.getBack() << endl;
    
    dq.eject();
    cout << "After delete rear element new rear become (9): " << dq.getBack() << endl;
    
    dq.eject();
    cout << "After delete rear element new rear become (8): " << dq.getBack() << endl;
    
    
    cout << "Insert element at rear end: 12" << endl;
    dq.inject(12);
    
    cout << "insert element at rear end: 11" << endl;
    dq.inject(11);
    
    cout << "get rear element (11): " << dq.getBack() << endl;
    
    dq.eject();
    cout << "After delete rear element new rear become (12): " << dq.getBack() << endl;
    
    cout << "inserting element at front end: 15" << endl;
    dq.push(15);
    
    cout << "get front element (15): " <<  dq.getFront() << endl;
    
    dq.pop();
    
    cout << "After delete front element new front become (1): " << dq.getFront() << endl;
    
    return 0;
}