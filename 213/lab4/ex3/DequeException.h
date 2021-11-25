#ifndef _EXCEPTION
#define _EXCEPTION
#include <string>
using namespace std;

class DequeException {
public:
    DequeException(string err){
	       error = err;
    }
    string error;

};
#endif // _EXCEPTION

