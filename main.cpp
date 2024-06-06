/**
* Title: AVL Trees and Heaps
* Author : Ahmet Furkan KIZIL
* ID: 22203112
* Section : 3
* Homework : 2
* Description : AVL Trees and Heaps with required implementations
*/

#include <iostream>
#include <fstream>

#include "Simulator.h"

int main(int argc, char** argv) {
    if (argc < 3) {
        cerr << "Usage: " << argv[0] << " <filename> <avgWaitingTime>" << endl;
        return 1;
    }

    string filename = argv[1];
    double avgWaitingTime = stod(argv[2]);

    Simulator simulator(filename, avgWaitingTime);
}

