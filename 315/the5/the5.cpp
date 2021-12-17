#include "the5.h"
// do not add extra libraries here

/*
W: the width of the field
L: the length of the field
partitions: 2D Boolean array for partitions, if a partition of w x l exists then partitions[x][y] is true.
numberOfCalls/numberOfIterations: method specific control parameter
*/

int recursiveMethod(int W, int L, bool** partitions, int* numberOfCalls){
	*numberOfCalls += 1;
	int wastedArea = 0;
	if (!partitions[W][L]) {
		wastedArea = W*L;
		int wastedArea_w = W*L;
		int wastedArea_l = W*L;
		for (int m=1; m<=W/2; m++) 
			wastedArea_w = recursiveMethod(W-m, L, partitions, numberOfCalls) + recursiveMethod(m, L, partitions, numberOfCalls);
		for (int n=1; n<=L/2; n++)
			wastedArea_l = recursiveMethod(W, L-n, partitions, numberOfCalls) + recursiveMethod(W, n, partitions, numberOfCalls);
		wastedArea = std::min(wastedArea, std::min(wastedArea_w, wastedArea_l));
	}
	return wastedArea;
}

int internalMemoization(int W, int L, bool **partitions, int *numberOfCalls, int **cache) {
	return 0;
}

int memoizationMethod(int W, int L, bool** partitions, int* numberOfCalls) {
	int** cache = new int*[W+1];
	for(int i = 0; i < W+1; i++){
		cache[i] = new int[L+1];
		std::fill_n(cache[i], L+1, 0);
	}
	return internalMemoization(W, L, partitions, numberOfCalls, cache);
}

int bottomUpMethod(int W, int L, bool** partitions, int* numberOfIterations){
	int** cache = new int*[W+1];
	for(int i = 0; i < W+1; i++){
		cache[i] = new int[L+1];
		for (int j = 0; j < L+1; j++){
			cache[i][j] = (partitions[i][j]) ? 0:i*j;
		}
	}

	int wastedArea_prev, wastedArea_prev_diag;
	for (int m = 1; m <= W; m++) {
		for (int n = 1; n <= L; n++) {
			*numberOfIterations += 1;
			if (partitions[m][n]) 
				continue;
			wastedArea_prev = std::min(cache[m-1][n], cache[m][n-1]);
			cache[m][n] = std::min(cache[m-1][n-1], std::min(wastedArea_prev, wastedArea_prev_diag));
		}
	}

	return cache[W][L];
}
