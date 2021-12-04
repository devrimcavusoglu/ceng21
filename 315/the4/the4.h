#ifndef THE4_H
#define THE4_H

#include <iostream>

int recursive_sln(int i, int*& arr, int &number_of_calls);
int memoization_sln(int i, int*& arr, int*& mem);
int dp_sln(int size, int*& arr, int*& mem);

#endif //THE4_H