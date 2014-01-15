/*
 * TopTensSearch.cpp
 *
 * Mike Smith April 2012
 */

#include "TopTensSearch.h"
#include "boost/regex.hpp"
#include "boost/algorithm/string.hpp"
#include <math.h>
#include "rapidxml.hpp"
#include <wn.h>
#include <set>
#include "../PopWord.h"

namespace std
{

struct DereferenceLess
{
   template <typename PtrType>
   bool operator()(PtrType pT1, PtrType pT2) const
   {
      return *pT1 < *pT2;
   }
};

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

int TopTensSearch::writer(char *data, size_t size, size_t nmemb,
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

string TopTensSearch::requestURL(string url)
{
	string buffer;
	char errorBuffer[CURL_ERROR_SIZE]; // Our curl objects
	CURL *curl;
	CURLcode result;

	// Create our curl handle
	curl = curl_easy_init();

        struct curl_slist *headers=NULL;
        headers=curl_slist_append(headers, "User-Agent: Nehovah (http://axon.cs.byu.edu/~nehovah/");

	if (curl)
	{
		// Now set up all of the curl options
		curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, errorBuffer);
		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
		curl_easy_setopt(curl, CURLOPT_HEADER, 0);
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
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
			//cout << buffer << "\n";
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
vector<PopWord> TopTensSearch::parsePage(string buffer, string word)
{
   vector<PopWord> results;
   set<PopWord*, DereferenceLess> unique;
//   boost::smatch what;
//   boost::regex expr(regex);

   //parse the XML document
   rapidxml::xml_document<> doc;
   doc.parse<0>((char*)buffer.c_str());

   rapidxml::xml_node<> *node = doc.first_node();

   //Filter the titles
   string exp(".*st "+word+"s?( (?!(in|about|from)).*|$)|.(?!\\w+s)* "+word+"s( (?!.*(in|about|from)).*|$)|.* "+word+"s? ((?!color)|(\\w+))s( (?!.*(in|about|from)).*|$)");
   boost::regex e(exp, boost::regex::icase);
   wninit();

   for (rapidxml::xml_node<> *list = node->first_node(); list; list = list->next_sibling())
   {
      //The list has:
      // * title
      // * link
      // * items
//      printf("Title: %s\n", list->first_node("title")->value());
      
      const string test = list->first_node("title")->value();
      //Determine if the title is any good
      if(boost::regex_match(test, e))
      {

         int count = 0;
         for (rapidxml::xml_node<> *attr = list->first_node("items")->first_node(); attr && count < 5; attr = attr->next_sibling())
         {
            std::string item = (std::string) attr->value();
            boost::regex re(" (in |from |of |- |\\(|:)", boost::regbase::icase);
            boost::sregex_token_iterator i(item.begin(), item.end(), re, -1);
            boost::sregex_token_iterator j;
            std::string found = *i++;
            if (i!=j)
            {
               boost::replace_all(found, " ", "_");
               //PopWord* pop = new PopWord(found, test, *i);
               set<PopWord*>::iterator it = unique.insert(unique.begin(), new PopWord(found, test, *i));
//               if (it != unique.end())
//               {
//                  cout << (*it)->getCount();
                  (*it)->incrementCount();
//                  cout << "\t1 |" << (*it)->getStem() << "|\t" << *i << " " << (*it)->getCount() << endl;
//               }
//               else
//                  unique.insert(pop);
            }
            else
            {
               boost::replace_all(item, " ", "_");
               bool inWN = false;

               for (int j=1; j <= 4; j++)
               {
                  //If the word is defined for the POS
                  if (is_defined((char*)item.c_str(), j) != 0)
                  {
                     set<PopWord*>::iterator it = unique.insert(unique.begin(), new PopWord(item, test));
                     (*it)->incrementCount();
                     inWN=true;
//                     cout << "\t\t2 " << item << endl;
                     break;
                  }
                  else 
                  {
                     char* morph = morphstr((char*)item.c_str(),j);
                     if (morph != NULL)
                     {
                        set<PopWord*>::iterator it = unique.insert(unique.begin(), new PopWord(item, test));
                        (*it)->incrementCount();
                        inWN=true;
//                        cout << "\t\t3 " << item << endl;
                        break;
                     }
                  }
               }
//               if(!inWN)
//                  std::cout << "Not used\t\t4 "<<item << std::endl;
            }
         }
      }
   }

   //Iterate through the unique set. Check how apparent the concept is in wikipedia
   int maxCount = 0;
   set<PopWord*>::iterator it;
   for (it=unique.begin(); it !=unique.end(); it++)
   {
      PopWord ttr = *(*it);
//      cout << ttr.getWord() << endl;
      //int count = -1;
      if (false)
      {
      string buffer = requestURL("http://en.wikipedia.org/w/api.php?format=json&action=parse&page="+ttr.getStem()+"&prop=links&redirects");
      boost::regex re("[\"\\s(:]" + word + "s?[)\"\\s]", boost::regbase::icase);
      boost::sregex_token_iterator i(buffer.begin(), buffer.end(), re, -1);
      boost::sregex_token_iterator j;

	      
//      cout << "-->\t" << buffer << endl;
      while (i != j)
      {
//         cout << "\t" << *i++ << endl;
         ttr.incrementCount();
      }
//      cout << count << endl << endl;
      }
     // ttr.setCount(count);
     if (ttr.getCount() > maxCount)
        maxCount=ttr.getCount();
      results.push_back(ttr);
      
   }
   for (int i =0; i < results.size(); i++)
   {
      results[i].setCount(results[i].getCount()/maxCount);
   }
   return results;
}

/*
 * The old favorite
 */
vector<PopWord> TopTensSearch::getResults(string word)
{
	string buffer;
	vector<PopWord> results;

	string url("http://share.thetoptens.com/mrsmith7.asp?s=" + word);
        //is user input plural?
        if (word[word.size()-1] !='s')
           url.append("s");
        else if (word[word.size()-2] != 's')
           word = word.substr(0, word.size()-1);

//	cout << "Retrieving " << url << endl;

	buffer = requestURL(url);

	if (buffer.length() != 0)
	{
		results=parsePage(buffer, word);
	}
	return results;
}
/*
PopWord::PopWord(string w, string t, string m)
{
   PopWord(w,t);
   metainfo=m;
}

PopWord::PopWord(string w, string t)
{
   word = w;
   title = t;
}

void PopWord::setCount(int c)
{
   count = c;
}

string PopWord::getWord()
{
   return word;
}

int PopWord::getCount()
{
   return count;
}

string PopWord::getTitle()
{
   return title;
}

string PopWord::getMetainfo()
{
   return metainfo;
}

bool PopWord::operator<(const PopWord& a) const
{
   return word < a.word;
}
*/
}
