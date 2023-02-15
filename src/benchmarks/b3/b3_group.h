
#ifndef MASTER_BENCHMARKS_B3_GROUP_H
#define MASTER_BENCHMARKS_B3_GROUP_H

#include <benchmark/benchmark.h>
#include <cassert>
#include <execution>
#include <iostream>

#include "../benchmark_utils.h"
#include "../benchmark_prefix.h"
#include "b3_1_expensive_branching.h"
#include "b3_2_expensive_branching_annotated.h"
#include "b3_3_expensive_sharing.h"
#include "b3_4_no_expensive_sharing.h"
#include "b3_5_force_false_sharing.h"
#include "b3_6_no_false_sharing.h"


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

//endregion b3_1_expensive_branching

//region b3_2_expensive_branching_annotated

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

//endregion b3_2_expensive_branching_annotated

//region b3_3_expensive_sharing

template<class Policy>
static void b3_3_expensive_sharing_wrapper(benchmark::State &state) {
    constexpr auto execution_policy = Policy{};

    const auto size = state.range(0);

    // lower bound of 1 is required so the function call `b3_3_expensive_sharing` will count every element
    std::vector<int> x(generate_uniform_dist_vec<int>(size, 1, 10));

    for (auto _: state) {
        const auto count = b3_3_expensive_sharing(execution_policy, x);

        state.PauseTiming();
        assert((count == size));
        state.ResumeTiming();
    }
}

//endregion b3_3_expensive_sharing

//region b3_4_no_expensive_sharing

template<class Policy>
static void b3_4_no_expensive_sharing_wrapper(benchmark::State &state) {
    constexpr auto execution_policy = Policy{};

    const auto size = state.range(0);

    // lower bound of 1 is required so the function call `b3_4_no_expensive_sharing` will count every element
    std::vector<int> x(generate_uniform_dist_vec<int>(size, 1, 10));

    for (auto _: state) {
        const auto count = b3_4_no_expensive_sharing(execution_policy, x);

        state.PauseTiming();
        assert((count == size));
        state.ResumeTiming();
    }
}

//endregion b3_4_no_expensive_sharing


//region b3_5_force_false_sharing

template<class Policy>
static void b3_5_force_false_sharing_wrapper(benchmark::State &state) {
    constexpr auto execution_policy = Policy{};

    const auto size = state.range(0);

    // lower bound of 1 is required so the function call `b3_5_force_false_sharing` will count every element
    const auto values = generate_uniform_dist_vec<int>(size, 1, 10);

    std::vector<force_false_sharing_struct> x(size);
    std::generate(x.begin(), x.end(), [n = 0, &values]() { return force_false_sharing_struct{values[n], 0}; });

    for (auto _: state) {
        const auto count = b3_5_force_false_sharing(execution_policy, x);

        state.PauseTiming();
        assert((count == size));
        state.ResumeTiming();
    }
}

//endregion b3_5_force_false_sharing

//region b3_6_no_false_sharing

template<class Policy>
static void b3_6_no_false_sharing_wrapper(benchmark::State &state) {
    constexpr auto execution_policy = Policy{};

    const auto size = state.range(0);

    // lower bound of 1 is required so the function call `b3_6_no_false_sharing` will count every element
    const auto values = generate_uniform_dist_vec<int>(size, 1, 10);

    std::vector<no_false_sharing_struct> x(size);
    std::generate(x.begin(), x.end(), [n = 0, &values]() { return no_false_sharing_struct{values[n], 0}; });

    for (auto _: state) {
        const auto count = b3_6_no_false_sharing(execution_policy, x);

        state.PauseTiming();
        assert((count == size));
        state.ResumeTiming();
    }
}

//endregion b3_6_no_false_sharing


// Register the function as a benchmark
#define B3_GROUP_BENCHMARKS \
        BENCHMARK_TEMPLATE1(b3_1_expensive_branching_fail,std::execution::sequenced_policy)->Name(BENCHMARK_NAME("b3_1_expensive_branching_fail_seq"))->RangeMultiplier(2)->Range(1 << 5, 1 << 20); \
        BENCHMARK_TEMPLATE1(b3_1_expensive_branching_fail,std::execution::parallel_policy)->Name(BENCHMARK_NAME("b3_1_expensive_branching_fail_par"))->RangeMultiplier(2)->Range(1 << 5, 1 << 20);     \
        BENCHMARK_TEMPLATE1(b3_1_expensive_branching_fail,std::execution::parallel_unsequenced_policy)->Name(BENCHMARK_NAME("b3_1_expensive_branching_fail_par_unseq"))->RangeMultiplier(2)->Range(1 << 5, 1 << 20); \
                            \
                            \
        BENCHMARK_TEMPLATE1(b3_2_expensive_branching_annotated_success,std::execution::sequenced_policy)->Name(BENCHMARK_NAME("b3_2_expensive_branching_annotated_success_seq"))->RangeMultiplier(2)->Range(1 << 5, 1 << 20); \
        BENCHMARK_TEMPLATE1(b3_2_expensive_branching_annotated_success,std::execution::parallel_policy)->Name(BENCHMARK_NAME("b3_2_expensive_branching_annotated_success_par"))->RangeMultiplier(2)->Range(1 << 5, 1 << 20);     \
        BENCHMARK_TEMPLATE1(b3_2_expensive_branching_annotated_success,std::execution::parallel_unsequenced_policy)->Name(BENCHMARK_NAME("b3_2_expensive_branching_annotated_success_par_unseq"))->RangeMultiplier(2)->Range(1 << 5, 1 << 20); \
                            \
                            \
        BENCHMARK_TEMPLATE1(b3_3_expensive_sharing_wrapper,std::execution::sequenced_policy)->Name(BENCHMARK_NAME("b3_3_expensive_sharing_seq"))->RangeMultiplier(2)->Range(1 << 5, 1 << 20); \
        BENCHMARK_TEMPLATE1(b3_3_expensive_sharing_wrapper,std::execution::parallel_policy)->Name(BENCHMARK_NAME("b3_3_expensive_sharing_par"))->RangeMultiplier(2)->Range(1 << 5, 1 << 20);     \
        BENCHMARK_TEMPLATE1(b3_3_expensive_sharing_wrapper,std::execution::parallel_unsequenced_policy)->Name(BENCHMARK_NAME("b3_3_expensive_sharing_par_unseq"))->RangeMultiplier(2)->Range(1 << 5, 1 << 20);       \
                            \
                            \
        BENCHMARK_TEMPLATE1(b3_4_no_expensive_sharing_wrapper,std::execution::sequenced_policy)->Name(BENCHMARK_NAME("b3_4_no_expensive_sharing_seq"))->RangeMultiplier(2)->Range(1 << 5, 1 << 20); \
        BENCHMARK_TEMPLATE1(b3_4_no_expensive_sharing_wrapper,std::execution::parallel_policy)->Name(BENCHMARK_NAME("b3_4_no_expensive_sharing_par"))->RangeMultiplier(2)->Range(1 << 5, 1 << 20);     \
        BENCHMARK_TEMPLATE1(b3_4_no_expensive_sharing_wrapper,std::execution::parallel_unsequenced_policy)->Name(BENCHMARK_NAME("b3_4_no_expensive_sharing_par_unseq"))->RangeMultiplier(2)->Range(1 << 5, 1 << 20); \
                            \
                            \
        BENCHMARK_TEMPLATE1(b3_5_force_false_sharing_wrapper,std::execution::sequenced_policy)->Name(BENCHMARK_NAME("b3_5_force_false_sharing_seq"))->RangeMultiplier(2)->Range(1 << 5, 1 << 20); \
        BENCHMARK_TEMPLATE1(b3_5_force_false_sharing_wrapper,std::execution::parallel_policy)->Name(BENCHMARK_NAME("b3_5_force_false_sharing_par"))->RangeMultiplier(2)->Range(1 << 5, 1 << 20);     \
        BENCHMARK_TEMPLATE1(b3_5_force_false_sharing_wrapper,std::execution::parallel_unsequenced_policy)->Name(BENCHMARK_NAME("b3_5_force_false_sharing_par_unseq"))->RangeMultiplier(2)->Range(1 << 5, 1 << 20); \
                            \
                            \
        BENCHMARK_TEMPLATE1(b3_6_no_false_sharing_wrapper,std::execution::sequenced_policy)->Name(BENCHMARK_NAME("b3_6_no_false_sharing_seq"))->RangeMultiplier(2)->Range(1 << 5, 1 << 20); \
        BENCHMARK_TEMPLATE1(b3_6_no_false_sharing_wrapper,std::execution::parallel_policy)->Name(BENCHMARK_NAME("b3_6_no_false_sharing_par"))->RangeMultiplier(2)->Range(1 << 5, 1 << 20);     \
        BENCHMARK_TEMPLATE1(b3_6_no_false_sharing_wrapper,std::execution::parallel_unsequenced_policy)->Name(BENCHMARK_NAME("b3_6_no_false_sharing_par_unseq"))->RangeMultiplier(2)->Range(1 << 5, 1 << 20); \



#endif //MASTER_BENCHMARKS_B3_GROUP_H
