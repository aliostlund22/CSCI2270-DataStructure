#ifndef HASHTABLE_H
#define HASHTABLE_H
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

struct Player{
	int hashCode;
	string year;
	string team;
	string league;
	string PlayerID;
	string salary;
	string Birth;
	string country;
	string weight;
	string height;
	string bat;
	string throws;
	string firstName;
	string lastName;
	Player *next;
	Player *previous;

	Player(int H, string Y, string T, string L, string ID, string S, string BY, string BC, string W, string Hi, string B, string Th, string FN, string LN){
		hashCode = H;
		year = Y;
		team = T;
		league = L;
		PlayerID = ID;
		salary = S;
		Birth = BY;
		country = BC;
		weight = W;
		height = Hi;
		bat = B;
		throws = Th;
		firstName = FN;
		lastName = LN;
		next = NULL;
		previous = NULL;
	}


};

class HashTable{
	private:
		Player **data;
		int TableSize = 0;
		Player *head = NULL;
        int chainCollisions=0,openCollisions=0,chainSearch=0,openSearch=0;
	public:
		~HashTable();
		HashTable(int tableSize);
		void insertChaining(Player *p);
		void insertOpenAddress(Player *p);
		int hashFunction(string firstName, string lastName);
		bool isNULLChain(Player *p);
        bool isNULLLinear(Player *p);

        int getTableSize();
		int getOpenSearchCount();
        int getOpenCollisions();

		int getChainSearchCount();
		int getChainCollisions();

        int findChaining(string &fname, string &lname);  // return search count
        int findOpenAddress(string &fname, string &lname);  // return search count

		bool chain = false;
		bool linear = false;

};
#endif
