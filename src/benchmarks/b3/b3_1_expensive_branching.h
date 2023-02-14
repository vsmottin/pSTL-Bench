
#ifndef MASTER_BENCHMARKS_B3_1_EXPENSIVE_BRANCHING_H
#define MASTER_BENCHMARKS_B3_1_EXPENSIVE_BRANCHING_H


#include <vector>
#include <cmath>
#include <algorithm>
#include <numeric>
#include <benchmark/benchmark.h>

template<class ExecutionPolicy>
inline void
b3_1_expensive_branching(ExecutionPolicy &policy, const std::vector<int> &input_data, const int &magic_number) {

    // we have here an expensive branch that if predicted wrongly we waste a lot of time.
    const auto res = std::all_of(policy, input_data.begin(), input_data.end(), [&magic_number](const auto &entry) {
        if (magic_number < entry) {
            return (3 * std::pow(std::tan(entry), std::cos(entry)) >= 1);
        } else {
            return std::sin(entry) < 1;
        }
    });

    benchmark::DoNotOptimize(res);
}

#endif //MASTER_BENCHMARKS_B3_1_EXPENSIVE_BRANCHING_H
