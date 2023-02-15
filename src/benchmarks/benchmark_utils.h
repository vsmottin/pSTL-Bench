
#ifndef MASTER_BENCHMARKS_BENCHMARK_UTILS_H
#define MASTER_BENCHMARKS_BENCHMARK_UTILS_H

#include <vector>
#include <random>
#include <algorithm>
#include <ctime>

template<typename T>
std::vector<T>
generate_uniform_dist_vec(const std::size_t &size, const int &lower_bound, const int &upper_bound) {

    std::mt19937 mt_engine(std::time(nullptr));
    std::uniform_real_distribution<> dist(lower_bound, upper_bound);

    std::vector<T> randValues(size);

    std::generate(randValues.begin(), randValues.end(), [&]() {
        return (T) dist(mt_engine);
    });

    return randValues;
}

#endif //MASTER_BENCHMARKS_BENCHMARK_UTILS_H
