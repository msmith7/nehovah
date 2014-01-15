/*
 * Neologism.h
 *
 * Mike Smith 2012
 */

#include "stdio.h"
#include "iostream"
#include <stdlib.h>
#include <vector>
#include <string>
#include "Word.h"

using namespace std;


class Neologism
{
   private:
      string word;
      double score;       //word?
      double preScore;    //concept in Prefix
      double sufScore;    //concept in Suffix
      double uniqueScore; //uniqueness
      double popScore;      //Comes from pop culture
   public:
      Word* prefix;
      Word* suffix;
      Neologism();
      Neologism(string name, double pre, double suf);
      Neologism(string name);
      ~Neologism(){};
      void setWord(string name);
      void setPrefix(Word* pre);
      void setSuffix(Word* suf);
      string getWord();
      bool operator<(const Neologism& a) const;
      void scoreWord();
      friend ostream &operator<<(ostream &stream, const Neologism& neo);
      bool checkScore();
};
