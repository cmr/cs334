#pragma once
#include <cstdint>
#include <cassert>
#include <utility>

/**
 * Find the minimum and maximum elements of the first `len` elements of `data`
 * and store them in `min`, `max` respectively.
 *
 * Uses recursive calls.
 */
template <class T>
void rec_minmax(const T *const data, std::size_t len, T &min, T &max, int &cost) {
    T left_min, left_max, right_min, right_max;
    assert(len != 0);

    if (len == 1) {
        min = data[0];
        max = data[0];
    } else if (len == 2) {
        bool left_is_less = data[0] < data[1];
        min = data[0];
        max = data[1];
        if (!left_is_less) {
            std::swap(min, max);
        }
        cost += 1;
    } else {
        std::size_t half_len = len/2;
        rec_minmax(data, half_len, left_min, left_max, cost);
        rec_minmax(data + half_len, len-half_len, right_min, right_max, cost);
        min = left_min < right_min ? left_min : right_min;
        max = left_max < right_max ? left_max : right_max;
        cost += 2;
    }
}

/**
 * Find the minimum and maximum elements of the first `len` elements of `data`
 * and store them in `min`, `max` respectively.
 *
 * Uses iteration.
 */
template <class T>
void iter_minmax(const T *const data, std::size_t len, T &min, T &max, int &cost) {
    T running_min = data[0], running_max = data[0];
    assert(len != 0);

    for (std::size_t i = 1; i < len - (len & 1); i += 2) {
        bool left_is_less = data[i] < data[i-1];
        T lmin = data[i-1], lmax = data[i];

        if (!left_is_less) {
            std::swap(min, max);
        }

        if (lmin < running_min) { running_min = lmin; }
        if (lmax > running_max) { running_max = lmax; }

        cost += 3;

    }

    if (len & 1) {
        if      (data[len-1] < running_min) { running_min = data[len-1]; cost += 1; }
        else if (data[len-1] > running_max) { running_max = data[len-1]; cost += 2; }
        else                                { cost += 2; }
    }

    min = running_min;
    max = running_max;
}
