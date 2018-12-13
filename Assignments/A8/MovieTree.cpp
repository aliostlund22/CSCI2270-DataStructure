//Alison Ostlund
//Assignment8
#include "MovieTree.h"
#include <iostream>

using namespace std;

//constructor
MovieTree::MovieTree()
{
  root = NULL;
}

//destructor
MovieTree::~MovieTree()
{
  DeleteAll(root);
}

//public print funtion to call private function
void MovieTree::printMovieInventory()
{
  printMovieInventory(root);
}

//private print function
void MovieTree::printMovieInventory(MovieNode *node)
{
  if (node == NULL)
    return;
  printMovieInventory(node->leftChild);
  cout <<"Movie: " <<node->title << " "<< node->quantity << endl;
  printMovieInventory(node->rightChild);
}

int MovieTree::countMovieNodes()
{
  int count =0;
  countMovieNodes(root,&count);
  return count;
}

void MovieTree::countMovieNodes(MovieNode *node, int *c)
{
  if (node == NULL)
    return;
  countMovieNodes(node->leftChild,c);
  (*c)++;
  countMovieNodes(node->rightChild,c);
}

//delete a single node by searching tree for title
void MovieTree::deleteMovieNode(string title)
{
  //search for node containing title
  MovieNode *current = search(title);

  //if not found
  if (current == NULL)
  {
    cout << "Movie not found." << endl;
    return;
  }
  if (current==root)
  {
    delete current;
    return;
  }

  //left = true when current is leftChild of parent
  bool left = false;
  if (current->parent->leftChild == current)
  {
    left = true;
  }

  //case of no children
  if (current->leftChild == NULL && current->rightChild == NULL)
  {
    if (left)
      current->parent->leftChild = NULL;
    else
      current->parent->rightChild = NULL;
    delete current;
    return;
  } else if (current->leftChild != NULL && current->rightChild != NULL) {
    //case of 2 children
    //get minimum of right branch to replace current
    MovieNode *min = treeMinimum(current->rightChild);
    if (min == NULL)
    {
        if (left)
          current->parent->leftChild=NULL;
        else
          current->parent->rightChild=NULL;
        delete current;
        return;
    } else if (current->rightChild == min){
      if (current->parent!=NULL)
      {
        if (left)
          current->parent->leftChild = min;
        else
          current->parent->rightChild = min;
      }
      min->parent = current->parent;
      min->leftChild = current->leftChild;
      if (current->leftChild!=NULL)
        current->leftChild->parent = min;
      delete current;
      return;
    } else {
      //just replace values of current so pointers remain
      min->parent->leftChild = NULL;
      current->title = min->title;
      current->ranking = min->ranking;
      current->year = min->year;
      current->quantity = min->quantity;
    }
  } else {
    //case of 1 child
    if (current->leftChild!=NULL)
    {
      //if child is leftChild
      current->leftChild->parent=current->parent;
      if (left)
        current->parent->leftChild = current->leftChild;
      else
        current->parent->rightChild = current->leftChild;
    } else {
      //if child is rightChild
      current->rightChild->parent=current->parent;
      if (left)
        current->parent->leftChild = current->rightChild;
        else
        current->parent->rightChild = current->rightChild;
    }
  }
}

void MovieTree::addMovieNode(int rank, string title, int year, int stock)
{
  MovieNode *tmp = new MovieNode(rank,title,year,stock);
  //set to root if tree empty
  if (root == NULL)
  {
    root = tmp;
    return;
  } else {
    MovieNode* current = root;
    //loop traversing to end of tree
    while (current!=NULL)
    {
      //go left if current comes earlier in alphabet
      if (current->title > title)
      {
        if (current->leftChild!=NULL)
        {
          current=current->leftChild;
        } else {
          tmp->parent = current;
          current->leftChild = tmp;
          return;
        }
      } else if (current->title < title) {
        //go right otherwise
        if (current->rightChild!=NULL)
        {
          current = current->rightChild;
        } else {
          tmp->parent = current;
          current->rightChild = tmp;
          return;
        }
      }
    }
  }
}

void MovieTree::findMovie(string title)
{
  MovieNode *foundMovie = searchRecursive(root,title);
  if (foundMovie == NULL)
  {
    cout << "Movie not found." << endl;
    return;
  } else {
    cout << "Movie Info:" << endl;
    cout << "===========" << endl;
    cout << "Ranking:" << foundMovie->ranking << endl;
    cout << "Title:" << foundMovie->title << endl;
    cout << "Year:" << foundMovie->year << endl;
    cout << "Quantity:" << foundMovie->quantity << endl;
  }
}

void MovieTree::rentMovie(string title)
{
  MovieNode *foundMovie = search(title);
  //cout << "1. "<< foundMovie->quantity << endl;
  //cout << "2. "<< foundMovie->quantity << endl;
  if (foundMovie == NULL)
  {
    cout << "Movie not found." << endl;
    return;
  } else {
    //decrease quantity by 1 when rented
    int j = foundMovie->quantity;
    j--;
    foundMovie->quantity=j;
    cout << "Movie has been rented." << endl;
    cout << "Movie Info:" << endl;
    cout << "===========" << endl;
    cout << "Ranking:" << foundMovie->ranking << endl;
    cout << "Title:" << foundMovie->title << endl;
    cout << "Year:" << foundMovie->year << endl;
    cout << "Quantity:" << foundMovie->quantity << endl;
  }
  if (foundMovie->quantity==0)
    deleteMovieNode(foundMovie->title);
}

MovieNode* MovieTree::search(string title)
{
  MovieNode* result = searchRecursive(root,title);
  return result;
}

MovieNode* MovieTree::searchRecursive(MovieNode *node, string title)
{
  //in order recursive search
  if (node == NULL)
    return NULL;
  else {
    if (node->title > title)
      return searchRecursive(node->leftChild,title);
    else if (node->title == title)
      return node;
    else
      return searchRecursive(node->rightChild,title);
  }
}

MovieNode* MovieTree::treeMinimum(MovieNode *current)
{
  if (current == NULL)
    return NULL;
  while (current->leftChild!=NULL)
    current = current->leftChild;
  return current;
}

void MovieTree::DeleteAll(MovieNode *node)
{
  //post order delete entire tree
  if (node == NULL)
    return;
  else {
  MovieNode *current = node;
  DeleteAll(current->leftChild);
  DeleteAll(current->rightChild);
  cout << "Deleting: " << current->title << endl;
  deleteMovieNode(current->title);
  }
}
