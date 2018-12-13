//Alison Ostlund helped by Matthew Donovan
//Assignment 10
//Rhonda Hoenigman

#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include "MovieTree.h"

using namespace std;

int main(int argc, char* argv[])
{
  //open text file
  ifstream txtfile;
    //cout << argv[1] << endl;
  txtfile.open(argv[1]);
  string line;
  MovieTree *t = new MovieTree();
  //add movie node using txtfile info until end of file
  while (getline(txtfile,line))
  {
    //parse each line for rank, title, year, and stock
    int ind1 = line.find(',');
    int ind2 = line.find(',',ind1+1);
    int ind3 = line.find(',',ind2+1);
    string srank = line.substr(0,ind1);
    int rank = stoi(srank);
    string title = line.substr(ind1+1,ind2-ind1-1);
    string syear = line.substr(ind2+1,ind3-ind2-1);
    int year = stoi(syear);
    string squant = line.substr(ind3+1);
    int quant = stoi(squant);
    //cout << line << endl;
    t->addMovieNode(rank,title,year,quant);

  }

  t->isValid();

  //print menu options
  cout << "======Main Menu======" << endl;
  cout << "1. Find a movie" << endl;
  cout << "2. Rent a movie" << endl;
  cout << "3. Print the inventory" << endl;
  cout << "4. Delete a movie" << endl;
  cout << "5. Count the movies" << endl;
  cout << "6. Count the longest path" << endl;
  cout << "7. Quit" << endl;

  //get user input
  string s;
  int input;
  getline(cin,s);
  input = stoi(s);

  while (input != 7)
  {
    switch(input) {
      case 1:{
        //find movie
        cout << "Enter title:" << endl;
        string q;
        getline(cin,q);
        t->findMovie(q);
        break;}
      case 2:{
        //rent movie
        cout << "Enter title:" << endl;
        string title;
        getline(cin,title);
        t->rentMovie(title);
        break;}
      case 3:{
        //print inventory
        t->printMovieInventory();
        break;}
      case 4:{
        //delete a single node
        cout << "Enter title:" << endl;
        string title;
        getline(cin,title);
        t->deleteMovieNode(title);
        break;}
      case 5:{
        //count total nodes
        cout << "Tree contains: " << t->countMovieNodes() <<" movies."<< endl;
        break;}
      case 6:{
        cout << "Longest Path: " << t->countLongestPath() << endl;
        break;}
      default: {
        cout << "Enter an option between 1-7:" << endl;
        getline(cin,s);
        input = stoi(s);
        break;}
      }
      //print menu and get input again
      cout << "======Main Menu======" << endl;
      cout << "1. Find a movie" << endl;
      cout << "2. Rent a movie" << endl;
      cout << "3. Print the inventory" << endl;
      cout << "4. Delete a movie" << endl;
      cout << "5. Count the movies" << endl;
      cout << "6. Count the longest path" << endl;
      cout << "7. Quit" << endl;
      //check for user input to loop again or quit
      getline(cin,s);
      input = stoi(s);
  }
  cout << "Goodbye!" << endl;
  //clear entire tree
  t->~MovieTree();
}
