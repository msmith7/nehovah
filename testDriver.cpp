#include <iostream>
#include <set>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <strings.h>
#include "neo.h"
#include "web/MoreWordsSearch.h"
#include "web/TopTensSearch.h"
#include "PopWord.h"

using namespace std;

int doRyansTest(int, char **);
int doTopTenTest(int, char **);

int main(int argc, char *argv[])
{

	if (strcasecmp(argv[1], "test") == 0)
	{
		if (argc > 2)
                {
			if (strcasecmp(argv[2], "ryan") == 0)
			{
				doRyansTest(argc, argv);
				return 0;
			}
			else if (strcasecmp(argv[2], "topten") == 0)
			{
				doTopTenTest(argc, argv);
				return 0;
			}
                }
	}
	int searchType = 2; //The type of search wordNet performs

	//Create WNTreeDictionary
	initializeDictionary();
	//vector of string returned from WordNet. The first dimension corresponds
	//to each word searched for. The second dimension corresponds to all of
	//the word's synonyms
	vector<vector<string> > words;
	vector<string> word;
        vector<vector<PopWord> > popWords;
	for (int i = 1; i < argc; i++)
	{
		words.push_back(queryWordNet(argv[i], searchType));
                popWords.push_back(TopTensSearch::getResults(argv[i]));
	}
//   word.push_back("school");
//   word.push_back("educate");
//   words.push_back(word);
//   word.clear();
//   word.push_back("automobile");
//   words.push_back(word);
	vector<Neologism> newWords = combine(words, popWords);
/*
        for (int i = 0; i < newWords.size(); i++)
        {
            cout << "TESTING " << newWords[i].prefix->toString() << endl;
           cout << newWords[i] << endl;
        }

*/	cout << newWords.size() << endl;

	//WNTreeCreator::getInstance()->printCounts(1);
	/*
	 for (int i=0; i<newWords.size(); i++)
	 {
	 cout << score(newWords[i]) << " " << newWords[i] << endl;
	 //      score(newWords[i]);
	 }
	 */
	return 1;
}

int doRyansTest(int argc, char * argv[])
{
	/*vector<MoreWordsResult> results =
			MoreWordsSearch::getMostCommonStartingWith("fast");
	for (int i = 0; i < results.size(); i++)
	{
		printf("%d: \"%s\" wpm = %d\n", i, results[i].word.c_str(),
				results[i].count);
	}
	results = MoreWordsSearch::getMostCommonEndingWith("fast");
	for (int i = 0; i < results.size(); i + i++)
	{
		printf("%d: \"%s\" wpm = %d\n", i + 1, results[i].word.c_str(),
				results[i].count);
	}*/
	vector<string> endings;
	endings.push_back("ion");
	endings.push_back("e");
	endings.push_back("ive");
	printf("Concept score: %s in %s = %f\n","edu","educator",MoreWordsSearch::getPrefixConceptScore("edu","educator"));
	printf("concept score: %s in %s = %f\n","cator","educator",MoreWordsSearch::getSuffixConceptScore("cator","educator"));
	printf("concept score: %s in %s = %f\n","cat","educat",MoreWordsSearch::getSuffixConceptScore("cat","educat",endings));
	vector<string> wordgroup;
	wordgroup.push_back("pants");
	wordgroup.push_back("knickers");
	wordgroup.push_back("bloomers");
	wordgroup.push_back("trousers");
	wordgroup.push_back("jeans");
	string str = "pants";
	printf("Unique score for %s: %f\n",str.c_str(), MoreWordsSearch::getUniqueScore(str,wordgroup));
	str = "knickers";
	printf("Unique score for %s: %f\n",str.c_str(), MoreWordsSearch::getUniqueScore(str,wordgroup));
	str = "bloomers";
	printf("Unique score for %s: %f\n",str.c_str(), MoreWordsSearch::getUniqueScore(str,wordgroup));
	str = "trousers";
	printf("Unique score for %s: %f\n",str.c_str(), MoreWordsSearch::getUniqueScore(str,wordgroup));
	str = "jeans";
	printf("Unique score for %s: %f\n",str.c_str(), MoreWordsSearch::getUniqueScore(str,wordgroup));


	return 0;

}

int doTopTenTest(int argc, char * argv[])
{
	vector<PopWord> results =TopTensSearch::getResults(argv[3]);
	for (int i = 0; i < results.size(); i++)
	{
		printf("\"%s\" %f %s %s\n",results[i].getStem().c_str(), results[i].getCount(), results[i].getTitle().c_str(), results[i].getMetainfo().c_str());
	}
	return 0;
}
