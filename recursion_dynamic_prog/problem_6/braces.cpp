#include <iostream>
#include <set>
#include <string>
#include <vector>

using namespace std;

const string ins("()");

static void
insert_braces_to_string (string &to_parse, set<string> &output)
{
	vector<int> positions;
	size_t found = to_parse.find('(');
	
	while (found != string::npos)
	{
		positions.push_back (found);
		found = to_parse.find ('(', found+1);
	}

	// insert () before and after positions found. ie two () for each '(' found
	for (auto i : positions)
	{
		for (int j = 0; j < 2; j++)
		{
			string toIns = to_parse;
			toIns.insert (i+j, ins);
			output.insert (toIns);
		}
	}
}

static void
generate_braces (set<string> input, int num, set<string> &result)
{
	set<string> output;

	for (auto i : input)
		insert_braces_to_string (i, output);

	--num;
	if (num > 0)
		generate_braces (output, num, result);
	if (num == 0)
		result = output;

}

int main ()
{
	int num = 2;
	set<string> braces;
	set<string> input;

	input.insert(ins);
	generate_braces (input, num-1, braces);

	for (auto i : braces)
		cout << i << endl;

	cout << "Number of braces generated  " << braces.size () << endl;
	return 0;
}
