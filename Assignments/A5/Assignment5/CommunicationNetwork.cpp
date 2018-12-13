//Ali Ostlund
//Assignment 5
//Hoenigman
//Helped by: Alex Whitfield, Denver Chernin



#include "CommunicationNetwork.h"
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>

using namespace std;

CommunicationNetwork::CommunicationNetwork()
{
  head = NULL;
  tail = NULL;
}

CommunicationNetwork::~CommunicationNetwork()
{
    cout<< "Goodbye!" << endl;
    deleteNetwork();
}

//delete entire network
void CommunicationNetwork::deleteNetwork()
{
  City *currentCity= new City;
  City *temp = head;
  currentCity = temp;
  if (head == NULL || tail == NULL)
  {
    return;
  }
  while (currentCity->next!= NULL)
  {
    temp = currentCity->next;
    cout << "deleting " << currentCity->cityName << endl;
    delete currentCity;
    currentCity = temp;
    currentCity->previous = NULL;
    head = currentCity;
  }
  cout << "deleting " << currentCity->cityName << endl;
  head = NULL;
}

//delete one city
void CommunicationNetwork::deleteCity(string dCity)
{
  City *currentCity = head;
  bool done = false;
  while (currentCity)
  {
    if (currentCity->cityName == dCity)
    {
      if (currentCity == head)
      {
        head = currentCity->next;
        delete currentCity;
        done = true;
      } else if (currentCity == tail)
      {
        currentCity->previous->next=NULL;
        tail = currentCity->previous;
        delete currentCity;
        done = true;
      } else {
        currentCity->previous->next = currentCity->next;
        currentCity->next->previous = currentCity->previous;
        delete currentCity;
        done = true;
      }
    } else {
      currentCity = currentCity->next;
    }
  }
  if (!done)
  {
    cout << dCity << "not found" << endl;
  }
}

void CommunicationNetwork::transmitMsg(char * filename)
{
  if (head == NULL)
  {
      cout << "Empty List" <<endl;
  }
  ifstream message;
  message.open(filename);
  string word;
  City *sending = head;
  City *receiving = head->next;
  //loop until end of message file
  while (message>>word)
    {
    sending = head;
    sending->message = word;
    receiving = sending->next;

    cout << sending->cityName << " received " << sending->message << endl;
    while (receiving != NULL)
        {
        receiving->message = word;
        sending->message = "";
        cout << receiving->cityName << " received " << receiving->message << endl;
        sending = receiving;
        receiving = receiving->next;
        }

    receiving = sending->previous;
    while (receiving!=NULL)
        {
        receiving->message = word;
        sending->message = "";
        cout << receiving->cityName << " received " << receiving->message << endl;
        sending = receiving;
        receiving = receiving->previous;
        }
    }
}

//print
void CommunicationNetwork::printNetwork()
{
  City *currentCity = head;
  if (currentCity==NULL)
  {
    cout << "===CURRENT PATH===" << endl;
    cout << "NULL" << endl;
    cout << "==================" << endl;
  } else {
    cout << "===CURRENT PATH===" << endl;
    cout << "NULL <- " << currentCity->cityName;
    currentCity=currentCity->next;
    while (currentCity != NULL)
    {
      cout << " <-> " <<currentCity->cityName;
      currentCity = currentCity->next;
    }
  cout << " -> NULL" << endl;
  cout << "==================" << endl;
  }
}

void CommunicationNetwork::buildNetwork()
{
  string cities[10] = {"Los Angeles", "Phoenix", "Denver", "Dallas", "St. Louis", "Chicago", "Atlanta", "Washington, D.C.", "New York", "Boston"};
  addCity("First",cities[0]);
  for (int i = 1; i < 10; i++)
  {
      addCity(cities[i-1],cities[i]);
  }
  printNetwork();
}

void CommunicationNetwork::addCity(string prevcity, string newcity)
{
  City *newc = new City(newcity, NULL, NULL, "");
  City *currentCity = head;
  if (head == NULL)
  {
    head = newc;
    tail=newc;
  } else if (prevcity == "First")
  {
    newc->next = currentCity;
    currentCity->previous = newc;
    head = newc;
  } else {
    while (currentCity != NULL)
    {
      if (currentCity->cityName == prevcity)
      {
        newc->next = currentCity->next;
        newc->previous = currentCity;
        currentCity->next = newc;
        if (newc->next == NULL)
        {
          tail = newc;
        }
        return;
      } else {
          currentCity = currentCity->next;
      }
    }
  }
}
