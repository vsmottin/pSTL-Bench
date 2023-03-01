
#ifndef MASTER_BENCHMARKS_B2_GROUP_H
#define MASTER_BENCHMARKS_B2_GROUP_H

#include <benchmark/benchmark.h>
#include <execution>
#include <iostream>

#include "../benchmark_prefix.h"
#include "../benchmark_utils.h"

#include "b2_1_basic_reduce.h"

//region b2_1_basic_reduce

template<class Policy, typename TYPE>
static void b2_1_basic_reduce_wrapper(benchmark::State &state) {
    constexpr auto execution_policy = Policy{};

    std::vector<TYPE> x(state.range(0), static_cast<TYPE>(1.5));
    for (auto _: state) {
        B2::b2_1_basic_reduce(execution_policy, x);
    }
}

#define REGISTER_B2_1_BASIC_REDUCE_WRAPPER(datatype)  \
    BENCHMARK_TEMPLATE2(b2_1_basic_reduce_wrapper, std::execution::sequenced_policy, datatype)->Name(BENCHMARK_NAME("b2_1_basic_reduce_" xstr(datatype) "_seq"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(1 << 5, 1 << 20);   \
    BENCHMARK_TEMPLATE2(b2_1_basic_reduce_wrapper, std::execution::parallel_policy, datatype)->Name(BENCHMARK_NAME("b2_1_basic_reduce_" xstr(datatype) "_par"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(1 << 5, 1 << 20);    \
    BENCHMARK_TEMPLATE2(b2_1_basic_reduce_wrapper, std::execution::parallel_unsequenced_policy, datatype)->Name(BENCHMARK_NAME("b2_1_basic_reduce_" xstr(datatype) "_par_unseq"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(1 << 5, 1 << 20);    \


//endregion b2_1_basic_reduce

// Register the function as a benchmark
#define B2_GROUP_BENCHMARKS \
                            \
            REGISTER_B2_1_BASIC_REDUCE_WRAPPER(char)                \
            REGISTER_B2_1_BASIC_REDUCE_WRAPPER(int)                 \
            REGISTER_B2_1_BASIC_REDUCE_WRAPPER(long)                \
            REGISTER_B2_1_BASIC_REDUCE_WRAPPER(unsigned long)       \
            REGISTER_B2_1_BASIC_REDUCE_WRAPPER(float)               \
            REGISTER_B2_1_BASIC_REDUCE_WRAPPER(double)              \
            REGISTER_B2_1_BASIC_REDUCE_WRAPPER(long double)


#endif //MASTER_BENCHMARKS_B2_GROUP_H
