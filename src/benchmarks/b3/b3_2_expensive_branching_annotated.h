
#ifndef MASTER_BENCHMARKS_B3_2_EXPENSIVE_BRANCHING_H
#define MASTER_BENCHMARKS_B3_2_EXPENSIVE_BRANCHING_H


#include <vector>
#include <cmath>
#include <algorithm>
#include <numeric>
#include <benchmark/benchmark.h>

template<class ExecutionPolicy>
inline void
b3_2_expensive_branching_annotated(ExecutionPolicy &policy, const std::vector<int> &input_data,
                                   const int &magic_number) {

    // we have here an expensive branch that if predicted wrongly we waste a lot of time.
    // To arrange the assembly better we add compilation hints
    const auto res = std::all_of(policy, input_data.begin(), input_data.end(), [&magic_number](const auto &entry) {
        if (magic_number < entry) [[unlikely]] {
            return (3 * std::pow(std::tan(entry), std::cos(entry)) >= 1);
        } else  [[likely]] {
            return std::sin(entry) < 1;
        }
    });

    benchmark::DoNotOptimize(res);
}

#endif //MASTER_BENCHMARKS_B3_2_EXPENSIVE_BRANCHING_H
