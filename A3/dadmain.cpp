//
//  main.cpp
//  HungerGames1
//
//
//  Copyright © 2017 Ali Ostlund. All rights reserved.
//
#include <iostream>
#include <fstream>
#include <iomanip>
#include <stdlib.h>


#include "uniqueWords.hpp"

using namespace std;


int main(int argc, const char * argv[]) {
    // insert code here...
    
    string filename, word;
    ifstream wordfile;
    int topWords = 0;
    uniqueWords myWords;
    
    // ***** open file ******** //
    //cout << "%d" << argc;
    if (argc != 3) {
        cout << "missing file name" << endl;
        return -1;
    } 
    filename = argv[1];
    topWords = atoi(argv[2]);
    // cout << filename << endl;
    //datafile.open("/Users/jostlund/Documents/Temp/Code/CraigsList/messageBoard.txt"); // temporary
    wordfile.open(filename);
    
    if (wordfile.fail())
    {
        cout << "File open error!" << endl;
        return -1;
    } else {
        cout << "File opened ok" << endl;
    }
    
    myWords.loadFile(wordfile);
    myWords.printSortedArray(topWords);

    
    return 0;
    
}
