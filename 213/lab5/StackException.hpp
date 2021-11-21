#ifndef _STACK_EXCEPTION
#define _STACK_EXCEPTION

#include <string>

using namespace std;

class StackException {
public:
    StackException(string err) {

        error = err;
    }

    string error;
};

#endif //_STACK_EXCEPTION
