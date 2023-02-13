
#ifndef MASTER_BENCHMARKS_B2_GROUP_H
#define MASTER_BENCHMARKS_B2_GROUP_H

#include <benchmark/benchmark.h>
#include <execution>
#include <iostream>
#include "b2_1_basic_reduce.h"
#include "../benchmark_prefix.h"

//region b2_1_basic_reduce

template<class Policy, typename TYPE>
static void b2_1_basic_reduce_wrapper(benchmark::State &state) {
    constexpr auto execution_policy = Policy{};

    std::vector<TYPE> x(state.range(0), static_cast<TYPE>(1.5));
    for (auto _: state) {
        b2_1_basic_reduce(execution_policy, x);
    }
}

//endregion b2_1_basic_reduce

// Register the function as a benchmark
#define B2_GROUP_BENCHMARKS \
                            \
                            \
    BENCHMARK_TEMPLATE2(b2_1_basic_reduce_wrapper, std::execution::sequenced_policy, char)->Name(BENCHMARK_NAME("b2_1_basic_reduce_char_seq"))->RangeMultiplier(2)->Range(1 << 5, 1 << 20); \
    BENCHMARK_TEMPLATE2(b2_1_basic_reduce_wrapper, std::execution::sequenced_policy, int)->Name(BENCHMARK_NAME("b2_1_basic_reduce_int_seq"))->RangeMultiplier(2)->Range(1 << 5, 1 << 20); \
    BENCHMARK_TEMPLATE2(b2_1_basic_reduce_wrapper, std::execution::sequenced_policy, long)->Name(BENCHMARK_NAME("b2_1_basic_reduce_long_seq"))->RangeMultiplier(2)->Range(1 << 5, 1 << 20); \
    BENCHMARK_TEMPLATE2(b2_1_basic_reduce_wrapper, std::execution::sequenced_policy, unsigned long)->Name(BENCHMARK_NAME("b2_1_basic_reduce_unsigned_long_seq"))->RangeMultiplier(2)->Range(1 << 5, 1 << 20); \
    BENCHMARK_TEMPLATE2(b2_1_basic_reduce_wrapper, std::execution::sequenced_policy, float)->Name(BENCHMARK_NAME("b2_1_basic_reduce_float_seq"))->RangeMultiplier(2)->Range(1 << 5, 1 << 20);               \
    BENCHMARK_TEMPLATE2(b2_1_basic_reduce_wrapper, std::execution::sequenced_policy, double)->Name(BENCHMARK_NAME("b2_1_basic_reduce_double_seq"))->RangeMultiplier(2)->Range(1 << 5, 1 << 20);               \
                            \
    BENCHMARK_TEMPLATE2(b2_1_basic_reduce_wrapper, std::execution::parallel_policy, char)->Name(BENCHMARK_NAME("b2_1_basic_reduce_char_par"))->RangeMultiplier(2)->Range(1 << 5, 1 << 20); \
    BENCHMARK_TEMPLATE2(b2_1_basic_reduce_wrapper, std::execution::parallel_policy, int)->Name(BENCHMARK_NAME("b2_1_basic_reduce_int_par"))->RangeMultiplier(2)->Range(1 << 5, 1 << 20); \
    BENCHMARK_TEMPLATE2(b2_1_basic_reduce_wrapper, std::execution::parallel_policy, long)->Name(BENCHMARK_NAME("b2_1_basic_reduce_long_par"))->RangeMultiplier(2)->Range(1 << 5, 1 << 20); \
    BENCHMARK_TEMPLATE2(b2_1_basic_reduce_wrapper, std::execution::parallel_policy, unsigned long)->Name(BENCHMARK_NAME("b2_1_basic_reduce_unsigned_long_par"))->RangeMultiplier(2)->Range(1 << 5, 1 << 20); \
    BENCHMARK_TEMPLATE2(b2_1_basic_reduce_wrapper, std::execution::parallel_policy, float)->Name(BENCHMARK_NAME("b2_1_basic_reduce_float_par"))->RangeMultiplier(2)->Range(1 << 5, 1 << 20);               \
    BENCHMARK_TEMPLATE2(b2_1_basic_reduce_wrapper, std::execution::parallel_policy, double)->Name(BENCHMARK_NAME("b2_1_basic_reduce_double_par"))->RangeMultiplier(2)->Range(1 << 5, 1 << 20);                \
                            \
    BENCHMARK_TEMPLATE2(b2_1_basic_reduce_wrapper, std::execution::parallel_unsequenced_policy, char)->Name(BENCHMARK_NAME("b2_1_basic_reduce_char_par_unseq"))->RangeMultiplier(2)->Range(1 << 5, 1 << 20); \
    BENCHMARK_TEMPLATE2(b2_1_basic_reduce_wrapper, std::execution::parallel_unsequenced_policy, int)->Name(BENCHMARK_NAME("b2_1_basic_reduce_int_par_unseq"))->RangeMultiplier(2)->Range(1 << 5, 1 << 20); \
    BENCHMARK_TEMPLATE2(b2_1_basic_reduce_wrapper, std::execution::parallel_unsequenced_policy, long)->Name(BENCHMARK_NAME("b2_1_basic_reduce_long_par_unseq"))->RangeMultiplier(2)->Range(1 << 5, 1 << 20); \
    BENCHMARK_TEMPLATE2(b2_1_basic_reduce_wrapper, std::execution::parallel_unsequenced_policy, unsigned long)->Name(BENCHMARK_NAME("b2_1_basic_reduce_unsigned_long_par_unseq"))->RangeMultiplier(2)->Range(1 << 5, 1 << 20); \
    BENCHMARK_TEMPLATE2(b2_1_basic_reduce_wrapper, std::execution::parallel_unsequenced_policy, float)->Name(BENCHMARK_NAME("b2_1_basic_reduce_float_par_unseq"))->RangeMultiplier(2)->Range(1 << 5, 1 << 20);               \
    BENCHMARK_TEMPLATE2(b2_1_basic_reduce_wrapper, std::execution::parallel_unsequenced_policy, double)->Name(BENCHMARK_NAME("b2_1_basic_reduce_double_par_unseq"))->RangeMultiplier(2)->Range(1 << 5, 1 << 20);                \

    
#endif //MASTER_BENCHMARKS_B2_GROUP_H
