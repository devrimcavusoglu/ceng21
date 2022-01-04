#include <chrono>
#include <iostream>


void print(std::string str) {
	std::cout << str << std::endl;
}


void print_array(int arr[], int size) {
	for (int i = 0; i < size; i++)
		std::cout << arr[i] << " ";
	std::cout << std::endl;
}

auto getTime() {
	return std::chrono::high_resolution_clock::now();
}


void timeElapsed(auto start_time, auto end_time) {
	std::cout << "Time elapsed: "
              << std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count()
              << " ns\n";
    std::cout << "==============================\n";
}

void shuffle(int *arr, int size) {
	for (int i = 0; i < 50; i+=3) {
		int idx = i % size;
		int s_idx = 2*i % size;
		std::swap(arr[idx], arr[s_idx]);
	}
}


int *insertionSort(int arr[], int size) {
	/*
	* The logic of insertion sort is neatly straightforward, it simply
	* divides (with pointers) the unsorted array into two parts, sorted and unsorted.
	* So the left part of the array is always sorted with the end of this sorted array
	* is *s and the unsorted array starts from *(s+1) up to n.
	* 
	* Properties:
	* - Comparison based.
	* - Stable.
	* - Adaptive (the performance improves of how much sorted the given array is).
	* - Worst-case Time complexity: O(n^2).
	* - Space complexity: O(1) only constant store of temporary variables.
	* - O(n^2) swaps.
	* - O(n^2) comparisons.
	*/
	int key;
	for (int i = 1; i < size; i++) {
		key = arr[i];
		for (int j = i - 1; j >= 0; j--) {
			if (arr[j] > key)
				std::swap(arr[j], arr[j+1]);
		}
	}
	return arr;
}


int argmin(int *arr, int size) {
	int _argmin = 0;
	for (int i = 0; i < size; i++) {
		if (arr[i] < arr[_argmin])
			_argmin = i; 
	}
	return _argmin;
}


int *selectionSort(int arr[], int size) {
	/*
	* The logic of insertion sort is neatly straightforward like insertion sort,
	* it again treats the unsorted array into two parts (with pointers), sorted and unsorted.
	* Initially, the whole array is unsorted. Starting from the beginning, it searchs for 
	* minimum value through i:n, and inserts it at the ith position.
	* 
	* Properties:
	* - Comparison based.
	* - Not stable.
	* - Not adaptive (the performance is the same for all sort of inputs).
	* - Worst-case Time complexity: O(n^2).
	* - Space complexity: O(1) only constant store of temporary variables.
	* - O(n^2) comparsions.
	* - O(n) swaps.
	*/
	for (int i = 0; i < size; i++) {
		int _argmin = argmin(&arr[i], size-i) + i;
		std::swap(arr[i], arr[_argmin]);
	}
	return arr;
}


int *mergeSort(int arr[], int size) {
	
	return arr;
}


int main() {
	int size = 5;
	int numbers[] = {1, 4, 3, 5, 2};
	int *arr_sorted;
	auto t1 = getTime();
	auto t2 = getTime();
    
	print("Printing numbers...");

	shuffle(numbers, size);
	print_array(numbers, size);
	print(">>> Insertion sort ..");
	t1 = getTime();
	arr_sorted = insertionSort(numbers, size);
	t2 = getTime();
	print_array(arr_sorted, size);
	timeElapsed(t1, t2);
	

	shuffle(numbers, size);
	print_array(numbers, size);
	print(">>> Selection sort ..");
	t1 = getTime();
	arr_sorted = selectionSort(numbers, size);
	t2 = getTime();
	print_array(arr_sorted, size);
	timeElapsed(t1, t2);
}