//Alison Ostlund //A4
#include "CommunicationNetwork.h"
#include <iostream>
#include <fstream>
#include <sstream>

CommunicationNetwork::CommunicationNetwork(){
    head = NULL;
    tail = NULL;
}
CommunicationNetwork::~CommunicationNetwork(){
    std::cout<<"Goodbye!"<<std::endl;
}

void CommunicationNetwork::buildNetwork(){
    std::string Cities[10] = {"Los Angeles","Phoenix","Denver","Dallas","St. Louis","Chicago","Atlanta","Washington, D.C.","New York","Boston"};
    head = new City;
    head->cityName = Cities[0];
    head->message = "";
    City *temp1 = head;
    for(int i = 1; i < 10; i++){
        City *temp2 = new City;
        temp2->cityName = Cities[i];
        temp2->message = "";
        temp2->next = NULL;
        temp1->next = temp2;
        temp1 = temp2;
    }
    printNetwork();
}

void CommunicationNetwork::addCity(std::string prevCity, std::string newCity){
    City *current = new City;
    current = head;
    City *city1 = new City;
    city1->cityName = newCity;
    city1->message = "";
    city1->next = NULL;
    while(current != NULL){
        if(current->cityName == prevCity){
                city1->next = current->next;
                current->next = city1;

        }
        current = current->next;
    }
}

void CommunicationNetwork::transmitMsg(char *fileName){
    std::ifstream dataFile;
    dataFile.open(fileName);
    std::string word;
    if(dataFile.good()){
        while(dataFile>>word){
            City *temp = head;
            temp->message = word;
            while((temp)){
                std::cout<<temp->cityName<<" received "<<word<<std::endl;
                //temp->next->message = temp->message;
                //temp->message = "";
                temp = temp->next;
            }
        }
    }
}

void CommunicationNetwork::printNetwork(){
    City *temp = head;
    std::cout<<"===CURRENT PATH==="<<std::endl;
    while(temp != NULL){
        std::cout<<temp->cityName<< " -> ";
        temp = temp->next;
    }
    std::cout<<"NULL"<<std::endl;
    std::cout<<"=================="<<std::endl;
}
