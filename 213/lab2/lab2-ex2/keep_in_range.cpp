#include <iostream>

// Write a C++ template function that removes all values of an array that are not in a range.
template<class C>
void keepInRange(C list[], int &size, C min, C max);
// list is the array.
// size is the number of elements in the array.
// min and max defines the range.
//
// remove all values in list that are not in range [min, max].
// size must be set to the new size of the array (i.e, number of unremoved elements).
// order of the values in list must not be changed.
//
// Example:
// before:
// list = [1, 3, 4, 5, 1, 2, 9, 3, 4]
// size = 9;
//
// keepInRange(list, size, 1, 3);
//
// after:
// list = [1, 3, 1, 2, 3, -, -, -, -]
//                       ------------
//					     (these values are unimportant)
// size = 5

// Definition of the keepInRange function.
template<class C>
void keepInRange(C list[], int &size, C min, C max)
{
    int r = 0;
    int dummy = min - 1;
    for (int i = 0; i<size; i++){
        if (list[i] < min or list[i] > max){
            for (int j = i+1; j<size; j++){
                if (list[j] >= min and list[j] <= max){
                    list[i] = list[j];
                    list[j] = dummy;
                    r--;
                    break;
                }
            }
            r++;
        }
    }
    size -= r;
    std::cout << "new size: " << size << "\n";
}