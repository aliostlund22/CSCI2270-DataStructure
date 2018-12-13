//
//  CommunicationNetwork.cpp
//  CommunicationNetwork
//
//  Created by Ali Ostlund on 2/19/17.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include "CommunicationNetwork.hpp"

using namespace std;


// COMMUNICATIONS NETWORK CLASS METHODS

CommunicationNetwork::CommunicationNetwork() {

    head = new City();
    tail = new City();
    
    if (head == NULL || tail == NULL) {
        cout << "Error: Initialization failed" << endl;
    }
    
    head->next = tail->next = NULL;
    head->previous = tail->previous = NULL;

}

CommunicationNetwork::~CommunicationNetwork() {

    if (head) delete head;
    if (tail) delete tail;
    
}


void CommunicationNetwork::buildNetwork() {
   
    City *next = NULL;
    
    City *current = head;
    for (int i=0; i<iCount; i++) {
    
        next = new City;
        current->next = next;
        
        next->cityName = startCities[i];
        next->previous = current;
        next->next = NULL;
        current = next;
        
    }
    next->next = tail;
    tail->previous = next;  // fix

}

void CommunicationNetwork::printNetwork() {

    City *next = head;
    
    if (head->next == NULL) return;  // network not built
    
    while (next->next != NULL) {
        if (!next->cityName.empty()) {
            
            if (next->previous->cityName.empty()) {
                cout << " <- ";
            } else {
                cout << " <->  ";
            }
            cout << next->cityName;
            
        } else {
            cout << "NULL";
        }
            next = next->next;
    }
    cout << " -> NULL" << endl;

}



void CommunicationNetwork::addCity(string prevCity, string newCity)
{
    City *current;
    current = head;

    City *city1 = new City;
    city1->cityName = newCity;
    city1->message = "";
    city1->next = NULL;
    city1->previous = NULL;
    
    if (head->next == NULL) return;  // network not built
    
    if(prevCity == "First") {   // added this
        
        city1->next = head->next;
        city1->previous = head;
        
        head->next->previous = city1;
        head->next = city1;
 
    } else {
    
        while(current != NULL){
            if(current->cityName == prevCity){
                
                city1->next = current->next;
                city1->previous = current; // fix
                
                current->next->previous = city1; // fix
                current->next = city1;
                
                break; // fix
            }
            current = current->next;
        }
    
    }
}

void CommunicationNetwork::deleteCity(string deleteCity)
{
    City *current;
    current = head;
    
    if (head->next == NULL) return;  // network not built
    
    
    while(current != NULL){
        if(current->cityName == deleteCity){
            
            current->previous->next = current->next;
            current->next->previous = current->previous;
            
            delete current;
            break;
        }
        current = current->next;
    }

}

void CommunicationNetwork::transmitMsg(string sFullMessage) {
    
    City *current;
    string sMessage = sFullMessage;
    
    if (head->next == NULL) return;  // network not built
    
 
/*
    // Use stream to get word by word from string
    istringstream iss(sMessage);  // included sstream
    string word;
    
    while (iss >> word) {
        
        cout << word << endl;
        
    }
 */
    
    // sMessage = "hello";  // debug
    
    // Send message from the head down
    current = head->next;
    while(current != NULL){
        cout << current->cityName << " received " << sMessage << endl;
        current = current->next;
        if (current->next == NULL) break; // skip the tail
    }

    
    // Send the message from the tail back
    current = tail->previous;
    while(current != NULL){
        cout << current->cityName << " received " << sMessage << endl;
        current = current->previous;
        if (current->previous == NULL) break; // skip the head
    }
    
} //this is like a string



void CommunicationNetwork::deleteNetwork()
{
    City *pNext = NULL;
    City *pCurrent = head->next;  // skip head
    
    while ( pCurrent != NULL )
    {
        pNext = pCurrent->next;  // save next
        delete pCurrent;  // delete current
        pCurrent = pNext;
        if (pCurrent->next == NULL) break;  // skip tail
    }
    
    
    head->next = tail->next = NULL;
    head->previous = tail->previous = NULL;
}




