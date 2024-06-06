/**
* Title: AVL Trees and Heaps
* Author : Ahmet Furkan KIZIL
* ID: 22203112
* Section : 3
* Homework : 2
* Description : AVL Trees and Heaps with required implementations
*/

#ifndef CS202_HW2_HEAP_H
#define CS202_HW2_HEAP_H
#include <iostream>
#include <fstream>
#include "Computer.h"
using namespace std;


class Heap {
public:
    Heap(string logFile);
    Heap(int sizeOfTheHeap);
    //~Heap();
    bool heapIsEmpty() const;
    void heapInsert(const Request& newItem);
    void heapDelete(Request& rootItem);
    void displayArray();
    int getTotalNumberOfRequests();
    void heapify(int root);
    int noOfSamePriorityRequests();
    int noOfSameRequestTime();
    void minHeapByRequestTimeInsert(const Request& newItem);
    void minHeapByRequestTimeDelete(Request &rootItem);
    void minHeapifyByRequestTime(int root);
    void minHeapByIdInsert(const Request& newItem);
    void minHeapByIdDelete(Request &rootItem);
    void minHeapifyById(int root);

private:
    int totalNumberOfRequests;
    Request* items;	            // Array of Requests
    int size;            	    // Number of current Requests
};

#endif //CS202_HW2_HEAP_H
