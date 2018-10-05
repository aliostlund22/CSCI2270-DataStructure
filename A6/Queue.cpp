//  Queue.cpp
//Alison Ostlund A6

#include <stdio.h>
#include <iostream>
#include "Queue.h"
#include <sstream>
using namespace std;


Queue::Queue(int qs)
{
    queueSize = qs;
    arrayQueue = new string[queueSize];
    queueHead = 0;
    queueTail = 0;
    queueCount= 0;

}

Queue::~Queue()
{
    cout<< "Goodbye!" << endl;
    //free memory
}

void Queue::enqueue(std::string word)
{

    if ( !queueIsFull() )
    {
        arrayQueue[queueTail] = word;
        queueCount++;
        queueTail++;

        cout << "E: " << word <<endl;
        cout << "H: " << queueHead << endl;
        cout << "T: " << queueTail << endl;
    }
    else
    {
        cout << "Queue is full" <<endl;
    }


}

void Queue::dequeue()
{
    if(!queueIsEmpty())
    {
        cout << "H: " << queueHead <<endl;
        cout << "T: " << queueTail <<endl;
//        cout << "word: " << arrayQueue[queueTail] <<endl; // fix
        cout << "word: " << arrayQueue[queueHead++] <<endl;

    }
    else
    {
        cout << "Queue is empty"<<endl;
    }
}

void Queue::printQueue()
{
    if (!queueIsEmpty())
    {

        for( int i = queueHead; i < queueTail; i++)
        {
            cout<< i <<": "<<arrayQueue[i]<<endl; //where current is the index
        }
    }
    else
    {
        cout << "Queue is empty" << endl;
    }

}


bool Queue::queueIsFull()
{

    if (queueCount < queueSize)
        return false;
    else
        return true;



}

bool Queue::queueIsEmpty()
{

    if (queueCount > 0)
        return false;
    else
        return true;


}

