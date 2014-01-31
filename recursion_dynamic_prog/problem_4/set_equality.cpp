#include <iostream>
#include <set>
#include <list>
#include <memory>

using namespace std;


bool
is_set_equal (shared_ptr<set<int>> a, shared_ptr<set<int>> b)
{
	cout << "Is true " << (*a == *b) << endl;
	return (*a == *b);
}

int 
main ()
{
	shared_ptr<set <int>> a(new set<int> ());
	shared_ptr<set <int>> b(new set<int> ());
	list <shared_ptr<set<int>>> setList;

	a->insert(3);
	a->insert(4);
	setList.push_back (a);
	
	b->insert(4);
	b->insert(3);
	setList.push_back (b);

	setList.unique(is_set_equal);

	cout << (*a == *b) << endl;
	cout << "Length of the unique list is " << setList.size () << endl;
	return  0;
}
