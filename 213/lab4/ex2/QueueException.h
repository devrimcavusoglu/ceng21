#ifndef _QUEUE_EXCEPTION
#define _QUEUE_EXCEPTION

#include <string>
using namespace std;

class QueueException {
public:
    QueueException(string err){
        error = err;
    }
    string error;

};
#endif // _QUEUE_EXCEPTION

