//This file is entirely for your test purposes. 
//This will not be evaluated, you can change it and experiment with it as you want.
#include <iostream>
#include <fstream>
#include <random>
#include <ctime>
#include "the0.h"

using namespace std;

void randomFill(int* arr, int size, int minval, int interval)
{
	for (int i=0; i <size; i++)
	{
		arr[i] = minval + (random() % interval);
	}
}

void print_to_file(int* arr, int size)
{
	ofstream ofile;
	ofile.open("sorted.txt");
	for(int i=0;i<size; i++) 
		ofile<<arr[i]<<endl;
}

void printArray(int *arr, int size){
	for (int i{0}; i<size; i++){
		cout << arr[i] << " ";
	}
	cout << "\n";
}

void simpleTest(int *arr, int size, int expected_comparison, int expected_swap){
	long comparison=0;
	long swap=0;
	cout << "Input array:\n";
	printArray(arr, size);
	insertionSort(arr, comparison, swap, size);
	cout << "Sorted array:\n";
	printArray(arr, size);
	cout << "Actual Comparisons: " << comparison << " & Swaps: " << swap << "\n";
	cout << "Expected Comparisons: " << expected_comparison << " & Swaps:" << expected_swap << "\n";
	cout << "-----------------------\n";
}


void testCase0(){
	int expected_comparison{5};
	int expected_swap{2};
	int size{4};
	int a[size] = {9, -2, 3, 15};
	int *arr;
	arr = a;
	simpleTest(arr, size, expected_comparison, expected_swap);
}

void testCase1(){
	int expected_comparison{9};
	int expected_swap{4};
	int size{6};
	int a[size] = {0, -5, -5, -5, 4, 1} ;
	int *arr;
	arr = a;
	simpleTest(arr, size, expected_comparison, expected_swap);
}

void testCase2(){
	int expected_comparison{6};
	int expected_swap{0};
	int size{7};
	int a[size] = {1, 5, 8, 10, 11, 17, 22} ;
	int *arr;
	arr = a;
	simpleTest(arr, size, expected_comparison, expected_swap);
}

void test()
{

	// Test trivial cases
	testCase0();
	testCase1();
	testCase2();
	
	clock_t begin, end;
	double duration;
	
	//data generation and initialization- you may test with your own data
	long comparison=0;
	long swap=0;
	int size=25000;
	int minval=0;
	int interval=size*10;
	int *arr = new int [size];

	randomFill(arr, size, minval, interval);
	//data generation end
	
	if ((begin = clock() ) ==-1) 
		cerr << "clock error" << endl;
	
	//Function call for the solution
	insertionSort(arr, comparison, swap, size);
	//Function end
	
	if ((end = clock() ) ==-1) 
		cerr << "clock error" << endl;
	
	//Calculate duration and print output

	duration = ((double) end - begin) / CLOCKS_PER_SEC;
	cout << "Duration: " << duration << " seconds." <<endl;
	cout << "Array size: " << size << "\n";
	cout<<"Number of Comparisons: " << comparison <<endl;
	cout<<"Number of Swaps: " << swap <<endl;
	print_to_file(arr,size);
	//Calculation and output end
	
}

int main()
{
	srandom(time(0));
	test();
	return 0;
}
	
	