// Alison Ostlund //helped  Matthew Donovan// Assignment 3 
#include "WordAnalysis.h"
#include <iostream>
#include <fstream>

using namespace std;

void WordAnalysis::doubleArrayAndAdd(string str)
{
  word *arr = new word[wordCount*2];
  //place values from old array in new array
  for (int i = 0; i < wordCount; i++)
  {
    arr[i].w=words[i].w;
    arr[i].count = words[i].count;
  }
  //free memory
  delete []words;
  //set old array equal to new
  words = arr;
  words[index].w = str;
  words[index].count = 1;
  index++;
  wordCount *= 2;
  timesDoubled++;
}

//constructor
WordAnalysis::WordAnalysis(int num)
{
  words = new word[num];
  wordCount = num;
  timesDoubled=0;
  index=0;
}

bool WordAnalysis::checkIfCommonWord(std::string str)
{
  string mcw[50] = {"the", "you", "one", "be", "do", "all", "to", "at", "would", "of", "this", "there", "and", "but", "their", "a", "his", "what", "in", "by", "so", "that", "from", "up", "have", "they", "out", "i", "we", "if", "it", "say", "about", "for", "her", "who", "not", "she", "get", "on", "or", "which", "with", "an", "go", "he", "will", "me", "as", "my"};
  //loop through array of common words comparing them to str
    for (int l = 0; l < 50; l++)
    {
        //return true if the word is common
        if (mcw[l]==str)
            return true;
    }
    //return false if not
    return false;
}

void WordAnalysis::sortData()
{
  //sort array from least to greatest
    for (int x = 0; x <= index; x++)
    {
      int mwordCount = x;
      for (int y = x; y <= index; y++)
      {
        if (words[mwordCount].count < words[y].count)
        mwordCount = y;
      }
        word temp = words[x];
        words[x] = words[mwordCount];
        words[mwordCount] = temp;
      }
}

bool WordAnalysis::readDataFile(char* str)
{
  ifstream datafile(str);
  if (!datafile.is_open())
  {
    //return error somehow
    return false;
  }
  string line;
  while (datafile>>line)
  {
    if (checkIfCommonWord(line))
      continue;
    bool foundmatch = false;

    //look through array to see if word found yet
    if (index == 0)
    {
      words[0].w = line;
      words[index].count = 1;
      index++;
    }
    for (int k = 0; k < index; k++)
    {
      //iterate counter if found
      if (line == words[k].w)
      {
        words[k].count++;
        foundmatch = true;
        break;
      }
    }
    //add to array if not already in it
    if (foundmatch==false)
    {
      if (index==wordCount) {
        doubleArrayAndAdd(line);
      }
      else
      {
      words[index].w=line;
      words[index].count = 1;
      index++;
      }
    }
  }
  sortData();
  return true;
}

int WordAnalysis::getWordCount()
{
  int sum;
  for (int y = 0; y < index; y++)
  {
    sum = sum + words[y].count;
  }
  return sum;
}

int WordAnalysis::getUniqueWordCount()
{
  return index;
}

int WordAnalysis::getArrayDoubling()
{
  return timesDoubled;
}

void WordAnalysis::printCommonWords(int num)
{
  for(int i = 0; i < num; i++)
  {
    cout << words[i].count << " - " << words[i].w << endl;
  }
}


WordAnalysis::~WordAnalysis()
{

}
