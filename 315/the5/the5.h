#ifndef _THE_5_H_
#define _THE_5_H_

#include <iostream>
#include <climits>
#include <cmath>
#include <cstdlib>

int recursiveMethod(int W, int L, bool** partitions, int* numberOfCalls);
int memoizationMethod(int W, int L, bool** partitions, int* numberOfCalls);
int bottomUpMethod(int W, int L, bool** partitions, int* numberOfIterations);

#endif