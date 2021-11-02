#include "the0.h"

/* == CONSTRAINTS ==
* a maximum execution time of 1 minute
* a 256 MB maximum memory limit
* a stack size of 64 MB for function calls (ie. recursive solutions)
* Each task has a complexity constraint explained in respective sections.
* Solutions with longer running times will not be graded.*/

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
