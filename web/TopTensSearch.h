/*
 * TopTensSearch.h
 *
 * Mike Smith 
 * April 2012
 */

#ifndef TOPTENSSEARCH_H_
#define TOPTENSSEARCH_H_

#include "curl/curl.h"
#include <string>
#include <iostream>
#include <vector>
#include "../PopWord.h"

namespace std
{
//class TopTensResult;
class TopTensSearch
{
private:
	static int writer(char *data, size_t size, size_t nmemb,
            std::string *buffer);
	static string requestURL(string url);
	static vector<PopWord> parsePage(string buffer, string word);
public:
	static vector<PopWord> getResults(string word);

};

/*
class TopTensResult
{
   string word;
   string title;
   string metainfo;
   int count;

   public:
      TopTensResult(string w, string t, string m);
      TopTensResult(string w, string t);
      void setCount(int c);
      string getWord();
      int getCount();
      string getTitle();
      string getMetainfo();
      bool operator<(const TopTensResult& a) const; 
};
*/
} /* namespace std */
#endif /* TOPTENSSEARCH_H_ */
