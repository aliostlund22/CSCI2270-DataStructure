//Alison Ostlund/ helped by Alex Markley and Hannah Haines
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stdlib.h>
using namespace std;

struct craigslist{            //declares the members in each line in the file
    string type;
    bool sale;
    int price;
};

int match (craigslist itemArr[], craigslist word, int index, int& searchCount)
{
    if(word.sale == 0)
        {
        for(int i = 0; i < index; i++)
        {
            searchCount++;
            if((word.type == itemArr[i].type) && (itemArr[i].sale == 1) && (word.price >= itemArr[i].price))
            {
                return i;
            }
        }
    }
    else
    {
        for(int i = 0; i < index; i++)
            {
            searchCount++;
            if((word.type == itemArr[i].type) && (itemArr[i].sale == 0) && (word.price <= itemArr[i].price))
            {
                return i;
            }
        }
    }
    return -1;
}
void Shifter (craigslist itemArr[], int index, int length, int& shiftCount)
{
    for(int i = index; i < length-1; i++)
        {
        shiftCount++;
        itemArr[i] = itemArr[i+1];
        }
}
void Printer (craigslist itemArr[], int index)
{
    for(int i = 0; i < index; i++)
        {
        if(itemArr[i].sale == 1)
        {
            cout << itemArr[i].type << ", for sale, " << itemArr[i].price << endl;
        }
        else
        {
            cout << itemArr[i].type << ", wanted, " << itemArr[i].price << endl;
        }
    }
}

int main(){
    craigslist itemArr[100];
    string fileName;                    //The itemArray declares the 100 lines in the file and the 3 members in each line
    cin >> fileName;
    ifstream dataFile(fileName.c_str());
    string line;
    int fileCount = 0;
    int searchCount = 0;
    int shiftCount = 0;
    int index;
    if (dataFile.fail())
        {
        cout << "Error file not opened" <<endl;
        return -1;
        }
    while (getline(dataFile,line)){
    fileCount++;
    craigslist word;
    int comma1 = line.find(',');                //find the first comma
    int comma2 = line.find_last_of(',');         //find the second comma
    word.type = line.substr(0,comma1);
    if(line.at(comma1+2) == 'f')
    {          //if item is for sale
        word.sale = 1;
    }
    else
    {
        word.sale = 0;                      //if item is wanted
    }
    word.price = stoi(line.substr(comma2 + 2,line.size() - (comma2 + 2)));
    int length;
    int matchCount = match(itemArr, word, index, searchCount);
    if (matchCount == -1)
    {
        itemArr[index] = word;
        index++;
    }
    else
    {
        if(itemArr[matchCount].sale == 1)
        {
            cout << itemArr[matchCount].type << " "<<itemArr[matchCount].price<<endl;
        }
        else
        {
            cout<<itemArr[matchCount].type<< " "<<word.price<<endl;
        }
        Shifter(itemArr,matchCount,index,shiftCount);
        index--;
    }
    }
    cout << "#" << endl;
    Printer(itemArr,index);
    cout << "#" << endl;
    cout<<"file read: "<<fileCount<<endl;
    cout<<"search array:"<<searchCount<<endl;
    cout<<"shift array:"<<shiftCount<<endl;
    return 0;
    }
