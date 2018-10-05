//Alison Ostlund helped by Matthew Donovan 
#include "MovieTree.h"
#include <iostream>
#include <string>

using namespace std;

MovieTree::MovieTree(){
    nil = new MovieNode(0,"",0,0);
    nil->isRed = false;
    nil->parent = nil;
    nil->rightChild = nil;
    nil->leftChild = nil;
    root = nil;
}

void MovieTree::printMovieInventory(){
    if(root->leftChild != nil){
        printMovieInventory(root->leftChild);
    }
    cout << "Movie: " << root->title << " " << root->quantity << endl;
    if(root->rightChild != nil){
        printMovieInventory(root->rightChild);
    }
}

int MovieTree::countMovieNodes(){
    return countMovieNodes(root);
}

void MovieTree::deleteMovieNode(string title){
    MovieNode* toDel = searchMovieTree(root, title);
    if(toDel == nil){
        cout << "Movie not found." << endl;
        return;
    } else {
        rbDelete(toDel);
    }
}

void MovieTree::addMovieNode(int ranking, std::string title, int releaseYear, int quantity){
    MovieNode* toAdd = new MovieNode(ranking, title, releaseYear, quantity);
    MovieNode* x = root;
    MovieNode* y = nil;
    while(x!= nil){
        y = x;
        if(toAdd->title.compare(x->title)<0){
            x = x->leftChild;
        } else {
            x = x->rightChild;
        }
    }
    toAdd->parent = y;
    if(y == nil){
        root = toAdd;
    } else if(toAdd->title.compare(y->title)<0){
        y->leftChild = toAdd;
    } else {
        y->rightChild = toAdd;
    }
    toAdd->leftChild = nil;
    toAdd->rightChild = nil;
    rbAddFixup(toAdd);
    rbValid(root);
}

void MovieTree::findMovie(string title){
    MovieNode* movie = searchMovieTree(root, title);
    if(movie == nil){
        cout << "Movie not found." << endl;
    } else {
        cout << "Movie Info:" << endl;
        cout << "===========" << endl;
        cout << "Ranking:" << movie->ranking << endl;
        cout << "Title:" << movie->title << endl;
        cout << "Year:" << movie->year << endl;
        cout << "Quantity:" << movie->quantity << endl;
    }
}

void MovieTree::rentMovie(string title){
    MovieNode* movie = searchMovieTree(root, title);
    if(movie == nil){
        cout << "Movie not found." << endl;
    } else {
        movie->quantity--;
        cout << "Movie has been rented." << endl;
        cout << "Movie Info:" << endl;
        cout << "===========" << endl;
        cout << "Ranking:" << movie->ranking << endl;
        cout << "Title:" << movie->title << endl;
        cout << "Year:" << movie->year << endl;
        cout << "Quantity:" << movie->quantity << endl;
        if(movie->quantity == 0){
            deleteMovieNode(title);
        }
    }
}

void MovieTree::DeleteAll(MovieNode* node){
    if(node != nil){
        DeleteAll(node->leftChild);
        DeleteAll(node->rightChild);
        cout << "Deleting: " << node->title << endl;
        delete node;
    }
}

void MovieTree::printMovieInventory(MovieNode* node){
    if(node->leftChild != nil){
        printMovieInventory(node->leftChild);
    }
    cout << "Movie: " << node->title << " " << node->quantity << endl;
    if(node->rightChild != nil){
        printMovieInventory(node->rightChild);
    }
}

int MovieTree::countMovieNodes(MovieNode* node){
    int c = 1;
    if(node == nil){
        return 0;
    } else {
        c+=countMovieNodes(node->leftChild);
        c+=countMovieNodes(node->rightChild);
        return c;
    }
}

MovieNode* MovieTree::searchMovieTree(MovieNode* node, string value){
    if(node == nil){
        return node;
    } else {
        if(node->title == value){
            return node;
        } else if(node->title.compare(value) > 0){
            return searchMovieTree(node->leftChild, value);
        } else {
            return searchMovieTree(node->rightChild, value);
        }
    }
}

bool MovieTree::isValid(){
    if(rbValid(root)!=0){
        return true;
    } else {
        return false;
    }
}

int MovieTree::countLongestPath(){
    return countLongestPath(root);
}

void MovieTree::rbAddFixup(MovieNode* x){
    while (x != root && x->parent->isRed) {
        if (x->parent == x->parent->parent->leftChild) {
            MovieNode *y = x->parent->parent->rightChild;
            if (y->isRed) {
                x->parent->isRed = false;
                y->isRed = false;
                x->parent->parent->isRed = true;
                x = x->parent->parent;
            } else {
                if (x == x->parent->rightChild) {
                    x = x->parent;
                    leftRotate(x);
                }
                x->parent->isRed = false;
                x->parent->parent->isRed = true;
                rightRotate(x->parent->parent);
            }
        } else {
            MovieNode *y = x->parent->parent->leftChild;
            if (y->isRed) {
                x->parent->isRed = false;
                y->isRed = false;
                x->parent->parent->isRed = true;
                x = x->parent->parent;
            } else {
                if (x == x->parent->leftChild) {
                    x = x->parent;
                    rightRotate(x);
                }
                x->parent->isRed = false;
                x->parent->parent->isRed = true;
                leftRotate(x->parent->parent);
            }
        }
    }
    root->isRed = false;
}

void MovieTree::leftRotate(MovieNode* x){
    MovieNode* t = x->rightChild;
    x->rightChild = t->leftChild;
    if(t->leftChild != nil){
        t->leftChild->parent = x;
    }
    t->parent = x->parent;
    if(x->parent == nil){
        root = t;
    } else if(x == x->parent->leftChild){
        x->parent->leftChild = t;
    } else {
        x->parent->rightChild = t;
    }
    t->leftChild = x;
    x->parent = t;
}

void MovieTree::rbDelete(MovieNode* z){
    MovieNode* x;
    MovieNode* y = z;
    bool yRed = y->isRed;
    if(z->leftChild == nil){
        x = z->rightChild;
        rbTransplant(z,z->rightChild);
    } else if (z->rightChild == nil){
        x = z->leftChild;
        rbTransplant(z,z->leftChild);
    } else {
        y = treeMinimum(z->rightChild);
        yRed = y->isRed;
        x = y->rightChild;
        if(y->parent == z){
            x->parent = y;
        } else {
            rbTransplant(y, y->rightChild);
            y->rightChild = z->rightChild;
            y->rightChild->parent = y;
        }
        rbTransplant(z,y);
        y->leftChild = z->leftChild;
        y->leftChild->parent = y;
        y->isRed = z->isRed;
    }
    if(!yRed){
        rbDeleteFixup(x);
    }
}

void MovieTree::rightRotate(MovieNode* x){
    MovieNode* t = x->leftChild;
    x->leftChild = t->rightChild;
    if(t->rightChild != nil){
        t->rightChild->parent = x;
    }
    t->parent = x->parent;
    if(x->parent == nil){
        root = t;
    } else if(x==x->parent->leftChild){
        x->parent->leftChild = t;
    } else {
        x->parent->rightChild = t;
    }
    t->rightChild = x;
    x->parent = t;
}

void MovieTree::rbDeleteFixup(MovieNode* x){
    MovieNode* w;
    while(x!=root && !x->isRed){
        if(x == x->parent->leftChild){
            w = x->parent->rightChild;
            if(w->isRed){
                w->isRed = false;
                x->parent->isRed = true;
                leftRotate(x->parent);
                w = x->parent->rightChild;
            }
            if(!w->leftChild->isRed && !w->rightChild->isRed){
                w->isRed = true;
                x = x->parent;
            } else {
                if(!w->rightChild->isRed){
                    w->leftChild->isRed = false;
                    w->isRed = true;
                    rightRotate(w);
                    w = x->parent->rightChild;
                }
                w->isRed = x->parent->isRed;
                x->parent->isRed = false;
                w->rightChild->isRed = true;
                leftRotate(x->parent);
                x = root;
            }
        } else {
            w = x->parent->leftChild;
            if(w->isRed){
                w->isRed = false;
                x->parent->isRed = true;
                rightRotate(x->parent);
                w = x->parent->leftChild;
            }
            if(!w->leftChild->isRed && !w->rightChild->isRed){
                w->isRed = true;
                x = x->parent;
            } else {
                if(!w->leftChild->isRed){
                    w->rightChild->isRed = false;
                    w->isRed = true;
                    leftRotate(w);
                    w = x->parent->leftChild;
                }
                w->isRed = x->parent->isRed;
                x->parent->isRed = false;
                w->leftChild->isRed = true;
                rightRotate(x->parent);
                x = root;
            }
        }
    }
    x->isRed = false;
}

void MovieTree::rbTransplant(MovieNode* u, MovieNode* v){
    if(u->parent == nil){
        root = v;
    } else if(u == u->parent->leftChild){
        u->parent->leftChild = v;
    } else {
        u->parent->rightChild = v;
    }
    v->parent = u->parent;
}

int MovieTree::rbValid(MovieNode* node){
    int lh = 0;
    int rh = 0;

    // If we are at a nil node just return 1
    if (node == nil){
        return 1;
    } else {
        // First check for consecutive red links->
        if (node->isRed){
            if(node->leftChild->isRed || node->rightChild->isRed){
                cout << "This tree contains a red violation" << endl;
                return 0;
            }
        }

        // Check for valid binary search tree->
        if ((node->leftChild != nil && node->leftChild->title.compare(node->title) > 0) || (node->rightChild != nil && node->rightChild->title.compare(node->title) < 0)){
            cout << "This tree contains a binary tree violation" << endl;
            return 0;
        }

        // Determine the height of let and right children->
        lh = rbValid(node->leftChild);
        rh = rbValid(node->rightChild);

        // black height mismatch
        if (lh != 0 && rh != 0 && lh != rh){
            cout << "This tree contains a black height violation" << endl;
            return 0;
        }

        // If neither height is zero, incrament if it if black->
        if (lh != 0 && rh != 0){
                if (node->isRed)
                    return lh;
                else
                    return lh+1;
        } else {
            return 0;
        }
    }
}

int MovieTree::countLongestPath(MovieNode* node){
    if(node == nil){
        return 0;
    }
    else {
        int r = countLongestPath(node->rightChild);
        int l = countLongestPath(node->leftChild);
        return (r>l?r+1:l+1);
    }
}


MovieNode* MovieTree::treeMinimum(MovieNode* node){
    MovieNode* temp = node;
    while(temp->leftChild!=nil){
        temp = temp->leftChild;
    }
    return temp;
}



MovieTree::~MovieTree(){
    DeleteAll(root);
}
