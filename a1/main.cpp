#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <assert.h>
#include <time.h>
#include <algorithm>

using namespace std;

// prototypes of sorts
void bsort(int array[], int size);
void isort(int array[], int size);
void ssort(int array[], int size);
void msort(int array[], int size);
void my_qsort(int array[], int size, int (*choose_pivot)(int [], int));

// median finder
void select(int array[], int size, int K, int &answer);

// helpers
void show(int array[], int size);
void copy(int src[], int dest[], int size);
void shuffle(int array[], int size);
void is_sorted(int array[], int size);

// pivot choosers
int random_pivot(int [], int);
int fixed_pivot(int [], int);
int median_pivot(int [], int);


// global cost variable
int cost;


///////////////////////////////////////////////////////////////////////
// main: testing all sorts
///////////////////////////////////////////////////////////////////////
int main(int argc, char *argv[])
{
	assert(argc > 1);

	// get size
	int total_size = atoi(argv[1]);

	for (int size = 1; size < total_size; size++) {
		// allocate array
		int test_array[size];
		for (int i=0; i<size; i++) {
			test_array[i] = i;
		}
		shuffle(test_array, size);

		int array[size];

		// testing mergesort
		cost = 0;
		copy(test_array, array, size);
		msort(array, size);
		is_sorted(array, size);
//		cout << cost << " ";

		// testing quicksort (with random pivot)
		cost = 0;
		copy(test_array, array, size);
		my_qsort(array, size, random_pivot);
		is_sorted(array, size);
//		cout << cost << " ";

		// testing quicksort (with median pivot)
		cost = 0;
		copy(test_array, array, size);
		my_qsort(array, size, median_pivot);
		is_sorted(array, size);
//		cout << cost << " ";

		// testing insertion sort
		cost = 0;
		copy(test_array, array, size);
		isort(array, size);
		is_sorted(array, size);
//		cout << cost << " ";

		// testing selection sort
		cost = 0;
		copy(test_array, array, size);
		ssort(array, size);
		is_sorted(array, size);
//		cout << cost << " ";

		// testing bubble sort
		cost = 0;
		copy(test_array, array, size);
		bsort(array, size);
		is_sorted(array, size);
//		cout << cost << " ";

//		cout << endl;
	}
}

///////////////////////////////////////////////////////////////////////
// HELPERS
///////////////////////////////////////////////////////////////////////

// randomly shuffle array
void shuffle(int array[], int size)
{
	int index;
	srand(time(0));
	for (int i=size-1; i>0; i--) {
		index = rand() % i;
        swap(array[i], array[index]);
	}
}

// display array
void show(int array[], int size)
{
    cerr << "Our array is: ";
	for (int i=0; i<size; i++) {
		cerr << array[i] << " ";
	}
	cerr << endl;
}

// array is sorted
void is_sorted(int array[], int size)
{
	for (int i=0; i<size-1; i++) {
		if (array[i] > array[i+1]) {
            cerr << "Array not sorted! ";
            show(array, size);
            abort();
        }
	}
}

// copy array
void copy(int src[], int dest[], int size)
{
	for (int i=0; i<size; i++) {
		dest[i] = src[i];
	}
}

// pivot choosers
int fixed_pivot(int array[], int size)
{
	return array[0];
}

int random_pivot(int array[], int size)
{
	return array[rand()%size];
}

int median_pivot(int array[], int size)
{
	int pivot;
	select(array, size, size>>1, pivot);
	return pivot;
}

