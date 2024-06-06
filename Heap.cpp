/**
* Title: AVL Trees and Heaps
* Author : Ahmet Furkan KIZIL
* ID: 22203112
* Section : 3
* Homework : 2
* Description : AVL Trees and Heaps with required implementations
*/

#include "Heap.h"
using namespace std;

// The codes for heap implementation are taken from the slides "L4_Heaps"
Heap::Heap(string logFile){
    size = 0;
    ifstream file(logFile);

    if (!file.is_open()) {
        throw runtime_error("Unable to open file " + logFile);
    }
    int numberOfRequests;
    file >> numberOfRequests;
    totalNumberOfRequests = numberOfRequests;
    this->items = new Request[totalNumberOfRequests];

}

Heap::Heap(int sizeOfTheHeap) {
    size = 0;
    this->items = new Request[sizeOfTheHeap];
}


/*
 * Heap::~Heap() {
    while (this->heapIsEmpty()) {
        Request r;
        this->heapDelete(r);
    }
}
 */


int Heap::getTotalNumberOfRequests() {
    return totalNumberOfRequests;
}

bool Heap::heapIsEmpty() const {
    return (size == 0);
}

void Heap::heapInsert(const Request& newItem){

    if (size >= getTotalNumberOfRequests()) {
        cout << "The heap is full" << endl;
    }

    items[size] = newItem;

    int place = size;
    int parent = (place - 1)/2;

    while ((place > 0) && (items[place].priority > items[parent].priority)){
        Request temp = items[parent];
        items[parent] = items[place];
        items[place] = temp;

        place = parent;
        parent = (place-1) / 2;
    }
    ++size;
}

void Heap::heapDelete(Request& rootItem){
    if (heapIsEmpty()){
        cout << "The heap is empty" << endl;
    }
    else {
        rootItem = items[0];
        items[0] = items[--size];
        heapify(0);
    }
}

void Heap::heapify(int root) {
    int child = 2 * root + 1;
    if (child < size) {
        int rightChild = child + 1;
        if((rightChild < size) && (items[rightChild].priority > items[child].priority)) {
            child = rightChild;
        }

        if (items[root].priority < items[child].priority) {
            Request temp = items[root];
            items[root] = items[child];
            items[child] = temp;
            heapify(child);
        }
    }
}


void Heap::displayArray() {
    for (int i = 0; i < size; ++i) {
       cout << "Request " << items[i].id << " | Priority " << items[i].priority << " | Request Time " << items[i].requestTime << " | Process Time " << items[i].processTime << " |" << endl;
    }
}

int Heap::noOfSamePriorityRequests() {
    int numberOfSamePriority = 0;
    int highestPriority = 0;
    highestPriority = items[0].priority;
    for (int i = 0; i < size; ++i) {
        if (items[i].priority == highestPriority) {
            numberOfSamePriority++;
        }
    }
    return numberOfSamePriority;
}

void Heap::minHeapByRequestTimeInsert(const Request& newItem){

    if (size >= 100000) {
        cout << "The heap is full" << endl;
    }

    items[size] = newItem;

    int place = size;
    int parent = (place - 1)/2;

    while ((place > 0) && (items[place].requestTime < items[parent].requestTime)){
        Request temp = items[parent];
        items[parent] = items[place];
        items[place] = temp;

        place = parent;
        parent = (place-1) / 2;
    }
    ++size;
}

void Heap::minHeapByRequestTimeDelete(Request& rootItem){
    if (heapIsEmpty()){
        cout << "The heap is empty" << endl;
    }
    else {
        rootItem = items[0];
        items[0] = items[--size];
        minHeapifyByRequestTime(0);
    }
}

void Heap::minHeapifyByRequestTime(int root) {
    int child = 2 * root + 1;
    if (child < size) {
        int rightChild = child + 1;
        if((rightChild < size) && (items[rightChild].requestTime < items[child].requestTime)) {
            child = rightChild;
        }

        if (items[root].requestTime > items[child].requestTime) {
            Request temp = items[root];
            items[root] = items[child];
            items[child] = temp;
            minHeapifyByRequestTime(child);
        }
    }
}

int Heap::noOfSameRequestTime() {
    int numberOfSameRequestTime = 0;
    int lowestRequestTime = 0;
    lowestRequestTime = items[0].requestTime;
    for (int i = 0; i < size; ++i) {
        if (items[i].requestTime == lowestRequestTime) {
            numberOfSameRequestTime++;
        }
    }
    return numberOfSameRequestTime;
}

void Heap::minHeapByIdInsert(const Request& newItem){

    if (size >= 100000) {
        cout << "The heap is full" << endl;
    }

    items[size] = newItem;

    int place = size;
    int parent = (place - 1)/2;

    while ((place > 0) && (items[place].id < items[parent].id)){
        Request temp = items[parent];
        items[parent] = items[place];
        items[place] = temp;

        place = parent;
        parent = (place-1) / 2;
    }
    ++size;
}

void Heap::minHeapByIdDelete(Request& rootItem){
    if (heapIsEmpty()){
        cout << "The heap is empty" << endl;
    }
    else {
        rootItem = items[0];
        items[0] = items[--size];
        minHeapifyById(0);
    }
}

void Heap::minHeapifyById(int root) {
    int child = 2 * root + 1;
    if (child < size) {
        int rightChild = child + 1;
        if((rightChild < size) && (items[rightChild].id < items[child].id)) {
            child = rightChild;
        }

        if (items[root].id > items[child].id) {
            Request temp = items[root];
            items[root] = items[child];
            items[child] = temp;
            minHeapifyById(child);
        }
    }
}




