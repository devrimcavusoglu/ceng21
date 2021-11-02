#include "pair.hpp"

/*              Default Constructor for Pair Class    */
Pair::Pair(int p1, int p2)
{
    pa = new int;
    pb = new int;
    *pa = p1;
    *pb = p2;
}


/*              Copy Constructor for Pair Class    */
Pair::Pair(const Pair &p)
{
    pa = new int;
    pb = new int;
    *pa = *p.pa;
    *pb = *p.pb;
}

/*                    Destructor for Pair Class  */
Pair::~Pair()
{
    delete pa;
    delete pb;
}

