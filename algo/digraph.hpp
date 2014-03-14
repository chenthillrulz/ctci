#include <iostream>
#include <set>
#include <map>

using namespace std;

template <class T>
class Node {
	public:
		T vertex;
		set<Node *> *edges;

		Node(T vert):vertex(vert)
		{
			edges = new set<Node *> ();
		}

		~Node ()
		{
			delete edges;
		}
};

template <class T>
class DiGraph {
	private:
		map<T, Node<T> *> *nodes;
	public:
		DiGraph ()
		{
			nodes = new map<T, Node<T> *> ();
		}

		~DiGraph ()
		{
			// iterate through map and delete nodes
		}

		// skipping error checks
		void addVertex (T vertex) 
		{
			if (nodes->count (vertex) == 0) {
				Node <T> *node = new Node<T> (vertex);
				nodes.insert (pair<T, Node<T> *> (vertex, node));
			}
		}

		void addSingleDirectionalEdge (T v, T w)
		{
			addVertex (v);
			addVertex (w);
			(nodes[v])->edges->insert (w);
		}

		void addBiDirectionalEdge (T v, T w)
		{
			addVertex (v);
			addVertex (w);
			nodes[v]->edges->insert (w);
			nodes[w]->edges->insert (v);
		}


};
