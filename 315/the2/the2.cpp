#include <iostream>
#include "the2.h"

//You may write your own helper functions here

template <class T>
void print_array(T *arr, int size){
	for(int i{}; i<size; i++){
		std::cout << arr[i] << " ";
	}
	std::cout << "\n";
}

template <class T>
void swappp(T &a, T &b, long &swap, long &comparison){		
	if (a != b){
		T temp = b;
		b = a;
		a = temp;
		swap++;
		comparison++;
	}
}

template <class T>
T minimum(T *arr, int size){
	int min = T();
	for (int i{}; i<size; i++){
		if (arr[i] < min)
			min = arr[i];
	}
	return min;
}

template <class T>
T min(T a, T b){
	if (a<b) return a;
	return b;
}

int distance(int a, int b){
	int dist = a-b;
	if (dist < 0){
		dist = -1 * dist;
	}
	return dist;
}

void set_dist(int i, int j, double &avg_dist, double &max_dist){
	double d;
	d = (double) distance(i,j);
	avg_dist += d;
	if (d > max_dist)
		max_dist = d;
}


int classical_partition(unsigned short *arr, int size, long &swap, long &comparison, double &avg_dist, double &max_dist){
	int pivot = arr[size-1];
	int i = -1;
	for (int j{}; j<size-1; j++){
		if (arr[j] >= pivot){
			i++;
			swappp(arr[i], arr[j], swap, comparison);
			set_dist(i, j, avg_dist, max_dist);
		}
	}
	swappp(arr[i+1], arr[size-1], swap, comparison);
	set_dist(i+1, size-1, avg_dist, max_dist);
	return i+1;
}

int hoare_partition(unsigned short *arr, int size, long &swap, long &comparison, double &avg_dist, double &max_dist){
	int pivot_idx = (int) (size-1)/2;
	int pivot = arr[pivot_idx];
	int i = -1;
	int j = size;
	while (true){
		do{
			j--;	
		} while (arr[j]<pivot);
		do{
			i++;	
		} while (arr[i]>pivot);
		if (i<j){
			swappp(arr[i], arr[j], swap, comparison);
			set_dist(i, j, avg_dist, max_dist);
		}
		else
			return j;
	}
}

void quickSort(unsigned short *arr, long &swap, double & avg_dist, double & max_dist, bool hoare, int size){
	if (size > 1){
		long temp_comp = 0;
		int p;
		if (!hoare){
			p = classical_partition(arr, size, swap, temp_comp, avg_dist, max_dist);
			quickSort(arr, swap, avg_dist, max_dist, hoare, p);
		}
		else{
			p = hoare_partition(arr, size, swap, temp_comp, avg_dist, max_dist);
			quickSort(arr, swap, avg_dist, max_dist, hoare, p+1);
		}
		quickSort(&arr[p+1], swap, avg_dist, max_dist, hoare, size-p);
	}
	avg_dist /= swap;
}

void partition_3way(unsigned short *arr, int &l, int &r, long &swap, long &comparison, int size){
	int i = 0;
	int j = 0;
	int p = size - 1;

	while (i<p){
		if (arr[i]>arr[size-1]){
			comparison++;
			swappp(arr[i], arr[j], swap, comparison);
			i++;
			j++;
		}
		else if (arr[i] == arr[size-1]){
			comparison++;
			p--;
			swappp(arr[i], arr[p], swap, comparison);
		}
		else
			i++;
	}
	print_array(arr, size);
	int m = min(p-j, size-p);
	comparison++;
	int k = size-m;
	while (k<size){
		swappp(arr[j], arr[k], swap, comparison);
		j++;
		k++;
	}
	l = j;
	r = p-j;
}


void quickSort3(unsigned short *arr, long &swap, long &comparison, int size) {
	if (size>1){
		int l,r;
		partition_3way(arr, l, r, swap, comparison, size);
		quickSort3(arr, swap, comparison, l);
		quickSort3(&arr[size-r], swap, comparison, r+1);
	}
}
