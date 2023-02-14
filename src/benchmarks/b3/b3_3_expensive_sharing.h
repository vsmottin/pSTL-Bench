
#ifndef MASTER_BENCHMARKS_B3_3_EXPENSIVE_SHARING_H
#define MASTER_BENCHMARKS_B3_3_EXPENSIVE_SHARING_H

#include <vector>
#include <cmath>
#include <algorithm>
#include <numeric>
#include <benchmark/benchmark.h>


template<class ExecutionPolicy>
inline std::size_t
b3_3_expensive_sharing(ExecutionPolicy &policy, const std::vector<int> &input_data) {

    std::atomic<bool> toggle{false};

    return std::count_if(policy, input_data.begin(), input_data.end(), [&toggle](const auto &val) {
        toggle = !toggle; // simulates an expensive mutex operation that forces us to wait
        return true;
    });
}

#endif //MASTER_BENCHMARKS_B3_3_EXPENSIVE_SHARING_H
