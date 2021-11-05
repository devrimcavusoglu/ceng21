#include "the1.h"


//You can add your own helper functions
void merge(int *arr, int low, int high, int mid);
void insertionSort(int* arr, long &comparison, long & swap, int size);
void merge(int *ar1, int *ar2, int size, int *output, long &comparison)
{    
    for(int i=0; i<size; i++)
        output[i]=ar1[i];

    for(int i=size; i<size*2; i++)
        output[i]=ar2[i-size];

    //sort the array
    long mock_swap = 0;
    insertionSort(output, comparison, mock_swap, size*2);
}

void insertionSort(int* arr, long &comparison, long & swap, int size) 
{
    int x;

    for (int i{1}; i<size; i++){
        x = arr[i];
        int j{i-1};
        while (j>=0 && arr[j] > x){
            arr[j+1] = arr[j];
            swap++;
            j--;
        }
        comparison += i-j;
        arr[j+1] = x;
    }
}


int sillySort(int* arr, long &comparison, long & swap, int size) 
{
    int num_of_calls = 1;

    if (size < 2)
    	return num_of_calls;
    else if (size == 2){
    	if (arr[1] < arr[0]){
    		int temp = arr[0];
    		arr[0] = arr[1];
    		arr[1] = temp;
	    	swap++;
    	}
    	comparison++;
    	return num_of_calls;
    }
  	else if (size < 4){
  		insertionSort(arr, comparison, swap, size);
  		num_of_calls++;
  	}
  	else {
  		int new_size = size/2;
  		int *q1_q2;
  		int *q2_q3;
  		int *q3_q4;
  		
  		q1_q2 = &arr[0];
  		q2_q3 = &arr[size/4];
  		q3_q4 = &arr[size/2];
  		
  		num_of_calls += sillySort(q1_q2, comparison, swap, new_size);
  		num_of_calls += sillySort(q2_q3, comparison, swap, new_size);
  		num_of_calls += sillySort(q3_q4, comparison, swap, new_size);
  		num_of_calls += sillySort(q1_q2, comparison, swap, new_size);
  		num_of_calls += sillySort(q2_q3, comparison, swap, new_size);
  		num_of_calls += sillySort(q1_q2, comparison, swap, new_size);	
  	}
	return num_of_calls;
}


int crossMergeSort(int *arr, long &comparison, int size)
{
	
	int num_of_calls=1;

	if (size < 2)
    	return num_of_calls;
    else if (size == 2){
    	if (arr[1] < arr[0]){
    		int temp = arr[0];
    		arr[0] = arr[1];
    		arr[1] = temp;
    	}
    	comparison++;
    	return num_of_calls;
    }
    else {
  		int new_size = size/4;
  		int *q1;
  		int *q2;
  		int *q3;
  		int *q4;
  		int *h1 = new int[size/2];
  		int *h2 = new int[size/2];
  		int *res;
  		
  		q1 = &arr[0];
  		q2 = &arr[size/4];
  		q3 = &arr[size/2];
  		q4 = &arr[3*size/4];
  		res = &arr[0];
  		
  		num_of_calls += crossMergeSort(q1, comparison, new_size);
  		num_of_calls += crossMergeSort(q2, comparison, new_size);
  		num_of_calls += crossMergeSort(q3, comparison, new_size);
  		num_of_calls += crossMergeSort(q4, comparison, new_size);

  		merge(q1, q3, new_size, h1, comparison);
  		merge(q2, q4, new_size, h2, comparison);
  		merge(h1, h2, new_size*2, res, comparison);

  		delete h1;
	  	delete h2;
  	}
	
	return num_of_calls;
	
}
