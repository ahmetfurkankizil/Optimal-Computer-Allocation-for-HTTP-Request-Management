/**
* Title: AVL Trees and Heaps
* Author : Ahmet Furkan KIZIL
* ID: 22203112
* Section : 3
* Homework : 2
* Description : AVL Trees and Heaps with required implementations
*/

#ifndef CS202_HW2_SIMULATOR_H
#define CS202_HW2_SIMULATOR_H
#include <iostream>
#include "Heap.h"
using namespace std;


class Simulator {
public:
    Simulator(string fileName, double avgWaitingTime);
    ~Simulator();
    int getCurrentTime();
    void moveOn();
    double calculateAvgWaitingTime();
    double simulate(int numberOfComputers);
    double simulateWithPrinting(int numberOfComputers);
    void addDelay(int delay);
    int optimize(double avgTime);


private:
    string fileName;
    int currentTime;
    int numberOfRequests;
    double avgWaitingTime;
    Heap* priorityHeap;
    Computer* computerArray;
    int totalDelay;
    double currentAvgWaitingTime;

};


#endif //CS202_HW2_SIMULATOR_H
