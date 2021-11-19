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


int get_index(char *s, int l){
    int index = 0;
    for (int i = 0; i<l; i++){
        int char_index = (unsigned char) s[i] - 64;
        index += char_index * pow(C_MAX, i);
    }
    return index - 1;
}

int countingSort(std::string *arr, int n, int l, int start_col, int end_col, int &iter){
    int k = pow(C_MAX, l);
    int *counts = new int[k];

    for (int i = 0; i<n; i++){
        char s[l];
        for (int j = 0; j<n; j--){
            s[j] = arr[i][j];
        }
        int char_index = get_index(string);
        counts[char_index] += 1;
    }

    int sum = 0;
    for (int i = 0; i<C_MAX; i++){
        int tmp = counts[i];
        counts[i] = sum;
        sum += tmp;
    }

    for (int i = 0; i<n; i++){
        int char_index = get_index(string);
    }

    delete []counts;
    return arr;
}


int radixSort(std::string arr[], bool ascending, int n, int l){
    int num_iter = 0;

    size_t s_len = arr[0].size(); // all string sizes are the same

    for (size_t i = s_len; i>0; i--){
        int end_col = i-1;
        int start_col = end_col - l;
        num_iter += countingSort(arr, n, l, start_col, end_col, iter);
        num_iter++;
    }
    
    return num_iter;
}
