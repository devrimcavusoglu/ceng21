#ifndef __myarray_h__
#define __myarray_h__

#include <iostream>


class MyArray
{
public:
    // Default constructor
    MyArray();
    
    // Constructs the array with first_el as its first element.
    MyArray(int first_el);
    
    // This is the destructor. It is automatically
    // called when an object of this class is destroyed.
    ~MyArray();

    // Copy constructor. Different from the assignment operator,
    // this is called when an object is "being created" as a
    // (DEEP) copy of another object.
    MyArray(const MyArray& rhs);
    
    // This is the assignment operator which is automatically
    // called when an object of type MyArray is assigned
    // to another object of the same type. Technically, it
    // does not have to return "MyArray&" but we do so to
    // allow chaining assignments such as: arr1 = arr2 = arr3
    // PLEASE AVOID SHALLOW COPY.
    MyArray& operator=(const MyArray& rhs);
    
    // Doubles size of arr allocated space without losing current 
    // data in arr. Updates size variable according to the final space.
    void double_size();
    
    // Adds the element el at the end of arr. 
    // If the arr is already full (i.e. size == n), the new element el
    // is inserted to the end, after doubling the size of the array. 
    void insert_data(int el);
    
    // Deletes the element in index ind (ind >=0 and ind < n )
    // by rearranging elements of arr so that remaining elements
    // are shifted to the left in the array.
    // (there will be no vacant array cell in the beginning
    // or between any two occupied cells of arr).
    void delete_data(int ind);
    
    int get_element(int ind);
    
    // Prints this string by putting the separator
    // character between each element in the data.
    // By default, do not print anything.
    // IMPLEMENTED.
    void print(char separator = '\0') const;
    
    // returns n
    int get_n();
    
    // returns size
    int get_size();
    
    
private:
    int* arr; // array data
    int n; // number of elements in arr
    int size; // total length of array
};


#endif // __myarray_h__

