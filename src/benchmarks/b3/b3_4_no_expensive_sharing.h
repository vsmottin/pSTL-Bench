
#ifndef MASTER_BENCHMARKS_B3_4_NO_EXPENSIVE_SHARING_H
#define MASTER_BENCHMARKS_B3_4_NO_EXPENSIVE_SHARING_H

#include <vector>
#include <cmath>
#include <algorithm>
#include <numeric>
#include <benchmark/benchmark.h>


template<class ExecutionPolicy>
inline std::size_t
b3_4_no_expensive_sharing(ExecutionPolicy &policy, const std::vector<int> &input_data) {

    return std::count_if(policy, input_data.begin(), input_data.end(), [](const auto &val) {
        return true;
    });
}

#endif //MASTER_BENCHMARKS_B3_4_NO_EXPENSIVE_SHARING_H
