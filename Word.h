/*
 * word.h
 *
 * Mike Smith 2012
 */

#ifndef WORD_H_
#define WORD_H_

#include "stdio.h"
#include "iostream"
#include <stdlib.h>
#include <vector>
#include <string>
#include "web/MoreWordsSearch.h"

using namespace std;

struct wordScore
{
   string word;
   double score;
   bool operator<(const wordScore& a) const
   {
      return word < a.word;
   }
};


class Word
{
   private:
      bool isWord;
      vector<wordScore> prefixes;
      vector<wordScore> suffixes;
      vector<string> endings;
      int source;
   protected:
      string stem;
   public:
      Word();
      Word(string name, bool isWord);
      ~Word(){};
      void setStem(string name);
      void setIsWord(bool word);
      void setSource(int source);
      void setEndings(vector<string> endings);
      virtual vector<wordScore> getPrefixes();
      virtual vector<wordScore> getSuffixes();
      bool operator<(const Word& a) const;
      string getStem();
      virtual string toString();
      string displayEndings();
      virtual int getType();
};

#endif /* WORD_H_ */
