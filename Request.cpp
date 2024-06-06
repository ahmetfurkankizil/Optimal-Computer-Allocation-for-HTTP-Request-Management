/**
* Title: AVL Trees and Heaps
* Author : Ahmet Furkan KIZIL
* ID: 22203112
* Section : 3
* Homework : 2
* Description : AVL Trees and Heaps with required implementations
*/

#include "Request.h"

Request::Request(int id, int priority, int requestTime, int processTime) {
    this->id = id;
    this->priority = priority;
    this->requestTime = requestTime;
    this->processTime = processTime;
}

Request::Request() {
    this->id = 0;
    this->priority = 0;
    this->requestTime = 0;
    this->processTime = 0;
}

int Request::getRequestTime() {
    return requestTime;
}

int Request::getProcessTime() {
    return processTime;
}

int Request::getPriority() {
    return priority;
}

int Request::getId() {
    return id;
}

