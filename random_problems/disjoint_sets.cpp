#include <set>
#include <list>
#include <iostream>
#include <sstream>

using namespace std;

typedef list< set<int> > listSet;


bool compare_length (set<int> &first, set<int> &second)
{
	return (first.size() < second.size());
}

int
main (int argc, char *argv[])
{
	listSet disjointList;
	int iter;

	set<int> a;
	cin >> iter;
	
	string dummy;	
	getline (cin, dummy);

	while (iter)
	{
		string line;
		set<int> iSet;

		cout << "Set begin: " << endl;

		getline (cin, line);
		stringstream ss(line);
		while (true) 
		{
		    int a;

		    ss >> a;
		    if (ss.fail())
			    break;
		    
		    iSet.insert (a);
		    cout << a << " ";
		}
		
		cout << "Set end: "<< endl;

		disjointList.push_back(iSet);
		--iter;
	}

	cout << "Number of sets: " << disjointList.size() << endl;
	disjointList.sort(compare_length);
	for (listSet::iterator iter=disjointList.begin(); iter != disjointList.end(); ++iter)
		cout << (*iter).size() << " ";
	cout << endl;
}
