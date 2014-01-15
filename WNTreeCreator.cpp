/*
 * WNTreeCreator.cpp
 *
 *  Created on: Feb 20, 2012
 *      Author: ryanhintze
 */

#include "WNTreeCreator.h"

using namespace std;

WNTreeCreator::WNTreeCreator(char * fileName)
{
	count = 0;
	root = new WNTNode();
	addDictionary(fileName);
}

WNTreeCreator::WNTreeCreator()
{
	count = 0;
	root = new WNTNode();
}

bool WNTreeCreator::addDictionary(char * fileName)
{
	string word;
	ifstream file(fileName);
	if (file.is_open())
	{
		while (file.good())
		{
			word = getNextWord(file);
			parseWord(word);
		}
		file.close();
		return true;
	}
	else
	{
		printf("%d: Invalid File - %s\n", __LINE__, fileName);
		return false;

	}
}

string WNTreeCreator::getNextWord(ifstream & file)
{
	string line;
	while (file.good())
	{
		getline(file, line);
		line = line.substr(0, line.find(" ", 0));
		for (unsigned int i = 0; i < line.size(); i++)
			line[i] = tolower(line[i]);
		if(line.find_first_not_of("abcdefghijklmnopqrstuvwxyz",0) != string::npos)
			continue;
		return line;

	}
	return "";
}

void WNTreeCreator::parseWord(string word)
{
	count++;
	//cout << word << endl;
	//cout << "Unique Count = " << root->uniqueCount << endl;
	bool suffix = true;
	bool prefix = true;
	int start = 0;
	int end = word.size();
	while(start < end)
	{
		WNTNode * currNode = root;
		currNode->useCount++;
		bool setNoVowelBefore = false;
		if((start > 0 && (word[start-1] != 'a' && word[start-1] != 'e' && word[start-1] != 'i'
		&& word[start-1] != 'o' && word[start-1] != 'u' && word[start-1] != 'y'))||start == 0)
		{
			setNoVowelBefore = true;
		}

		for(int i = start; i < end; i++)
		{
			currNode = getNode(currNode, word.at(i));
			if(start == 0)
			{
				currNode->addPrefixWord(word);
				currNode->prefixCount++;
			}
			if(i == end - 1)
			{
				currNode->suffixCount++;
				if (start == 0)
					currNode->isWord = true;
			}
			currNode->useCount++;
			if(setNoVowelBefore)
				currNode->vowelBefore = false;
			if(i < end - 1 && word[i+1] != 'a' && word[i+1] != 'e' && word[i+1] != 'i'
					&& word[i+1] != 'o' && word[i+1] != 'u' && word[i+1] != 'y')
				currNode->vowelAfter  = false;
		}
		start++;

	}

}

void WNTreeCreator::parseWordSimple(string word)
{
	count++;
	//cout << word << endl;
	//cout << "Unique Count = " << root->uniqueCount << endl;
	bool suffix = true;
	bool prefix = true;
	int start = 0;
	int end = word.size();
//	while(start < end)
//	{
		WNTNode * currNode = root;
		currNode->useCount++;
		bool setNoVowelBefore = false;
		if((start > 0 && (word[start-1] != 'a' && word[start-1] != 'e' && word[start-1] != 'i'
		&& word[start-1] != 'o' && word[start-1] != 'u' && word[start-1] != 'y'))||start == 0)
		{
			setNoVowelBefore = true;
		}

		for(int i = start; i < end; i++)
		{
			currNode = getNode(currNode, word.at(i));
			if(start == 0)
				currNode->prefixCount++;
			if(i == end - 1)
			{
				currNode->suffixCount++;
				if (start == 0)
					currNode->isWord = true;
			}
			currNode->useCount++;
			if(setNoVowelBefore)
				currNode->vowelBefore = false;
			currNode->vowelAfter = (i < end - 1 && (word[i+1] == 'a' || word[i+1] == 'e' || word[i+1] == 'i'
					|| word[i+1] == 'o' || word[i+1] == 'u' || word[i+1] == 'y'));
		}
//		start++;

//	}

}

WNTNode * WNTreeCreator::getNode(WNTNode * parent, char id)
{
	if(id == 'a')
	{
		if(parent->a == NULL) //Need to create new node
		{
			parent->a = new WNTNode(id);
			parent->a->parent = parent;
			//increase unique count
			parent->a->increaseUniqueCount();
			parent->linkCount++;
		}
		return parent->a;
	}
	if(id == 'b')
	{
		if(parent->b == NULL) //Need to create new node
		{
			parent->b = new WNTNode(id);
			parent->b->parent = parent;
			//increase unique count
			parent->b->increaseUniqueCount();
			parent->linkCount++;
		}
		return parent->b;
	}
	if(id == 'c')
	{
		if(parent->c == NULL) //Need to create new node
		{
			parent->c = new WNTNode(id);
			parent->c->parent = parent;
			//increase unique count
			parent->c->increaseUniqueCount();
			parent->linkCount++;
		}
		return parent->c;
	}
	if(id == 'd')
	{
		if(parent->d == NULL) //Need to create new node
		{
			parent->d = new WNTNode(id);
			parent->d->parent = parent;
			//increase unique count
			parent->d->increaseUniqueCount();
			parent->linkCount++;
		}
		return parent->d;
	}
	if(id == 'e')
	{
		if(parent->e == NULL) //Need to create new node
		{
			parent->e = new WNTNode(id);
			parent->e->parent = parent;
			//increase unique count
			parent->e->increaseUniqueCount();
			parent->linkCount++;
		}
		return parent->e;
	}
	if(id == 'f')
	{
		if(parent->f == NULL) //Need to create new node
		{
			parent->f = new WNTNode(id);
			parent->f->parent = parent;
			//increase unique count
			parent->f->increaseUniqueCount();
			parent->linkCount++;
		}
		return parent->f;
	}
	if(id == 'g')
	{
		if(parent->g == NULL) //Need to create new node
		{
			parent->g = new WNTNode(id);
			parent->g->parent = parent;
			//increase unique count
			parent->g->increaseUniqueCount();
			parent->linkCount++;
		}
		return parent->g;
	}
	if(id == 'h')
	{
		if(parent->h == NULL) //Need to create new node
		{
			parent->h = new WNTNode(id);
			parent->h->parent = parent;
			//increase unique count
			parent->h->increaseUniqueCount();
			parent->linkCount++;
		}
		return parent->h;
	}
	if(id == 'i')
	{
		if(parent->i == NULL) //Need to create new node
		{
			parent->i = new WNTNode(id);
			parent->i->parent = parent;
			//increase unique count
			parent->i->increaseUniqueCount();
			parent->linkCount++;
		}
		return parent->i;
	}
	if(id == 'j')
	{
		if(parent->j == NULL) //Need to create new node
		{
			parent->j = new WNTNode(id);
			parent->j->parent = parent;
			//increase unique count
			parent->j->increaseUniqueCount();
			parent->linkCount++;
		}
		return parent->j;
	}
	if(id == 'k')
	{
		if(parent->k == NULL) //Need to create new node
		{
			parent->k = new WNTNode(id);
			parent->k->parent = parent;
			//increase unique count
			parent->k->increaseUniqueCount();
			parent->linkCount++;
		}
		return parent->k;
	}
	if(id == 'l')
	{
		if(parent->l == NULL) //Need to create new node
		{
			parent->l = new WNTNode(id);
			parent->l->parent = parent;
			//increase unique count
			parent->l->increaseUniqueCount();
			parent->linkCount++;
		}
		return parent->l;
	}
	if(id == 'm')
	{
		if(parent->m == NULL) //Need to create new node
		{
			parent->m = new WNTNode(id);
			parent->m->parent = parent;
			//increase unique count
			parent->m->increaseUniqueCount();
			parent->linkCount++;
		}
		return parent->m;
	}
	if(id == 'n')
	{
		if(parent->n == NULL) //Need to create new node
		{
			parent->n = new WNTNode(id);
			parent->n->parent = parent;
			//increase unique count
			parent->n->increaseUniqueCount();
			parent->linkCount++;
		}
		return parent->n;
	}
	if(id == 'o')
	{
		if(parent->o == NULL) //Need to create new node
		{
			parent->o = new WNTNode(id);
			parent->o->parent = parent;
			//increase unique count
			parent->o->increaseUniqueCount();
			parent->linkCount++;
		}
		return parent->o;
	}
	if(id == 'p')
	{
		if(parent->p == NULL) //Need to create new node
		{
			parent->p = new WNTNode(id);
			parent->p->parent = parent;
			//increase unique count
			parent->p->increaseUniqueCount();
			parent->linkCount++;
		}
		return parent->p;
	}
	if(id == 'q')
	{
		if(parent->q == NULL) //Need to create new node
		{
			parent->q = new WNTNode(id);
			parent->q->parent = parent;
			//increase unique count
			parent->q->increaseUniqueCount();
			parent->linkCount++;
		}
		return parent->q;
	}
	if(id == 'r')
	{
		if(parent->r == NULL) //Need to create new node
		{
			parent->r = new WNTNode(id);
			parent->r->parent = parent;
			//increase unique count
			parent->r->increaseUniqueCount();
			parent->linkCount++;
		}
		return parent->r;
	}
	if(id == 's')
	{
		if(parent->s == NULL) //Need to create new node
		{
			parent->s = new WNTNode(id);
			parent->s->parent = parent;
			//increase unique count
			parent->s->increaseUniqueCount();
			parent->linkCount++;
		}
		return parent->s;
	}
	if(id == 't')
	{
		if(parent->t == NULL) //Need to create new node
		{
			parent->t = new WNTNode(id);
			parent->t->parent = parent;
			//increase unique count
			parent->t->increaseUniqueCount();
			parent->linkCount++;
		}
		return parent->t;
	}
	if(id == 'u')
	{
		if(parent->u == NULL) //Need to create new node
		{
			parent->u = new WNTNode(id);
			parent->u->parent = parent;
			//increase unique count
			parent->u->increaseUniqueCount();
			parent->linkCount++;
		}
		return parent->u;
	}
	if(id == 'v')
	{
		if(parent->v == NULL) //Need to create new node
		{
			parent->v = new WNTNode(id);
			parent->v->parent = parent;
			//increase unique count
			parent->v->increaseUniqueCount();
			parent->linkCount++;
		}
		return parent->v;
	}
	if(id == 'w')
	{
		if(parent->w == NULL) //Need to create new node
		{
			parent->w = new WNTNode(id);
			parent->w->parent = parent;
			//increase unique count
			parent->w->increaseUniqueCount();
			parent->linkCount++;
		}
		return parent->w;
	}
	if(id == 'x')
	{
		if(parent->x == NULL) //Need to create new node
		{
			parent->x = new WNTNode(id);
			parent->x->parent = parent;
			//increase unique count
			parent->x->increaseUniqueCount();
			parent->linkCount++;
		}
		return parent->x;
	}
	if(id == 'y')
	{
		if(parent->y == NULL) //Need to create new node
		{
			parent->y = new WNTNode(id);
			parent->y->parent = parent;
			//increase unique count
			parent->y->increaseUniqueCount();
			parent->linkCount++;
		}
		return parent->y;
	}
	if(id == 'z')
	{
		if(parent->z == NULL) //Need to create new node
		{
			parent->z = new WNTNode(id);
			parent->z->parent = parent;
			//increase unique count
			parent->z->increaseUniqueCount();
			parent->linkCount++;
		}
		return parent->z;
	}
	cout << "ENCOUNTERED UNKNOWN CHAR - " << id << " - ERROR!" << endl;
	return NULL;
}

vector<Word*> WNTreeCreator::getStemWords()
{
  return root->getStemWords(); 
}

void WNTreeCreator::printCounts(int type, int cutoff, bool above)
{
	root->printCounts(type, "", cutoff, above);
}

void WNTreeCreator::trim(int type, int cutoff, bool above)
{
	root->trim(type, cutoff, above);
}


/* namespace std */
