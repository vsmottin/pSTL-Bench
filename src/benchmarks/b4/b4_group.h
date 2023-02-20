
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
#include "b4_2_stable_sort_cutoff.h"
#include "b4_3_set_union_cutoff.h"

//TODO: ask for help with stable_sort and merge because of
// ```
// b4_1_merge_cutoff_wrapper_par_unseq/524288                     617785 ns       617102 ns         1127
// terminate called after throwing an instance of 'std::bad_alloc'
//  what():  std::bad_alloc
// Aborted
// ```

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


//region b4_2_stable_sort_cutoff

template<class Policy>
static void b4_2_stable_sort_cutoff_already_sorted_wrapper(benchmark::State &state) {
    constexpr auto execution_policy = Policy{};

    const auto &size = state.range(0);

    auto already_sorted_vec = suite::generate_increment_vec<int>(size, 1);

    for (auto _: state) {
        b4_2_stable_sort_cutoff(execution_policy, already_sorted_vec);

        state.PauseTiming();
        assert(already_sorted_vec[0] <= already_sorted_vec[1]);
        state.ResumeTiming();
    }
}

template<class Policy>
static void b4_2_stable_sort_cutoff_not_sorted_wrapper(benchmark::State &state) {
    constexpr auto execution_policy = Policy{};

    const auto &size = state.range(0);

    auto already_sorted_vec = suite::generate_uniform_dist_vec<int>(size, 50, 100);

    for (auto _: state) {
        b4_2_stable_sort_cutoff(execution_policy, already_sorted_vec);

        state.PauseTiming();
        assert(already_sorted_vec[0] <= already_sorted_vec[1]);
        state.ResumeTiming();
    }
}

template<class Policy>
static void b4_2_stable_sort_cutoff_decrement_sorted_wrapper(benchmark::State &state) {
    constexpr auto execution_policy = Policy{};

    const auto &size = state.range(0);

    auto already_sorted_vec = suite::generate_decrement_vec<int>(size, size + 1, 1);

    for (auto _: state) {
        b4_2_stable_sort_cutoff(execution_policy, already_sorted_vec);

        state.PauseTiming();
        assert(already_sorted_vec[0] <= already_sorted_vec[1]);
        state.ResumeTiming();
    }
}

//endregion b4_2_stable_sort_cutoff


//region b4_3_set_union_cutoff

template<class Policy>
static void b4_3_set_union_cutoff_one_empty(benchmark::State &state) {
    constexpr auto execution_policy = Policy{};

    const auto &size = state.range(0);

    const auto already_sorted_vec = suite::generate_increment_vec(size, 1);
    const std::vector<int> empty_vec;

    for (auto _: state) {
        const auto res = b4_3_set_union_cutoff(execution_policy, already_sorted_vec, empty_vec);

        state.PauseTiming();
        assert(res[0] <= res[1]);
        assert(res.size() <= already_sorted_vec.size() + empty_vec.size());
        state.ResumeTiming();
    }
}

template<class Policy>
static void b4_3_set_union_cutoff_one_wholly_greater(benchmark::State &state) {
    constexpr auto execution_policy = Policy{};

    const auto &size = state.range(0);

    // every element inside already_sorted_vec_0_to_size is smaller than every element in already_sorted_vec_size_to_2size
    const auto already_sorted_vec_0_to_size = suite::generate_increment_vec(size, 1);
    const auto already_sorted_vec_size_to_2size = suite::generate_increment_vec<int>(size, size, 1);

    for (auto _: state) {
        const auto res = b4_3_set_union_cutoff(execution_policy,
                                               already_sorted_vec_0_to_size,
                                               already_sorted_vec_size_to_2size);

        state.PauseTiming();
        assert(res[0] <= res[1]);
        assert(res.size() <= already_sorted_vec_size_to_2size.size() + already_sorted_vec_0_to_size.size());
        state.ResumeTiming();
    }
}

template<class Policy>
static void b4_3_set_union_cutoff_front_overhang(benchmark::State &state) {
    constexpr auto execution_policy = Policy{};

    const auto &size = state.range(0);

    const auto vec1 = suite::generate_increment_vec(size, 1);
    const auto vec2 = suite::generate_increment_vec<int>(size, size / 2, 1);

    for (auto _: state) {
        const auto res = b4_3_set_union_cutoff(execution_policy, vec1, vec2);

        state.PauseTiming();
        assert(res[0] <= res[1]);
        assert(res.size() <= vec2.size() + vec1.size());
        state.ResumeTiming();
    }
}

//endregion b4_3_set_union_cutoff


// Register the function as a benchmark
#define B4_GROUP_BENCHMARKS \
                            \
                            \
        BENCHMARK_TEMPLATE1(b4_1_merge_cutoff_wrapper,std::execution::sequenced_policy)->Name(BENCHMARK_NAME("b4_1_merge_cutoff_wrapper_seq"))->RangeMultiplier(2)->Range(1 << 2, 1 << 20); \
        BENCHMARK_TEMPLATE1(b4_1_merge_cutoff_wrapper,std::execution::parallel_policy)->Name(BENCHMARK_NAME("b4_1_merge_cutoff_wrapper_par"))->RangeMultiplier(2)->Range(1 << 2, 1 << 20);     \
        BENCHMARK_TEMPLATE1(b4_1_merge_cutoff_wrapper,std::execution::parallel_unsequenced_policy)->Name(BENCHMARK_NAME("b4_1_merge_cutoff_wrapper_par_unseq"))->RangeMultiplier(2)->Range(1 << 2, 1 << 20); \
        BENCHMARK_TEMPLATE1(b4_1_merge_cutoff_wrapper,std::execution::unsequenced_policy)->Name(BENCHMARK_NAME("b4_1_merge_cutoff_wrapper_unseq"))->RangeMultiplier(2)->Range(1 << 2, 1 << 20); \
                            \
                            \
        BENCHMARK_TEMPLATE1(b4_2_stable_sort_cutoff_already_sorted_wrapper,std::execution::sequenced_policy)->Name(BENCHMARK_NAME("b4_2_stable_sort_cutoff_already_sorted_seq"))->RangeMultiplier(2)->Range(1 << 2, 1 << 20); \
        BENCHMARK_TEMPLATE1(b4_2_stable_sort_cutoff_already_sorted_wrapper,std::execution::parallel_policy)->Name(BENCHMARK_NAME("b4_2_stable_sort_cutoff_already_sorted_par"))->RangeMultiplier(2)->Range(1 << 2, 1 << 20);     \
        BENCHMARK_TEMPLATE1(b4_2_stable_sort_cutoff_already_sorted_wrapper,std::execution::parallel_unsequenced_policy)->Name(BENCHMARK_NAME("b4_2_stable_sort_cutoff_already_sorted_par_unseq"))->RangeMultiplier(2)->Range(1 << 2, 1 << 20); \
        BENCHMARK_TEMPLATE1(b4_2_stable_sort_cutoff_already_sorted_wrapper,std::execution::unsequenced_policy)->Name(BENCHMARK_NAME("b4_2_stable_sort_cutoff_already_sorted_unseq"))->RangeMultiplier(2)->Range(1 << 2, 1 << 20);\
                            \
                            \
        BENCHMARK_TEMPLATE1(b4_2_stable_sort_cutoff_decrement_sorted_wrapper,std::execution::sequenced_policy)->Name(BENCHMARK_NAME("b4_2_stable_sort_cutoff_decrement_sorted_seq"))->RangeMultiplier(2)->Range(1 << 2, 1 << 20); \
        BENCHMARK_TEMPLATE1(b4_2_stable_sort_cutoff_decrement_sorted_wrapper,std::execution::parallel_policy)->Name(BENCHMARK_NAME("b4_2_stable_sort_cutoff_decrement_sorted_par"))->RangeMultiplier(2)->Range(1 << 2, 1 << 20);     \
        BENCHMARK_TEMPLATE1(b4_2_stable_sort_cutoff_decrement_sorted_wrapper,std::execution::parallel_unsequenced_policy)->Name(BENCHMARK_NAME("b4_2_stable_sort_cutoff_decrement_sorted_par_unseq"))->RangeMultiplier(2)->Range(1 << 2, 1 << 20); \
        BENCHMARK_TEMPLATE1(b4_2_stable_sort_cutoff_decrement_sorted_wrapper,std::execution::unsequenced_policy)->Name(BENCHMARK_NAME("b4_2_stable_sort_cutoff_decrement_sorted_unseq"))->RangeMultiplier(2)->Range(1 << 2, 1 << 20);     \
                            \
                            \
        BENCHMARK_TEMPLATE1(b4_2_stable_sort_cutoff_not_sorted_wrapper,std::execution::sequenced_policy)->Name(BENCHMARK_NAME("b4_2_stable_sort_cutoff_not_sorted_seq"))->RangeMultiplier(2)->Range(1 << 2, 1 << 20); \
        BENCHMARK_TEMPLATE1(b4_2_stable_sort_cutoff_not_sorted_wrapper,std::execution::parallel_policy)->Name(BENCHMARK_NAME("b4_2_stable_sort_cutoff_not_sorted_par"))->RangeMultiplier(2)->Range(1 << 2, 1 << 20);     \
        BENCHMARK_TEMPLATE1(b4_2_stable_sort_cutoff_not_sorted_wrapper,std::execution::parallel_unsequenced_policy)->Name(BENCHMARK_NAME("b4_2_stable_sort_cutoff_not_sorted_par_unseq"))->RangeMultiplier(2)->Range(1 << 2, 1 << 20); \
        BENCHMARK_TEMPLATE1(b4_2_stable_sort_cutoff_not_sorted_wrapper,std::execution::unsequenced_policy)->Name(BENCHMARK_NAME("b4_2_stable_sort_cutoff_not_sorted_unseq"))->RangeMultiplier(2)->Range(1 << 2, 1 << 20);     \
                            \
                            \
                            \
                            \
        BENCHMARK_TEMPLATE1(b4_3_set_union_cutoff_one_empty,std::execution::sequenced_policy)->Name(BENCHMARK_NAME("b4_3_set_union_cutoff_one_empty_seq"))->RangeMultiplier(2)->Range(1 << 2, 1 << 20); \
        BENCHMARK_TEMPLATE1(b4_3_set_union_cutoff_one_empty,std::execution::parallel_policy)->Name(BENCHMARK_NAME("b4_3_set_union_cutoff_one_empty_par"))->RangeMultiplier(2)->Range(1 << 2, 1 << 20);     \
        BENCHMARK_TEMPLATE1(b4_3_set_union_cutoff_one_empty,std::execution::parallel_unsequenced_policy)->Name(BENCHMARK_NAME("b4_3_set_union_cutoff_one_empty_par_unseq"))->RangeMultiplier(2)->Range(1 << 2, 1 << 20); \
        BENCHMARK_TEMPLATE1(b4_3_set_union_cutoff_one_empty,std::execution::unsequenced_policy)->Name(BENCHMARK_NAME("b4_3_set_union_cutoff_one_empty_unseq"))->RangeMultiplier(2)->Range(1 << 2, 1 << 20);              \
                            \
                            \
        BENCHMARK_TEMPLATE1(b4_3_set_union_cutoff_one_wholly_greater,std::execution::sequenced_policy)->Name(BENCHMARK_NAME("b4_3_set_union_cutoff_one_wholly_greater_seq"))->RangeMultiplier(2)->Range(1 << 2, 1 << 20); \
        BENCHMARK_TEMPLATE1(b4_3_set_union_cutoff_one_wholly_greater,std::execution::parallel_policy)->Name(BENCHMARK_NAME("b4_3_set_union_cutoff_one_wholly_greater_par"))->RangeMultiplier(2)->Range(1 << 2, 1 << 20);     \
        BENCHMARK_TEMPLATE1(b4_3_set_union_cutoff_one_wholly_greater,std::execution::parallel_unsequenced_policy)->Name(BENCHMARK_NAME("b4_3_set_union_cutoff_one_wholly_greater_par_unseq"))->RangeMultiplier(2)->Range(1 << 2, 1 << 20); \
        BENCHMARK_TEMPLATE1(b4_3_set_union_cutoff_one_wholly_greater,std::execution::unsequenced_policy)->Name(BENCHMARK_NAME("b4_3_set_union_cutoff_one_wholly_greater_unseq"))->RangeMultiplier(2)->Range(1 << 2, 1 << 20);\
                            \
                            \
        BENCHMARK_TEMPLATE1(b4_3_set_union_cutoff_front_overhang,std::execution::sequenced_policy)->Name(BENCHMARK_NAME("b4_3_set_union_cutoff_front_overhang_seq"))->RangeMultiplier(2)->Range(1 << 2, 1 << 20); \
        BENCHMARK_TEMPLATE1(b4_3_set_union_cutoff_front_overhang,std::execution::parallel_policy)->Name(BENCHMARK_NAME("b4_3_set_union_cutoff_front_overhang_par"))->RangeMultiplier(2)->Range(1 << 2, 1 << 20);     \
        BENCHMARK_TEMPLATE1(b4_3_set_union_cutoff_front_overhang,std::execution::parallel_unsequenced_policy)->Name(BENCHMARK_NAME("b4_3_set_union_cutoff_front_overhang_par_unseq"))->RangeMultiplier(2)->Range(1 << 2, 1 << 20); \
        BENCHMARK_TEMPLATE1(b4_3_set_union_cutoff_front_overhang,std::execution::unsequenced_policy)->Name(BENCHMARK_NAME("b4_3_set_union_cutoff_front_overhang_unseq"))->RangeMultiplier(2)->Range(1 << 2, 1 << 20);          \


#endif //MASTER_BENCHMARKS_B4_GROUP_H
