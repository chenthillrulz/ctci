#include <iostream>
#include <boost/config.hpp>
#include <string>
#include <stack>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graphviz.hpp>

using namespace std;

struct Vertex
{
	string name;		
};

typedef boost::adjacency_list<boost::setS ,boost::vecS, boost::bidirectionalS, Vertex> DiGraph;

static void
formDirectedGraph (DiGraph &g, string &patStr)
{
	stack<int> brace_or;

	int len = patStr.length();
	for (int i = 0 ; i < len; i++)
	{
		char c = patStr[i];
		int lb = i;

		add_vertex (g);
		g[i].name = patStr[i];
		
		if (c == '(' || c == '|')
			brace_or.push (i);
		else if (c == ')')
		{
			int orC = brace_or.top();
			brace_or.pop();
			if (patStr[orC] == '|')
			{
				lb = brace_or.top();
				brace_or.pop();
				add_edge (lb, orC+1, g);
				add_edge (orC, i, g);
			} else
				lb = orC;

		}

		if (i < len-1 && patStr[i+1] == '*')
		{
			add_edge (lb, i+1, g);
			add_edge (i+1, lb, g);
		}

		if (c == '(' || c == '*' || c == ')')
			add_edge (i, i+1, g);
	}

	boost::write_graphviz (std::cout, g, boost::make_label_writer(boost::get (&Vertex::name, g)));
}

int main (int argc, char *argv[])
{
	if (argc != 3) {
		cout << "Usage: ./prog input_string pattern_string  \n";
		return -1;
	}

	string inputStr (argv[1]);
	string patStr(argv[2]);

	DiGraph g;
	formDirectedGraph (g, patStr);

	return 0;
}
