//Alison Ostlund
//Final Project
#include "HashTable.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <math.h>
using namespace std;

HashTable::HashTable(int tableSize){
	data = new Player*[tableSize]; // array of players with tablesize in main
	for(int i = 0; i < tableSize; i++){
		data[i] = NULL; //sets index's of arrays to NULL
	}
    TableSize = tableSize;
    openCollisions= 0;
    chainCollisions = 0;
    chainSearch = 0;
    openSearch = 0;
}

HashTable::~HashTable(){
    delete data;
}

int HashTable::hashFunction(string firstName, string lastName){
	unsigned int code = 0; //Hash code before mod
    unsigned int seed = 101;
	for(int i = 0; i < firstName.length(); i++){
        code = code * seed + firstName[i];   // ASCII values of first name added
	}
	for(int j = 0; j < lastName.length(); j++){
        code = code * seed + lastName[j];//ASCII values of last name added
	}
	return code % TableSize; //hash code returned
}

bool HashTable::isNULLChain(Player *p){
    int pos = p->hashCode; //pos = the index of array where new player is placed

    if(data[pos] == NULL){ //if array place = NULL
        return true;
    } else {
        return false; //Not NULL
    }
}
bool HashTable::isNULLLinear(Player *p){
    int pos = p->hashCode; //pos = the index of array where new player should be placed
    if(data[pos] == NULL){ //if array place = NULL
        return true;
    } else {
        return false; // not NULL
    }
}


void HashTable::insertChaining(Player *node){
    //linked listed so pointers must be set
    node->next = NULL;
    bool blank = isNULLChain(P); // checks if spot in array is blank
    if(blank){
        node->previous = NULL; //sets node to head of ll
        data[node->hashCode] = node; //adds player to the assigned index in array

    } else{
        Player *temp = data[node->hashCode]; //temp pointer to find next space in ll
        chainCollisions++;  // FIX
        while(temp->next != NULL){ //find where to put the new player node
            temp = temp->next;
            chainSearch++;
        }
        temp->next = node; //assign next/previous pointers for all players
        node->next = NULL;
        node->previous = temp;
    }

}


int HashTable::findChaining(string &fname, string &lname) {  // return search count
    int sCount = 0;
    int hashCode = 0;
    bool bFound = false;

    hashCode = hashFunction(fname, lname);
    Player *temp = data[hashCode];

    while (temp != NULL) {
        if ((temp->firstName == fname) && (temp->lastName == lname)) {
            bFound=true;
            break;
        }
        temp = temp->next;
        sCount++;  // search count
    }

    if (bFound==true) {
        return sCount;
    } else {
        return -1;
    }
}


void HashTable::insertOpenAddress(Player *P){
    //No ll in this part so will ignore setting the next and previous pointers
    bool N = isNULLLinear(P);
    if(N){
        data[P->hashCode] = P;
    } else{

        int iter = 1;
        openCollisions++;
        while((data[P->hashCode + iter] != NULL) && (P->hashCode + iter <= TableSize)){
            iter++;
            openSearch++;
        }
        int index = P->hashCode + iter;
        data[index] = P;
    }

}

int HashTable::findOpenAddress(string &fname, string &lname) {  // return search count
    int sCount = 0;
    int iCount = 0;
    int hashCode = 0;
    bool bFound = false;

    hashCode = hashFunction(fname, lname);
    iCount = hashCode;  // start searching in array from hashcode index, down...
    Player *temp = data[iCount];

    while (iCount < TableSize) {
        if ((temp->firstName == fname) && (temp->lastName == lname)) {
            bFound=true;
            break;
        }
        sCount++;  // conflicts
        iCount++;  // index
        temp = data[iCount];
    }

    if (bFound==true) {
        return sCount;
    } else {
        return -1;
    }
}


int HashTable::getOpenCollisions(){
    return openCollisions;
}
int HashTable::getOpenSearchCount(){
    return openSearch;
}
int HashTable::getChainCollisions(){
    return chainCollisions;
}
int HashTable::getTableSize(){
    return TableSize;
}
int HashTable::getChainSearchCount(){
    return chainSearch;
}




