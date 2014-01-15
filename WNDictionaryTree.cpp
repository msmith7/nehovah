/*
 * WNDictionaryTree.cpp
 *
 * Mike Smith 2012
 *
 * A tree of the words in WordNet
 */

#include "WNDictionaryTree.h"

using namespace std;

WNDictionaryTree::WNDictionaryTree()
: WNTreeCreator()
{
}

bool WNDictionaryTree::instanceFlag=false;
WNDictionaryTree* WNDictionaryTree::instance = NULL;
WNDictionaryTree* WNDictionaryTree::getInstance()
{
   if(! instanceFlag)
   {
      instance=new WNDictionaryTree();
      instanceFlag=true;
      return instance;
   }
   else
   {
      return instance;
   }
}
