//Alison Ostlund // A6
#ifndef QUEUE_H
#define QUEUE_H
#include <iostream>

class Queue
{
    public:
        Queue(int qs);
        ~Queue();
        //circular queue methods
        void enqueue(std::string word);
        void dequeue(); //should send through network, call transmit msg
        void printQueue();
        bool queueIsFull(); //send when full
        bool queueIsEmpty(); //send when empty

    protected:
    private:
        int queueSize;
        int queueHead;
        int queueTail;
        int queueCount;
        std::string *arrayQueue;
};

#endif // QUEUE_H
