#include <iostream>
#include <set>
#include <map>

using namespace std;

template <class T>
class Node {
	public:
		T vertex;
		set<Node<T> *> *edges;

		Node(T vert):vertex(vert)
		{
			edges = new set<Node<T> *> ();
		}

		~Node ()
		{
			delete edges;
		}
};

template <class T>
class DiGraph {
	public:
		map<T, Node<T> *> *nodes;
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
				nodes->insert (pair<T, Node<T> *> (vertex, node));
			}
		}

		void addSingleDirectionalEdge (T v, T w)
		{
			addVertex (v);
			addVertex (w);
			(nodes->at(v))->edges->insert (nodes->at (w));
		}

		void addBiDirectionalEdge (T v, T w)
		{
			addVertex (v);
			addVertex (w);
			
			(nodes->at(v))->edges->insert (nodes->at(w));
			(nodes->at(w))->edges->insert (nodes->at(v));
		}
};
