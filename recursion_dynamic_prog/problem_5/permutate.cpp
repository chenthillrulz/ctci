#include <iostream>
#include <string>
#include <map>
#include <boost/timer/timer.hpp>

using namespace std;

static void
permutate (string &outputBuilder, string &remaining, map<string, bool> &results)
{
	if (remaining.empty ()) {
		results[outputBuilder] = true;
		return;
	}

	string::iterator first = remaining.begin ();
	for (string::iterator iter = first; iter != remaining.end(); ++iter)
	{
		string newOutput = outputBuilder + *iter;

		string newRemaining = remaining;
		int distance = iter - first;
		newRemaining.erase (distance, 1);

		permutate (newOutput, newRemaining, results);
	}

	return;
}

int main ()
{
	string input("permutate");
	string outputBuilder("");
	map<string,bool> results;
	boost::timer::auto_cpu_timer t(3);

	permutate (outputBuilder, input, results);

	/* for (auto i : results)
	{
		cout << i.first << endl;
	} */

	cout << "Number of permutations of the string " << results.size () << endl;
	return 0;
}
