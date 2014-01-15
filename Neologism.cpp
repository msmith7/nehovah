/*
 * Neologism.cpp
 *
 * Mike Smith 2012
 */

#include "stdio.h"
#include "iostream"
#include <stdlib.h>
#include <vector>
#include <string>
#include "Neologism.h"
#include <typeinfo>
#include "PopWord.h"

using namespace std;
      
Neologism::Neologism()
{
   setWord("");
   score = 0;
   preScore = 0;
   sufScore = 0;
   uniqueScore = 0;
   popScore = 0;
}

Neologism::Neologism(string name, double pre, double suf)
{
   setWord(name);
   score = 0;
   preScore = pre;
   sufScore = suf;
   uniqueScore = 0;
   popScore = 0;
}

Neologism::Neologism(string name)
{
   setWord(name);
   score = 0;
   preScore = 0;
   sufScore = 0;
   uniqueScore = 0;
   popScore = 0;
}

void Neologism::setWord(string name)
{
   word=name;
}

void Neologism::setPrefix(Word* pre)
{
   if (pre->getType() == 2)
      popScore+=1;
   prefix = pre;
}

void Neologism::setSuffix(Word* suf)
{
   if (suf->getType() == 2)
      popScore+=1;
   suffix = suf;
}

string Neologism::getWord()
{
   return word;
}

bool Neologism::operator<(const Neologism& a) const
{
   return word < a.word;
}

void Neologism::scoreWord()
{
   //Check for syllable exchange
   //Check for overlapping letters
   string pre = prefix->getStem();
   string suf = suffix->getStem();
   score = 0;

   int i = 0;
   while (pre[i] == word[i])
   {
      i++;
   }

   int j = suf.size();
   int k = word.size();
   while (suf[j] == word[k] && k> i && j > 0)
   {
      j--;
      k--;
   }

   string usedPre = word.substr(0,i);
   string usedSuf = suf.substr(0,j);

   //Syllalbe exchange. only in words without the whole prefix
   if (word.find(suf)==string::npos)
   {

      int overlap = 0;
      //is there any overlap?
      while (j > 0 && i>0 && word[i-1] == suf[j-1])
      {
         i--;
         j--;
         overlap++;
         score++;
      }

      //count the number of vowels
      bool wordVowel = false;
      bool sufVowel = false;
      bool last = false;
      do
      {
         last = (i==-1 || j ==-1);
         wordVowel = false;
         sufVowel = false;
         while (!wordVowel && i >= 0)
         {
            wordVowel = (word[i] == 'a' || word[i] == 'e' || word[i] == 'i' || word[i] == 'o' || word[i] == 'u' || word[i] == 'y');
            i--;
            if (i >= 0 && wordVowel && (word[i] == 'a' || word[i] == 'e' || word[i] == 'i' || word[i] == 'o' || word[i] == 'u' || word[i] == 'y'))
               i--; 
            while(last && i >=0 && word[i] != 'a' && word[i] != 'e' && word[i] != 'i' && word[i] != 'o' && word[i] != 'u' && word[i] != 'y')
               i--;
         }

         while (!sufVowel && j >= 0)
         {
            sufVowel = (suf[j] == 'a' || suf[j] == 'e' || suf[j] == 'i' || suf[j] == 'o' || suf[j] == 'u' || suf[j] == 'y');
            j--;
            //account for diphthongs
            if (j >= 0 && sufVowel && (suf[j] == 'a' || suf[j] == 'e' || suf[j] == 'j' || suf[j] == 'o' || suf[j] == 'u' || suf[j] == 'y'))
               j--;
         }
         if (last) break;
      }while(i > -1 || j > -1);

      //if there is overlap, adjust the prefix and sufix
      if (overlap > 0)
      {
         i = 0;
         while (pre[i] == word[i])
         {
            i++;
         }
  
         j = suf.size();
         k = word.size();
         while (suf[j] == word[k] && k> i && j > 0)
         {
            j--;
            k--;
         }

         usedPre = word.substr(0,i + overlap);
         usedSuf = suf.substr(0,j - overlap);
      }
      
   }
   if (i ==-1&& j ==-1)
   {
      score++;
   }
}

ostream& operator<<(ostream &stream, const Neologism& neo)
{
   stream << neo.word << " " << neo.score << " " << neo.preScore << " " << neo.sufScore << " " << neo.uniqueScore << " " << neo.popScore << " - |" << neo.prefix->toString() << "| |" << neo.suffix->toString() << "| |" << neo.suffix->displayEndings() << "|";
   return stream;
}

bool Neologism::checkScore()
{
   return (word.size() > 4 && (score + preScore + sufScore + uniqueScore + popScore) > 0);
}
