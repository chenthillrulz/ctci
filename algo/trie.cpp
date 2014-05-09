#include <iostream>
#include <map>
#include <list>
#include <string>

using namespace std;

typedef map<char,bool> charMap;

struct _TrieNode;
typedef struct _TrieNode TrieNode;

struct _TrieNode
{
	char value;
	bool isWord;
	map<char, TrieNode *> *charMap;

	_TrieNode (char val, bool bIsWord):value(val), isWord(bIsWord)
	{
		charMap = new map <char, TrieNode *>;
	}
};


class Trie
{
	private:
		TrieNode *root;

		void InsertString (const char *str, TrieNode *node)
		{
			if (!node)
				return;

			if (!str || !*str)
				return;

			char val = *str;
			bool isWord = false;
			if (str[1] == '\0')
				isWord = true;
			TrieNode *newNode = (*(node->charMap))[val];
			if (!newNode)
			{
				newNode = new TrieNode (val, isWord);
				(*(node->charMap)) [val] = newNode;
			} else
				newNode->isWord = isWord;

			InsertString (str+1, newNode);
		}

		// if maxCount is -1 produce all matches
		void SearchMatches (const char *substr, TrieNode *iNode, list<string> *result, string word, int maxCount)
		{
			if (!iNode || iNode->charMap->size () == 0)
				return;
			if (maxCount != -1 && result->size () >= maxCount)
				return;

			bool hasChar = false;
			if (substr && *substr)
				hasChar = true;

			if (hasChar)
			{
				if (iNode->charMap->find (*substr) == iNode->charMap->end ())
					return;
				word += *substr;
				TrieNode *node = (*(iNode->charMap))[*substr];

				// move forward
				SearchMatches (substr+1, node, result, word, maxCount);
				return;
			}

			for (map<char, TrieNode *>::iterator iter = iNode->charMap->begin (); iter != iNode->charMap->end(); iter++)
			{
				char val = (*iter).first;
				TrieNode *node = (*iter).second;
				string newWord;

				newWord = word + val;
				if (node->isWord)
					result->push_back (newWord);

				// Get deeper
				// Shouldnt we actually do a bfs search here ? ;-)
				SearchMatches (hasChar ? substr+1:substr, node, result, newWord, maxCount);
			}

		}

	public:
		Trie ()
		{
			root = new TrieNode (-1, false);
		}

		void Insert (string &word)
		{
			InsertString (word.c_str (), root);
		}

		void Search (string &prefix, list<string> *result, int maxCount)
		{
			SearchMatches (prefix.c_str (), root, result, "", maxCount);
		}
};


int main ()
{
	int numWords;
	Trie autoCompletionTrie;

	cin >> numWords;
	while (numWords--)
	{
		string word;
		
		cin >> word;
		autoCompletionTrie.Insert (word);
	}

	list<string> result;
	string prefix = "vik";
	autoCompletionTrie.Search (prefix, &result, -1);

	cout << "List of matches " << endl;
	for (list<string>::iterator iter = result.begin(); iter != result.end(); iter++)
	{
		cout << *iter << endl;
	}
}
