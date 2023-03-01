
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
#include "b4_4_set_difference_cutoff.h"

//region b4_1_merge_cutoff

template<class Policy>
static void b4_1_merge_cutoff_wrapper(benchmark::State &state) {
    constexpr auto execution_policy = Policy{};

    const auto &size = state.range(0);

    // https://en.cppreference.com/w/cpp/algorithm/merge
    // we need two sorted vectors to use std::merge
    // vec_2_inc and vec_5_inc are indeed sorted

    const auto vec_2_inc = suite::generate_increment<suite::int_vec>(size, 2);
    const auto vec_5_inc = suite::generate_increment<suite::int_vec>(size, 5);

    for (auto _: state) {
        const auto res = B4::b4_1_merge_cutoff(execution_policy, vec_2_inc, vec_5_inc);

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

    auto already_sorted_vec = suite::generate_increment<suite::int_vec>(size, 1);

    for (auto _: state) {
        B4::b4_2_stable_sort_cutoff(execution_policy, already_sorted_vec);

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
        B4::b4_2_stable_sort_cutoff(execution_policy, already_sorted_vec);

        state.PauseTiming();
        assert(already_sorted_vec[0] <= already_sorted_vec[1]);
        state.ResumeTiming();
    }
}

template<class Policy>
static void b4_2_stable_sort_cutoff_decrement_sorted_wrapper(benchmark::State &state) {
    constexpr auto execution_policy = Policy{};

    const auto &size = state.range(0);

    auto already_sorted_vec = suite::generate_decrement<suite::int_vec, int>(size, size + 1, 1);

    for (auto _: state) {
        B4::b4_2_stable_sort_cutoff(execution_policy, already_sorted_vec);

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

    const auto already_sorted_vec = suite::generate_increment<suite::int_vec>(size, 1);
    const std::vector<int> empty_vec;

    for (auto _: state) {
        const auto res = B4::b4_3_set_union_cutoff(execution_policy, already_sorted_vec, empty_vec);

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
    const auto already_sorted_vec_0_to_size = suite::generate_increment<suite::int_vec>(size, 1);
    const auto already_sorted_vec_size_to_2size = suite::generate_increment<suite::int_vec, int>(size, size, 1);

    for (auto _: state) {
        const auto res = B4::b4_3_set_union_cutoff(execution_policy,
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

    const auto vec1 = suite::generate_increment<suite::int_vec>(size, 1);
    const auto vec2 = suite::generate_increment<suite::int_vec, int>(size, size / 2, 1);

    for (auto _: state) {
        const auto res = B4::b4_3_set_union_cutoff(execution_policy, vec1, vec2);

        state.PauseTiming();
        assert(res[0] <= res[1]);
        assert(res.size() <= vec2.size() + vec1.size());
        state.ResumeTiming();
    }
}

//endregion b4_3_set_union_cutoff

//region b4_4_set_difference_cutoff

template<class Policy>
static void b4_4_set_difference_cutoff_left_empty(benchmark::State &state) {
    constexpr auto execution_policy = Policy{};

    const auto &size = state.range(0);

    // since the left vector is empty we know the difference can only be empty
    // this test simply checks if this simple check is really done or parallel execution just started.
    const auto vec1 = suite::generate_increment<suite::int_vec>(size, 1);
    const std::vector<int> empty_vec{};

    for (auto _: state) {
        const auto res = B4::b4_4_set_difference_cutoff(execution_policy, empty_vec, vec1);

        state.PauseTiming();
        assert(res.size() == 0);
        state.ResumeTiming();
    }
}

template<class Policy>
static void b4_4_set_difference_cutoff_right_empty(benchmark::State &state) {
    constexpr auto execution_policy = Policy{};

    const auto &size = state.range(0);

    // since the right vector is empty we know the difference is the left vector
    // this should result in a copy of the vec1.
    const auto vec1 = suite::generate_increment<suite::int_vec>(size, 1);
    const std::vector<int> empty_vec{};

    for (auto _: state) {
        const auto res = B4::b4_4_set_difference_cutoff(execution_policy, vec1, empty_vec);

        state.PauseTiming();
        assert(res[0] <= res[1]);
        assert(res.size() == vec1.size());
        state.ResumeTiming();
    }
}

template<class Policy>
static void b4_4_set_difference_cutoff_wholly_greater(benchmark::State &state) {
    constexpr auto execution_policy = Policy{};

    const auto &size = state.range(0);

    // since the right vector is wholly greater than the left we know the difference is the left vector (aka no intersect)
    // this should result in a copy of the vec1.
    const auto vec1 = suite::generate_increment<suite::int_vec>(size, 1);
    const auto vec2 = suite::generate_increment<suite::int_vec, int>(size, size + 2, 1);

    for (auto _: state) {
        const auto res = B4::b4_4_set_difference_cutoff(execution_policy, vec1, vec2);

        state.PauseTiming();
        assert(res[0] <= res[1]);
        assert(res.size() == vec1.size());
        state.ResumeTiming();
    }
}

template<class Policy>
static void b4_4_set_difference_cutoff_intersected(benchmark::State &state) {
    constexpr auto execution_policy = Policy{};

    const auto &size = state.range(0);

    // since the vector intersect we acutally have to calculate the difference
    const auto vec1 = suite::generate_increment<suite::int_vec>(size, 1);
    const auto vec2 = suite::generate_increment<suite::int_vec, int>(size, 1);

    for (auto _: state) {
        const auto res = B4::b4_4_set_difference_cutoff(execution_policy, vec1, vec2);

        state.PauseTiming();
        assert(res.size() >= 2 && res[res.size() - 1] == 0);
        state.ResumeTiming();
    }
}

//endregion b4_4_set_difference_cutoff


// Register the function as a benchmark
#define B4_GROUP_BENCHMARKS \
                            \
                            \
        BENCHMARK_TEMPLATE1(b4_1_merge_cutoff_wrapper,std::execution::sequenced_policy)->Name(BENCHMARK_NAME("b4_1_merge_cutoff_wrapper_seq"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(1 << 2, 1 << 20); \
        BENCHMARK_TEMPLATE1(b4_1_merge_cutoff_wrapper,std::execution::parallel_policy)->Name(BENCHMARK_NAME("b4_1_merge_cutoff_wrapper_par"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(1 << 2, 1 << 20);     \
        BENCHMARK_TEMPLATE1(b4_1_merge_cutoff_wrapper,std::execution::parallel_unsequenced_policy)->Name(BENCHMARK_NAME("b4_1_merge_cutoff_wrapper_par_unseq"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(1 << 2, 1 << 20); \
        BENCHMARK_TEMPLATE1(b4_1_merge_cutoff_wrapper,std::execution::unsequenced_policy)->Name(BENCHMARK_NAME("b4_1_merge_cutoff_wrapper_unseq"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(1 << 2, 1 << 20); \
                            \
                            \
        BENCHMARK_TEMPLATE1(b4_2_stable_sort_cutoff_already_sorted_wrapper,std::execution::sequenced_policy)->Name(BENCHMARK_NAME("b4_2_stable_sort_cutoff_already_sorted_seq"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(1 << 2, 1 << 20); \
        BENCHMARK_TEMPLATE1(b4_2_stable_sort_cutoff_already_sorted_wrapper,std::execution::parallel_policy)->Name(BENCHMARK_NAME("b4_2_stable_sort_cutoff_already_sorted_par"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(1 << 2, 1 << 20);     \
        BENCHMARK_TEMPLATE1(b4_2_stable_sort_cutoff_already_sorted_wrapper,std::execution::parallel_unsequenced_policy)->Name(BENCHMARK_NAME("b4_2_stable_sort_cutoff_already_sorted_par_unseq"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(1 << 2, 1 << 20); \
        BENCHMARK_TEMPLATE1(b4_2_stable_sort_cutoff_already_sorted_wrapper,std::execution::unsequenced_policy)->Name(BENCHMARK_NAME("b4_2_stable_sort_cutoff_already_sorted_unseq"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(1 << 2, 1 << 20);\
                            \
                            \
        BENCHMARK_TEMPLATE1(b4_2_stable_sort_cutoff_decrement_sorted_wrapper,std::execution::sequenced_policy)->Name(BENCHMARK_NAME("b4_2_stable_sort_cutoff_decrement_sorted_seq"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(1 << 2, 1 << 20); \
        BENCHMARK_TEMPLATE1(b4_2_stable_sort_cutoff_decrement_sorted_wrapper,std::execution::parallel_policy)->Name(BENCHMARK_NAME("b4_2_stable_sort_cutoff_decrement_sorted_par"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(1 << 2, 1 << 20);     \
        BENCHMARK_TEMPLATE1(b4_2_stable_sort_cutoff_decrement_sorted_wrapper,std::execution::parallel_unsequenced_policy)->Name(BENCHMARK_NAME("b4_2_stable_sort_cutoff_decrement_sorted_par_unseq"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(1 << 2, 1 << 20); \
        BENCHMARK_TEMPLATE1(b4_2_stable_sort_cutoff_decrement_sorted_wrapper,std::execution::unsequenced_policy)->Name(BENCHMARK_NAME("b4_2_stable_sort_cutoff_decrement_sorted_unseq"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(1 << 2, 1 << 20);     \
                            \
                            \
        BENCHMARK_TEMPLATE1(b4_2_stable_sort_cutoff_not_sorted_wrapper,std::execution::sequenced_policy)->Name(BENCHMARK_NAME("b4_2_stable_sort_cutoff_not_sorted_seq"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(1 << 2, 1 << 20); \
        BENCHMARK_TEMPLATE1(b4_2_stable_sort_cutoff_not_sorted_wrapper,std::execution::parallel_policy)->Name(BENCHMARK_NAME("b4_2_stable_sort_cutoff_not_sorted_par"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(1 << 2, 1 << 20);     \
        BENCHMARK_TEMPLATE1(b4_2_stable_sort_cutoff_not_sorted_wrapper,std::execution::parallel_unsequenced_policy)->Name(BENCHMARK_NAME("b4_2_stable_sort_cutoff_not_sorted_par_unseq"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(1 << 2, 1 << 20); \
        BENCHMARK_TEMPLATE1(b4_2_stable_sort_cutoff_not_sorted_wrapper,std::execution::unsequenced_policy)->Name(BENCHMARK_NAME("b4_2_stable_sort_cutoff_not_sorted_unseq"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(1 << 2, 1 << 20);     \
                            \
                            \
                            \
                            \
        BENCHMARK_TEMPLATE1(b4_3_set_union_cutoff_one_empty,std::execution::sequenced_policy)->Name(BENCHMARK_NAME("b4_3_set_union_cutoff_one_empty_seq"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(1 << 2, 1 << 20); \
        BENCHMARK_TEMPLATE1(b4_3_set_union_cutoff_one_empty,std::execution::parallel_policy)->Name(BENCHMARK_NAME("b4_3_set_union_cutoff_one_empty_par"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(1 << 2, 1 << 20);     \
        BENCHMARK_TEMPLATE1(b4_3_set_union_cutoff_one_empty,std::execution::parallel_unsequenced_policy)->Name(BENCHMARK_NAME("b4_3_set_union_cutoff_one_empty_par_unseq"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(1 << 2, 1 << 20); \
        BENCHMARK_TEMPLATE1(b4_3_set_union_cutoff_one_empty,std::execution::unsequenced_policy)->Name(BENCHMARK_NAME("b4_3_set_union_cutoff_one_empty_unseq"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(1 << 2, 1 << 20);              \
                            \
                            \
        BENCHMARK_TEMPLATE1(b4_3_set_union_cutoff_one_wholly_greater,std::execution::sequenced_policy)->Name(BENCHMARK_NAME("b4_3_set_union_cutoff_one_wholly_greater_seq"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(1 << 2, 1 << 20); \
        BENCHMARK_TEMPLATE1(b4_3_set_union_cutoff_one_wholly_greater,std::execution::parallel_policy)->Name(BENCHMARK_NAME("b4_3_set_union_cutoff_one_wholly_greater_par"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(1 << 2, 1 << 20);     \
        BENCHMARK_TEMPLATE1(b4_3_set_union_cutoff_one_wholly_greater,std::execution::parallel_unsequenced_policy)->Name(BENCHMARK_NAME("b4_3_set_union_cutoff_one_wholly_greater_par_unseq"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(1 << 2, 1 << 20); \
        BENCHMARK_TEMPLATE1(b4_3_set_union_cutoff_one_wholly_greater,std::execution::unsequenced_policy)->Name(BENCHMARK_NAME("b4_3_set_union_cutoff_one_wholly_greater_unseq"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(1 << 2, 1 << 20);\
                            \
                            \
        BENCHMARK_TEMPLATE1(b4_3_set_union_cutoff_front_overhang,std::execution::sequenced_policy)->Name(BENCHMARK_NAME("b4_3_set_union_cutoff_front_overhang_seq"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(1 << 2, 1 << 20); \
        BENCHMARK_TEMPLATE1(b4_3_set_union_cutoff_front_overhang,std::execution::parallel_policy)->Name(BENCHMARK_NAME("b4_3_set_union_cutoff_front_overhang_par"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(1 << 2, 1 << 20);     \
        BENCHMARK_TEMPLATE1(b4_3_set_union_cutoff_front_overhang,std::execution::parallel_unsequenced_policy)->Name(BENCHMARK_NAME("b4_3_set_union_cutoff_front_overhang_par_unseq"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(1 << 2, 1 << 20); \
        BENCHMARK_TEMPLATE1(b4_3_set_union_cutoff_front_overhang,std::execution::unsequenced_policy)->Name(BENCHMARK_NAME("b4_3_set_union_cutoff_front_overhang_unseq"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(1 << 2, 1 << 20);         \
                            \
                            \
                            \
                            \
        BENCHMARK_TEMPLATE1(b4_4_set_difference_cutoff_left_empty,std::execution::sequenced_policy)->Name(BENCHMARK_NAME("b4_4_set_difference_cutoff_left_empty_seq"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(1 << 2, 1 << 20); \
        BENCHMARK_TEMPLATE1(b4_4_set_difference_cutoff_left_empty,std::execution::parallel_policy)->Name(BENCHMARK_NAME("b4_4_set_difference_cutoff_left_empty_par"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(1 << 2, 1 << 20);     \
        BENCHMARK_TEMPLATE1(b4_4_set_difference_cutoff_left_empty,std::execution::parallel_unsequenced_policy)->Name(BENCHMARK_NAME("b4_4_set_difference_cutoff_left_empty_par_unseq"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(1 << 2, 1 << 20); \
        BENCHMARK_TEMPLATE1(b4_4_set_difference_cutoff_left_empty,std::execution::unsequenced_policy)->Name(BENCHMARK_NAME("b4_4_set_difference_cutoff_left_empty_unseq"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(1 << 2, 1 << 20);       \
                            \
                            \
        BENCHMARK_TEMPLATE1(b4_4_set_difference_cutoff_right_empty,std::execution::sequenced_policy)->Name(BENCHMARK_NAME("b4_4_set_difference_cutoff_right_empty_seq"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(1 << 2, 1 << 20); \
        BENCHMARK_TEMPLATE1(b4_4_set_difference_cutoff_right_empty,std::execution::parallel_policy)->Name(BENCHMARK_NAME("b4_4_set_difference_cutoff_right_empty_par"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(1 << 2, 1 << 20);     \
        BENCHMARK_TEMPLATE1(b4_4_set_difference_cutoff_right_empty,std::execution::parallel_unsequenced_policy)->Name(BENCHMARK_NAME("b4_4_set_difference_cutoff_right_empty_par_unseq"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(1 << 2, 1 << 20); \
        BENCHMARK_TEMPLATE1(b4_4_set_difference_cutoff_right_empty,std::execution::unsequenced_policy)->Name(BENCHMARK_NAME("b4_4_set_difference_cutoff_right_empty_unseq"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(1 << 2, 1 << 20);          \
                            \
                            \
        BENCHMARK_TEMPLATE1(b4_4_set_difference_cutoff_wholly_greater,std::execution::sequenced_policy)->Name(BENCHMARK_NAME("b4_4_set_difference_cutoff_wholly_greater_seq"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(1 << 2, 1 << 20); \
        BENCHMARK_TEMPLATE1(b4_4_set_difference_cutoff_wholly_greater,std::execution::parallel_policy)->Name(BENCHMARK_NAME("b4_4_set_difference_cutoff_wholly_greater_par"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(1 << 2, 1 << 20);     \
        BENCHMARK_TEMPLATE1(b4_4_set_difference_cutoff_wholly_greater,std::execution::parallel_unsequenced_policy)->Name(BENCHMARK_NAME("b4_4_set_difference_cutoff_wholly_greater_par_unseq"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(1 << 2, 1 << 20); \
        BENCHMARK_TEMPLATE1(b4_4_set_difference_cutoff_wholly_greater,std::execution::unsequenced_policy)->Name(BENCHMARK_NAME("b4_4_set_difference_cutoff_wholly_greater_unseq"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(1 << 2, 1 << 20);          \
                            \
                            \
        BENCHMARK_TEMPLATE1(b4_4_set_difference_cutoff_intersected,std::execution::sequenced_policy)->Name(BENCHMARK_NAME("b4_4_set_difference_cutoff_intersected_seq"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(1 << 2, 1 << 20); \
        BENCHMARK_TEMPLATE1(b4_4_set_difference_cutoff_intersected,std::execution::parallel_policy)->Name(BENCHMARK_NAME("b4_4_set_difference_cutoff_intersected_par"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(1 << 2, 1 << 20);     \
        BENCHMARK_TEMPLATE1(b4_4_set_difference_cutoff_intersected,std::execution::parallel_unsequenced_policy)->Name(BENCHMARK_NAME("b4_4_set_difference_cutoff_intersected_par_unseq"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(1 << 2, 1 << 20); \
        BENCHMARK_TEMPLATE1(b4_4_set_difference_cutoff_intersected,std::execution::unsequenced_policy)->Name(BENCHMARK_NAME("b4_4_set_difference_cutoff_intersected_unseq"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(1 << 2, 1 << 20);          \



#endif //MASTER_BENCHMARKS_B4_GROUP_H
