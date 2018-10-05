//Alison Ostlund
//Final Project
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;
#include "HashTable.h"

int main(int argc, const char * argv[]){

	ifstream dataFile;
    string filename;
    int tableSize=5147; //default table size

    if (argc < 2) {  //support 3 args including table size
        cout << "missing file hame" << endl;
        return -1;
    }
    if (argc == 3) {
        tableSize= atoi(argv[2]);
    }

    filename = argv[1];
    dataFile.open(filename);
	if(!dataFile.is_open()){
		cout<<"Failed"<<endl;
	}

    // /////// build tables ///////////////////
    int lineCount = 0;
    int userinput = 0;
    string line = "";

    string yr, team, league, ID, salary, FName, LName, birth, country, weight, height, bat, throws;



    HashTable chainHashTable(tableSize);
    HashTable openHashTable(tableSize);

    while(getline(dataFile, line)){
        int hashCode = 0;
        if(lineCount == 0){

        } else {
            stringstream ss(line);
            getline(ss, yr, ',');
            getline(ss, team, ',');
            getline(ss, league, ',');
            getline(ss, ID, ',');
            getline(ss, salary, ',');
            getline(ss, FName, ',');
            getline(ss, LName, ',');
            getline(ss, birth, ',');
            getline(ss, country, ',');
            getline(ss, weight, ',');
            getline(ss, height, ',');
            getline(ss, bat, ',');
            getline(ss, throws, ',');

            // CHAIN INSERT
            hashCode = chainHashTable.hashFunction(FName, LName);
            Player *playerc = new Player(hashCode, yr, team, league, ID, salary, birth, country, weight, height, bat, throws, FName, LName);
            chainHashTable.insertChaining(playerc);

            // OPEN INSERT
            hashCode = openHashTable.hashFunction(FName, LName);
            Player *playero = new Player(hashCode, yr, team, league, ID, salary, birth, country, weight, height, bat, throws, FName, LName);
            openHashTable.insertOpenAddress(playero);



        }
        lineCount++;

    }

    cout<<"Hash table size: "<<chainHashTable.getTableSize()<<endl;
    cout<<"Collisions using open addressing: "<<openHashTable.getOpenCollisions() <<endl;
    cout<<"Collisions using chaining: "<<chainHashTable.getChainCollisions() <<endl;
    cout<<"Search operations using  open addressing: "<<openHashTable.getOpenSearchCount() <<endl;
    cout<<"Search operations using chaining: "<<chainHashTable.getChainSearchCount() <<endl;
    cout << endl;

    while(userinput != 2){

        cout<<"===MAIN MENU==="<<endl;
        cout<<"1. Query Hashtable"<<endl;
        cout<<"2. Quit"<<endl;
        cout << endl;

        cin>>userinput;
        if(userinput == 1){
            int oCount = 0, cCount = 0;
            string fname, lname;
            cout << "Enter a first name: "<<endl;
            cin.ignore();
            getline(cin, fname);
            cout << "Enter a last name: "<<endl;
            getline(cin, lname);

            cout << fname << " " << lname << endl;
            oCount = openHashTable.findOpenAddress(fname, lname);
            cCount = chainHashTable.findChaining(fname, lname);

            cout<<"Search operations using  open addressing: "<< oCount <<endl;
            cout<<"Search operations using chaining: "<< cCount <<endl;

        }
    }
}



