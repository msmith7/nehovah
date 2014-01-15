/*
 * WNTreeCreator.h
 *
 *  Created on: Feb 20, 2012
 *      Author: ryanhintze
 */

#ifndef WNTREECREATOR_H_
#define WNTREECREATOR_H_

#include <stdio.h>
#include <string>
#include <fstream>
#include <iostream>
#include "WNTNode.h"

namespace std
{

class WNTreeCreator
{
private:
//      static bool instanceFlag;
//	static WNTreeCreator *instance;
	int count;
public:
	WNTreeCreator(char * fileName);
	WNTreeCreator();
//        static WNTreeCreator* getInstance();
//	~WNTreeCreator()
//	{
//		instanceFlag=false;
//	}
	WNTNode * root;
	bool addDictionary(char * fileName);
	void printCounts(int type, int cutoff = 1, bool above = true);
	void trim(int type, int cutoff, bool above = true);
	void parseWord(string line);
	void parseWordSimple(string line);
	vector<Word*> getStemWords();

private:
	string getNextWord(ifstream & file);
	WNTNode * getNode(WNTNode * parent, char id);
};

} /* namespace std */
#endif /* WNTREECREATOR_H_ */
