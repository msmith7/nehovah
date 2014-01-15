/*
 * Word.cpp
 *
 * Mike Smith 2012
 */

#include "Word.h"

using namespace std;

Word::Word()
{
   stem='0';
}

Word::Word(string name, bool isWord)
{
   setStem(name);
   setIsWord(isWord);
}

void Word::setStem(string name)
{
   stem = name;
   //break Word up into syllables (every vowel and consecuative consonants)
   int end = stem.size() - 1;

   wordScore thisWord;
   //check for silent e (e trailing a non-vowel)
   if (stem[end] == 'e' && stem[end-1]!='e')// && stem[end-2]!='i' && stem[end-2]!='o' && stem[end-2]!='u' && stem[end-2]!= 'y')
   {
      end--;
      thisWord.word = stem.substr(0,end);
   }
   else if (stem[end] == 'd' && stem[end-1] == 'e' && end > 3)
   {
      thisWord.word = stem.substr(0,end-1);
//      cout << stem.substr(0,end-1) << endl;
   }
   else if (stem[end] == 'g' && stem[end-1]=='n' && stem[end-2]=='i')
   {
      thisWord.word = stem.substr(0,end-2);
//      cout << stem.substr(0,end-2) << endl;
   }
   //RYAN
   //Check concept
   //thisWord.score = ConceptSearch::getBeginConceptScore(thisWord.word);
   thisWord.score = MoreWordsSearch::getPrefixConceptScore(thisWord.word,name);
   prefixes.push_back(thisWord);
      

   int lastVowel = stem.substr(0,end+1).find_last_of("aeiouy");
   if (lastVowel == end)
      lastVowel--;
   int firstVowel = stem.find_first_of("aeiouy");
   bool prevVowel = (firstVowel == 0);

//   cout << "first " << firstVowel << " last " << lastVowel << " " << stem << endl;
   wordScore sufWord;
   sufWord.word=stem;
   sufWord.score = MoreWordsSearch::getSuffixConceptScore(sufWord.word,name,endings);
   suffixes.push_back(sufWord);
   for (int i = firstVowel; i < lastVowel; i++)
   {
      //Find the vowels
      if (stem[i]=='a' || stem[i]=='e' || stem[i]=='i' || stem[i]=='o' || stem[i]=='u' || stem[i]== 'y')
      {
         if (i < lastVowel - 2 && stem[i+1]!='a' && stem[i+1]!='e' && stem[i+1]!='i' && stem[i+1]!='o' && stem[i+1]!='u' && stem[i+1]!= 'y'
             && stem[i+2]!='a' && stem[i+2]!='e' && stem[i+2]!='i' && stem[i+2]!='o' && stem[i+2]!='u' && stem[i+2]!= 'y')
         {
            prevVowel = true;
            do{
               if (stem[i+2]=='h' && (stem[i+1]=='t' || stem[i+1]=='c' || stem[i+1]=='s'))
               {
                  if (prevVowel)
                  i--;
                  else
                  i++;
               }
               i++;
               prevVowel = false;
               thisWord.word=stem.substr(0,i+1);
               thisWord.score = MoreWordsSearch::getPrefixConceptScore(thisWord.word,name);
               prefixes.push_back(thisWord);
               sufWord.word=stem.substr(i+1);
               sufWord.score = MoreWordsSearch::getSuffixConceptScore(sufWord.word,name,endings);
               suffixes.push_back(sufWord);
//               cout << stem.substr(0, i+1) << " " << stem.substr(i+1) << " " << stem[i] << " " << i << endl;
               if (stem[i+2]=='h' && (stem[i+1]=='t' || stem[i+1]=='c' || stem[i+1]=='s'))
                  i++;
            } while (stem[i+2]!='a' && stem[i+2]!='e' && stem[i+2]!='i' && stem[i+2]!='o' && stem[i+2]!='u' && stem[i+2]!= 'y' && i < lastVowel);
         }
         else
         {
            thisWord.word=stem.substr(0,i+1);
            thisWord.score = MoreWordsSearch::getPrefixConceptScore(thisWord.word,name);
            prefixes.push_back(thisWord);
            sufWord.word=stem.substr(i+1);
            sufWord.score = MoreWordsSearch::getSuffixConceptScore(sufWord.word,name,endings);
            suffixes.push_back(sufWord);
//            cout << stem.substr(0,i+1) << " " << stem.substr(i+1) << " " << stem[i] << " " << i << endl;
            prevVowel = true;
         }
      }
      else
      {
         prevVowel = false;
      }
   }
}

void Word::setIsWord(bool word)
{
   isWord=word;
}

void Word::setSource(int s)
{
   source = s;
}

void Word::setEndings(vector<string> e)
{
   endings = e;
}

vector<wordScore> Word::getPrefixes()
{
   return prefixes;
}

vector<wordScore> Word::getSuffixes()
{
   return suffixes;
}

bool Word::operator<(const Word& a) const
{
   return stem < a.stem;
}

string Word::getStem()
{
   return stem;
}

string Word::toString()
{
   return (stem);
}

string Word::displayEndings()
{
   string rtn = "";
   for (int i = 0; i < endings.size(); i++)
   {
      rtn.append(" -" + endings[i]);
   }
   return rtn;
}

int Word::getType()
{
   return 1;
}
