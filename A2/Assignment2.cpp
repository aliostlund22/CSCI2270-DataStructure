//Alison Ostlund/ CSCI2270 Assignment 2 / Help by Denver Chernin
#include<string>
#include<iostream>
#include<fstream>
#include<stdlib.h>
using namespace std;

struct words{
    string word = "";
    int num = 0;
};

bool isCommonWord(string word){
    bool CommonWord = false;
    if((word == "the")||(word == "be")||(word == "to") ||
       (word == "of")||(word == "and")||(word == "a") ||
       (word == "in")||(word == "that")||(word == "have")||
       (word == "i") ||(word == "it")||(word == "for") ||
       (word == "not")||(word == "on")||(word == "with")||
       (word == "he")|| (word == "as")||(word == "you")||
       (word == "do")||(word == "at")||(word == "this")||
       (word == "but")||(word == "his")||(word == "by")||
       (word == "by")||(word == "from")||(word == "they")||
       (word == "we")||(word == "say")||(word == "her")||
       (word == "she")||(word == "or")||(word == "an")||
       (word == "will")||(word == "my")||(word == "one")||
       (word == "all")||(word == "would")||(word == "there")||
       (word == "their")||(word == "what")||(word == "so")||
       (word == "up")||(word == "out")||(word == "if")||
       (word == "about")||(word == "who")||(word == "get")||
       (word == "which")||(word == "go")||(word == "me")){
        CommonWord = true;
       }
       return CommonWord;
}


int main(int argc, char *argv[]){
    if(argc != 3){
        cout<<"Improper Arguments";
        exit(0);
    }
    string fileName = argv[1];
    int n = atoi(argv[2]);

    int aDouble = 0;
    int size = 100;
    words *wordArray = new words[size];
    string token;
    ifstream DataFile;
    DataFile.open(fileName.c_str());
    int indexArray = 0;
    bool match = false;
    int uniqueWord = 0;
    while(DataFile>>token){
        if(!isCommonWord(token)){
            for(int i = 0; i < size; i++){
                if(token == wordArray[i].word){
                    wordArray[i].num++;
                    match = true;
                    break;
                }
            }
            if(!match){
                wordArray[indexArray].word = token;
                wordArray[indexArray].num++;
                indexArray++;
                uniqueWord++;
            }
            match = false;

            if(indexArray == size - 1){
                size = size *2;
                words *wordArray2 = new words[size];
                for(int j =0; j < size/2; j++){
                    wordArray2[j].num = wordArray[j].num;
                    wordArray2[j].word = wordArray[j].word;
                }
                delete []wordArray2;
                wordArray = wordArray2;
                aDouble++;

            }
        } else {
            //WORD IS A COMMON WORD
            //DO NOTHING WITH IT
        }
    }

    int wordCount = 0;
    for(int i = 0; i < size; i++){
        wordCount += wordArray[i].num;
    }

    for(int k = 0; k <= indexArray; k++){
        int x = k;
        for(int y = k; y <= indexArray; y++){
            if(wordArray[x].num < wordArray[y].num){
                x = y;
            }
        }
        words temp = wordArray[k];
        wordArray[k] = wordArray[x];
        wordArray[x] = temp;
    }

    for(int i = 0; i <= n-1; i++){
        cout<<wordArray[i].num<<" – "<<wordArray[i].word<<endl;

    }
    cout<< "#" <<endl;
    cout<<"Array doubled: "<<aDouble<<endl;
    cout<< "#" <<endl;
    cout<<"Unique non-common words: "<<uniqueWord<<endl;
    cout<< "#" <<endl;
    cout<<"Total non-common words: "<<wordCount<<endl;




}
