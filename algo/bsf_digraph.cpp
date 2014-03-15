#include "digraph.hpp"
#include <sstream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <queue>

using namespace std;

class BFS
{
	public:
		BFS (DiGraph<int> &iGraph):graph(iGraph) 
		{
			queue<int> visitedNodes;
			int connID = 0;
			
			for (map<int, Node<int> *>::iterator iter=graph.nodes->begin(); iter != graph.nodes->end(); ++iter)
			{
				if (visited[iter->first] == false)
				{
					visitedNodes.push (iter->first);
					connID++;
				}

				while (!visitedNodes.empty ())
				{
					int node = visitedNodes.front ();
					visitedNodes.pop ();
					visited[node] = true;
					connectionMap[node] = connID;

					for (set<Node<int> *>::iterator iter1 = (graph.nodes->at(node))->edges->begin(); 
							iter1 != (graph.nodes->at(node))->edges->end(); ++iter1)
					{
						if (visited[(*iter1)->vertex] == false)
							visitedNodes.push ((*iter1)->vertex);
					}
				}
			}
		}

		bool isConnected (int v, int w)
		{
			if (connectionMap[v] == connectionMap[w])
				return true;
			else 
				return false;
		}

	private:
		DiGraph<int> &graph;
		map<int, int> connectionMap; 
		map<int, bool> visited; 
};

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

	BFS bfs(graph);

	cout << "is 1 and 4 connected " << bfs.isConnected (1, 4) << endl;
	cout << "is 2 and 4 connected " << bfs.isConnected (2, 4) << endl;
	cout << "is 1 and 6 connected " << bfs.isConnected (1, 6) << endl;
	cout << "is 5 and 6 connected " << bfs.isConnected (5, 6) << endl;

	return 0;
}
