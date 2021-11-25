#ifndef STACK_EXCEPTION_H
#define STACK_EXCEPTION_H

#include <string>

using namespace std;

class StackException {

public:
    
    StackException(string err) {
        
        error = err;
    }
    
    string error;
};

#endif //STACK_EXCEPTION_H
