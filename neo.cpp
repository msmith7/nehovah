/*
 * neo.cpp
 *
 * Mike Smith 2012
 */

#include <algorithm>
#include <iostream>
#include <set>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include "wn.h"
#include "neo.h"

using namespace std;

struct DereferenceLess
{
   template <typename PtrType>
   bool operator()(PtrType pT1, PtrType pT2) const
   {    
      return *pT1 < *pT2;
   }    
};

void initializeDictionary()
{  
   WNDictionaryTree* wnt = WNDictionaryTree::getInstance();
   wnt->addDictionary("/usr/share/wordnet/index.noun");
   wnt->addDictionary("/usr/share/wordnet/index.adv");
   wnt->addDictionary("/usr/share/wordnet/index.adj");
   wnt->addDictionary("/usr/share/wordnet/index.verb");
}

vector<Neologism> combine(vector< vector <string> > words, vector<vector<PopWord> > popWords)
{
   vector<Neologism> combine;
   set<Neologism*, DereferenceLess> unique;
   vector< vector <Word*> > stemmedWords;

   WNDictionaryTree* wnt = WNDictionaryTree::getInstance();

   //Create a WNTree of the words from each source word
   for (int i=0; i < words.size(); i++)
   {
      WNTreeCreator wnt = WNTreeCreator();
      for (int j=0; j<words[i].size(); j++)
      {
         wnt.parseWordSimple(words[i][j]);
      }
      stemmedWords.push_back(wnt.getStemWords());
   }

   //Add pop culture words to be combined
   for (int i=0; i < popWords.size(); i++)
   {
      for (int j=0; j<popWords[i].size(); j++)
      {
         stemmedWords[i].push_back(&popWords[i][j]);
      }
   }

   //Combine the prefixes and suffixes
   for (int i = 0; i < stemmedWords.size()-1; i++)
   {

      for (int j = 0; j < stemmedWords[i].size(); j++)
      {
         vector<wordScore> prefix1 = stemmedWords[i][j]->getPrefixes();
         vector<wordScore> suffix1 = stemmedWords[i][j]->getSuffixes();

         for (int x = i+1; x < stemmedWords.size(); x++)
         {
            for (int y = 0; y < stemmedWords[x].size(); y++)
            {
               vector<wordScore> prefix2 = stemmedWords[x][y]->getPrefixes();
               vector<wordScore> suffix2 = stemmedWords[x][y]->getSuffixes();

               for(int preIt = 0; preIt < prefix1.size(); preIt++)
               {
                  for(int sufIt = 0; sufIt < suffix2.size(); sufIt++)
                  {
                     int val = 1;
                     if (prefix1[preIt].word.size() < val)
                        val = prefix1[preIt].word.size();
                     WNTNode *node = wnt->root->getWord(prefix1[preIt].word.substr(prefix1[preIt].word.size()-val) + suffix2[sufIt].word.substr(0,1));
                     if (node != NULL)
                     {
                        string newWord = prefix1[preIt].word + suffix2[sufIt].word;
                        if (newWord.compare(stemmedWords[i][j]->getStem()) != 0 && newWord.compare(stemmedWords[x][y]->getStem()) != 0) 
                        {
                           Neologism* neo = new Neologism(newWord, prefix1[preIt].score, suffix2[sufIt].score); //prefix1[preIt] + suffix2[sufIt]);
                           neo->setPrefix(stemmedWords[i][j]);
                           neo->setSuffix(stemmedWords[x][y]);
                           unique.insert(neo);
                        }
                     }
                  }
               }

               for(int preIt = 0; preIt < prefix2.size(); preIt++)
               {
                  for(int sufIt = 0; sufIt < suffix1.size(); sufIt++)
                  {
                     int val = 1;
                     if (prefix2[preIt].word.size() <val)
                        val = prefix2[preIt].word.size();
                     WNTNode *node = wnt->root->getWord(prefix2[preIt].word.substr(prefix2[preIt].word.size()-val) + suffix1[sufIt].word.substr(0,1));
                     if (node != NULL)
                     {
                        string newWord = prefix2[preIt].word + suffix1[sufIt].word;
                        if (newWord.compare(stemmedWords[x][y]->getStem()) != 0 && newWord.compare(stemmedWords[i][j]->getStem()) != 0) 
                        {
                           Neologism* neo = new Neologism(newWord, prefix2[preIt].score, suffix1[sufIt].score);
                           neo->setPrefix(stemmedWords[x][y]);
                           neo->setSuffix(stemmedWords[i][j]);
                           unique.insert(neo);
                        }
                     }
                  }
               }
            }
         }
      }
   }

   set<Neologism*>::iterator it;
   for ( it=unique.begin(); it!=unique.end(); it++)
   {
      (*it)->scoreWord();
      combine.push_back(*(*it));
      if ((*it)->checkScore())
         cout << *(*it) << endl;
   }
   return combine;
}

vector<string> queryWordNet(string word, int searchType)
{
   vector<string> words;
   set<string> unique_words;
   //initialize the wordNet library
   wninit();

   //Read in the word and lookup type from the command line
   //See http://wordnet.princeton.edu/man/wnsearch.3WN.html
   //section on ptr_type

   //Loop through the 4 parts of speech:
   //1- NOUN
   //2- VERB
   //3- ADJECTIVE
   //4- ADVERB
   for (int j=1; j <= 4; j++)
   {
      //If the word is not defined for the POS, find its stem
      if (is_defined((char*)word.c_str(), j) == 0)
      {
         char* morph = morphstr((char*)word.c_str(),j);
         if (morph != NULL)
            word=(string) morph;
      }
      
      //Get the information about the word
      SynsetPtr synSet = findtheinfo_ds((char*)word.c_str(),j,searchType,ALLSENSES);
//      if (synSet != NULL)
//      cout << "Synset: " << synSet->hereiam << " " << j << " " << word << endl;

      //Loop through the synsets
      while(synSet)
      {
         //Loop through the words in each synset (the senses)
         int i = 0;
         for (i = 0; i < synSet->wcount; i++)
         {
            if (((string)synSet->words[i]).find("-")==string::npos)
            {
            char* split = strtok(synSet->words[i],"_");
            while(split != NULL)
            {
               unique_words.insert(split);
               split = strtok(NULL, "_");
            }
            }
         }

         //add the first level of synonyms
         SynsetPtr syns = traceptrs_ds(synSet,searchType,j,0);
         if (syns!=NULL)
         {
            for (i =0; i < syns->wcount;i++)
            {

            if (((string)syns->words[i]).find("-")==string::npos)
            {
               char* split = strtok(syns->words[i],"_");
               while(split != NULL)
               {
                  unique_words.insert(split);
                  split = strtok(NULL, "_");
               }
            }
            }
         }
         free_syns(syns);
         //get the next synset
         synSet=synSet->nextss;
      }

      //Free memory occupied by the synset
      free_syns(synSet);

   }

   set<string>::iterator it;
   for (it=unique_words.begin(); it!=unique_words.end(); it++)
   {
      string dude = *it;
      std::transform(dude.begin(), dude.end(), dude.begin(), ::tolower);
      words.push_back(dude);//*it);
   }
   return words;
}

vector<wordScore> scoreWords(vector<string> words)
{
   vector<wordScore> scored_words;
   for (int i =0; i < words.size(); i++)
   {
      wordScore thisWord;
      thisWord.word=words[i];
      thisWord.score=score(words[i]);
   }

   return scored_words;
}

double score(string word)
{
   WNDictionaryTree* wnt = WNDictionaryTree::getInstance();
   int size = word.size();
   //std::transform(word.begin(), word.end(), word.begin(), ::tolower);
   WNTNode *node = wnt->root->getWord(word);
   int sum=0;
   int pre=0;
   int suf=0;
   int length = 3;
   string prefix;
   string suffix;
   bool needSuf = true;

if (word.size() >=length)
{
   for (int i =0; i<word.size()-length+1;i++)
   {
      node=wnt->root->getWord(word.substr(i,length));
      //Weed out bad words
      if (node == NULL)
      {
         sum=0;
         break;
      }
      //Find the best prefix and suffix
      if(node->useCount == 0) 
         return 0;
      
      if (i ==0)
      {
         pre = node->prefixCount;
      }
      else if(i == word.size()-3)
      {
         suf=node->suffixCount;
      }

   }
}
   if (pre ==0)
      return 0;

   //Some how decide if the word captures the intended concepts
   
   return 1;
   return (sum * 1.0/(word.size()-length + 1)) + pre + suf;

   //Look for prefix and suffix scores/counts
   for (int i =1; i<size; i++)
   {
      //Looks at the prefix
      cout << word.substr(0, size-i) << endl;
      node = wnt->root->getWord(word.substr(0,size-i));
      if (node == NULL)
      {
         cout << "\tNULL\n";
      }
      else
      {
         cout << "WordCount\t" << word.substr(0,size-i).size() << endl;
         cout << "UseCount\t" << node->useCount << endl;
         cout << "PreCount\t" << node->prefixCount << endl;
         cout << "SufCount\t" << node->suffixCount << endl;
         cout << "UniCount\t" << node->uniqueCount << endl;
      }
      delete(node);
      //Looks at the suffix
      cout << word.substr(i) << endl;
      node = wnt->root->getWord(word.substr(i));
      if (node == NULL)
      {
         cout << "\tNULL\n";
      }
      else
      {
         cout << "WordCount\t" << word.substr(i).size() << endl;
         cout << "UseCount\t" << node->useCount << endl;
         cout << "PreCount\t" << node->prefixCount << endl;
         cout << "SufCount\t" << node->suffixCount << endl;
         cout << "UniCount\t" << node->uniqueCount << endl;
      }
      delete(node);
   }
   return 0.1;
}
