// this file is for you for testing purposes, it won't be included in evaluation.

#include <iostream>
#include <random>
#include <ctime>
#include <cstdlib>
#include "the4.h"

int getRandomInt(){
        int r = rand()%100;
        return r;
}


void randomArray(int*& array, int size){
    array = new int [size];
    for (int i = 0; i < size; i++){
        int r = getRandomInt();
        array[i] = r;
    }
}


void printArrayInLine(int arr[], int arraySize){
        std::cout << "{ ";
        for(int i = 0; i < arraySize; i++){
                std::cout << arr[i];
        if (i == arraySize - 1){
            continue;
        }else{
            std::cout << ", ";
        }
        }
        std::cout << " }" << std::endl;
}



void test(){
    clock_t begin, end;
        double duration;
    int max_sum_rec;
        int max_sum_mem;
        int max_sum_dp;


    int size = 6;      // max 10000
    int* arr;
    //arr = new int [size]{8, 64, 55, 34, 46};
    arr = new int [size] {50, 30, 100, 10, 80, 100};
    //randomArray(arr, size);
    std::cout << "Array:" << std::endl;
    printArrayInLine(arr, size);



        std::cout << "_____________RECURSIVE IMPLEMENTATION:_____________" << std::endl;

    int number_of_calls_rec = 0;

    if ((begin = clock() ) ==-1)
                std::cerr << "clock error" << std::endl;

        max_sum_rec = recursive_sln(size-1, arr, number_of_calls_rec);

    if ((end = clock() ) ==-1)
                std::cerr << "clock error" << std::endl;

    duration = ((double) end - begin) / CLOCKS_PER_SEC;
        std::cout << "Duration: " << duration << " seconds." << std::endl;

        std::cout << "Max sum: " << max_sum_rec << std::endl;
    std::cout << "Number of recursive calls: " << number_of_calls_rec << std::endl;

        std::cout << "---------------------------------------------------";
        std::cout << "\n" << std::endl;



        int* mem = new int[size];


        std::cout << "______________________MEMOIZATION:__________________" << std::endl;

        for(int i = 0; i <= size-1; i++) mem[i] = -1;


        if ((begin = clock() ) ==-1)
                std::cerr << "clock error" << std::endl;

    max_sum_mem = memoization_sln(size-1, arr, mem);
    if ((end = clock() ) ==-1)
                std::cerr << "clock error" << std::endl;

    duration = ((double) end - begin) / CLOCKS_PER_SEC;
        std::cout << "Duration: " << duration << " seconds." << std::endl;

        std::cout << "Max sum: " << max_sum_mem << std::endl;
        std::cout << "Final mem: " << std::endl;
        printArrayInLine(mem, size);

        std::cout << "----------------------------------------------------";
        std::cout << "\n" << std::endl;




        std::cout << "__________________DYNAMIC PROGRAMMING:______________" << std::endl;

        for(int i = 0; i < size; i++) mem[i] = -1;


    if ((begin = clock() ) ==-1)
                std::cerr << "clock error" << std::endl;

        max_sum_dp = dp_sln(size, arr, mem);

    if ((end = clock() ) ==-1)
                std::cerr << "clock error" << std::endl;

    duration = ((double) end - begin) / CLOCKS_PER_SEC;
        std::cout << "Duration: " << duration << " seconds." << std::endl;

        std::cout << "Max sum: " << max_sum_dp << std::endl;
        std::cout << "Final mem: " << std::endl;
        printArrayInLine(mem, size);

        std::cout << "----------------------------------------------------";
        std::cout << "\n" << std::endl;

}

int main()
{
        srand(time(0));
    test();
        return 0;
}
