#include <iostream>
#include <boost/config.hpp>
#include <string>
#include <stack>
#include <vector>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/depth_first_search.hpp>
#include <boost/graph/breadth_first_search.hpp>
#include <boost/graph/graphviz.hpp>

using namespace std;

struct Vertex
{
	string name;		
};

typedef boost::adjacency_list<boost::setS ,boost::vecS, boost::bidirectionalS, Vertex> DiGraph;
typedef boost::graph_traits<DiGraph>::vertex_descriptor MyVertex;

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

//	boost::write_graphviz (std::cout, g, boost::make_label_writer(boost::get (&Vertex::name, g)));
}

class VertexVisitor : public boost::default_bfs_visitor
{
	set<int> &visited;
	public:
	VertexVisitor (set<int> &reachable):visited(reachable) 
	{
	}

	void discover_vertex (MyVertex v, const DiGraph &g) const
	{
		visited.insert (v);
	}
};

static bool
pattern_matches (string &input, DiGraph &g, string &patt)
{
	set<int> reachable;
	set<int> matches;
	VertexVisitor vis(reachable);
	boost::breadth_first_search (g, 0, boost::visitor(vis));

	for (char c : input)
	{
		for (int i : reachable)
		{
			if (i == (patt.length () - 1))
				continue;

			if (c == patt[i] || c == '.')
				matches.insert (i+1);
		}

		reachable.clear ();
		for (int i : matches)
		{
			boost::breadth_first_search (g, i, boost::visitor(vis));
		}
		matches.clear ();
	}

	for (int v : reachable)
		if (v == (patt.length () - 1))
			return true;

	return false;
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
	bool matches = pattern_matches (inputStr, g, patStr);

	cout << "Pattern matches - " << matches << endl;

	return 0;
}
