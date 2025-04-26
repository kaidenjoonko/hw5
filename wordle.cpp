#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
void finder(string temp, const std::string& in, const std::string& floating, const std::set<std::string>& dict, set<string>& list, int index);


// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here

    //1. create a list to store possible words
    std::set<std::string> list;
    string temp = in;

    finder(temp, in, floating, dict, list, 0);

    return list;
}

void finder(string temp, const std::string& in, const std::string& floating, const std::set<std::string>& dict, set<string>& list, int index){
  if(index == in.size()){
    if(dict.find(temp) != dict.end() && floating.empty()){
      list.insert(temp);
    }
    return;
  }

  //loop through current char
  char c = in[index];
  if(c == '-'){
    int blank = 0;
    for(size_t i = index; i < in.size(); i++){
      if(in[i] == '-'){
        blank++;
      }
    }

    for(char j = 'a'; j<= 'z'; j++){
      string floatChar = floating;
      if(floating.find(j) != string::npos){
        floatChar.erase(floating.find(j), 1);
        //swap
        temp[index] = j;
        finder(temp, in, floatChar, dict, list, index+1);
      }else if(floating.size() < blank){
        temp[index] = j;
        finder(temp, in, floatChar, dict, list, index + 1);
      }
    }
  }else{
        temp[index] = c;
        finder(temp, in, floating, dict, list, index+1);
  }
}