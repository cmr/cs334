#include <algorithm>
#include <vector>
#include <iostream>
#include <cstdio>

extern int cost;
extern void show(int array[], int size);

/* CS344 Assignment 1, Corey Richardson */

/* Bubble sort */
void bsort(int array[], int size) {
    // avoid underflow below
    if (size == 0) return;

    bool sorted = false;
    while (!sorted) {
        sorted = true;
        for (int i = 0; i < size-1; i++) {
            cost++;
            if (array[i] > array[i+1]) {
                std::swap(array[i], array[i+1]);
                sorted = false;
            }
        }
    }
}

/* Insertion sort */
void isort(int array[], int size) {
    if (size == 0) return;

    for (int i = 1; i < size; i++) {
        int j = i;
        while (j > 0 && array[j-1] > array[j]) {
            cost++;
            std::swap(array[j-1], array[j]);
            j--;
        }
    }
}

/* Selection sort */
void ssort(int array[], int size) {
    for (int i = 0; i < size; i++) {
        int k = i;
        for (int j = i+1; j < size; j++) {
            cost++;
            if (array[j] < array[k]) {
                k = j;
            }
        }
        std::swap(array[i], array[k]);
    }
}

/* Given two sorted regions of array, start..middle and middle..end, make
 * start..end a single sorted region.
 */
template<typename T>
static void merge(T array[], int start, int middle, int end) {
    T *scratch = new T[end - start];

    int firstlen = middle - start, lastlen = end - middle;
    if (firstlen == 0 || lastlen == 0) {
        return;
    }

    int left = start, right = middle, i = 0;
    while (left != middle && right != end) {
        if (array[left] > array[right]) {
            scratch[i++] = array[left++];
        } else {
            scratch[i++] = array[right++];
        }
    }

    while (right < end) {
        scratch[i++] = array[right++];
    }
    while (left < middle) {
        scratch[i++] = array[left++];
    }

    for (i = end - start; i < end; i++) {
        array[i] = scratch[i - end - start];
    }
}

/* Sort the region of array from start to end. */
template<typename T>
static void msort_inner(T array[], int start, int end) {
    int diff = end - start;
    if (diff == 0) { // one element
        return;
    } else if (diff == 1) { // two elements
        cost++;
        if (array[start] > array[end]) {
            std::swap(array[start], array[end]);
        }
        return;
    }

    int middle = start + (diff / 2);
    msort_inner(array, start, middle);
    msort_inner(array, middle, end);
    merge(array, start, middle, end);
}

void msort(int array[], int size) {
    if (size == 0) return;
    msort_inner(array, 0, size-1);
}

template<typename T>
static void qsort_inner(T array[], int start, int end, T (*choose_pivot)(T[], int)) {
      T pivot = choose_pivot(array + start, end - start);
      int i = start, j = end;
      while (i <= j) {
            while (array[i] < pivot)
                  i++;
            while (array[j] > pivot)
                  j--;
            if (i <= j) {
                  std::swap(array[i++], array[j--]);
            }
      };
      if (start < j)
            qsort_inner(array, start, j, choose_pivot);
      if (i < end)
            qsort_inner(array, i, end, choose_pivot);
}

void my_qsort(int array[], int size, int (*choose_pivot)(int[], int)) {
    if (size < 2) return;
    qsort_inner(array, 0, size - 1, choose_pivot);
}

template<typename T> static int select_inner(T array[], int start, int end, int K);

template<typename T>
static int mom(T array[], int start, int end) {
    int num_meds = (end - start) / 5;
    for (int i = 0; i < num_meds; i++) {
        int left = start + 5 * i;
        int right = std::min(left + 4, end);
        bsort(array + left, right - left);
        std::swap(array[start + i], array[left + (right - left)/2]);
    }
    if (num_meds > 5) {
        return mom(array, start, start + num_meds - 1);
    } else {
        bsort(array + start, num_meds);
        return start + num_meds / 2;
    }
}

///* Returns index of median element using the median-of-medians (linear time)
// * selection algorithm. Selects the Kth smallest item from the list. */
//template<typename T>
//static int select_inner(T array[], int start, int end, int K) {
//    if (end - start + 1 <= 5) {
//        bsort(array + start, end - start + 1);
//        return start + K - 1;
//    }
//
//    for (int i = 0; i < (end + 1) / 5; i++) {
//        int left = 5 * i;
//        int right = left + 4;
//        if (right > end) {
//            right = end;
//        }
//        int med_idx = select_inner(array, left, right, 3);
//        std::swap(array[med_idx], array[i]);
//    }
//
//    // the first end/5 elements are the medians from earlier, select their
//    // median (the (end/5) * 1/2 element).
//    return select_inner(array, 0, (end + 1) / 5, (end + 1) / 10);
//}

void select(int array[], int size, int K, int &answer) {
    answer = array[mom(array, 0, size - 1)];
}
