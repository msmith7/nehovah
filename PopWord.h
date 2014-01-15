/*
 * PopWord.h
 *
 * Mike Smith 2012
 */

#ifndef POPWORD_H_
#define POPWORD_H_

#include "stdio.h"
#include "iostream"
#include <stdlib.h>
#include <vector>
#include <string>
#include "Word.h"

using namespace std;

class PopWord : public Word
{
   private:
      string topTenTitle;
      string metainfo;
      double count;
   public:
      PopWord(string w, string t, string m);
      PopWord(string w, string t);
      void setCount(double c);
      double getCount();
      string getTitle();
      string getMetainfo();
      vector<wordScore> getPrefixes();
      vector<wordScore> getSuffixes();
      void incrementCount();
      bool operator<(const PopWord& a) const;
      bool operator<(const PopWord* a) const;
      string toString();
      int getType();
};

#endif /* POPWORD_H_ */
