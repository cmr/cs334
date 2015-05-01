#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "graph.h"
using namespace std;

/* main:
 * test driver for generating a random graph.
 * to compile:
 *	g++ -g -o test_make_graph make_graph.cpp
 * to run:
 *	./test_make_graph 13 my_graph.txt
 * this creates a graph on 13 vertices and writes it to the file "my_graph.txt"
 */
int main( int argc, char *argv[] )
{
	assert( argc > 2 );

	// create random graph of a given size
	int size;
	size = atoi( argv[1] );

	vector<int> my_vertices;
	for (int i=0; i<size; i++) {
		my_vertices.push_back(i);
	}

	Graph<int> my_random_graph( my_vertices, true );

#ifdef DEBUG
	cerr << "Random graph of size " << size << ":" << endl;
	cerr << my_random_graph;
#endif

	// write graph out to file
	ofstream out;
	out.open( argv[2] );
	out << my_random_graph;
	out.close();

}

