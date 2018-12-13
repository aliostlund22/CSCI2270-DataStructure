#include <iostream>
#include <fstream>
#include <iomanip>
#include <stdlib.h>

using namespace std;

struct craigslist
{
    string type;
    bool sale;//0 = wanted/ 1 = for sale
    int price;
};

int check(int counter, int &searchCount, craigslist itemArray[],craigslist word)
{
    if(word.sale == 0)  // Wanted
    {
        for(int i = 0; i < counter; i++)
        {
            searchCount++;
            if((word.type == itemArray[i].type) && (itemArray[i].sale == 1) && (word.price >= itemArray[i].price))
            {
                return i;  // wanted >= sale
            }
        }
    }
    else
    {
        for(int i = 0; i < counter; i++) // For Sale
        {
            searchCount++;
            if((word.type == itemArray[i].type) && (itemArray[i].sale == 0) && (word.price <= itemArray[i].price))
            {
                return i;  // for sale <= wanted
            }
        }
    }
    return -1;
}
void printer (craigslist itemArray[], int index)
{
    for(int i = 0; i < index; i++)
    {
        if(itemArray[i].sale == 1)
        {
            cout << itemArray[i].type << ", for sale, " << itemArray[i].price << endl;
        }
        else
        {
            cout << itemArray[i].type << ", wanted, " << itemArray[i].price << endl;
        }
    }
}

void shifter(craigslist itemArray[], int &shiftCount, int counter, int len)
{
 //   for(int j = counter; j < counter-1; j++)
    int j = 0; // FIX3 - minor fix
    for(j = counter; j <= len-1; j++)  // FIX4 - use len (index) to shifting up full list

        {
        shiftCount++;
        itemArray[j] = itemArray[j+1];
        }
}


int main()
{
    craigslist itemArray[100];
    string filename;
    ifstream datafile;
    string line;
    int index = 0;
    int fileCount = 0;
    int searchCount = 0;
    int shiftCount = 0;


    cout << "Enter a file name"<< endl;
    cin >> filename;
    datafile.open(filename.c_str());    // FIX0 - Return this if it works on your computer...   I just hard coded for now per below


    if (datafile.fail())
        {
            cout << "File open error!" << endl;
            return -1;
        }


    // Process the file
    while(getline(datafile,line))
    {
        fileCount++;
        craigslist word;
        int comma1 = line.find(',');
        int comma2 = line.find_last_of(',');
        int matchCount = 0;  // FIX1   - just a nit fix

        word.type = line.substr(0, comma1);
        if (line.at(comma1 + 2) == 'f') // searching if line says for sale or wanted
        {
            word.sale = 1;
        }
        else
        {
            word.sale = 0;
        }

        word.price = stoi(line.substr(comma2 +2, line.size()-(comma2 +2))); //string into int

        matchCount = check(index, searchCount, itemArray, word);

        if(matchCount == -1)// meaning match wasnt found
        {
            itemArray[index] = word;
            index++;
        }
        else //match found at index matchcount
        {
            if(itemArray[matchCount].sale == 1)
            {
                cout << itemArray[matchCount].type << " " << itemArray[matchCount].price << endl;
            }
            else
            {
                // cout << itemArray[matchCount].type << " " << word.price << endl; FIX2 - use itemArray.price, not word.price
                cout << itemArray[matchCount].type << " " << itemArray[matchCount].price << endl;
            }
           // cout << "=======================" << endl;  // debug
           // cout << "Matched " << word.type << " " << word.sale << " " << word.price << endl;  // debug
           // cout << "=======================" << endl;  // debug

            shifter(itemArray, shiftCount, matchCount, index);
            index--;

            // printer(itemArray, index); // debug
            // cout << "=======================" << endl;  // debug
            // cout << "=======================" << endl;  // debug

        }

   }

    cout << "#" << endl;
    printer(itemArray, index);
    cout << "#" << endl;
    cout << "file read:" << fileCount << endl;
    cout << "search array:" << searchCount<< endl;
    cout << "shift array:" << shiftCount<< endl;
    return 0;


}

