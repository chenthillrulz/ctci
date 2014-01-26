#include <iostream>
#include <set>
#include <list>
#include <memory>

using namespace std;

typedef list<shared_ptr<set<int>>> setList;

bool
is_set_equal (shared_ptr<set<int>> a, shared_ptr<set<int>> b)
{
	bool isEqual = (*a == *b);
//	cout << "Set is equal " << isEqual << endl;
	return isEqual;
}

bool
list_compare_func (shared_ptr<set<int>> a, shared_ptr<set<int>> b)
{
	return *a < *b;	
}

bool
has_item_in_set (shared_ptr<set<int>> sptrSet, int val)
{
	set<int>::iterator iter;

	iter = sptrSet->find (val);
	return (iter != sptrSet->end());
}

static setList
generate_sets (setList appendTo, shared_ptr< list<int> > individualItems)
{
	setList result;

	for (auto i : *individualItems)
	{
		for (auto j : appendTo)
		{
			if (has_item_in_set (j, i) == false)
			{
				shared_ptr<set<int>> subset (new set <int> (*j));
				subset->insert (i);
				result.push_back (subset);
			}
		}
	}

	// remove duplicate sets from result
	result.sort (list_compare_func);
	result.unique (is_set_equal);

	cout << "Number of subsets generated in current recursive call " << result.size () << endl;

	if (result.size () != 1)
	{
		setList resultToAdd = generate_sets (result, individualItems);
		result.merge(resultToAdd);
	}

	return result;
}

int 
main ()
{
	setList result, resultToAdd;
	shared_ptr< set<int> > initialSet (new set<int> ());
	shared_ptr< list<int> > individualItems (new list<int> ());

	cout << "Problem: Generate all subsets for set { ";
	for (int i=5; i < 9; i ++)
	{
		cout << i << " ";	
		initialSet->insert (i);
	}
	cout << "}" << endl;


	for (auto i : *initialSet)
	{
		individualItems->push_back (i);

		shared_ptr<set<int>> subset (new set <int> ());
		subset->insert (i);
		result.push_back (subset);
	}

	resultToAdd = generate_sets (result, individualItems);
	result.merge (resultToAdd);
	
	cout << "subsets generated " << endl;
	for (auto i : result)
	{
		cout << "Subset elements " << endl;
		for (auto j : *i)
		{
			cout << " " << j;
		}
		cout << endl;
	}
	cout << "Total number of subsets generated " << result.size () << endl;

	return 0;
}
