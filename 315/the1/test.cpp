//This file is entirely for your test purposes. 
//This will not be evaluated, you can change it and experiment with it as you want.
#include <iostream>
#include <fstream>
#include <random>
#include <ctime>
#include "the1.h"

//the1.h only contains declaration of the function sillySort  and crossMergeSort which are:
//int sillySort(int* arr, long &comparison, long & swap, int size) ;
//int crossMergeSort(int *arr, long &comparison, int size);

using namespace std;

void randomFill(int*& arr, int size, int minval, int interval)
{
	arr = new int [size];
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

void read_from_file(int*& arr, int& size)
{

	char addr[]= "input01.txt";
	ifstream infile (addr);
	
	if (!infile.is_open())
	{
		cout << "File \'"<< addr 
			<< "\' can not be opened. Make sure that this file exists." <<endl;
		return;
	}
	infile >> size;
	arr = new int [size];
	
	for (int i=0; i<size;i++) {
		
		infile >> arr[i];
	}
	
}
	

void test()
{
	
	clock_t begin, end;
	double duration;
	
	//data generation and initialization- you may test with your own data
	long comparison=0;
	long swap=0;
	int num_of_calls;
	int size= 1 << 11;	 // maximum 2^11 for sillySort and 2^16 ( 1 << 16) for crossMergeSort 
	int minval=0;
	int interval= size*2; // you can try to minimize interval for data generation to make your code test more equality conditions
	int *arr;
	
	//Randomly generate initial array:
	randomFill(arr, size, minval, interval);
	
	//Read the test inputs. input01.txt through input04.txt exists.
	//read_from_file(arr, size);
	
	//data generation or read end
	
	if ((begin = clock() ) ==-1) 
		cerr << "clock error" << endl;
	
	//Function call for the solution
	
	//num_of_calls=sillySort(arr, comparison, swap, size) ;
	
	num_of_calls=crossMergeSort(arr, comparison, size);
	
	//Function end
	
	if ((end = clock() ) ==-1) 
		cerr << "clock error" << endl;
	
	//Calculate duration and print output
	
	duration = ((double) end - begin) / CLOCKS_PER_SEC;
	cout << "Duration: " << duration << " seconds." <<endl;
	cout<<"Number of Comparisons: " << comparison <<endl;
	cout<<"Number of sillySort or crossMergeSort calls: " << num_of_calls <<endl;
	cout<<"Number of Swaps(0 for crossMergeSort): " << swap <<endl;
	print_to_file(arr,size);
	//Calculation and output end
	
}

int main()
{
	srandom(time(0));
	test();
	return 0;
}
	
	