#include "the4.h"



int max(int *&arr, int size) {
    int max_value = 0;
    for (int i = 0; i < size; i++) {
        if (arr[i] > max_value)
            max_value = arr[i];
    }
    return max_value;
}


int argmax(int *&arr, int size) {
    int max_value = 0;
    int max_index = 0;
    for (int i = 0; i < size; i++) {
        if (arr[i] > max_value) {
            max_index = i;
            max_value = arr[i];
        }
    }
    return max_index;
}


int recursive_sln(int i, int*& arr, int &number_of_calls){ //direct recursive
    number_of_calls+=1;
    
    int sum = 0;
    int size = i+1;

    if (size <= 3 and number_of_calls == 1) {
        return max(arr, size);
    }
    else if (size == 2) {
        return arr[0] + arr[1];
    }
    else {
        int *subarr = new int [2];
        int sub_sum = 0;
        for (int k = 0; k < size; k++) {
            subarr[0] = arr[k];
            for (int j = k+3; j < size; j++) {
                subarr[1] = arr[j];
                sub_sum = recursive_sln(1, subarr, number_of_calls);
                if (sub_sum > sum)
                    sum = sub_sum;
            }
        }
        delete [] subarr;
    }

    return sum;
}


/*int recursive_sln(int i, int*& arr, int &number_of_calls){ //direct recursive
    number_of_calls+=1;
    
    int sum = 0;
    int size = i+1;

    if (size <= 3 and number_of_calls == 1)
        return max(arr, size);
    else if (size <= 3) {
        int m1 = max(arr, size);
        arr[argmax(arr, size)] = 0;
        int m2 = max(arr, size);
        return m1 + m2;
    }

    // construct subarrays and invoke recursive call for each
    int sub_max = 0;
    for (int j = i; j > 2; j--) {
        // construct a subarray from arr
        int sub_size = j-1;
        int *subarr = new int[sub_size];
        subarr[sub_size-1] = arr[j];
        for (int k = j-3; k >= 0; k--) 
            subarr[k] = arr[k];

        // recursive call for subarray
        sub_max = recursive_sln(sub_size-1, subarr, number_of_calls);
        if (sub_max > sum)
            sum = sub_max;
        // release the allocated memory
        delete [] subarr;
    }

    return sum;
}*/




int memoization_sln(int i, int*& arr, int*& mem){ //memoization

    //your code here

    return 0; // this is a dummy return value. YOU SHOULD CHANGE THIS!
}



int dp_sln(int size, int*& arr, int*& mem){ //dynamic programming
    if (size <= 3 and mem[0] == -1)
        return max(arr, size);
    else if (size <= 3) {
        int m1 = max(arr, size);
        arr[argmax(arr, size)] = 0;
        int m2 = max(arr, size);
        return m1 + m2;
    }

    
    int prev_max;
    for (int i = 0; i < size; i++) {
        prev_max = arr[i];

        else if (arr[i] > prev_max) {
            mem[i] = arr[i] + max(mem, i-1);
            prev_max = arr[i];
        }
        else
            mem[i] = mem[i-1];
    } 
    return max(mem, size);
}

