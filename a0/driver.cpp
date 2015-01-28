#include <chrono>
#include <fstream>
#include <iostream>
#include <random>
#include <vector>

#include "minmax.h"

#if RECURSIVE
#define minmax rec_minmax
#else
#define minmax iter_minmax
#endif

int main(int argc, char **argv) {
#if BENCHMARK
    std::mt19937 rng;
    rng.seed(static_cast<std::mt19937::result_type>(std::chrono::system_clock::now().time_since_epoch().count()));
    std::uniform_int_distribution<std::mt19937::result_type> dist(0, 100000000);

    std::vector<std::mt19937::result_type> data;
    for (int i = 0; i < 2500; i++) {
        std::mt19937::result_type min, max;
        int cost = 0;
        data.push_back(dist(rng));
        minmax(data.data(), data.size(), min, max, cost);
        std::cout << data.size() << ' ' << min << ' ' << max << ' ' << cost << std::endl;
    }
#else
    if (argc != 2) {
        std::cerr << "A single argument is required: the file storing the data";
        return 1;
    }

    std::fstream input(argv[1]);
    std::size_t len;
    input >> len;
    std::vector<int> data;
    data.reserve(len);

    for (std::size_t i = 0; i < len; i++) {
        int val;
        input >> val;
        data.push_back(val);
    }
    int min, max, cost = 0;

    minmax(data.data(), data.size(), min, max, cost);
    std::cout << len << ' ' << min << ' ' << max << ' ' << cost << std::endl;

#endif

    return 0;
}
