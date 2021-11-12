//This file is entirely for your test purposes. 
//This will not be evaluated, you can change it and experiment with it as you want.
#include <iostream>
#include <fstream>
#include <random>
#include <ctime>
#include "the2.h"

//the2.h only contains declaration of the function quickSort  and quickSort3 which are:
//void quickSort(unsigned short* arr, long &swap, double & avg_dist, double & max_dist, bool hoare, int size);
//void quickSort3(unsigned short *arr, long &swap, long &comparison, int size);

using namespace std;

void randomFill(unsigned short*& arr, int size, unsigned short minval, unsigned short interval)
{
	arr = new unsigned short [size];
	for (int i=0; i <size; i++)
	{
		arr[i] = minval + (random() % interval);
	}
}

template <class T>
void print_array(T *arr, int size){
	for(int i{}; i<size; i++){
		std::cout << arr[i] << " ";
	}
	std::cout << "\n";
}

void print_to_file(unsigned short* arr, int size)
{
	ofstream ofile;
	ofile.open("sorted.txt");
	ofile<<size<<endl;
	for(int i=0;i<size; i++) 
		ofile<<arr[i]<<endl;
}

void read_from_file(unsigned short*& arr, int& size)
{

	char addr[]= "in01.txt"; //You can test from in01.txt to in04.txt
	ifstream infile (addr);
	
	if (!infile.is_open())
	{
		cout << "File \'"<< addr 
			<< "\' can not be opened. Make sure that this file exists." <<endl;
		return;
	}
	infile >> size;
	arr = new unsigned short [size];
	
	for (int i=0; i<size;i++) {
		
		infile >> arr[i];
	}
	
}
	

void test()
{
	
	
	clock_t begin, end;
	double duration;
	
	char f_select='c'; // c tests for quicksort with classical partitioning, h for quicksort with hoare partitioning, 3 for 3-way quicksort
	//data generation and initialization- you may test with your own data
	long comparison=0;
	long swap=0;
	double avg_dist=0;
	double max_dist=0;
	bool hoare, q3;
	//bool rand_fill=true;
	
	switch(f_select) {
		
		case '3':
		q3=true;
		break;
		case 'h':
		q3=false;
		hoare=true;
		break;
		case 'c':
		q3=false;
		hoare=false;
		break;
		default:
		cout<<"Invalid argument for function selection."<<endl;
		return;
	}
	
	
	
	int size= 1 << 1;	                                    // for maximum see the "boundaries for test cases" part
	//unsigned short minval=0;
	//unsigned short interval= (unsigned short)((1<<5)-1);   // unsigned short 65535 in maximum , you can try to minimize interval for data generation to make your code test more equality conditions
	//unsigned short *arr;
	unsigned short *arr;
	//unsigned short temp[] = {2, 1, 14, 6, 3, 0, 99, 3};
	unsigned short temp[] = {0, 3};
	arr = temp;	
	/*
	
	BOUNDARIES FOR TEST CASES. THESE ARE THE MOST DIFFICULT INPUTS TO BE TESTED
	
	***QUICKSORT WITH CLASSICAL PARTITIONING *** NOTE THAT IT PERFORMS BETTER WHEN THERE ARE LESS EQUALITY CONDITIONS IN OUR CASE LARGER INTERVAL FOR NUMBERS TO BE GENERATED
	
	size <= 2^16 when interval == 2^16-1
	size <= 2^20 when interval >= 2^13-1
	size <= 2^19 when interval >= 2^11-1
	size <= 2^18 when interval >= 2^9 -1
	size <= 2^17 when interval >= 2^7 -1
	size <= 2^16 when interval >= 2^5 -1
	
	********************************
	
	***QUICKSORT WITH HOARE PARTITIONING *** INTERVAL HAS NO EFFECT
	
	size <= 2^22
	
	********************************
	
	***3-WAY QUICKSORT *** IT PERFORMS BETTER WHEN THERE ARE MORE EQUALITY CONDITIONS IN OUR CASE SMALLER INTERVAL FOR NUMBERS TO BE GENERATED
	
	size <=2^25 when interval <= 2^2-1
	size <=2^24 when interval <= 2^5-1
	size <=2^23 when interval <= 2^10-1
	size <=2^22 when interval <= 2^16-1
	
	********************************

	
	*/
	
	
	/*if(rand_fill)
	    randomFill(arr, size, minval, interval);    //Randomly generate initial array
	else
	    read_from_file(arr, size);                  //Read the test inputs. in01.txt through in04.txt exists. Due to the limitation of the system larger inputs are not stored but generated on evaluation.
	*/

	print_array(arr, size);
	//data generation or read end
	if ((begin = clock() ) ==-1) 
		cerr << "clock error" << endl;
	
	//Function call for the solution
	
	if(q3)
	    quickSort3(arr, swap, comparison, size);
	else
	    quickSort(arr, swap, avg_dist, max_dist, hoare, size);
	
	print_array(arr, size);
	//Function end
	
	if ((end = clock() ) ==-1) 
		cerr << "clock error" << endl;
	
	//Calculate duration and print output
	cout<<"Number of Swaps: " << swap <<endl;
	
	duration = ((double) end - begin) / CLOCKS_PER_SEC;
	cout << "Duration: " << duration << " seconds." <<endl;
    if(q3)
        cout<<"Number of Comparisons: " << comparison <<endl;
    else
    {
        cout<<"Average Distance of Swaps(0 for quickSort3): " << avg_dist <<endl;
        cout<<"Maximum Distance of Swaps(0 for quickSort3): " << max_dist <<endl;
    }
	
	cout <<"Size of the array:"<< size << endl;
	
	//print_to_file(arr,size);
	
	//Calculation and output end
	
}

int main()
{
	srandom(time(0));
	test();
	return 0;
}
	
	