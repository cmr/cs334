#ifndef BST_H
#define BST_H

#include "tree.h"

template<class T> class BST;

// Binary Search Tree
template <class T>
class BST : public Tree<T> {
public:
	// constructors
	BST( const T &v )
		: Tree<T>(v) {}

	BST( const T &v, BST<T> *l, BST<T> *r )
		: Tree<T>(v,l,r) {}

	BST( const T &v, BST<T> *l, BST<T> *r, BST<T> *p )
		: Tree<T>(v,l,r,p) {}


	// unvirtualized utilities
	BST<T> * search( const T &v );
		// returns pointer to node (containing value, if exists) or NULL (otherwise)

	BST<T> * insert( const T &v );
		// returns pointer to updated tree (which contains value)

	BST<T> * remove( const T &v );
		// returns pointer to updated tree (which no longer contains value)

};

#include "bst.cpp"

#endif

