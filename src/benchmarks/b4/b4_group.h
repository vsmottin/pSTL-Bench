
#ifndef MASTER_BENCHMARKS_B4_GROUP_H
#define MASTER_BENCHMARKS_B4_GROUP_H

#include <benchmark/benchmark.h>
#include <execution>
#include <vector>
#include <cassert>
#include <iostream>

#include "../benchmark_prefix.h"
#include "../benchmark_utils.h"
#include "b4_1_merge_cutoff.h"

//region b4_1_merge_cutoff

template<class Policy>
static void b4_1_merge_cutoff_wrapper(benchmark::State &state) {
    constexpr auto execution_policy = Policy{};

    const auto &size = state.range(0);

    // https://en.cppreference.com/w/cpp/algorithm/merge
    // we need two sorted vectors to use std::merge
    // vec_2_inc and vec_5_inc are indeed sorted

    const auto vec_2_inc = suite::generate_increment_vec<int>(size, 2);
    const auto vec_5_inc = suite::generate_increment_vec<int>(size, 5);

    for (auto _: state) {
        const auto res = b4_1_merge_cutoff(execution_policy, vec_2_inc, vec_5_inc);

        state.PauseTiming();
        assert(res.size() == 2 * size);
        state.ResumeTiming();
    }
}

//endregion b4_1_merge_cutoff

// Register the function as a benchmark
#define B4_GROUP_BENCHMARKS \
        BENCHMARK_TEMPLATE1(b4_1_merge_cutoff_wrapper,std::execution::sequenced_policy)->Name(BENCHMARK_NAME("b4_1_merge_cutoff_wrapper_seq"))->RangeMultiplier(2)->Range(1 << 2, 1 << 20); \
        BENCHMARK_TEMPLATE1(b4_1_merge_cutoff_wrapper,std::execution::parallel_policy)->Name(BENCHMARK_NAME("b4_1_merge_cutoff_wrapper_par"))->RangeMultiplier(2)->Range(1 << 2, 1 << 20);     \
        BENCHMARK_TEMPLATE1(b4_1_merge_cutoff_wrapper,std::execution::parallel_unsequenced_policy)->Name(BENCHMARK_NAME("b4_1_merge_cutoff_wrapper_par_unseq"))->RangeMultiplier(2)->Range(1 << 2, 1 << 20); \



#endif //MASTER_BENCHMARKS_B4_GROUP_H
