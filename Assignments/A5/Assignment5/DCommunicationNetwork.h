//
//  CommunicationNetwork.hpp
//  CommunicationNetwork
//
//  Created by Ali Ostlund on 2/19/17.
//


#ifndef COMMUNICATIONNETWORK_H
#define COMMUNICATIONNETWORK_H

#include <iostream>
#include <fstream>

using namespace std;


struct City{
    string cityName;
    string message;
    City *next;
    City *previous;
    
    City(){}; // default constructor
    
    City(string initName, City *initNext, City *initPrevious, string initMessage)
    {
        cityName = initName;
        next = initNext;
        previous = initPrevious;
        message = initMessage;
    }
    
};


class CommunicationNetwork
{
public:
    CommunicationNetwork();
    ~CommunicationNetwork();
    
    void addCity(string previousCity, string newCity);
    void buildNetwork();
    //void transmitMsg(char *); //this is like a string
    void transmitMsg(string sFullMessage);
    void printNetwork();
    void deleteCity(string deleteCity);
    void deleteNetwork();
    
protected:
private:
    City *head = NULL;
    City *tail = NULL;
    
    
    int iCount = 10;
    string  startCities [10] = {"Los Angeles", "Phoenix", "Denver", "Dallas", "St. Louuis", "Chicago", "Atlanta", "Washington D.C.", "New York", "Boston"};
    
    
};

#endif // COMMUNICATIONNETWORK_H


