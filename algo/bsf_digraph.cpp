#include "digraph.hpp"
#include <sstream>
#include <string>
#include <cstdlib>
#include <cstring>

using namespace std;

int main ()
{
	string line;
	Node <int> dummy(1);
	DiGraph<int> graph;

	line.reserve (100);
	while (true)
	{
		getline (cin, line);
		if (!strcmp (line.c_str(), "END"))
			break;
		istringstream iss (line);
		string v, w;
		iss >> v;
		iss >> w;

		graph.addSingleDirectionalEdge (atoi (v.c_str ()), atoi(w.c_str()));
	}
}
