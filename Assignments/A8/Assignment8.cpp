/*
 Alison Ostlund
 Helped by Matthew Donovan/ Denver Cherin
    Assignment 8
    Rhonda Hoenigman
*/

#include "MovieTree.h"
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <ctype.h>

using namespace std;

int main(int argc, char *argv[])
{
  //open text file
  ifstream txtfile;
  txtfile.open(argv[1]);
  string l;
  MovieTree *t = new MovieTree();
  //add movie node using txtfile info until end of file
  while (getline(txtfile,l))
  {
    //parse each line for rank, title, year, and stock
    int ind1 = l.find(',');
    int ind2 = l.find(',',ind1+1);
    int ind3 = l.find(',',ind2+1);
    string srank = l.substr(0,ind1);
    int rank = stoi(srank);
    string title = l.substr(ind1+1,ind2-ind1-1);
    string syear = l.substr(ind2+1,ind3-ind2-1);
    int year = stoi(syear);
    string squant = l.substr(ind3+1);
    int quant = stoi(squant);
    //cout << line<< endl;
    t->addMovieNode(rank,title,year,quant);
  }


  //print menu options
  cout << "======Main Menu======" << endl;
  cout << "1. Find a movie" << endl;
  cout << "2. Rent a movie" << endl;
  cout << "3. Print the inventory" << endl;
  cout << "4. Delete a movie" << endl;
  cout << "5. Count the movies" << endl;
  cout << "6. Quit" << endl;

  //get input and run until user quits
  string in ="6";
  getline(cin,in);
  int input = stoi(in);

  //run program until user enters a 6
  while (input != 6)
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
      default: {
        cout << "Enter an option between 1-6:" << endl;
        getline(cin,in);
        input = stoi(in);
        break;}

    }
    //print menu and get input again
    cout << "======Main Menu======" << endl;
    cout << "1. Find a movie" << endl;
    cout << "2. Rent a movie" << endl;
    cout << "3. Print the inventory" << endl;
    cout << "4. Delete a movie" << endl;
    cout << "5. Count the movies" << endl;
    cout << "6. Quit" << endl;
    //check for user input to loop again or quit
    getline(cin,in);
    input = stoi(in);
  }
  //
  cout << "Goodbye!" << endl;
  //clear entire tree
  t->~MovieTree();
}
