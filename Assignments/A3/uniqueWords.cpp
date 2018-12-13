//
//  uniqueWords.cpp
//  HungerGames1
//
//  Copyright © 2017 Ali Ostlund. All rights reserved.
//

#include "uniqueWords.hpp"
#include <iostream>
#include <fstream>
using namespace std;


uniqueWords::uniqueWords() {}
uniqueWords::~uniqueWords() {}


int uniqueWords::loadFile(ifstream &fileName) {
    
    string word;
    // initialize wordArray
    
    wordArray = new uniqueWord[arraysize];
    if (wordArray == NULL) {
        // cout << "Memory error" << endl;
        return -1;
    }
    
    // **** process word file ******* //
    while (fileName >> word)
    {
        // remove unwanted words
        if (isUnwanted(word) == false) {
        
        // check for duplicate
            insertWord(word);
            wordcount++;
    
        }
                if (uniquecount == arraysize-1) {
            if (doubleArray() < 0) return -1;
        }
    }
    
    return 0;
    
}

bool uniqueWords::isUnwanted(string word) {
   
    for (int i=0; i<50; i++) {
        if (word == skip[i])
            return true;
    }
    
    return false; // not on the list
    
}

bool uniqueWords::insertWord (string word) {
    
    int iCompare=0;
    uniqueWord tempWord1, tempWord2;
    
    if (uniquecount == 0) { // insert first word
        wordArray[0].word = word;
        wordArray[0].count = 1;
        uniquecount++;
        return true;
    }
    for (int i=0; i<uniquecount; i++)  {  // look for match in current array
        
        iCompare = word.compare(wordArray[i].word);
        
        if (iCompare == 0) { // match found
            
            wordArray[i].count++;
            return false; // done
            
        } else if (iCompare < 0) { // less and unique, so insert and shift
            
            // replace
            tempWord1=wordArray[i]; // save current position
            wordArray[i].word = word; // insert new word
            wordArray[i].count= 1;
            
            // shift down  FIX FIX FIX
            for (int j=i+1; j<arraysize; j++) {  // shift down
                    
                tempWord2=wordArray[j]; // save next
                wordArray[j] = tempWord1; // set current
                tempWord1=tempWord2;  // next
                
            }
            uniquecount++;
            return true;  // done
            
        }
    }
    
   // Not found, so unique and add to the end
    wordArray[uniquecount].word = word;
    wordArray[uniquecount].count= 1;
    uniquecount++;
    
    return true;
}

int uniqueWords::doubleArray() {
    
    uniqueWord *wordArray2 = wordArray;
    int i = 0;
    
    wordArray = new uniqueWord[arraysize*2];
    if (wordArray == NULL) return -1;  // allocation failed
    
    while (i<arraysize) {
        wordArray[i] = wordArray2[i];
        i++;
    }
    
    arraysize*=2;
    doublecount++;
    // free(wordArray2[]);
    delete[] wordArray2;
    return 0;
    
}

void uniqueWords::printSortedArray(int topWords) {
    int i=0, j=0;
    uniqueWord maxWord1, maxWord2;
    
    maxWord1.count=0; // get started
    maxWord2.count=99999;
    
    while (i< topWords) {

        for (j=0; j<uniquecount; j++) {
            
            if (wordArray[j].count > maxWord1.count && wordArray[j].count < maxWord2.count) {
                maxWord1 = wordArray[j];
            }
        }
        
        cout << maxWord1.count << " - " << maxWord1.word <<endl;
        maxWord2.count = maxWord1.count;
        maxWord1.count=0;
        i++;
    }


    cout << "#" <<endl;
    cout << "Array Doubled: " << doublecount <<endl;
    cout << "#" <<endl;
    cout << "Unique non-common words: " << uniquecount << endl;
    cout << "#" <<endl;
    cout << "Total non-common words: " << wordcount << endl << endl;
}


void uniqueWords::printArray() {
    
    int i=0;
    cout << "---------------------------------" << endl;

    while (i<uniquecount) {
        cout <<  wordArray[i].count << " " << wordArray[i].word << endl;
        i++;
    }
    //cout << "Total words: " << wordcount << endl;
    cout << "Array doubled: " << doublecount << endl; // 7
    cout << "Unique non-common words: " << uniquecount << endl; // 7682
    cout << "Total non-common words: " << notuniquecount << endl; // "59157
    cout << "---------------------------------" << endl;

}

