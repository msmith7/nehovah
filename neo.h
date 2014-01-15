/*
 * neo.h
 *
 * Mike Smith 2012
 */

#include <iostream>
#include <set>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include "wn.h"
#include "WNDictionaryTree.h"
#include "Neologism.h"
#include "Word.h"
#include "web/TopTensSearch.h"
//#include "WNTreeCreator.h"
//#include "WNDictionaryTree.h"

using namespace std;
/*
struct wordScore
{
   string word;
   double score;
   bool operator<(const wordScore& a) const
   {
      return word < a.word;
   }
};*/
//bool compareWords(const wordScore& first, const wordScore& second);
void initializeDictionary();
vector<Neologism> combine(vector< vector <string> > words, vector< vector <PopWord> > popWords);

vector<string> queryWordNet(string word, int searchType);

//returns a sorted vector of words according to their score
vector<wordScore> scoreWords(vector< vector <string> > words);
double score(string word);
