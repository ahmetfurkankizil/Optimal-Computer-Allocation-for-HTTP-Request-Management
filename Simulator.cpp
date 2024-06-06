/**
* Title: AVL Trees and Heaps
* Author : Ahmet Furkan KIZIL
* ID: 22203112
* Section : 3
* Homework : 2
* Description : AVL Trees and Heaps with required implementations
*/
#include "Simulator.h"
#include <iomanip>
using namespace std;

Simulator::Simulator(string fileName, double avgWaitingTime) {
    this->fileName = fileName;
    ifstream file(fileName);
    file >> this->numberOfRequests;
    this->currentTime = 0;
    priorityHeap = new Heap(fileName);
    this->currentAvgWaitingTime = 0;
    this->totalDelay = 0;
    this->avgWaitingTime = avgWaitingTime;

    int numberOfOptimumComputers = optimize(avgWaitingTime);
    cout << "Minimum number of computers required: " << numberOfOptimumComputers << endl << endl;
    cout << "Simulation with " << numberOfOptimumComputers << " computers:" << endl << endl;
    double averageTimeForString = simulateWithPrinting(numberOfOptimumComputers);
    cout << endl << "Average waiting time: " << fixed   << setprecision(2) << averageTimeForString << " ms" << endl;
}


Simulator::~Simulator() {
    delete [] priorityHeap;
    //delete [] computerArray;
}

int Simulator::getCurrentTime() {
    return currentTime;
}

double Simulator::calculateAvgWaitingTime() {
    return (this->currentAvgWaitingTime/ this->numberOfRequests);
}

void Simulator::moveOn() {
    currentTime++;
}

void Simulator::addDelay(int delay) {
    this->currentAvgWaitingTime += delay;
}

double Simulator::simulate(int numberOfComputers) {
    this->currentTime = 0;
    this->currentAvgWaitingTime = 0;
    computerArray = new Computer[numberOfComputers];

    // Initialising the computers
    for (int i = 0; i < numberOfComputers; ++i) {
        computerArray[i] = Computer(i);
    }

    ifstream file(fileName);
    int noOfRequests;
    int remainingNumberOfRequests;
    file >> noOfRequests;
    remainingNumberOfRequests = noOfRequests;

    int key, priority, requestTime, processTime;
    file >> key >> priority >> requestTime >> processTime;
    bool allRequestsAreProcessed = false;

    while (remainingNumberOfRequests != 0) {

        // Inserting the waiting request at the priority heap
        while (getCurrentTime() >= requestTime && !allRequestsAreProcessed) {
            Request r(key, priority, requestTime, processTime);
            this->priorityHeap->heapInsert(r);
            if (file.eof()) {
                allRequestsAreProcessed = true;
                break;
            }
            file >> key >> priority >> requestTime >> processTime;
        }

        //cout << "The heap at ms: " << currentTime << endl;
        //this->priorityHeap->displayArray();

        // Assigning the available computers
        for (int i = 0; i < numberOfComputers; ++i) {
            if(computerArray[i].isAvaliable()) {
                if(!this->priorityHeap->heapIsEmpty()) {
                    int immediateDelay = 0;
                    int noOfSamePriorityRequests = priorityHeap->noOfSamePriorityRequests();
                    if (noOfSamePriorityRequests > 1) {
                        Heap* tempPriorityHeap = new Heap(noOfSamePriorityRequests);
                        for (int j = 0; j < noOfSamePriorityRequests; ++j) {
                            Request r;
                            priorityHeap->heapDelete(r);
                            tempPriorityHeap->minHeapByRequestTimeInsert(r);
                        }

                        int noOfSameRequestTime = tempPriorityHeap->noOfSameRequestTime();
                        if (noOfSameRequestTime > 1) {
                            Heap *innerTempPriorityHeap = new Heap(noOfSameRequestTime);
                            for (int j = 0; j < noOfSameRequestTime; ++j) {
                                Request r;
                                tempPriorityHeap->minHeapByRequestTimeDelete(r);
                                innerTempPriorityHeap->minHeapByIdInsert(r);
                            }

                            Request r;
                            innerTempPriorityHeap->minHeapByIdDelete(r);
                            if (getCurrentTime() > r.getRequestTime()) {
                                immediateDelay = (getCurrentTime() - r.getRequestTime());
                                addDelay(immediateDelay);
                            }
                            remainingNumberOfRequests--;
                            computerArray[i].assign(r, immediateDelay);
                            // cout << "Computer " << computerArray[i].getComputerId() << " takes request " << r.getId() << " at ms " << getCurrentTime() << " (wait: " << immediateDelay << " ms)" << endl;
                            while (!innerTempPriorityHeap->heapIsEmpty()) {
                                Request r;
                                innerTempPriorityHeap->minHeapByIdDelete(r);
                                tempPriorityHeap->minHeapByRequestTimeInsert(r);
                            }
                            while (!tempPriorityHeap->heapIsEmpty()) {
                                Request r;
                                tempPriorityHeap->minHeapByRequestTimeDelete(r);
                                priorityHeap->heapInsert(r);
                            }
                            delete innerTempPriorityHeap;
                        }
                        else {
                            Request r;
                            tempPriorityHeap->minHeapByRequestTimeDelete(r);
                            if (getCurrentTime() > r.getRequestTime()) {
                                immediateDelay = (getCurrentTime() - r.getRequestTime());
                                addDelay(immediateDelay);
                            }
                            remainingNumberOfRequests--;
                            computerArray[i].assign(r, immediateDelay);
                            // cout << "Computer " << computerArray[i].getComputerId() << " takes request " << r.getId() << " at ms " << getCurrentTime() << " (wait: " << immediateDelay << " ms)" << endl;
                            while (!tempPriorityHeap->heapIsEmpty()) {
                                Request r;
                                tempPriorityHeap->minHeapByRequestTimeDelete(r);
                                priorityHeap->heapInsert(r);
                            }
                        }
                        //delete tempPriorityHeap;
                    } else {
                        Request r;
                        this->priorityHeap->heapDelete(r);

                        if (getCurrentTime() > r.getRequestTime()) {
                            immediateDelay = (getCurrentTime() - r.getRequestTime());
                            addDelay(immediateDelay);
                        }

                        remainingNumberOfRequests--;
                        computerArray[i].assign(r, immediateDelay);
                        //cout << "Computer " << computerArray[i].getComputerId() << " takes request " << r.getId() << " at ms " << getCurrentTime() << " (wait: " << immediateDelay << " ms)" << endl;
                    }


                }
            }
        }

        // Checking if any computer is finished or not (if finished free them)
        for (int i = 0; i < numberOfComputers; ++i) {
            computerArray[i].checkIfFinished(getCurrentTime());
        }

        moveOn();
    }
    delete computerArray;
    return calculateAvgWaitingTime();
}

double Simulator::simulateWithPrinting(int numberOfComputers) {
    this->currentTime = 0;
    this->currentAvgWaitingTime = 0;
    computerArray = new Computer[numberOfComputers];

    // Initialising the computers
    for (int i = 0; i < numberOfComputers; ++i) {
        computerArray[i] = Computer(i);
    }

    ifstream file(fileName);
    int noOfRequests;
    int remainingNumberOfRequests;
    file >> noOfRequests;
    remainingNumberOfRequests = noOfRequests;

    int key, priority, requestTime, processTime;
    file >> key >> priority >> requestTime >> processTime;
    bool allRequestsAreProcessed = false;

    while (remainingNumberOfRequests != 0) {

        // Inserting the waiting request at the priority heap
        while (getCurrentTime() >= requestTime && !allRequestsAreProcessed) {
            Request r(key, priority, requestTime, processTime);
            this->priorityHeap->heapInsert(r);
            if (file.eof()) {
                allRequestsAreProcessed = true;
                break;
            }
            file >> key >> priority >> requestTime >> processTime;
        }

        //cout << "The heap at ms: " << currentTime << endl;
        //this->priorityHeap->displayArray();

        // Assigning the available computers
        for (int i = 0; i < numberOfComputers; ++i) {
            if(computerArray[i].isAvaliable()) {
                if(!this->priorityHeap->heapIsEmpty()) {
                    int immediateDelay = 0;
                    int noOfSamePriorityRequests = priorityHeap->noOfSamePriorityRequests();
                    if (noOfSamePriorityRequests > 1) {
                        Heap* tempPriorityHeap = new Heap(noOfSamePriorityRequests);
                        for (int j = 0; j < noOfSamePriorityRequests; ++j) {
                            Request r;
                            priorityHeap->heapDelete(r);
                            tempPriorityHeap->minHeapByRequestTimeInsert(r);
                        }

                        int noOfSameRequestTime = tempPriorityHeap->noOfSameRequestTime();
                        if (noOfSameRequestTime > 1) {
                            Heap *innerTempPriorityHeap = new Heap(noOfSameRequestTime);
                            for (int j = 0; j < noOfSameRequestTime; ++j) {
                                Request r;
                                tempPriorityHeap->minHeapByRequestTimeDelete(r);
                                innerTempPriorityHeap->minHeapByIdInsert(r);
                            }

                            Request r;
                            innerTempPriorityHeap->minHeapByIdDelete(r);
                            if (getCurrentTime() > r.getRequestTime()) {
                                immediateDelay = (getCurrentTime() - r.getRequestTime());
                                addDelay(immediateDelay);
                            }
                            remainingNumberOfRequests--;
                            computerArray[i].assign(r, immediateDelay);
                            cout << "Computer " << computerArray[i].getComputerId() << " takes request " << r.getId()
                                 << " at ms " << getCurrentTime() << " (wait: " << immediateDelay << " ms)" << endl;
                            while (!innerTempPriorityHeap->heapIsEmpty()) {
                                Request r;
                                innerTempPriorityHeap->minHeapByIdDelete(r);
                                tempPriorityHeap->minHeapByRequestTimeInsert(r);
                            }
                            while (!tempPriorityHeap->heapIsEmpty()) {
                                Request r;
                                tempPriorityHeap->minHeapByRequestTimeDelete(r);
                                priorityHeap->heapInsert(r);
                            }
                            //delete innerTempPriorityHeap;
                        }
                        else {
                            Request r;
                            tempPriorityHeap->minHeapByRequestTimeDelete(r);
                            if (getCurrentTime() > r.getRequestTime()) {
                                immediateDelay = (getCurrentTime() - r.getRequestTime());
                                addDelay(immediateDelay);
                            }
                            remainingNumberOfRequests--;
                            computerArray[i].assign(r, immediateDelay);
                            cout << "Computer " << computerArray[i].getComputerId() << " takes request " << r.getId()
                                 << " at ms " << getCurrentTime() << " (wait: " << immediateDelay << " ms)" << endl;
                            while (!tempPriorityHeap->heapIsEmpty()) {
                                Request r;
                                tempPriorityHeap->minHeapByRequestTimeDelete(r);
                                priorityHeap->heapInsert(r);
                            }
                        }
                        //delete tempPriorityHeap;
                    } else {
                        Request r;
                        this->priorityHeap->heapDelete(r);

                        if (getCurrentTime() > r.getRequestTime()) {
                            immediateDelay = (getCurrentTime() - r.getRequestTime());
                            addDelay(immediateDelay);
                        }

                        remainingNumberOfRequests--;
                        computerArray[i].assign(r, immediateDelay);
                        cout << "Computer " << computerArray[i].getComputerId() << " takes request " << r.getId() << " at ms " << getCurrentTime() << " (wait: " << immediateDelay << " ms)" << endl;
                    }


                }
            }
        }

        // Checking if any computer is finished or not (if finished free them)
        for (int i = 0; i < numberOfComputers; ++i) {
            computerArray[i].checkIfFinished(getCurrentTime());
        }

        moveOn();
    }
    delete computerArray;
    return calculateAvgWaitingTime();
}

int Simulator::optimize(double avgTime) {
    int numberOfOptimumComputers = 1;               // 1 yap
    double optimumAvgTime = 100000000;

    while (avgTime < optimumAvgTime) {
        optimumAvgTime = simulate(numberOfOptimumComputers);
        numberOfOptimumComputers++;
    }
    numberOfOptimumComputers--;
    return numberOfOptimumComputers;
}

