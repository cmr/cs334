#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "graph.h"
using namespace std;

/* main:
 * test driver for Depth First Search (DFS) on graphs. 
 * to compile:
 *	g++ -g -o test_dfs dfs_graph.cpp
 * to run:
 *	./test_search_graph in_graph.txt out_dfs.txt
 * this reads a graph from the file "in_graph.txt" and 
 * runs DFS on the input graph and outputs the DFS tree
 * to the file "out_dfs.txt"
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

	// run DFS
	Graph<int> my_dfs_tree( my_graph.DFS() );

	// write out graph
	ofstream out;
	out.open( argv[2] );
	out << my_dfs_tree << endl;
	out.close();

#ifdef DEBUG
	// show output graph
	cerr << "Output DFS tree:" << endl;
	cerr << my_dfs_tree;
#endif
}



