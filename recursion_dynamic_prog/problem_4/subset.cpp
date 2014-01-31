#include <iostream>
#include <set>
#include <list>
#include <memory>

using namespace std;

typedef list<shared_ptr<set<int>>> setList;


bool
is_set_equal (shared_ptr<set<int>> a, shared_ptr<set<int>> b)
{
	return (*a == *b);
}


static setList
generate_sets (setList appendTo, shared_ptr< list<int> > individualItems)
{
	setList result;


	for (auto i : *individualItems)
	{
		for (auto j : appendTo)
		{
			shared_ptr<set<int>> subset (new set <int> (*j));
			subset->insert (i);
			result.push_back (subset);
		}
	}

	// remove duplicates from result
	result.unique (is_set_equal);

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
	setList result;
	shared_ptr< set<int> > initialSet (new set<int> ());
	shared_ptr< list<int> > individualItems (new list<int> ());

	for (int i=5; i < 9; i ++)
		initialSet->insert (i);

	for (auto i : *initialSet)
	{
		individualItems->push_back (i);

		shared_ptr<set<int>> subset (new set <int> ());
		subset->insert (i);
		result.push_back (subset);
	}

	result = generate_sets (result, individualItems);

	cout << "Total number of subsets generated " << result.size () << endl;

	return 0;
}
