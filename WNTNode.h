/*
 * WNTNode.h
 *
 *  Created on: Feb 20, 2012
 *      Author: ryanhintze
 */

#ifndef WNTNODE_H_
#define WNTNODE_H_

#include "stdio.h"
#include "iostream"
#include <stdlib.h>
#include <vector>
#include "Word.h"

namespace std
{

class WNTNode
{
private:
public:
	static const int SUFFIX = 0;
	static const int PREFIX = 1;
	static const int UNIQUE = 2;
	static const int COUNT  = 3;
	static const int LINK   = 4;

	static const int MAX_PREFIX_WORDS = 50;
	int useCount;
	int prefixCount;
	int suffixCount;
	int uniqueCount;
	int linkCount;				//Count of how many nodes link to this one
	bool vowelAfter;
	bool vowelBefore;
	bool isWord;
	bool isAmbiguous;
	bool syllable;
	bool isVowel;
	char id;
	WNTNode * a;
	WNTNode * b;
	WNTNode * c;
	WNTNode * d;
	WNTNode * e;
	WNTNode * f;
	WNTNode * g;
	WNTNode * h;
	WNTNode * i;
	WNTNode * j;
	WNTNode * k;
	WNTNode * l;
	WNTNode * m;
	WNTNode * n;
	WNTNode * o;
	WNTNode * p;
	WNTNode * q;
	WNTNode * r;
	WNTNode * s;
	WNTNode * t;
	WNTNode * u;
	WNTNode * v;
	WNTNode * w;
	WNTNode * x;
	WNTNode * y;
	WNTNode * z;
	WNTNode * parent;
	vector<string> prefix_words;
private:

	///HELPER FUNCTIONS///
	void init();
	bool printCount(int type, string current, int cutoff = 1, bool above = true);
	bool trimMe(int type, int cutoff, bool above = true);
        void getEndings(vector<string>& endings, string current, int count);

public:
	WNTNode();
	WNTNode(char);
	~WNTNode(){};
	void increaseUniqueCount();													///< increases the unique count of the node and all its parents
	void printWordStats(string word);											///< Prints obtained statistics about a requested word
	WNTNode * getWord(string word);												///< Gets a word from a string
	void printCounts(int type, string current,
			int cutoff = 1, bool above = true);									///< Prints Count Statistics
	void trim(int type, int cutoff, bool above = true);							///< Trims the tree
	vector<Word*> getStemWords();
	void getStemWords(vector<Word*>& words, string current);

	void addPrefixWord(string word);
	void printPrefixWords();
};

} /* namespace std */
#endif /* WNTNODE_H_ */
