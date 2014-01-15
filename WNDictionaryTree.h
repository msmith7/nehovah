/*
 * WNDictionaryTree.h
 *
 * Mike Smith 2012
 *
 * A tree of the words in WordNet
 */

#include "WNTreeCreator.h"

namespace std
{

   class WNDictionaryTree : public WNTreeCreator
   {
      private:
         static bool instanceFlag;
         static WNDictionaryTree *instance;
         WNDictionaryTree();
      public:
         static WNDictionaryTree* getInstance();
         ~WNDictionaryTree()
         {
            instanceFlag = false;
         }
   };
}
