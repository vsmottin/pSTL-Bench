
#ifndef MASTER_BENCHMARKS_B3_GROUP_H
#define MASTER_BENCHMARKS_B3_GROUP_H

#include <benchmark/benchmark.h>
#include <execution>
#include <iostream>
#include "../benchmark_prefix.h"
#include "b3_1_expensive_branching.h"
#include "b3_2_expensive_branching_annotated.h"

//region b3_1_expensive_branching

template<class Policy>
static void b3_1_expensive_branching_fail(benchmark::State &state) {
    constexpr auto execution_policy = Policy{};

    // we just use this to trick the optimizer
    const int rand_magic_number_gt_1 = std::rand() + 2;

    std::vector<int> x(state.range(0), 1);
    for (auto _: state) {
        b3_1_expensive_branching(execution_policy, x, rand_magic_number_gt_1);
    }
}

template<class Policy>
static void b3_2_expensive_branching_annotated_success(benchmark::State &state) {
    constexpr auto execution_policy = Policy{};

    // we just use this to trick the optimizer
    const int rand_magic_number_gt_1 = std::rand() + 2;

    std::vector<int> x(state.range(0), 1);
    for (auto _: state) {
        b3_2_expensive_branching_annotated(execution_policy, x, rand_magic_number_gt_1);
    }
}


//endregion b3_1_expensive_branching

// Register the function as a benchmark
#define B3_GROUP_BENCHMARKS \
        BENCHMARK_TEMPLATE1(b3_1_expensive_branching_fail,std::execution::sequenced_policy)->Name(BENCHMARK_NAME("b3_1_expensive_branching_fail_seq"))->RangeMultiplier(2)->Range(1 << 5, 1 << 20); \
        BENCHMARK_TEMPLATE1(b3_1_expensive_branching_fail,std::execution::parallel_policy)->Name(BENCHMARK_NAME("b3_1_expensive_branching_fail_par"))->RangeMultiplier(2)->Range(1 << 5, 1 << 20);     \
        BENCHMARK_TEMPLATE1(b3_1_expensive_branching_fail,std::execution::parallel_unsequenced_policy)->Name(BENCHMARK_NAME("b3_1_expensive_branching_fail_par_unseq"))->RangeMultiplier(2)->Range(1 << 5, 1 << 20); \
                            \
                            \
        BENCHMARK_TEMPLATE1(b3_2_expensive_branching_annotated_success,std::execution::sequenced_policy)->Name(BENCHMARK_NAME("b3_2_expensive_branching_annotated_success_seq"))->RangeMultiplier(2)->Range(1 << 5, 1 << 20); \
        BENCHMARK_TEMPLATE1(b3_2_expensive_branching_annotated_success,std::execution::parallel_policy)->Name(BENCHMARK_NAME("b3_2_expensive_branching_annotated_success_par"))->RangeMultiplier(2)->Range(1 << 5, 1 << 20);     \
        BENCHMARK_TEMPLATE1(b3_2_expensive_branching_annotated_success,std::execution::parallel_unsequenced_policy)->Name(BENCHMARK_NAME("b3_2_expensive_branching_annotated_success_par_unseq"))->RangeMultiplier(2)->Range(1 << 5, 1 << 20);

#endif //MASTER_BENCHMARKS_B3_GROUP_H
