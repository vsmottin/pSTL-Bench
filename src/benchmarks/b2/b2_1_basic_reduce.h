#ifndef MASTER_BENCHMARKS_B2_1_BASIC_REDUCE_H
#define MASTER_BENCHMARKS_B2_1_BASIC_REDUCE_H


#include <vector>
#include <cmath>
#include <algorithm>
#include <numeric>
#include <benchmark/benchmark.h>

template<class ExecutionPolicy, typename TYPE>
inline void b2_1_basic_reduce(ExecutionPolicy &policy, const std::vector<TYPE> &input_data) {

    const auto sum = std::reduce(policy, input_data.begin(), input_data.end());
    benchmark::DoNotOptimize(sum);
}


#endif //MASTER_BENCHMARKS_B2_1_BASIC_REDUCE_H
