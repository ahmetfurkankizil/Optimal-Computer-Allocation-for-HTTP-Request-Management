/**
* Title: AVL Trees and Heaps
* Author : Ahmet Furkan KIZIL
* ID: 22203112
* Section : 3
* Homework : 2
* Description : AVL Trees and Heaps with required implementations
*/

#ifndef CS202_HW2_REQUEST_H
#define CS202_HW2_REQUEST_H


class Request {
public:
    int id;
    int priority;
    int requestTime;
    int processTime;
    Request();
    Request(int key, int priority, int requestTime, int processTime);
    int getRequestTime();
    int getId();
    int getPriority();
    int getProcessTime();
};


#endif //CS202_HW2_REQUEST_H
