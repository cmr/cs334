#ifndef TREE_H
#define TREE_H

#include <vector>
using namespace std;

// Parent class for trees
template <class T>
class Tree {
public:
	// constructors
	Tree( const T &v )
		: value(v), left(NULL), right(NULL), parent(NULL), height(0) {}

	Tree( const T &v, Tree<T> *l, Tree<T> *r )
		: value(v), left(l), right(r), parent(NULL) { updateHeight(); }

	Tree( const T &v, Tree<T> *l, Tree<T> *r, Tree<T> *p )
		: value(v), left(l), right(r), parent(p) { updateHeight(); }

	Tree( const T &v, Tree<T> *l, Tree<T> *r, Tree<T> *p, int h )
		: value(v), left(l), right(r), parent(p), height(h) {}


	// cloners
	Tree( const Tree<T> &t )
		: value(t.value), left(t.left), right(t.right), parent(t.parent), height(t.height) {}

	Tree( Tree<T> *t )
		: value(t->value), left(t->left), right(t->right), parent(t->parent), height(t->height) {}


	// accessors
	T & getValue()  		{ return value; }
	Tree<T> * getLeft()		{ return left; }
	Tree<T> * getRight()  	{ return right; }
	Tree<T> * getParent() 	{ return parent; }
	int getHeight()			{ return height; }


	// mutators
	void setValue( const T &v )		{ value = v; }
	void setLeft( Tree<T> *l )		{ left = l; }
	void setRight( Tree<T> *r ) 	{ right = r; }
	void setParent( Tree<T> *p )	{ parent = p; }
	void setHeight( int h )			{ height = h; }

	void updateHeight();		// recompute heights of all nodes


	// purely virtual utilities
	virtual Tree<T> * search( const T &v ) = 0;
	virtual Tree<T> * insert( const T &v ) = 0;
	virtual Tree<T> * remove( const T &v ) = 0;


	// little helpers
	Tree<T> * successor() const;
	void inOrder( vector<T> &sequence ) const;
	void show() const { show(0, 0); }

protected:
	T value;
	Tree<T> *left;
	Tree<T> *right;
	Tree<T> *parent;
	int height;

	void show( int spaces, int side ) const;

};

#include "tree.cpp"

#endif
