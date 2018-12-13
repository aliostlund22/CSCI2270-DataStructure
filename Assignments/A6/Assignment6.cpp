//Alison Ostlund
//Assignment6
//  main.cpp

#include <stdio.h>
#include <iostream>
#include "Queue.h"
#include <sstream>


using namespace std;

int main()
{

    //cout<<"HELLO"<<endl;

    Queue wQueue = Queue(10);
    string choice = "";
    string input = "";
    string sentence = "";

    while (choice != "5")
    {
        cout <<"======Main Menu=====" << endl;
        cout <<"1. Enqueue word" <<endl;
        cout <<"2. Dequeue word" <<endl;
        cout <<"3. Print queue" <<endl;
        cout <<"4. Enqueue sentence" <<endl;
        cout <<"5. Quit" <<endl;
        cin >> choice;
        if (choice =="1")
        {
            cout <<"word: ";
            cin >> input;
            wQueue.enqueue(input);
            input.clear();
        }
        else if(choice == "2")
        {
            wQueue.dequeue();
        }
        else if (choice =="3")
        {
            wQueue.printQueue();
        }
        else if (choice =="4")
        {

            cout << "sentence: ";
            cin.ignore();
            std::getline(cin, sentence);

             //cout << "entered " << sentence << endl;

            //do code here to split and enqueue sentence

            istringstream iss(sentence);  // use sstream to parse the word
            while (iss >> input) {
                wQueue.enqueue(input);
            }
            sentence.clear();

        }

    }



}
