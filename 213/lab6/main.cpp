#include <iostream>

#include "heap_functions.h"
#include "HeapPriorityQueue.h"

using namespace std;

void print_array(int arr[], int size) {
    for (int i = 0; i < size; i++)
        std::cout << arr[i] << " ";
    std::cout << endl;
}


void test_descending(int arr[], int size) {
    std::cout << "Testing descending..\n";
    std::cout << "Printing raw array..\n";
    print_array(arr, size);
    descending(arr, size);
    std::cout << "Printing after descending sort..\n";
    print_array(arr, size);
    std::cout << "============ END OF TEST ============\n";
}

void test_kthsmallest(HeapPriorityQueue<int> heap, int k) {
    std::cout << "Testing kth smallest..\n";
    std::cout << "Printing heap..\n";
    heap.print();
    int min_k = kthsmallest(heap, k);
    std::cout << "kth smallest: " << min_k << std::endl;
    std::cout << "============ END OF TEST ============\n";
}

void test_isconsecutive(HeapPriorityQueue<int> heap) {
    std::cout << "Testing isConsecutive..\n";
    std::cout << "Printing raw array..\n";
    heap.print();
    bool is_consecutive = isConsecutive(heap);
    std::cout << "is consecutive: " << is_consecutive << std::endl;
    std::cout << "============ END OF TEST ============\n";
}


void test_changepriority(HeapPriorityQueue<int> heap, int old_val, int new_val) {
    std::cout << "Testing changePriority..\n";
    std::cout << "Printing raw array..\n";
    heap.print();
    heap.changePriority(old_val, new_val);
    heap.print();
    std::cout << "============ END OF TEST ============\n";
}



int main() {
    int size = 8;
    //int numbers[] = {42, 17, 9, 42, 35, -1, 88};
    int numbers[] = {3, 55, 18, 74, 91, 29, 62, 100};

    HeapPriorityQueue<int> heap;
    for (int i = 0; i < size; i++)
        heap.add(numbers[i]);

    HeapPriorityQueue<int> heap_consecutive;
    for (int i = 0; i < size; i++)
        heap_consecutive.add(i);


    test_descending(numbers, size);
    test_kthsmallest(heap, 4);
    test_isconsecutive(heap);
    test_isconsecutive(heap_consecutive);
    test_changepriority(heap, 62, -3);

    return 0;
}
