/*
 *  PopWord.cpp
 *  
 *  Mike Smith April 2012
 */


#include "PopWord.h"

PopWord::PopWord(string w, string t, string m) : Word(w, true)
{
//   PopWord(w,t);
   topTenTitle = t;
   metainfo=m;
   count=-1;
}

PopWord::PopWord(string w, string t) : Word(w, true)
{
   topTenTitle = t;
   metainfo="";
   count=-1;
}

void PopWord::setCount(double c)
{
   count = c;
}

double PopWord::getCount()
{
   return count;
}

string PopWord::getTitle()
{
   return topTenTitle;
}

string PopWord::getMetainfo()
{
   return metainfo;
}

vector<wordScore> PopWord::getPrefixes() 
{
   vector<wordScore> rtnVal = Word::getPrefixes();
   wordScore rtn;
   rtn.word = getStem();
   rtn.score = count;
   rtnVal.push_back(rtn);
//   for (int i = 0; i < rtnVal.size(); i++)
//   {
//      rtnVal[i].score = count;
//   }
   return rtnVal;
}

vector<wordScore> PopWord::getSuffixes()
{
   vector<wordScore> rtnVal = Word::getSuffixes();
   wordScore rtn;
   rtn.word = getStem();
   rtn.score = count;
   rtnVal.push_back(rtn);
//   for (int i = 0; i < rtnVal.size(); i++)
//   {
//      rtnVal[i].score = count;
//   }
   return rtnVal;
}

void PopWord::incrementCount()
{
   count++;
}

bool PopWord::operator<(const PopWord* a) const
{
   return stem < a->stem;
}
bool PopWord::operator<(const PopWord& a) const
{
   return stem < a.stem;
}

string PopWord::toString()
{
   return (stem + " " + topTenTitle + " " + metainfo);
}

int PopWord::getType()
{
   return 2;
}
