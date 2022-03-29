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


void merge(int array[], int const left, int const mid, int const right) {
    auto const subArrayOne = mid - left + 1;
    auto const subArrayTwo = right - mid;
  
    // Create temp arrays
    auto *leftArray = new int[subArrayOne],
         *rightArray = new int[subArrayTwo];
  
    // Copy data to temp arrays leftArray[] and rightArray[]
    for (auto i = 0; i < subArrayOne; i++)
        leftArray[i] = array[left + i];
    for (auto j = 0; j < subArrayTwo; j++)
        rightArray[j] = array[mid + 1 + j];
  
    auto indexOfSubArrayOne = 0, // Initial index of first sub-array
        indexOfSubArrayTwo = 0; // Initial index of second sub-array
    int indexOfMergedArray = left; // Initial index of merged array
  
    // Merge the temp arrays back into array[left..right]
    while (indexOfSubArrayOne < subArrayOne && indexOfSubArrayTwo < subArrayTwo) {
        if (leftArray[indexOfSubArrayOne] <= rightArray[indexOfSubArrayTwo]) {
            array[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
            indexOfSubArrayOne++;
        }
        else {
            array[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
            indexOfSubArrayTwo++;
        }
        indexOfMergedArray++;
    }
    // Copy the remaining elements of
    // left[], if there are any
    while (indexOfSubArrayOne < subArrayOne) {
        array[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
        indexOfSubArrayOne++;
        indexOfMergedArray++;
    }
    // Copy the remaining elements of
    // right[], if there are any
    while (indexOfSubArrayTwo < subArrayTwo) {
        array[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
        indexOfSubArrayTwo++;
        indexOfMergedArray++;
    }
}


int *mergeSort(int arr[], int begin, int end) {
	/*
	*
	* Properties:
	* - Comparison based.
	* - Divide & Conquer.
	* - Stable.
	* - Not adaptive (the performance is the same for all sort of inputs).
	* - Worst-case Time complexity: O(n*lg(n)).
	* - Space complexity: O(n)
	* - Number of calls: O(n) = 2*n - 1
	*/
    if (begin >= end)
        return arr; // Returns recursively
  
    int mid = (begin + end) / 2;
    mergeSort(arr, begin, mid);
    mergeSort(arr, mid + 1, end);

    merge(arr, begin, mid, end);
    return arr;
}


int *heapSort(int arr[], int begin, int end) {
	/*
	*
	* Properties:
	* - Comparison based.
	* - Inplace.
	* - Not stable.
	* - Not adaptive (the performance is the same for all sort of inputs).
	* - Worst-case Time complexity: O(n*lg(n)).
	* - Space complexity: O(1)
	*/
    if (begin >= end)
        return arr; // Returns recursively
  
    int mid = (begin + end) / 2;
    std::cout << "b & m & e : " << begin << " " << mid << " " << end << std::endl;
    mergeSort(arr, begin, mid);
    mergeSort(arr, mid + 1, end);

    merge(arr, begin, mid, end);
    return arr;
}



int *bubbleSort(int arr[], int size) {
	/*
	* 
	* Properties:
	* - Comparsion based.
	* - Inplace.
	* - Adaptive.
	* - Time complexity: O(n^2)
	* - Space complexity: O(1)
	*/
	for (int i = 0; i < size; i++) {
		int j = size-1;
		do {
			if (arr[j] < arr[j-1]) 
				std::swap(arr[j], arr[j-1]);
			j--;
		} while (j > i);
	}
	return arr;
}



int *shellSort(int arr[], int size) {
	/*
	* 
	* Properties:
	* - Comparsion based.
	* - Inplace.
	* - Adaptive.
	* - Time complexity: O(n^2)
	* - Space complexity: O(1)
	*/
	int h = 1;
	int *sorted_h;
	while (h < size)
		h = 3*h;
	while (h>0) {
		h /= 3;
		sorted_h = insertionSort(&arr[h], size-h+1);
		for (int i = 0; i<size-h+1; i++)
			arr[h+i] = sorted_h[i];
	}
	return arr;
}


int *quickSort(int arr[], int size) {
	/*
	* 
	* Properties:
	* - Comparsion based.
	* - Inplace.
	* - Adaptive.
	* - Time complexity: O(n^2)
	* - Space complexity: O(1)
	*/
	std::swap(arr[0], arr[size-1]);

	int k = 0;

	for (int i = 1; i<size; i++) {
		if (arr[i] < arr[0])
			std::swap(arr[++k], arr[i]);
		std::swap(arr[0], arr[k]);
	}
	quickSort(arr, k-1);
	quickSort(&arr[k], size-k+1);
	return arr;
}

int main() {
	const int size = 25;
	int numbers[size];
	for (int i = 0; i<size; i++) 
		numbers[i] = i;
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

	shuffle(numbers, size);
	print_array(numbers, size);
	print(">>> Merge sort ..");
	t1 = getTime();
	arr_sorted = mergeSort(numbers, 0, size-1);
	t2 = getTime();
	print_array(arr_sorted, size);
	timeElapsed(t1, t2);


	shuffle(numbers, size);
	print_array(numbers, size);
	print(">>> Bubble sort ..");
	t1 = getTime();
	arr_sorted = bubbleSort(numbers, size);
	t2 = getTime();
	print_array(arr_sorted, size);
	timeElapsed(t1, t2);

	shuffle(numbers, size);
	print_array(numbers, size);
	print(">>> Shell sort ..");
	t1 = getTime();
	arr_sorted = shellSort(numbers, size);
	t2 = getTime();
	print_array(arr_sorted, size);
	timeElapsed(t1, t2);

	shuffle(numbers, size);
	print_array(numbers, size);
	print(">>> Quick sort ..");
	t1 = getTime();
	arr_sorted = quickSort(numbers, size);
	t2 = getTime();
	print_array(arr_sorted, size);
	timeElapsed(t1, t2);
}