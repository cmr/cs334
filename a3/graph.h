#ifndef GRAPH_H
#define GRAPH_H

#include <sstream>
#include <vector>
#include <map>
using namespace std;

template <class T>
class Graph
{
private:
	typedef typename std::map< T, vector<T> > AdjacencyList;
	AdjacencyList adjacency_list;
	int size;
	bool directed;

public:
	// constructors
	Graph():size(0), directed(false) { adjacency_list.clear(); }
		// for empty graph
	Graph( const vector<T> &vertex_set, bool is_directed );
		// for random graph
	Graph( const Graph<T> &g ):size(g.size), directed(g.directed)
		{ adjacency_list = g.adjacency_list; }
		// copy constructor

	// destructor
	~Graph() { adjacency_list.clear(); }

	// accessors
	int getSize() { return size; }
		// returns the number of vertices
	vector<T> vertices();
		// returns all vertices in the graph

	// predicates
	bool is_vertex( const T &u ) const;
		// true if u is a vertex in the graph
	bool is_edge( const T &u, const T &v ) const;
		// true if (u,v) is an edge in the graph
	bool is_directed() const { return directed; }
		// true if the graph is directed

	// mutator(s)
	void setDirected(bool b) { directed = b; }
	void insert( const T &u, const T &v );
		// adds a new edge (u,v) to the graph


	// iterator for vertices
	//  reuses iterator for std::map
	typedef typename AdjacencyList::const_iterator vertex_iterator;
	vertex_iterator begin() const { return adjacency_list.begin(); }
	vertex_iterator end() const { return adjacency_list.end(); }


	// iterator for neighborhoods
	//  uses an inner iterator class
	class neighbor_iterator {
	public:
		neighbor_iterator( Graph<T> &g, T &v )
			{ alist = g.adjacency_list[v]; }
		T begin() 	{ it = alist.begin(); return *it; }
		bool end() 	{ return (it == alist.end()); }
		T next() 	{ return *(++it); }
	private:
		typedef typename vector<T>::const_iterator private_iterator;
		vector<T> alist;
		private_iterator it;
	};


	// overloaded output (generates graphviz format)
	friend ostream & operator<<(ostream &out, Graph<T> &graph) {
        string conn;
        if (graph.directed) {
            cout << "digraph {" << endl;
            conn = "--";
        } else {
            cout << "graph { " << endl;
            conn = "->";
        }

        for (typename Graph<T>::vertex_iterator vert = graph.begin(); vert != graph.end(); vert++) {
            Graph<T>::neighbor_iterator neighs(graph, const_cast<T&>(vert->first));
            // graph can't have vertices with no neighbors?
            //cout << vert->first << ";" << endl;
            for (typename vector<T>::const_iterator neigh = vert->second.begin(); neigh != vert->second.end(); neigh++) {
                cout << vert->first << conn << *neigh << ";" << endl;
            }
        }

        cout << "}" << endl;
		return out;
	}

	// overloaded input (assumes graphviz format)
	friend istream & operator>>(istream &in, Graph<T> &graph) {
        string kind;
        string tmp;
        in >> kind;
        graph.setDirected(kind == "digraph");
        in >> tmp; // eat {
        T left, right;
        while (in) {
            in >> left >> tmp >> right >> tmp;
            graph.insert(left, right);
        }
		return in;
	}


	// graph searches
	Graph<T> BFS( const T &start_vertex );
	Graph<T> DFS();

};


#include "graph.cpp"

#endif


