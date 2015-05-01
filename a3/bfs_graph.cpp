#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "graph.h"
using namespace std;

/* main:
 * test driver for Breadth First Search (BFS) on graphs. 
 * to compile:
 *	g++ -g -o test_bfs bfs_graph.cpp
 * to run:
 *	./test_bfs in_graph.txt out_bfs.txt
 * this reads a graph from the file "in_graph.txt" and 
 * runs BFS (starting at first vertex) on the input graph
 * and writes out the BFS tree to "out_bfs.txt"
 */
int main( int argc, char *argv[] )
{
	assert( argc > 2 );

	// read in graph 
	Graph<int> my_graph;
	ifstream in;
	in.open( argv[1] );
	in >> my_graph;
	in.close();

#ifdef DEBUG
	// show input graph
	cerr << "Input graph:" << endl;
	cerr << my_graph;
#endif

	// run BFS
	int start_vertex = 0;
	Graph<int> my_bfs_tree( my_graph.BFS(start_vertex) );

	// write out graph
	ofstream out;
	out.open( argv[2] );
	out << my_bfs_tree << endl;
	out.close();

#ifdef DEBUG
	// show output graph
	cerr << "Output BFS tree:" << endl;
	cerr << my_bfs_tree;
#endif
}


