#include <iostream>
#include "myvector.h"

int main()
{
    int init_val = 3; 
    int size = 4;
    MyVector<int> myvec(init_val, size);

    std::cout << myvec;


    return 0;
}
