
#ifndef MASTER_BENCHMARKS_BENCHMARK_UTILS_H
#define MASTER_BENCHMARKS_BENCHMARK_UTILS_H

#include <vector>
#include <random>
#include <algorithm>

#define DEFAULT_MU 100
#define DEFAULT_SIGMA 10

template<typename T>
std::vector<T>
generate_random_dist_vec(const std::size_t &size,
                         const int mu = DEFAULT_MU,
                         const int sigma = DEFAULT_SIGMA
) {

    std::vector<T> randValues(size);

    std::mt19937 mt_engine(std::time(nullptr));
    std::uniform_real_distribution<> uniformDist(mu, sigma);

    std::generate(randValues.begin(), randValues.end(), [&]() {
        return (T) uniformDist(mt_engine);
    });

    return randValues;
}

#endif //MASTER_BENCHMARKS_BENCHMARK_UTILS_H
