/*
 * MoreWordsSearch.h
 *
 *  Created on: Mar 22, 2012
 *      Author: ryanhintze
 */

#ifndef MOREWORDSSEARCH_H_
#define MOREWORDSSEARCH_H_

#include "curl/curl.h"
#include <string>
#include <iostream>
#include <vector>
#include <iostream>
#include <fstream>
#include <sys/stat.h>

namespace std
{
class MoreWordsResult;
class MoreWordsSearch
{
public:
	struct MoreWordsInfo
	{
		string part;
		string word;
		vector<MoreWordsResult> results;
		double conceptScore;
		double topNScore;
		double uniqueScore;
	};
private:
	static int writer(char *data, size_t size, size_t nmemb,
            std::string *buffer);
	static string requestURL(string url);
	static vector<MoreWordsResult> parsePage(const string buffer, const string regex);
	static double getConceptScore(string part, string word, vector<MoreWordsResult> mwr);
	static double getTopNScore   (string word, int N, vector<MoreWordsResult> mwr);
	static MoreWordsInfo getInfo (string part, string word, int N, vector<MoreWordsResult> mwr);
	static MoreWordsResult getWord(string word);
	static vector<MoreWordsResult> getWords(vector<string> words);
public:
	static vector<MoreWordsResult> getMostCommonStartingWith(string word);
	static vector<MoreWordsResult> getMostCommonEndingWith  (string word);
	static double        getPrefixConceptScore(string prefix, string word);
	static double        getSuffixConceptScore(string suffix, string word);
	static double        getSuffixConceptScore(string suffix, string word, vector<string> endings);
	static double        getPrefixTopNScore   (string prefix, string word, int N=10);
	static double        getSuffixTopNScore   (string suffix, string word, int N=10);
	static double        getUniqueScore       (string word,   vector<string> wordGroup);
	static MoreWordsInfo getPrefixInfo        (string prefix, string word, int N=10);
	static MoreWordsInfo getSuffixInfo        (string suffix, string word, int N=10);
	//static vector<MoreWordsResult> getMostCommonWith(string word);//Doesn't exist on Morewords.com

};

class MoreWordsResult
{
public:
	string word;
	int count;
	MoreWordsResult(string _word,int _count);
};

} /* namespace std */
#endif /* MOREWORDSSEARCH_H_ */
