// this file is for you for testing purposes, it won't be included in evaluation.

#include <iostream>
#include <random>
#include <ctime>
#include "the3.h"

char getRandomChar(){
	return 'A' + (rand() % 26);
}

std::string getRandomString(int length){
	char* result_array = new char[length];
	for(int i = 0; i < length; i++){
		result_array[i] = getRandomChar();
	}
	std::string result(result_array, length);
	return result;
}

void randomArray(std::string*& array, int size, int length)
{
  array = new std::string[size];
  for (int i = 0; i < size; i++)
  {
    array[i] = getRandomString(length);
  }
}

void printArrayInLine(std::string arr[], int arraySize){
	std::cout << "{ ";
	for(int i = 0; i < arraySize; i++){
		std::cout << "\"" << arr[i] << "\"";
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
    int numberOfIterations;

   /* int size = 10;      // max 1000000
    int length = 5;     // max 12
    int l = 2;      // number of characters to be used in counting sort (1,2,3,4 or 6)
*/
    int size = 4;      // max 1000000
    int length = 2;     // max 12
    int l = 1;      // number of characters to be used in counting sort (1,2,3,4 or 6)


    std::string* arr;

    arr = new std::string[4];
    arr[0] = "BA";
    arr[1] = "AA";
    arr[2] = "BB";
    arr[3] = "AB";
    //randomArray(arr, size, length);
    std::cout << "Array before sorting:" << std::endl;
    printArrayInLine(arr, size);
    if ((begin = clock() ) ==-1)
		std::cerr << "clock error" << std::endl;

    numberOfIterations = radixSort(arr, true, size, l);

    if ((end = clock() ) ==-1)
		std::cerr << "clock error" << std::endl;

    duration = ((double) end - begin) / CLOCKS_PER_SEC;
	std::cout << "Duration: " << duration << " seconds." << std::endl;

    std::cout << "Number of Iterations: " << numberOfIterations << std::endl;
    std::cout << "Array after sorting:" << std::endl;
    printArrayInLine(arr, size);
}

int main()
{
	srandom(time(0));
    //abc();
    test();
	return 0;
}
