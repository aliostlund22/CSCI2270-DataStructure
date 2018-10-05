//Alison Ostlund A4
#include <iostream>
#include "CommunicationNetwork.h"
#include <fstream>
#include <sstream>

using namespace std;

int main(int argc, char* argv[])
{
    char* file = argv[1];
    CommunicationNetwork city = CommunicationNetwork();
    string num = "";
    string newCity, prevCity = "";
    while ( num != "5")
    {
		cout <<	"======Main Menu======"	<<endl;					
		cout <<	"1. Build Network"<<	endl;					
		cout <<	"2. Print Network Path"	<<	endl;					
		cout <<	"3. Transmit Message Coast-To-Coast" <<	endl;					
		cout <<	"4. Add City"<<	endl;	
		cout <<	"5. Quit"<<	endl;	
        getline(cin, num);
        if (num == "1")
        {
            city.buildNetwork();
        }
        else if (num == "2")
        {
            city.printNetwork();
        }
        else if (num == "3")
        {
            city.transmitMsg(file);
        }
        else if (num == "4")
        {
            cout << "Enter a city name: " <<endl;
            getline(cin, newCity);
            cout<< "Enter a previous city name: "<<endl;
            getline(cin, prevCity);
            city.addCity(prevCity, newCity);
        }


    }
}
