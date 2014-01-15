/*
 * WNTNode.cpp
 *
 *  Created on: Feb 20, 2012
 *      Author: ryanhintze
 */

#include "WNTNode.h"

using namespace std;

WNTNode::WNTNode()
{
	id = '0';
	init();
}

WNTNode::WNTNode(char nid)
{
	if (!isalpha(nid))
	{
		cout << "Error Trying to add -> " << nid << endl;
		exit(0);
	}
	id = nid;
	init();
}

void WNTNode::init()
{
	useCount = 0;
	prefixCount = 0;
	suffixCount = 0;
	uniqueCount = 0;
	linkCount = 0;
	vowelAfter = true;
	vowelBefore = true;
	isWord = false;
	isAmbiguous = false;
	syllable = false;
	parent = NULL;
	a = NULL;
	b = NULL;
	c = NULL;
	d = NULL;
	e = NULL;
	f = NULL;
	g = NULL;
	h = NULL;
	i = NULL;
	j = NULL;
	k = NULL;
	l = NULL;
	m = NULL;
	n = NULL;
	o = NULL;
	p = NULL;
	q = NULL;
	r = NULL;
	s = NULL;
	t = NULL;
	u = NULL;
	v = NULL;
	w = NULL;
	x = NULL;
	y = NULL;
	z = NULL;
}

void WNTNode::increaseUniqueCount()
{
	uniqueCount++;
	if (parent != NULL)
		parent->increaseUniqueCount();
}
void WNTNode::printWordStats(string word)
{
	WNTNode * wnode = getWord(word);

	if (wnode != NULL)
	{
		string vowelAfter = "false";
		if (wnode->vowelAfter)
			vowelAfter = "true";
		string vowelBefore = "false";
		if (wnode->vowelBefore)
			vowelBefore = "true";
		printf(
				"word = %s\n\tSuffix Count = %d\n\tPrefix Count = %d\n\tUnique Count = %d\n\tCount = %d\n\tVowel Before = %s\n\tVowel After = %s\n",
				word.c_str(), wnode->suffixCount, wnode->prefixCount,
				wnode->uniqueCount, wnode->useCount, vowelBefore.c_str(),
				vowelAfter.c_str());
	}
	else
		printf("word = %s\n\tNOT FOUND!\n", word.c_str());
}

WNTNode * WNTNode::getWord(string word)
{
	if (word.size() == 0)
		return this;
	if (word[0] == 'a')
	{
		if (a == NULL)
			return NULL;
		else
			return a->getWord(word.substr(1, word.size() - 1));
	}
	if (word[0] == 'b')
	{
		if (b == NULL)
			return NULL;
		else
			return b->getWord(word.substr(1, word.size() - 1));
	}
	if (word[0] == 'c')
	{
		if (c == NULL)
			return NULL;
		else
			return c->getWord(word.substr(1, word.size() - 1));
	}
	if (word[0] == 'd')
	{
		if (d == NULL)
			return NULL;
		else
			return d->getWord(word.substr(1, word.size() - 1));
	}
	if (word[0] == 'e')
	{
		if (e == NULL)
			return NULL;
		else
			return e->getWord(word.substr(1, word.size() - 1));
	}
	if (word[0] == 'f')
	{
		if (f == NULL)
			return NULL;
		else
			return f->getWord(word.substr(1, word.size() - 1));
	}
	if (word[0] == 'g')
	{
		if (g == NULL)
			return NULL;
		else
			return g->getWord(word.substr(1, word.size() - 1));
	}
	if (word[0] == 'h')
	{
		if (h == NULL)
			return NULL;
		else
			return h->getWord(word.substr(1, word.size() - 1));
	}
	if (word[0] == 'i')
	{
		if (i == NULL)
			return NULL;
		else
			return i->getWord(word.substr(1, word.size() - 1));
	}
	if (word[0] == 'j')
	{
		if (j == NULL)
			return NULL;
		else
			return j->getWord(word.substr(1, word.size() - 1));
	}
	if (word[0] == 'k')
	{
		if (k == NULL)
			return NULL;
		else
			return k->getWord(word.substr(1, word.size() - 1));
	}
	if (word[0] == 'l')
	{
		if (l == NULL)
			return NULL;
		else
			return l->getWord(word.substr(1, word.size() - 1));
	}
	if (word[0] == 'l')
	{
		if (l == NULL)
			return NULL;
		else
			return l->getWord(word.substr(1, word.size() - 1));
	}
	if (word[0] == 'm')
	{
		if (m == NULL)
			return NULL;
		else
			return m->getWord(word.substr(1, word.size() - 1));
	}
	if (word[0] == 'n')
	{
		if (n == NULL)
			return NULL;
		else
			return n->getWord(word.substr(1, word.size() - 1));
	}
	if (word[0] == 'o')
	{
		if (o == NULL)
			return NULL;
		else
			return o->getWord(word.substr(1, word.size() - 1));
	}
	if (word[0] == 'p')
	{
		if (p == NULL)
			return NULL;
		else
			return p->getWord(word.substr(1, word.size() - 1));
	}
	if (word[0] == 'q')
	{
		if (q == NULL)
			return NULL;
		else
			return q->getWord(word.substr(1, word.size() - 1));
	}
	if (word[0] == 'r')
	{
		if (r == NULL)
			return NULL;
		else
			return r->getWord(word.substr(1, word.size() - 1));
	}
	if (word[0] == 's')
	{
		if (s == NULL)
			return NULL;
		else
			return s->getWord(word.substr(1, word.size() - 1));
	}
	if (word[0] == 't')
	{
		if (t == NULL)
			return NULL;
		else
			return t->getWord(word.substr(1, word.size() - 1));
	}
	if (word[0] == 'u')
	{
		if (u == NULL)
			return NULL;
		else
			return u->getWord(word.substr(1, word.size() - 1));
	}
	if (word[0] == 'v')
	{
		if (v == NULL)
			return NULL;
		else
			return v->getWord(word.substr(1, word.size() - 1));
	}
	if (word[0] == 'w')
	{
		if (w == NULL)
			return NULL;
		else
			return w->getWord(word.substr(1, word.size() - 1));
	}
	if (word[0] == 'x')
	{
		if (x == NULL)
			return NULL;
		else
			return x->getWord(word.substr(1, word.size() - 1));
	}
	if (word[0] == 'y')
	{
		if (y == NULL)
			return NULL;
		else
			return y->getWord(word.substr(1, word.size() - 1));
	}
	if (word[0] == 'z')
	{
		if (z == NULL)
			return NULL;
		else
			return z->getWord(word.substr(1, word.size() - 1));
	}
	return NULL;
}

bool WNTNode::printCount(int type, string current, int cutoff, bool above)
{
	int valToPrint = 0;
	if (type == SUFFIX)
		valToPrint = suffixCount;

	else if (type == PREFIX)
		valToPrint = prefixCount;
	else if (type == UNIQUE)
		valToPrint = uniqueCount;
	else if (type == COUNT)
		valToPrint = useCount;
	else if (type == LINK)
		valToPrint = linkCount;
	else
	{
		printf("UNKNOWN TYPE %d\n", type);
		return false;
	}
	if (above)
	{
		if (valToPrint >= cutoff)
			printf("%d %s\n", valToPrint, current.c_str());
	}
	else
	{

		if (valToPrint <= cutoff && valToPrint > 0)
			printf("%d %s\n", valToPrint, current.c_str());
	}
	return true;

}

/* Prints information about all nodes based on type, cutoff and above parameters.
 *
 * @param type - What information to print (SUFFIX,PREFIX,COUNT,UNIQUE). Easy to set using WNTNode::COUNT etc...
 * @param current - a string that carries information about the current traversal of nodes (root->a->p->p->l->e would produce 'apple')
 * @param cutoff - The cutoff value for printing info, inclusive
 * @param above - default = true, print values above the cutoff if true, below if false
 */
void WNTNode::printCounts(int type, string current, int cutoff, bool above)
{
	if (id != '0') //Not root
	{
		current += id;
		if (!printCount(type, current, cutoff, above))
			return;
	}
	if (a != NULL)
		a->printCounts(type, current, cutoff, above);
	if (b != NULL)
		b->printCounts(type, current, cutoff, above);
	if (c != NULL)
		c->printCounts(type, current, cutoff, above);
	if (d != NULL)
		d->printCounts(type, current, cutoff, above);
	if (e != NULL)
		e->printCounts(type, current, cutoff, above);
	if (f != NULL)
		f->printCounts(type, current, cutoff, above);
	if (g != NULL)
		g->printCounts(type, current, cutoff, above);
	if (h != NULL)
		h->printCounts(type, current, cutoff, above);
	if (i != NULL)
		i->printCounts(type, current, cutoff, above);
	if (j != NULL)
		j->printCounts(type, current, cutoff, above);
	if (k != NULL)
		k->printCounts(type, current, cutoff, above);
	if (l != NULL)
		l->printCounts(type, current, cutoff, above);
	if (m != NULL)
		m->printCounts(type, current, cutoff, above);
	if (n != NULL)
		n->printCounts(type, current, cutoff, above);
	if (o != NULL)
		o->printCounts(type, current, cutoff, above);
	if (p != NULL)
		p->printCounts(type, current, cutoff, above);
	if (q != NULL)
		q->printCounts(type, current, cutoff, above);
	if (r != NULL)
		r->printCounts(type, current, cutoff, above);
	if (s != NULL)
		s->printCounts(type, current, cutoff, above);
	if (t != NULL)
		t->printCounts(type, current, cutoff, above);
	if (u != NULL)
		u->printCounts(type, current, cutoff, above);
	if (v != NULL)
		v->printCounts(type, current, cutoff, above);
	if (w != NULL)
		w->printCounts(type, current, cutoff, above);
	if (x != NULL)
		x->printCounts(type, current, cutoff, above);
	if (y != NULL)
		y->printCounts(type, current, cutoff, above);
	if (z != NULL)
		z->printCounts(type, current, cutoff, above);
}

bool WNTNode::trimMe(int type, int cutoff, bool above)
{

	int * valToTrim;
	if (type == SUFFIX)
		valToTrim = &suffixCount;

	else if (type == PREFIX)
		valToTrim = &prefixCount;
	else if (type == UNIQUE)
		valToTrim = &uniqueCount;
	else if (type == COUNT)
		valToTrim = &useCount;
	else if (type == LINK)
		valToTrim = &linkCount;
	else
	{
		printf("UNKNOWN TYPE %d\n", type);
		return false;
	}

	if (above)
	{
		if (*valToTrim >= cutoff)
			(*valToTrim) = 0;
	}
	else
	{
		if (*valToTrim <= cutoff)
			(*valToTrim) = 0;
	}
	return true;
}

/* Trims the node based on type, cutoff and above parameters.
 *
 * @param type - which parameter the nodes are supposed to be trimmed on. Easy to set using WNTNode::COUNT etc...
 * @param cutoff - The value which they are to be trimmed about, inclusive
 * @param above - default = true, trim above the cutoff if true, below the cutoff if false
 *
 */
void WNTNode::trim(int type, int cutoff, bool above)
{
	if (id != '0') //Not root
	{
		if (!trimMe(type, cutoff, above))
			return;
	}
	if (a != NULL)
		a->trim(type, cutoff, above);
	if (b != NULL)
		b->trim(type, cutoff, above);
	if (c != NULL)
		c->trim(type, cutoff, above);
	if (d != NULL)
		d->trim(type, cutoff, above);
	if (e != NULL)
		e->trim(type, cutoff, above);
	if (f != NULL)
		f->trim(type, cutoff, above);
	if (g != NULL)
		g->trim(type, cutoff, above);
	if (h != NULL)
		h->trim(type, cutoff, above);
	if (i != NULL)
		i->trim(type, cutoff, above);
	if (j != NULL)
		j->trim(type, cutoff, above);
	if (k != NULL)
		k->trim(type, cutoff, above);
	if (l != NULL)
		l->trim(type, cutoff, above);
	if (m != NULL)
		m->trim(type, cutoff, above);
	if (n != NULL)
		n->trim(type, cutoff, above);
	if (o != NULL)
		o->trim(type, cutoff, above);
	if (p != NULL)
		p->trim(type, cutoff, above);
	if (q != NULL)
		q->trim(type, cutoff, above);
	if (r != NULL)
		r->trim(type, cutoff, above);
	if (s != NULL)
		s->trim(type, cutoff, above);
	if (t != NULL)
		t->trim(type, cutoff, above);
	if (u != NULL)
		u->trim(type, cutoff, above);
	if (v != NULL)
		v->trim(type, cutoff, above);
	if (w != NULL)
		w->trim(type, cutoff, above);
	if (x != NULL)
		x->trim(type, cutoff, above);
	if (y != NULL)
		y->trim(type, cutoff, above);
	if (z != NULL)
		z->trim(type, cutoff, above);

}

vector<Word*> WNTNode::getStemWords()
{
   vector<Word*> words;
   string dude;
   getStemWords(words, dude);
   return words;
}

void WNTNode::getStemWords(vector<Word*>& words, string current)
{
	if (id != '0') //Not root
	{
		current += id;
	}
//if (syllable)
//{
//   cout << current << endl;
//}
        if(current.size() > 3 && linkCount > 1)
        {
		Word* stem = new Word();
		stem->setStem(current);
		stem->setIsWord(isWord);
                vector<string> endings;
                string end;
                getEndings(endings, end, 0);
                stem->setEndings(endings);
	      	words.push_back(stem);
		return;
        }
        else if (isWord)
        {
		Word* stem = new Word();
		stem->setStem(current);
		stem->setIsWord(isWord);
                if (linkCount > 0)
                {
                   vector<string> endings;
                   string end;
                   getEndings(endings, end, 0);
                   stem->setEndings(endings);
                } 
	      	words.push_back(stem);
		if (useCount == 2)
			return;
        }

	if (a != NULL)
		a->getStemWords(words, current);
	if (b != NULL)
		b->getStemWords(words, current);
	if (c != NULL)
		c->getStemWords(words, current);
	if (d != NULL)
		d->getStemWords(words, current);
	if (e != NULL)
		e->getStemWords(words, current);
	if (f != NULL)
		f->getStemWords(words, current);
	if (g != NULL)
		g->getStemWords(words, current);
	if (h != NULL)
		h->getStemWords(words, current);
	if (i != NULL)
		i->getStemWords(words, current);
	if (j != NULL)
		j->getStemWords(words, current);
	if (k != NULL)
		k->getStemWords(words, current);
	if (l != NULL)
		l->getStemWords(words, current);
	if (m != NULL)
		m->getStemWords(words, current);
	if (n != NULL)
		n->getStemWords(words, current);
	if (o != NULL)
		o->getStemWords(words, current);
	if (p != NULL)
		p->getStemWords(words, current);
	if (q != NULL)
		q->getStemWords(words, current);
	if (r != NULL)
		r->getStemWords(words, current);
	if (s != NULL)
		s->getStemWords(words, current);
	if (t != NULL)
		t->getStemWords(words, current);
	if (u != NULL)
		u->getStemWords(words, current);
	if (v != NULL)
		v->getStemWords(words, current);
	if (w != NULL)
		w->getStemWords(words, current);
	if (x != NULL)
		x->getStemWords(words, current);
	if (y != NULL)
		y->getStemWords(words, current);
	if (z != NULL)
		z->getStemWords(words, current);
}

void WNTNode::getEndings(vector<string>& endings, string current, int count)
{
   if (count > 0)
   {
   current += id;
   if (isWord)
   {
      endings.push_back(current);
   }
   }
   count++;

	if (a != NULL)
                a->getEndings(endings, current, count);
        if (b != NULL)
                b->getEndings(endings, current, count);
        if (c != NULL)
                c->getEndings(endings, current, count);
        if (d != NULL)
                d->getEndings(endings, current, count);
        if (e != NULL)
                e->getEndings(endings, current, count);
        if (f != NULL)
                f->getEndings(endings, current, count);
        if (g != NULL)
                g->getEndings(endings, current, count);
        if (h != NULL)
                h->getEndings(endings, current, count);
        if (i != NULL)
                i->getEndings(endings, current, count);
        if (j != NULL)
                j->getEndings(endings, current, count);
        if (k != NULL)
                k->getEndings(endings, current, count);
        if (l != NULL)
                l->getEndings(endings, current, count);
        if (m != NULL)
                m->getEndings(endings, current, count);
        if (n != NULL)
                n->getEndings(endings, current, count);
        if (o != NULL)
                o->getEndings(endings, current, count);
        if (p != NULL)
                p->getEndings(endings, current, count);
        if (q != NULL)
                q->getEndings(endings, current, count);
        if (r != NULL)
                r->getEndings(endings, current, count);
        if (s != NULL)
                s->getEndings(endings, current, count);
        if (t != NULL)
                t->getEndings(endings, current, count);
        if (u != NULL)
                u->getEndings(endings, current, count);
        if (v != NULL)
                v->getEndings(endings, current, count);
        if (w != NULL)
                w->getEndings(endings, current, count);
        if (x != NULL)
                x->getEndings(endings, current, count);
        if (y != NULL)
                y->getEndings(endings, current, count);
        if (z != NULL)
                z->getEndings(endings, current, count);

}

void WNTNode::addPrefixWord(string word)
{
	if(isAmbiguous)
		return;
	prefix_words.push_back(word);
	if(prefix_words.size() >= MAX_PREFIX_WORDS)
		isAmbiguous = true;
}

void WNTNode::printPrefixWords()
{
	for (int i =0; i<prefix_words.size(); i++)
		printf("%s ", prefix_words[i].c_str());
	printf("\n");
}
