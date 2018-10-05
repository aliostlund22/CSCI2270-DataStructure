//
//  uniqueWords.hpp
//  HungerGames1
//
//  Created by JJ Ostlund on 2/1/17.
//  Copyright © 2017 Ali Ostlund. All rights reserved.
//

#ifndef uniqueWords_hpp
#define uniqueWords_hpp


#include <iostream>
using namespace std;

class uniqueWords {
    
private:
    int wordcount=0, uniquecount=0, notuniquecount=0, doublecount=0;

    
    struct uniqueWord
    {
        string word;
        int count;
    };
    uniqueWord *wordArray = NULL;
    int arraysize=100; // start size
    
    string skip [50] = {"the", "you", "one", "be", "do", "all", "to", "at", "would", "of", "this", "there", "and", "but", "their", "a", "his", "what", "in", "by", "so", "that", "from", "up", "have", "they", "out", "i", "we", "if", "it", "say", "about", "for", "her", "who", "not", "she", "get", "on", "or", "which", "with", "an", "go", "he", "will", "me", "as", "my"};

    
public:
    uniqueWords();
    virtual ~uniqueWords();
    
    int loadFile(ifstream &fileName);
    int processFile();
    void printArray();
    void printSortedArray(int topWords);
    bool isUnwanted(string word);
    bool insertWord (string word);
    
    int doubleArray();
    
};


#endif /* uniqueWords_hpp */
