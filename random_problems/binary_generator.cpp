#include <iostream>
#include <list>
#include <string>
#include <cstdlib>
#include <cmath>

using namespace std;

static void
generate_binary_values (list<string> &intermediate_vals, int &count_iter, int limit)
{
	list<string> updated_intermediate_vals;

	for (list<string>::iterator iter=intermediate_vals.begin(); iter != intermediate_vals.end(); iter++)
	{
		for (int twice = 0; twice < 2; twice++)
		{
			string next = *iter;
			
			if (twice == 0)
				next += " 0";
			else
				next += " 1";
			count_iter++;
			cout << next << endl;
			updated_intermediate_vals.push_back (next);
			if (count_iter == limit)
				return;
		}
	}
	generate_binary_values (updated_intermediate_vals, count_iter, limit);
}


// Generates all binary numbers from 1 to n taking O(1) for each number
int 
main (int argc, char *argv[])
{
	if (argc != 2)
	{
		cout << "Usage ./a.out <limit number> " << endl;
		return -1;
	}

	int limit = atoi (argv[1]);

	if (limit == 0)
		return 0;

	cout << 1 << endl;
	
	if (limit == 1)
	{
		return 0;
	}

	list<string> binaryVals;
	binaryVals.push_back ("1");

	int count_iter = 1;
	generate_binary_values (binaryVals, count_iter, limit);
}
