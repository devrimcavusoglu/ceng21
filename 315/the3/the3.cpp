#include "the3.h"

#define C_MAX 26


// do not add extra libraries here

// https://stackoverflow.com/questions/32543683/radix-sort-array-of-strings


/*
    arr       : array to be sorted, in order to get points this array should contain be in sorted state before returning
    ascending : true for ascending, false for descending 
    n         : number of elements in the array
    l         : the number of characters used in counting sort at each time
    
    you can use ceil function from cmath    
*/

void abc(){
    char a = 'Z';
    char b = 'B';
    char aa[] = "AA";
    char bb[] = "BB";
    char ab[] = "AB";

    int a_i = (int) a - 65;
    int b_i = (unsigned char) b;
    std::cout << a_i << " " << b_i << "\n";
}


int get_index(std::string s, int s_len, int start_col, int end_col){
    int index = 0;
    for (int i = end_col; i>=start_col; i--){
        int char_index = (unsigned char) s[i] - 64;
        index += char_index * pow(C_MAX, end_col-i);
    }
    return index - 1;
}

int countingSort(std::string *arr, int n, int l, int start_col, int end_col, int &num_iter){
    int k = pow(C_MAX, l);
    int *counts = new int[k];
    std::string *output = new std::string[n];

    size_t s_len = arr[0].size();

    for (int i = 0; i<n; i++){
        int char_index = get_index(arr[i], s_len, start_col, end_col);
        counts[char_index] += 1;
        num_iter++;
    }

    for (int i = 1; i<k; i++){
        counts[i] = counts[i-1];
        num_iter++;
    }

    for (int i = n-1; i>=0; i--){
        int j = get_index(arr[i], s_len, start_col, end_col);
        std::cout << j << " " << counts[j] << "\n";
        counts[j] -= 1;
        output[counts[j]] = arr[i];
        num_iter++;
    }

    std::cout << output[0] << "\n";

    for (int i = 0; i<n; i++){
        arr[i] = output[i];
        num_iter++;
    }

    delete []counts;
    delete []output;

    return num_iter;
}


int radixSort(std::string arr[], bool ascending, int n, int l){
    int num_iter = 0;
    int end_col, start_col;
    std::string *ptr_arr = arr;

    size_t s_len = arr[0].size(); // all string sizes are the same

    for (int i = s_len-1; i>=0; i--){
        end_col = i;
        start_col = end_col - l + 1;
        num_iter += countingSort(ptr_arr, n, l, start_col, end_col, num_iter);
        num_iter++;
    }
    
    return num_iter;
}
