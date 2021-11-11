#include <iostream>
#include "keep_in_range.cpp"


template<class T>
void print_array(T *array, int size){
    for (int i = 0; i<size-1; i++){
        std::cout << array[i] << " ";
    }
    std::cout << array[size-1] << "\n";
}

int main()
{
    int size = 9;
    int array[size] = {1, 3, 4, 5, 1, 2, 9, 3, 4};

    print_array(array, 9);
    keepInRange(array, size, 1, 3);
    print_array(array, 9);

    return 0;
}
