#ifndef HEAP_FUNCTIONS_H
#define HEAP_FUNCTIONS_H

#include "HeapPriorityQueue.h"

/* TODO : Q1 */
/* Accepts an array of integers and the length of the array, and rearranges 
 * the integers in the array to be in descending order using a 
 * HeapPriorityQueue as a helper. For example if the array passed stores 
 * [42, 9, 22, 17, -3, 81], after the call the array should store 
 * [81, 42, 22, 17, 9, -3]. 
 */
void descending(int arr[], int len);

/* TODO : Q2 */
/* Accepts a HeapPriorityQueue of integers and an integer k as parameters and 
 * returns the kth-smallest integer from the priority queue. For example if 
 * the queue passed stores the integers [42, 50, 45, 78, 61] and k is 4, 
 * return the fourth-smallest integer which is 61. If k is 0 or negative or 
 * greater than the size of the priority queue, throw an 
 * IllegalArgumentException. If your method modifies the state of the 
 * priority queue during its computation it should restore the queue before 
 * it returns. You may use one stack or queue as auxiliary storage. 
 */
int kthsmallest(HeapPriorityQueue<int> heap, int k);

/* TODO : Q3 */
/* Accepts a HeapPriorityQueue of integers as parameter and returns true if 
 * the queue contains a sequence of consecutive integers starting from the 
 * front of the queue. For example if the priority queue stores 
 * [7, 8, 9, 10, 11] your method should return true. If your method modifies 
 * the state of the priority queue during its computation it should restore 
 * the queue before it returns. You may use one stack or queue as 
 * auxiliary storage.
 */
bool isConsecutive(HeapPriorityQueue<int> heap);

#endif //HEAP_FUNCTIONS_H
