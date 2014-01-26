#include <iostream>
#include <vector>
#include <map>

using namespace std;

map<int,int> countMap;

int count_possible_steps (vector<int> &possible_steps, int total_steps)
{
	int count = 0;
	
	try {
		int ret = countMap.at(100);
	} catch (const out_of_range &oor)
	{
	}

	for (auto step : possible_steps)
	{
		if (total_steps - step > 0)
			count += count_possible_steps (possible_steps, total_steps - step);
		else if (total_steps - step == 0)
			count++;
	}

	countMap[total_steps] = count;

	return count;
}

int
main (int argc, char *argv[])
{
	vector <int> possible_steps;
	int nSteps;

	cout << "Enter the number of steps as a positive integer greater than zero " << endl;
	cin >> nSteps;
	if (nSteps <= 0) {
		cout << "Invalid argument  - " << nSteps << endl;
		return -1;
	}

	possible_steps.push_back (3);
	possible_steps.push_back (2);
	possible_steps.push_back (1);

	int possible_ways = count_possible_steps (possible_steps, nSteps);
	cout << "Number of possible ways to climb - " << possible_ways << endl;

	return 0;
}
