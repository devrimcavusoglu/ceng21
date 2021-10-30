#ifndef __pair_hpp__
#define __pair_hpp__

#include <iostream>

class Pair
{
    public:
        int *pa,*pb;
        Pair(int p1, int p2);
        Pair(const Pair &p);
        ~Pair();
};

#endif // __pair_hpp__
