#include <iostream>
#include <random>
#include <ctime>
#include "the5.h"

int getRandomInt(int max){
        int r = rand() % max + 1;
        return r;
}

void createAndWritePartitions(int numberOfPartitions, bool** partitions, int W, int L){

	std::cout << "Field: " << W << " x " << L << std::endl;	

	for(int p = 0; p < numberOfPartitions; p++){
		int w = getRandomInt(W);
		int l = getRandomInt(L);
		while (partitions[w][l]){		// make sure that no two partitions are same
			w = getRandomInt(W);
			l = getRandomInt(L);
		}
		partitions[w][l] = true;
		std::cout << "Partition " << (p+1) << ": " << w << " x " << l << std::endl;
	}
}

void testRecursive(int W, int L, bool** partitions){
	std::cout << "\n***Testing Recursive Method***\n"; 
	clock_t begin, end;
	double duration;
	int numberOfCalls = 0;

	if ((begin = clock() ) ==-1)
		std::cerr << "clock error" << std::endl;

	int wastage = recursiveMethod(W, L, partitions, &numberOfCalls);

	if ((end = clock() ) ==-1)
		std::cerr << "clock error" << std::endl;

	duration = ((double) end - begin) / CLOCKS_PER_SEC;
	std::cout << "Duration: " << duration << " seconds." << std::endl;
	std::cout << "Wasted Area: " << wastage << std::endl;
	std::cout << "Number of Calls: " << numberOfCalls << std::endl;
	std::cout << "******************************\n";
}

void testMemoization(int W, int L, bool** partitions){
	std::cout << "\n***Testing Memoization Method***\n";
	clock_t begin, end;
	double duration;
	int numberOfCalls = 0;

	if ((begin = clock() ) ==-1)
		std::cerr << "clock error" << std::endl;
	
	int wastage = memoizationMethod(W, L, partitions, &numberOfCalls);

	if ((end = clock() ) ==-1)
		std::cerr << "clock error" << std::endl;

	duration = ((double) end - begin) / CLOCKS_PER_SEC;
	std::cout << "Duration: " << duration << " seconds." << std::endl;
	std::cout << "Wasted Area: " << wastage << std::endl;
	std::cout << "Number of Calls: " << numberOfCalls << std::endl;
	std::cout << "******************************\n";
}

void testBottomUp(int W, int L, bool** partitions){
	std::cout << "\n***Testing Bottom-up Method***\n";
	clock_t begin, end;
	double duration;
	int numberOfIterations = 0;

	if ((begin = clock() ) ==-1)
		std::cerr << "clock error" << std::endl;
	
	int wastage = bottomUpMethod(W, L, partitions, &numberOfIterations);

	if ((end = clock() ) ==-1)
		std::cerr << "clock error" << std::endl;

	duration = ((double) end - begin) / CLOCKS_PER_SEC;
	std::cout << "Duration: " << duration << " seconds." << std::endl;
	std::cout << "Wasted Area: " << wastage << std::endl;
	std::cout << "Number of Iterations: " << numberOfIterations << std::endl;
	std::cout << "******************************\n";
}

void test(){

	// Field
	int W = 5;
	int L = 3;

	// Initialization for partitions
	bool** partitions = new bool*[W+1];
	for(int i = 0; i < W+1; i++){
		partitions[i] = new bool[L+1];
		for (int j = 0; j < L+1; j++){
			partitions[i][j] = false;
		}
	}

	int numberOfPartitions = 2;
	createAndWritePartitions(numberOfPartitions, partitions, W, L);

	testRecursive(W, L, partitions);
	testMemoization(W, L, partitions);
	testBottomUp(W, L, partitions);
}

int main() {
    srand(time(0));
    test();
    return 0;
}
