/**
* Title: AVL Trees and Heaps
* Author : Ahmet Furkan KIZIL
* ID: 22203112
* Section : 3
* Homework : 2
* Description : AVL Trees and Heaps with required implementations
*/

#include "Computer.h"

Computer::Computer(int id) {
    // Initialising computer objects
    this->id = id;
    this->availability = true;
    this->startTime = 0;
    this->workTime = 0;
    this->possibleDelay = 0;
}

Computer::Computer() {}


int Computer::getComputerId() {
    return id;
}

bool Computer::isAvaliable() {
    return availability;
}

int Computer::getStartTime() {
    return startTime;
}

int Computer::getWorkTime() {
    return workTime;
}

void Computer::assign(Request request, int possibleDelay) {
    this->availability = false;
    this->startTime = request.getRequestTime();
    this->workTime = request.getProcessTime();
    this->possibleDelay = possibleDelay;
}

void Computer::free() {
    this->availability = true;
    this->startTime = 0;
    this->workTime = 0;
}

void Computer::checkIfFinished(int currentTime) {
    if(!isAvaliable()) {
        if((currentTime - this->startTime) == (workTime+possibleDelay)) {
            free();
            //cout << "Computer " << id << " is now free at " << currentTime << " ms." << endl;
        }
    }
}
