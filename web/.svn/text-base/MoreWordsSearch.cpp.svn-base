/*
 * MoreWordsSearch.cpp
 *
 *  Created on: Mar 22, 2012
 *      Author: ryanhintze
 */

#include "MoreWordsSearch.h"
#include "boost/regex.hpp"
#include <math.h>

namespace std
{

/* CREDIT TO TODD
 *
 * This is a very simple example of how to use libcurl from within
 * a C++  program. The basic idea is that you want to retrieve the
 * contents of a web page as a string. Obviously, you can replace
 * the buffer object with anything you want and adjust elsewhere
 * accordingly.
 *
 * Hope you find it useful..
 *
 * Todd Papaioannou
 */

int MoreWordsSearch::writer(char *data, size_t size, size_t nmemb,
		std::string *buffer)
{
	// What we will return
	int result = 0;

	// Is there anything in the buffer?
	if (buffer != NULL)
	{
		// Append the data to the buffer
		buffer->append(data, size * nmemb);

		// How much did we write?
		result = size * nmemb;
	}

	return result;
}

string MoreWordsSearch::requestURL(string url)
{
	string buffer;
	char errorBuffer[CURL_ERROR_SIZE]; // Our curl objects
	CURL *curl;
	CURLcode result;

	// Create our curl handle
	curl = curl_easy_init();

	if (curl)
	{
		// Now set up all of the curl options
		curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, errorBuffer);
		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
		curl_easy_setopt(curl, CURLOPT_HEADER, 0);
		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writer);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);

		// Attempt to retrieve the remote page
		result = curl_easy_perform(curl);

		// Always cleanup
		curl_easy_cleanup(curl);

		// Did we succeed?
		if (result != CURLE_OK)
		{
//			cout << "Page Successfully Retrieved" << endl;
//			//cout << buffer << "\n";
//		}
//		else
//		{
			cout << "Error: [" << result << "] - " << errorBuffer;
			return "";
		}
	}
	else
	{
		cout << "Could not curl!" << endl;
		return "";
	}
	return buffer;
}
vector<MoreWordsResult> MoreWordsSearch::parsePage(const string buffer, const string regex)
{
	vector<MoreWordsResult> results;
	boost::smatch what;
	boost::regex expr(regex);
	string tempbuffer = buffer;
	int start = 0;
	while (start < buffer.length()
			&& boost::regex_search(tempbuffer, what, expr,
					boost::match_default))
	{
		int a = 0;
		start += (int) what.position(a) + (int) what[0].length();
		/*// FOR DEBUGGING
		 unsigned i, j;
		 std::cout << "** Match found **\n Sub-Expressions:\n";
		 for (i = 0; i < what.size(); i++)
		 std::cout << " $" << i << " = \"" << what[i] << "\"" << endl;
		 //*/
			results.push_back(
					*(new MoreWordsResult(what[1].str(),
							atoi(what[2].str().c_str()))));
		tempbuffer = buffer.substr(start);
	}
//	if (results.size() == 0)
//	{
//		std::cout << "** No Match found **\n";
//	}
	return results;
}
/*
 * The old favorite
 */
vector<MoreWordsResult> MoreWordsSearch::getMostCommonStartingWith(string word)
{
	string buffer;
	vector<MoreWordsResult> results;
	if (word.length() < 1 || word.find('_') != string::npos)
		return results;

	struct stat st;
	if (stat("./data", &st) != 0)
	{
		system("mkdir ./data");
	}
	if (stat("./data/prefix", &st) != 0)
	{
		system("mkdir ./data/prefix");
	}
	//convert to lower
	for(int i=0; i < word.length(); i++)
	{
		word[i] = tolower(word[i]);
	}
	string file = "./data/prefix/" + word + ".mwr";
	ifstream infile(file.c_str());
	if (infile.is_open())
	{
		string line;
		while (infile.good())
		{
			getline(infile, line);
			string found = line.substr(0, line.find('\t'));
			int count = atoi(line.substr(line.find('\t') + 1).c_str());
			if (found.length() > 0)
			{
				MoreWordsResult mwr(found, count);
				results.push_back(mwr);
				//printf("%s: pushing %s - %d\n", file.c_str(), mwr.word.c_str(),
				//		mwr.count);
			}
		}
		infile.close();

	}
	else
	{
		string url(
				"http://www.morewords.com/most-common-starting-with/" + word
						+ "/");

//		cout << "Retrieving " << url << endl;

		buffer = requestURL(url);

		if (buffer.length() != 0)
		{
			results =
					parsePage(
							buffer,
							"<a href=\"/word/(.+)/\">\\1</a> <small>\\((\\d+)\\)</small><br />");
		}
		ofstream outfile(file.c_str());
		if (outfile.is_open())
		{
			for (int i = 0; i < results.size(); i++)
			{
				outfile << results[i].word << "\t" << results[i].count << endl;
			}
			outfile.close();
		}
	}
	return results;
}

/*
 * The old favorite
 */
vector<MoreWordsResult> MoreWordsSearch::getMostCommonEndingWith(string word)
{
	string buffer;
	vector<MoreWordsResult> results;

	if (word.length() < 1 || word.find('_') != string::npos)
		return results;


	struct stat st;
	if (stat("./data", &st) != 0)
	{
		system("mkdir ./data");
	}
	if (stat("./data/suffix", &st) != 0)
	{
		system("mkdir ./data/suffix");
	}
	//convert to lower
	for(signed int i=0; i < word.length(); i++)
	{
		word[i] = tolower(word[i]);
	}
	string file = "./data/suffix/" + word + ".mwr";

	ifstream infile(file.c_str());
	if (infile.is_open())
	{
		string line;
		while (infile.good())
		{
			getline(infile, line);
			string found = line.substr(0, line.find('\t'));
			int count = atoi(line.substr(line.find('\t') + 1).c_str());
			if (found.length() > 0)
			{
				MoreWordsResult mwr(found, count);
				results.push_back(mwr);
				//printf("%s: pushing %s - %d\n", file.c_str(), mwr.word.c_str(),
				//		mwr.count);
			}
		}

		infile.close();
	}
	else
	{
	string url("http://www.morewords.com/most-common-ends-with/" + word + "/");

//	cout << "Retrieving " << url << endl;

	buffer = requestURL(url);

	if (buffer.length() != 0)
	{
		results =
				parsePage(
						buffer,
						"<a href=\"/word/(.+)/\">\\1</a> <small> - <strong>\\d</strong>, (\\d+)</small><br />");
	}
	ofstream outfile(file.c_str());
	if (outfile.is_open())
	{
		for (int i = 0; i < results.size(); i++)
		{
			outfile << results[i].word << "\t" << results[i].count << endl;
		}
		outfile.close();
	}


	}
	return results;
}

MoreWordsResult::MoreWordsResult(string _word, int _count)
{
	word = _word;
	count = _count;
}

double MoreWordsSearch::getPrefixConceptScore(string pre, string word)
{
	//Verify that it is a prefix
	if (word.find(pre) != 0)
	{
		return 0.0;
	}
	if (word.find('_') != string::npos)
	{
		word = word.substr(0, word.find('_'));
		//cout << "word changed to " << word << endl;
	}
	vector<MoreWordsResult> result = getMostCommonStartingWith(pre);
	return getConceptScore(pre, word, result);
}

double MoreWordsSearch::getPrefixTopNScore(string pre, string word, int N)
{
	//Verify that it is a prefix
	if (word.find(pre) != 0)
	{
		return 0.0;
	}
	vector<MoreWordsResult> result = getMostCommonStartingWith(pre);
	return getTopNScore(word, N, result);
}

double MoreWordsSearch::getSuffixConceptScore(string suf, string word)
{
	//Verify that it is a prefix
	if (word.find(suf) < 0)
	{
		return 0.0;
	}
	vector<MoreWordsResult> result = getMostCommonEndingWith(suf);
	return getConceptScore(suf, word, result);
}

double MoreWordsSearch::getSuffixConceptScore(string suffix, string word, vector<string> endings)
{
	if(endings.size() == 0)
		return getSuffixConceptScore(suffix, word);
	double sum = 0.0;
	for(signed int i=0; i< endings.size(); i++)
	{
		sum += getSuffixConceptScore(suffix + endings[i], word + endings[i]);
		//cout << suffix+endings[i] << " in " << word+endings[i] << endl;
	}
	return sum/(double)endings.size();
}

double MoreWordsSearch::getSuffixTopNScore(string suf, string word, int N)
{
	//Verify that it is a prefix
	if (word.find(suf) < 0)
	{
		return 0.0;
	}
	vector<MoreWordsResult> result = getMostCommonEndingWith(suf);
	return getTopNScore(word, N, result);
}

double cutoffHIGH  = 0.10;
double cutoffLOW = 0.01;
double cutoffLow_score=0.8;
double MoreWordsSearch::getConceptScore(string part, string word,
		vector<MoreWordsResult> mwr)
{

	if (mwr.size() == 0)
		return 0.0;
	double sum = 0.5;
	double wordScore = 0.5;
	double max = 0.5;
	for (int i = 0; i < mwr.size(); i++)
	{
		if (mwr[i].word.compare(word) == 0)
			wordScore += (double) mwr[i].count;
		sum += mwr[i].count;
	}
	double score = wordScore/sum;
	if(score >= cutoffHIGH)
		return 1.0;
	if(score >= cutoffLOW)
	{
		//solve cutoff properties
		double a=(cutoffLow_score-1)/(cutoffLOW-cutoffHIGH);
		double b=(cutoffLOW-cutoffHIGH*cutoffLow_score)/(cutoffLOW-cutoffHIGH);
		return score*a+b;
	}
	return (score/cutoffLOW)*cutoffLow_score;
}

double MoreWordsSearch::getUniqueScore(string word, vector<string> wordGroup)
{
	if (wordGroup.size() == 0)
		return 1.0;
	vector<MoreWordsResult> allWords = getWords(wordGroup);
	MoreWordsResult myword = getWord(word);
	int max = myword.count;
	for(int i=0; i< allWords.size(); i++)
	{
		if (allWords[i].count > max)
			max = allWords[i].count;
	}
	if(max == 0.0)
		return 1.0;
	return 1.0 - (double)myword.count/(double)max;

}

vector<MoreWordsResult> MoreWordsSearch::getWords(vector<string> words)
{
	vector<MoreWordsResult> ret;
	for(int i=0; i< words.size(); i++)
	{
		ret.push_back(getWord(words[i]));
	}
	return ret;
}

MoreWordsResult MoreWordsSearch::getWord(string word)
{
	vector<MoreWordsResult> all = getMostCommonStartingWith(word);
	for(int i=0; i < all.size(); i++)
		if(all[i].word.compare(word) == 0)
			return all[i];
	MoreWordsResult ret(word, 0);
	return ret;
}

double MoreWordsSearch::getTopNScore(string word, int N,
		vector<MoreWordsResult> mwr)
{
	if (mwr.size() == 0)
		return 0.0;
	if (mwr.size() < N)
		N = mwr.size();
	for (int i = 0; i < N; i++)
		if (word.compare(mwr[i].word) == 0)
			return ((double) (N - i)) / ((double) N);
	return 0;
}

MoreWordsSearch::MoreWordsInfo MoreWordsSearch::getPrefixInfo(string pre,
		string word, int N)
{
	vector<MoreWordsResult> results = getMostCommonStartingWith(pre);
	return getInfo(pre, word, N, results);

}

MoreWordsSearch::MoreWordsInfo MoreWordsSearch::getSuffixInfo(string suf,
		string word, int N)
{
	vector<MoreWordsResult> results = getMostCommonEndingWith(suf);
	return getInfo(suf, word, N, results);

}

MoreWordsSearch::MoreWordsInfo MoreWordsSearch::getInfo(string part,
		string word, int N, vector<MoreWordsResult> mwr)
{
	MoreWordsInfo mwi;
	mwi.part = part;
	mwi.word = word;
	mwi.results = mwr;
	mwi.conceptScore = getConceptScore(part, word, mwr);
	mwi.topNScore = getTopNScore(word, N, mwr);
	mwi.uniqueScore = 0;
	return mwi;
}

} /* namespace std */

