/* methods for Tree class */

#include <assert.h>
#include <iostream>
#include <string>
#include <vector>
using namespace std;


// (re)compute height 
template <class T>
void Tree<T>::updateHeight()
{
	if (left == NULL && right == NULL) 
	{
		height = 0;
	}
	else if (left == NULL) 
	{
		right->updateHeight();
		height = 1 + right->height;
	}
	else if (right == NULL) 
	{
		left->updateHeight();
		height = 1 + left->height;
	}
	else 
	{
		left->updateHeight();
		right->updateHeight();
		height = 1 + max(left->height,right->height);
	}
}

// returns successor ("smallest" item in right subtree)
template <class T>
Tree<T> * Tree<T>::successor() const
{
	Tree<T> * next;

	if (right == NULL)
	{
		return NULL;
	}

	next = right;
	while (next->left != NULL)
	{
		next = next->left;
	}
	return next;
}

// compute inorder traversal sequence 
template <class T>
void Tree<T>::inOrder( vector<T> &sequence ) const
{
	if (left != NULL)
	{
		left->inOrder( sequence );
	}

	sequence.push_back(value);

	if (right != NULL)
	{
		right->inOrder( sequence );
	}
}


// simple tree printer
template <class T>
void Tree<T>::show( int spaces, int side ) const
{
	for (int i = 0; i < spaces; i++)
	{
		cerr << " ";
	}

	if (side < 0) 
	{
		cerr << "<" << value << "]" << endl;
	}
	else if (side > 0) 
	{
		cerr << "[" << value << ">" << endl;
	}
	else 
	{
		cerr << "[" << value << "]" << endl;
	}

	if (left != NULL)
	{
		left->show( spaces+4, -1 );
	}

	if (right != NULL)
	{
		right->show( spaces+4, +1 );
	}

}


// inline max
inline int max(int a, int b)
{
    return (a > b ? a : b);
}




