#ifndef MASTER_BENCHMARKS_B2_1_BASIC_REDUCE_H
#define MASTER_BENCHMARKS_B2_1_BASIC_REDUCE_H


#include <vector>
#include <cmath>
#include <algorithm>
#include <numeric>
#include <benchmark/benchmark.h>

namespace B2 {

    template<class ExecutionPolicy, typename TYPE>
    inline TYPE b2_1_basic_reduce(ExecutionPolicy &policy, const std::vector<TYPE> &input_data) {

        // this is a straight forward reduce because we only want to check how data types effect the performance.
        // The goal: do we have to care about data type size or not when using parallel stl ?
        return std::reduce(policy, input_data.begin(), input_data.end());
    }

}


#endif //MASTER_BENCHMARKS_B2_1_BASIC_REDUCE_H
