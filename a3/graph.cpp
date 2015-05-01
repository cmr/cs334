#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <map>
#include <queue>
#include <stack>
#include <assert.h>
#include <time.h>
#include <tr1/random>
using namespace std;


/////////////////////////////////////////////////////////
// constructors
/////////////////////////////////////////////////////////

// construct a random graph
template <class T>
Graph<T>::Graph( const vector<T> &vertex_set, bool is_directed )
{
    std::tr1::variate_generator<std::tr1::mt19937, std::tr1::uniform_real<> > rng(std::tr1::mt19937(time(NULL)), std::tr1::uniform_real<>());

	size = vertex_set.size();
	directed = is_directed;

    double unif_prob = 1 / 5.0;

    // With uniform probability, add an edge between any two vertices. Why
    // size*size? Because that is the maximum number of possible edges.
    for (typename vector<T>::const_iterator it = vertex_set.begin(); it != vertex_set.end(); it++) {
        for (typename vector<T>::const_iterator it2 = vertex_set.begin(); it2 != vertex_set.end(); it2++) {
            if (rng() < unif_prob) {
                insert(*it, *it2);
            }
        }
    }
}

/////////////////////////////////////////////////////////
// accessors
/////////////////////////////////////////////////////////

template <class T>
vector<T> Graph<T>::vertices()
{
	vector<T> vertex_set;

	for (vertex_iterator i = begin(); i != end(); i++) {
		vertex_set.push_back(i->first);
	}
	return vertex_set;
}



/////////////////////////////////////////////////////////
// mutators
/////////////////////////////////////////////////////////

// insert edge
template <class T>
void Graph<T>::insert( const T &u, const T &v )
{
	adjacency_list[u].push_back(v);
    if (directed) {
        adjacency_list[v].push_back(u);
    }
}



/////////////////////////////////////////////////////////
// predicates
/////////////////////////////////////////////////////////

template <class T>
bool Graph<T>::is_vertex( const T &u ) const
{
	return (adjacency_list.find(u) != end());
}

template <class T>
bool Graph<T>::is_edge( const T &u, const T &v ) const
{
	vertex_iterator i = adjacency_list.find(u);
	if (i == end()) {
		return false;
	}
	assert( i->first == u );

	typedef typename std::vector<T> NeighborList;
	typedef typename NeighborList::const_iterator neighbor_iterator;

	NeighborList neighbors = i->second;
	neighbor_iterator j = find( neighbors.begin(), neighbors.end(), v );
	return (j != neighbors.end()) ? true : false;
}





////////////////////////////////////////////////////////////
// Breadth First Search
////////////////////////////////////////////////////////////
enum COLOR {WHITE, GRAY, BLACK};

template <class T>
struct BFS_Vertex {
	COLOR color;
	int distance;
	T previous;
};


template <class T>
Graph<T> Graph<T>::BFS( const T & start_vertex )
{
	map<T, BFS_Vertex<T> > BFS_Tree;
	Graph<T> outputTree;
	queue<T> BFS_Queue;

    BFS_Tree[start_vertex].color = BLACK;
    BFS_Tree[start_vertex].distance = 0;
    BFS_Queue.push(start_vertex);

    while (!BFS_Queue.empty()) {
        const T & e = BFS_Queue.front();
        cout << "Processing node from queue: " << e << endl;
        BFS_Queue.pop();
        BFS_Vertex<T> &me = BFS_Tree[e];
        Graph<T>::neighbor_iterator neighs = Graph<T>::neighbor_iterator(*this, const_cast<T&>(e));
        if (neighs.end()) { cout << "No neighbors :(" << endl; continue; }
        for (T neigh = neighs.begin(); !neighs.end(); neigh = neighs.next()) {
            if (BFS_Tree.find(neigh) == BFS_Tree.end()) {
                BFS_Tree[neigh].color = BLACK;
                BFS_Tree[neigh].distance = me.distance + 1;
                BFS_Queue.push(neigh);
                outputTree.insert(e, neigh);
            }
        }
    }

	return outputTree;
}




////////////////////////////////////////////////////////////
// Depth First Search
////////////////////////////////////////////////////////////
template <class T>
struct DFS_Vertex {
	COLOR color;
	int discover_time, finish_time;
	T previous;
};

template <class T>
void
DFS_Visit(Graph<T> *graph, Graph<T> *outputTree, map<T, DFS_Vertex<T> > &DFS_Tree, const T &node, int &time) {
    for (typename Graph<T>::vertex_iterator verts = graph->begin(); verts != graph->end(); verts++) {
        DFS_Vertex<T> &vert = DFS_Tree[verts->first];
        if (vert.color == WHITE) {
            time++;
            vert.color = GRAY;
            typename Graph<T>::neighbor_iterator neighs = typename Graph<T>::neighbor_iterator((Graph<T>&)graph, const_cast<T&>(verts->first));
            for (T neigh = neighs.begin(); !neighs.end(); neigh = neighs.next()) {
                DFS_Vertex<T> &neigh_vert = DFS_Tree[neigh];
                if (neigh_vert.color == WHITE) {
                    neigh_vert.previous = verts->first;
                    outputTree->insert(verts->first, neigh);
                    DFS_Visit(graph, outputTree, DFS_Tree, neigh, time);
                }
            }
            vert.color = BLACK;
            time++;
            vert.finish_time = time;
        }
    }
}

template <class T>
Graph<T> Graph<T>::DFS()
{
	map<T, DFS_Vertex<T> > DFS_Tree;
	Graph<T> outputTree;
	//stack<T> DFS_Stack;

    int time = 0;

    for (typename Graph<T>::vertex_iterator verts = this->begin(); verts != this->end(); verts++) {
        DFS_Tree[verts->first].color = WHITE;
    }

    for (typename Graph<T>::vertex_iterator verts = this->begin(); verts != this->end(); verts++) {
        if (DFS_Tree[verts->first].color == WHITE) {
            DFS_Visit<T>(this, &outputTree, DFS_Tree, verts->first, time);
        }
    }

	return outputTree;
}


