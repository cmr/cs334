//
// test driver for BST, AVL and Splay trees
//

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <iostream>
#include <fstream>
#include <string>

#ifdef TEST_BST
#include "bst.h"
#endif
#ifdef TEST_AVL
#include "avl.h"
#endif
#ifdef TEST_SPLAY
#include "splay.h"
#endif

using namespace std;

// prototypes
inline void swap(int &, int &);
void shuffle(int [], int);
void show(int [], int);
void is_sorted(const vector<int> &);
void copy(int [], int [], int);
void copy(int [], const char *, int);


////////////////////////////////////////////////////////////////////////////////
// main: three tests in one
////////////////////////////////////////////////////////////////////////////////
int main( int argc, char *argv[] )
{
	// setup root of tree and an extra pointer called boo
#ifdef TEST_BST
	BST<int> *root = NULL;
	BST<int> *boo  = NULL;
#endif
#ifdef TEST_AVL
	AVL<int> *root = NULL;
	AVL<int> *boo  = NULL;
#endif
#ifdef TEST_SPLAY
	Splay<int> *root = NULL;
	Splay<int> *boo  = NULL;
#endif

////////////////////////////////////////////////////////////////////////////////
// OPTION 1: INTERACTIVE TESTING
////////////////////////////////////////////////////////////////////////////////
#ifdef TEST_INTERACTIVE

	int choice, value;

	while (1)
	{
		// menu prompt
		cerr << "OPTIONS: ";
		cerr << "0.print ";
		cerr << "1.search ";
		cerr << "2.insert ";
		cerr << "3.delete ";
		cerr << "4.quit " << endl;

		cerr << "Your choice: ";
		cin >> choice;

		switch(choice)
		{
		case 0: /* PRINT */
			if (root != NULL)
			{
				root->show();
			}
			break;

		case 1: /* SEARCH */
			cerr << "SEARCH = ";
			cin >> value;

			if (root == NULL)
			{ // tree is empty: nothing exists
				cerr << "[" << value << "] not found" << endl;
			}
			else
			{
				// search value, get pointer to node (containing value)
				boo = root->search(value);
#ifdef TEST_SPLAY
				// splay: searched node should be root, so update root here
				root = boo;
#endif
				// report search result
				if (boo == NULL || boo->getValue() != value)
				{
					cerr << "[" << value << "] not found" << endl;
				}
				else
				{
					cerr << "Found [" << boo->getValue() << "]" << endl;
				}

				// show tree after search
				root->show();
			}
			break;

		case 2: /* INSERT */
			cerr << "INSERT = ";
			cin >> value;

			if (root == NULL)
			{ // tree is empty

				// allocate new node via root
#ifdef TEST_BST
				root = new BST<int>(value);
#endif
#ifdef TEST_AVL
				root = new AVL<int>(value);
#endif
#ifdef TEST_SPLAY
				root = new Splay<int>(value, ROOT);
#endif
			}
			else
			{
				// insert value, update root
				root = root->insert(value);
			}

			// show tree after insert
			root->show();
			break;

		case 3: /* REMOVE */
			cerr << "DELETE = ";
			cin >> value;

			if (root != NULL)
			{ // check tree is not empty
				root = root->remove(value);

				if (root != NULL)
				{
					// show tree after delete if not empty
					root->show();
				}
			}
			break;

		case 4:
			// quit testing
			return 0;
		}
	}

#endif
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
// OPTION 2: BATCH TESTING
////////////////////////////////////////////////////////////////////////////////
#ifdef TEST_COMPLEXITY

	// determine size of input from command line
	if ( argc <= 1 )
	{
		fprintf(stderr, "Usage: ./test_me <size>\n");
		exit(1);
	}
	int num_items = atoi(argv[1]);

	// prepare array of integers
	int array[num_items];
	for (int i=0; i<num_items; i++)
	{
		array[i] = i;
	}

	// shuffle and show
	shuffle(array, num_items);
	show(array, num_items);

	// prepare vector
	vector<int> vec_array;


	// Stage 1: repeated insertions
	//
	cerr << "Insertions: " << endl;
	for (int i=0; i<num_items; i++)
	{
		cerr << "INSERT[" << array[i] << "]" << endl;

		if (root == NULL)
		{ // three root flavors

#ifdef TEST_BST
			root = new BST<int>(array[0]);
#elif TEST_AVL
			root = new AVL<int>(array[0]);
#elif TEST_SPLAY
			root = new Splay<int>(array[0], ROOT);
#endif
		}
		else
		{
			// insert value and update root
			root = root->insert(array[i]);
		}

#ifdef TEST_SPLAY
		boo = root;	// splay: newly inserted node must be at root
#else
		boo = root->search(array[i]);	// bst, avl: not so
#endif

		// check the value
		assert( boo != NULL && array[i] == boo->getValue() );

		// check tree is in-order
		vec_array.clear();
		root->inOrder( vec_array );
		is_sorted( vec_array );

		// check height of tree
		root->updateHeight();
#ifdef MAIN_ECHO
		cerr << "Height[" << root->getHeight() << "]" << endl;
		root->show();
#endif
	}
	cerr << endl;


	// Stage 2: repeated searches
	//
	cerr << "Searches: " << endl;
	for (int i=0; i<num_items; i++)
	{
		cerr << "SEARCH[" << array[i] << "]" << endl;

#ifdef TEST_SPLAY
		root = root->search(array[i]);
		assert( array[i] == root->getValue() );
#else
		boo = root->search(array[i]);
		assert( array[i] == boo->getValue() );
#endif

		// check tree is in-order
		vec_array.clear();
		root->inOrder( vec_array );
		is_sorted( vec_array );

		// check height of tree
		root->updateHeight();
#ifdef MAIN_ECHO
		cerr << "Height = " << root->getHeight() << endl;
		root->show();
#endif
	}
	cerr << endl;


	// Stage 3: repeated deletions
	//
	cerr << "Deletions: " << endl;
	for (int i=0; i<num_items; i++)
	{
		cerr << "DEL[" << array[i] << "]" << endl;

		// remove value, update root
		root = root->remove(array[i]);

#ifdef MAIN_ECHO
		if (root != NULL)
		{
			// check tree is in-order
			vec_array.clear();
			root->inOrder( vec_array );
			is_sorted( vec_array );

			// calculate height of tree
			root->updateHeight();
			cerr << "Height = " << root->getHeight() << endl;
			root->show();
		}
		else
		{
			cerr << "empty-tree" << endl;
		}
	}
#endif

	assert( root == NULL );
	cerr << endl;

#endif
////////////////////////////////////////////////////////////////////////////////

}


////////////////////////////////////////////////////////////////////////////////
// HELPERS
////////////////////////////////////////////////////////////////////////////////

// swap two elements
inline void swap(int &a, int &b)
{
	int tmp = a; a = b; b = tmp;
}

// pseudorandom array shuffle
void shuffle(int array[], int size)
{
    int index;
    srand(time(0));
    for (int i=size-1; i>0; i--) {
        index = rand() % i;
        swap(array[i], array[index]);
    }
}

// show array
void show(int array[], int size)
{
	cerr << "Array = [ ";
    for (int i=0; i<size; i++) {
        cerr << array[i] << " ";
    }
    cerr << "]" << endl;
}

// check vector is sorted
void is_sorted(const vector<int> &v)
{
    for (int i=0; i<v.size()-1; i++) {
        assert(v[i] <= v[i+1]);
    }
}

// copy array
void copy(int src[], int dest[], int size)
{
    for (int i=0; i<size; i++) {
        dest[i] = src[i];
    }
}


////////////////////////////////////////////////////////////////////////////////



