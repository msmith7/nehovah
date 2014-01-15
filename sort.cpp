#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>
//#include <regex.h>
//#include <boost/foreach.hpp>
//#include <boost/tokenizer.hpp>

using namespace std;

struct Neologism
{
   string word;
   double score;
};

bool operator<(const Neologism& left, const Neologism& right)
{
    return left.score < right.score;
}

int main(int argc, char* argv[])
{
   if (argc!= 6 && argc!=7)
   {
      cerr << "Usage: fileName slider1.val slider2.val slider3.val slider4.val (excludedTerms)\n";
      return -1;
   }
   vector<Neologism> neos;
   //filename slider1.val slider2.val slider3.val slider4.val
   char* fileName = argv[1];
//   double pop = (atoi(argv[2])-100) * 1.0/400;
   double pop = atoi(argv[2]) * 1.0/400;
   double con = atoi(argv[3]) * 1.0/200;
   double syl = atoi(argv[4]) * 1.0/200;
   double uni = atoi(argv[5]) * 1.0/200;
   double sum = pop+con+syl+uni;
/*   bool regBool = false;
   char* reg=NULL;
   if (argc==7)
   {
      regBool = true;
      reg = argv[6];
   }
   regex_t regex;
   int reti;

   //compile the regular expression
   if (regBool)
   {
      reti = regcomp(&regex, reg, 0);
      if( reti ) {cerr << "Could not compile regex\n"; exit(1); }
   }
*/
   //cout << pop << " " << con << " " << syl << " " << uni << endl;

   //Read in file
   string line;
   ifstream infile;
   infile.open(fileName);
//cout << reg << endl;
   while(!infile.eof())
   {
      vector<string> tokens;
      getline(infile, line);
/*cout << regBool << " " << reg << endl;
//      if(!regBool || (regBool && regexec(&regex, line.c_str(),0,NULL,0)))
      if(regBool && regexec(&regex, line.c_str(),0,NULL,0))
      {
cout << line << endl;
*/
      boost::split(tokens, line, boost::is_any_of(" "), boost::token_compress_on);
      if (tokens.size() > 6)
      {
         Neologism neo;
         neo.word = line;
//cout << neo.word << endl;
//cout << "Word " << tokens[0] << endl;
         neo.score = (syl * atof(tokens[1].c_str()) + (con * (atof(tokens[2].c_str()) + atof(tokens[3].c_str()))/2) + (uni * atof(tokens[4].c_str())) + (pop *atof( tokens[5].c_str()))) / sum;
//         cout << tokens[1].c_str() << " " << (atof(tokens[2].c_str()) + atof(tokens[3].c_str()))/2 << " " << tokens[4].c_str() << " " << tokens[5].c_str() << " " << line << " " << neo.score << endl;
//cout << "Score " << neo.score << endl;
         neos.push_back(neo);
      }
//      char_separator<char> sep(" ");
//      tokenizer< char_separator<char> > tokens(line, sep);
/*      }
*/
   }
//cout << "file done\n";
   infile.close();
//cout << "sorting\n";
   sort(neos.begin(), neos.end());
//cout << "done sorting\n";
   double score = neos[neos.size()-1].score;
//   for (int i = neos.size()-1; i >= neos.size() || i < 0; i--)
   for (int i = neos.size()-1; i >= 0; i--)
   {
      score = neos[i].score;
      cout << neos[i].score << " " << neos[i].word << endl;
//      cout << neos[i].word << endl;
   }
//cout << pop << " " << con << " " << syl << " " << uni << endl;
//   set<Neologism>::iterator it;
//   for (it = neos.begin(); it != neos.end(); it++)
//      cout << (*it).word << endl;
}
