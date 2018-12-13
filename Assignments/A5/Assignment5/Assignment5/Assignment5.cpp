//Alison Ostlund
//Assignment 5
//Hoenigman

#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include "CommunicationNetwork.h"

using namespace std;

int main(int argc, char* argv[])
    {
    char* fileName = argv[1];
    string newCity= "";
    string oldCity = "";
    string dCity = "";
    CommunicationNetwork Network = CommunicationNetwork();
    string option = "";
    while(option != "7"){
        cout << "======Main Menu======"<< endl;
        cout << "1. Build Network"<< endl;;
        cout << "2. Print Network Path"<< endl;
        cout << "3. Transmit Message Coast-To-Coast-To-Coast"<< endl;
        cout << "4. Add City"<< endl;
        cout << "5. Delete City" << endl;
        cout << "6. Clear Network"<< endl;
        cout << "7. Quit"<< endl;
        getline(cin, option);
        if (option =="1")
        {
            Network.buildNetwork();
        }
        else if(option == "2")
        {
            Network.printNetwork();
        }
        else if (option =="3")
        {
            Network.transmitMsg(fileName);
        }
        else if (option =="4")
        {
            cout<<"Enter a city name: "<< endl;
            getline(cin, newCity);
            cout<< "Enter a previous city name: "<< endl;
            getline(cin, oldCity);
            Network.addCity(oldCity, newCity);
        }
        else if (option == "5")
        {
            cout<<"Enter a city name: "<<endl;
            getline(cin, dCity);
            Network.deleteCity(dCity);
        }
        else if (option == "6")
        {
            Network.deleteNetwork();
        }

        }
}
