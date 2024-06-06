/**
* Title: AVL Trees and Heaps
* Author : Ahmet Furkan KIZIL
* ID: 22203112
* Section : 3
* Homework : 2
* Description : AVL Trees and Heaps with required implementations
*/

#ifndef CS202_HW2_COMPUTER_H
#define CS202_HW2_COMPUTER_H

#include "Request.h"
#include <iostream>
using namespace std;

class Computer {
public:
    Computer(int id);
    Computer();
    int getComputerId();
    bool isAvaliable();
    int getStartTime();
    int getWorkTime();

    void assign(Request request, int possibleDelay);
    void free();
    void checkIfFinished(int currentTime);

private:
    int id;
    bool availability;
    int startTime;
    int workTime;
    int possibleDelay;
};


#endif //CS202_HW2_COMPUTER_H
