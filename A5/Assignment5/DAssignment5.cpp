//
//  Assignment5.cpp
//  CommunicationNetwork
//
//  Created by JJ Ostlund on 2/19/17.
//  Copyright © 2017 Ali Ostlund. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include <fstream>
#include "CommunicationNetwork.hpp"

using namespace std;


// MAIN PROGRAM

int main(int argc, const char * argv[]) {
    
    string filename, sMessage;
    ifstream cityFile;
    CommunicationNetwork myNetwork;
    
    
    // ***** open file ******** //
    //cout << "%d" << argc;
    if (argc != 2) {
        cout << "missing file name" << endl;
        return -1;
    }
    
    filename = argv[1];
    // cout << filename << endl;  // debug
    
    cityFile.open(filename);
    
    if (cityFile.fail())
    {
        cout << "File open error!" << endl;
        return -1;
    } else {
       // cout << "File opened ok" << endl;  // debug
    }
    
    // ***** Load Message from the File ***** //
    getline(cityFile, sMessage);
    if (sMessage.empty() ) {
        cout << "Empty File" << endl;
    }
    //cout << sMessage << endl;   // debug
    
    // ***** Initialize Cities ***** //
    // INSERT MENU HERE
    
    
    

    // DEBUGGING STUFF BELOW
    
    // ***** Initialize Cities ***** //
    myNetwork.buildNetwork();
    
    // **** add City test ***** //
     myNetwork.addCity("Denver", "Boulder");
     myNetwork.addCity("First", "Hawaii");
     myNetwork.deleteCity("Dallas");
    
    // **** send message **** //
    myNetwork.transmitMsg(sMessage);
    
    // ***** Print Cities ***** //
    myNetwork.printNetwork();
    
    // ****** Delete Network ******* //
    myNetwork.deleteNetwork();
    
    // VERIFY NOTHING BLOWS UP until network built
/*
    // ***** Print Cities ***** //
    myNetwork.printNetwork();
    
    // **** add City test ***** //
    myNetwork.addCity("Denver", "Boulder");
    myNetwork.addCity("First", "Hawaii");
    myNetwork.deleteCity("Dallas");
    
    // **** send message **** //
    myNetwork.transmitMsg(sMessage);
    
    // ***** Pring Cities ***** //
    myNetwork.printNetwork();
    
    // DO IT AGAIN
    
    // ***** Initialize Cities ***** //
    myNetwork.buildNetwork();
    
    // **** add City test ***** //
    myNetwork.addCity("Denver", "Boulder");
    myNetwork.addCity("First", "Hawaii");
    myNetwork.deleteCity("Dallas");
    
    // **** send message **** //
    myNetwork.transmitMsg(sMessage);
    
    // ***** Pring Cities ***** //
    myNetwork.printNetwork();
*/
    
    
    return 0;
    
}
