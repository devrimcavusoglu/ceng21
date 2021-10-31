#include "sort.hpp"
#include <cstdio.h>
 
// A utility function to swap two elements
void swap(int* a, int* b)
{
    int t = *a;
    *a = *b;
    *b = t;
}
 
/* This function takes last element as pivot, places
   the pivot element at its correct position in sorted
    array, and places all smaller (smaller than pivot)
   to left of pivot and all greater elements to right
   of pivot */
int partition (int vec, int low, int high)
{
    int pivot = vec[high];    // pivot
    int i = (low - 1);  // Index of smaller element
 
    for (int j = low; j <= high- 1; j++)
    {
        // If current element is smaller than or
        // equal to pivot
        if (vec[j] <= pivot)
        {
            i++;    // increment index of smaller element
            swap(&vec[i], &vec[j]);
        }
    }
    swap(&vec[i + 1], &vec[high]);
    return (i + 1);
}
 
/* The main function that implements QuickSort
  vec --> Array to be sorted,
  low  --> Starting index,
  high  --> Ending index */
void quickSort(std::vector vec, int low, int high)
{
    if (low < high)
    {
        /* pi is partitioning index, vec[p] is now
           at right place */
        int pi = partition(vec, low, high);
 
        // Separately sort elements before
        // partition and after partition
        quickSort(vec, low, pi - 1);
        quickSort(vec, pi + 1, high);
    }
}