
#ifndef MASTER_BENCHMARKS_B4_GROUP_H
#define MASTER_BENCHMARKS_B4_GROUP_H

#include <chrono>
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

    const auto vec_2_inc = suite::generate_increment<Policy>(execution_policy, size, 2);
    const auto vec_5_inc = suite::generate_increment<Policy>(execution_policy, size, 5);

    std::vector<int> result(vec_2_inc.size() + vec_5_inc.size());
    suite::fill_init<Policy>(result, -1);

    for (auto _: state) {
        WRAP_TIMING(B4::b4_1_merge_cutoff(execution_policy, vec_2_inc, vec_5_inc, result);)

        assert(result[result.size() - 1] >= size - 1);
        assert(result.size() == 2 * size);
    }

    // https://ccfd.github.io/courses/hpc_lab01.html
    const int64_t actual_size_in_bytes = sizeof(int) *
                                         (int64_t(vec_2_inc.size()) + int64_t(vec_5_inc.size()));

    state.SetBytesProcessed(int64_t(state.iterations()) * actual_size_in_bytes);
}

//endregion b4_1_merge_cutoff


//region b4_2_stable_sort_cutoff

template<class Policy>
static void b4_2_stable_sort_cutoff_already_sorted_wrapper(benchmark::State &state) {
    constexpr auto execution_policy = Policy{};

    const auto &size = state.range(0);

    auto already_sorted_vec = suite::generate_increment<Policy>(execution_policy, size, 1);

    for (auto _: state) {
        WRAP_TIMING(B4::b4_2_stable_sort_cutoff(execution_policy, already_sorted_vec);)

        std::vector res_check = already_sorted_vec;
        assert(res_check[0] <= res_check[1]);
    }

    // https://ccfd.github.io/courses/hpc_lab01.html
    const int64_t actual_size_in_bytes = sizeof(int) *
                                         (int64_t(already_sorted_vec.size()));

    state.SetBytesProcessed(int64_t(state.iterations()) * actual_size_in_bytes);
}

template<class Policy>
static void b4_2_stable_sort_cutoff_not_sorted_wrapper(benchmark::State &state) {
    constexpr auto execution_policy = Policy{};

    const auto &size = state.range(0);

    auto not_sorted_vec = suite::generate_uniform_dist_vec<Policy>(size, 50, 100);

    for (auto _: state) {
        WRAP_TIMING(B4::b4_2_stable_sort_cutoff(execution_policy, not_sorted_vec);)

        assert(not_sorted_vec[0] <= not_sorted_vec[1]);
    }

    // https://ccfd.github.io/courses/hpc_lab01.html
    const int64_t actual_size_in_bytes = sizeof(int) *
                                         (int64_t(not_sorted_vec.size()));

    state.SetBytesProcessed(int64_t(state.iterations()) * actual_size_in_bytes);
}

template<class Policy>
static void b4_2_stable_sort_cutoff_decrement_sorted_wrapper(benchmark::State &state) {
    constexpr auto execution_policy = Policy{};

    const auto &size = static_cast<int>(state.range(0));

    auto already_sorted_vec = suite::generate_decrement<Policy>(execution_policy, size, size, 1);

    for (auto _: state) {
        WRAP_TIMING(B4::b4_2_stable_sort_cutoff(execution_policy, already_sorted_vec);)

        std::vector<int> res_check = already_sorted_vec;
        assert(res_check[0] <= res_check[1]);
    }

    // https://ccfd.github.io/courses/hpc_lab01.html
    const int64_t actual_size_in_bytes = sizeof(int) *
                                         (int64_t(already_sorted_vec.size()));

    state.SetBytesProcessed(int64_t(state.iterations()) * actual_size_in_bytes);
}

//endregion b4_2_stable_sort_cutoff


//region b4_3_set_union_cutoff

template<class Policy>
static void b4_3_set_union_cutoff_one_empty(benchmark::State &state) {
    constexpr auto execution_policy = Policy{};

    const auto &size = state.range(0);

    const auto already_sorted_vec = suite::generate_increment<Policy>(execution_policy, size, 1);
    const std::vector<int> empty_vec;

    std::vector<int> res(already_sorted_vec.size());
    suite::fill_init<Policy>(res, -1);

    for (auto _: state) {
        WRAP_TIMING(B4::b4_3_set_union_cutoff(execution_policy, already_sorted_vec, empty_vec, res);)

        std::vector<int> res_check = res;
        assert(res_check[0] <= res_check[1]);
        assert(res_check.size() <= already_sorted_vec.size() + empty_vec.size());
    }

    // https://ccfd.github.io/courses/hpc_lab01.html
    const int64_t actual_size_in_bytes = sizeof(int) *
                                         (int64_t(already_sorted_vec.size()));

    state.SetBytesProcessed(int64_t(state.iterations()) * actual_size_in_bytes);
}

template<class Policy>
static void b4_3_set_union_cutoff_one_wholly_greater(benchmark::State &state) {
    constexpr auto execution_policy = Policy{};

    const auto &size = static_cast<int>(state.range(0));

    // every element inside already_sorted_vec_0_to_size is smaller than every element in already_sorted_vec_size_to_2size
    const auto already_sorted_vec_0_to_size = suite::generate_increment<Policy>(execution_policy, size, 1);
    const auto already_sorted_vec_size_to_2size = suite::generate_increment<Policy>(execution_policy, size, size, 1);

    std::vector<int> res(already_sorted_vec_0_to_size.size() + already_sorted_vec_size_to_2size.size());

    for (auto _: state) {
        WRAP_TIMING(B4::b4_3_set_union_cutoff(execution_policy,
                                              already_sorted_vec_0_to_size,
                                              already_sorted_vec_size_to_2size,
                                              res);)

        std::vector res_check = res;
        assert(res_check[0] <= res_check[1]);
        assert(res_check.size() <= already_sorted_vec_size_to_2size.size() + already_sorted_vec_0_to_size.size());
    }

    // https://ccfd.github.io/courses/hpc_lab01.html
    const int64_t actual_size_in_bytes = sizeof(int) *
                                         (int64_t(already_sorted_vec_0_to_size.size()) +
                                          int64_t(already_sorted_vec_size_to_2size.size()));

    state.SetBytesProcessed(int64_t(state.iterations()) * actual_size_in_bytes);
}

template<class Policy>
static void b4_3_set_union_cutoff_front_overhang(benchmark::State &state) {
    constexpr auto execution_policy = Policy{};

    const auto &size = static_cast<int>(state.range(0));

    const auto vec1 = suite::generate_increment<Policy>(execution_policy, size, 1);
    const auto vec2 = suite::generate_increment<Policy>(execution_policy, size, size / 2, 1);

    std::vector<int> res(vec1.size() + vec2.size());

    for (auto _: state) {
        WRAP_TIMING(B4::b4_3_set_union_cutoff(execution_policy, vec1, vec2, res);)

        std::vector<int> res_check = res;
        assert(res_check[0] <= res_check[1]);
        assert(res_check.size() <= vec2.size() + vec1.size());
    }

    // https://ccfd.github.io/courses/hpc_lab01.html
    const int64_t actual_size_in_bytes = sizeof(int) *
                                         (int64_t(vec1.size()) +
                                          int64_t(vec2.size()));

    state.SetBytesProcessed(int64_t(state.iterations()) * actual_size_in_bytes);
}

//endregion b4_3_set_union_cutoff

//region b4_4_set_difference_cutoff

template<class Policy>
static void b4_4_set_difference_cutoff_left_empty(benchmark::State &state) {
    constexpr auto execution_policy = Policy{};

    const auto &size = state.range(0);

    // since the left vector is empty we know the difference can only be empty
    // this test simply checks if this simple check is really done or parallel execution just started.
    const auto vec1 = suite::generate_increment<Policy>(execution_policy, size, 1);
    const std::vector<int> empty_vec{};

    constexpr auto unrealistic_number = -9999;
    std::vector<int> res(vec1.size());
    suite::fill_init<Policy>(res, unrealistic_number);

    for (auto _: state) {
        WRAP_TIMING(B4::b4_4_set_difference_cutoff(execution_policy, empty_vec, vec1, res);)

        assert(res[0] == unrealistic_number);
    }

    // https://ccfd.github.io/courses/hpc_lab01.html
    const int64_t actual_size_in_bytes = sizeof(int) *
                                         (int64_t(vec1.size()));

    state.SetBytesProcessed(int64_t(state.iterations()) * actual_size_in_bytes);
}

template<class Policy>
static void b4_4_set_difference_cutoff_right_empty(benchmark::State &state) {
    constexpr auto execution_policy = Policy{};

    const auto &size = state.range(0);

    // since the right vector is empty we know the difference is the left vector
    // this should result in a copy of the vec1.
    const auto vec1 = suite::generate_increment<Policy>(execution_policy, size, 1);
    std::vector<int> empty_vec{};

    std::vector<int> res(vec1.size());

    for (auto _: state) {
        WRAP_TIMING(B4::b4_4_set_difference_cutoff(execution_policy, vec1, empty_vec, res);)

        std::vector res_check = res;
        assert(res_check[0] <= res_check[1]);
        assert(res_check.size() == vec1.size());
    }

    // https://ccfd.github.io/courses/hpc_lab01.html
    const int64_t actual_size_in_bytes = sizeof(int) *
                                         (int64_t(vec1.size()));

    state.SetBytesProcessed(int64_t(state.iterations()) * actual_size_in_bytes);
}

template<class Policy>
static void b4_4_set_difference_cutoff_wholly_greater(benchmark::State &state) {
    constexpr auto execution_policy = Policy{};

    const auto &size = static_cast<int>(state.range(0));

    // since the right vector is wholly greater than the left we know the difference is the left vector (aka no intersect)
    // this should result in a copy of the vec1.
    const auto vec1 = suite::generate_increment<Policy>(execution_policy, size, 1);
    const auto vec2 = suite::generate_increment<Policy>(execution_policy, size, size + 2, 1);

    std::vector<int> res(vec1.size());

    for (auto _: state) {
        WRAP_TIMING(B4::b4_4_set_difference_cutoff(execution_policy, vec1, vec2, res);)

        std::vector res_check = res;
        assert(res_check[0] <= res_check[1]);
        assert(res_check.size() == vec1.size());
    }

    // https://ccfd.github.io/courses/hpc_lab01.html
    const int64_t actual_size_in_bytes = sizeof(int) *
                                         (int64_t(vec1.size()) + int64_t(vec2.size()));

    state.SetBytesProcessed(int64_t(state.iterations()) * actual_size_in_bytes);
}

template<class Policy>
static void b4_4_set_difference_cutoff_intersected(benchmark::State &state) {
    constexpr auto execution_policy = Policy{};

    const auto &size = state.range(0);

    // since the vector intersect we acutally have to calculate the difference
    const auto vec1 = suite::generate_increment<Policy>(execution_policy, size, 1);
    const auto vec2 = suite::generate_increment<Policy>(execution_policy, size, 1);

    std::vector<int> res(vec1.size());

    for (auto _: state) {
        WRAP_TIMING(B4::b4_4_set_difference_cutoff(execution_policy, vec1, vec2, res);)

        std::vector res_check = res;
        assert(res_check.size() >= 2);
        assert(res_check[res_check.size() - 1] == 0);
    }

    // https://ccfd.github.io/courses/hpc_lab01.html
    const int64_t actual_size_in_bytes = sizeof(int) *
                                         (int64_t(vec1.size()) + int64_t(vec2.size()));

    state.SetBytesProcessed(int64_t(state.iterations()) * actual_size_in_bytes);
}

//endregion b4_4_set_difference_cutoff


// Register the function as a benchmark
#define B4_GROUP_BENCHMARKS \
                            \
                            \
        BENCHMARK_TEMPLATE1(b4_1_merge_cutoff_wrapper,std::execution::sequenced_policy)->Name(BENCHMARK_NAME("b4_1_merge_cutoff_wrapper_seq"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(MAX_INPUT_SIZE, MAX_INPUT_SIZE); \
        BENCHMARK_TEMPLATE1(b4_1_merge_cutoff_wrapper,std::execution::parallel_policy)->Name(BENCHMARK_NAME("b4_1_merge_cutoff_wrapper_par"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(1 << 2, MAX_INPUT_SIZE);     \
                            \
                            \
        BENCHMARK_TEMPLATE1(b4_2_stable_sort_cutoff_already_sorted_wrapper,std::execution::sequenced_policy)->Name(BENCHMARK_NAME("b4_2_stable_sort_cutoff_already_sorted_seq"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(MAX_INPUT_SIZE, MAX_INPUT_SIZE); \
        BENCHMARK_TEMPLATE1(b4_2_stable_sort_cutoff_already_sorted_wrapper,std::execution::parallel_policy)->Name(BENCHMARK_NAME("b4_2_stable_sort_cutoff_already_sorted_par"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(1 << 2, MAX_INPUT_SIZE);     \
                            \
                            \
        BENCHMARK_TEMPLATE1(b4_2_stable_sort_cutoff_decrement_sorted_wrapper,std::execution::sequenced_policy)->Name(BENCHMARK_NAME("b4_2_stable_sort_cutoff_decrement_sorted_seq"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(MAX_INPUT_SIZE, MAX_INPUT_SIZE); \
        BENCHMARK_TEMPLATE1(b4_2_stable_sort_cutoff_decrement_sorted_wrapper,std::execution::parallel_policy)->Name(BENCHMARK_NAME("b4_2_stable_sort_cutoff_decrement_sorted_par"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(1 << 2, MAX_INPUT_SIZE);     \
                            \
                            \
        BENCHMARK_TEMPLATE1(b4_2_stable_sort_cutoff_not_sorted_wrapper,std::execution::sequenced_policy)->Name(BENCHMARK_NAME("b4_2_stable_sort_cutoff_not_sorted_seq"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(MAX_INPUT_SIZE, MAX_INPUT_SIZE); \
        BENCHMARK_TEMPLATE1(b4_2_stable_sort_cutoff_not_sorted_wrapper,std::execution::parallel_policy)->Name(BENCHMARK_NAME("b4_2_stable_sort_cutoff_not_sorted_par"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(1 << 2, MAX_INPUT_SIZE);     \
                            \
                            \
                            \
                            \
        BENCHMARK_TEMPLATE1(b4_3_set_union_cutoff_one_empty,std::execution::sequenced_policy)->Name(BENCHMARK_NAME("b4_3_set_union_cutoff_one_empty_seq"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(MAX_INPUT_SIZE, MAX_INPUT_SIZE); \
        BENCHMARK_TEMPLATE1(b4_3_set_union_cutoff_one_empty,std::execution::parallel_policy)->Name(BENCHMARK_NAME("b4_3_set_union_cutoff_one_empty_par"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(1 << 2, MAX_INPUT_SIZE);     \
                            \
                            \
        BENCHMARK_TEMPLATE1(b4_3_set_union_cutoff_one_wholly_greater,std::execution::sequenced_policy)->Name(BENCHMARK_NAME("b4_3_set_union_cutoff_one_wholly_greater_seq"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(MAX_INPUT_SIZE, MAX_INPUT_SIZE); \
        BENCHMARK_TEMPLATE1(b4_3_set_union_cutoff_one_wholly_greater,std::execution::parallel_policy)->Name(BENCHMARK_NAME("b4_3_set_union_cutoff_one_wholly_greater_par"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(1 << 2, MAX_INPUT_SIZE);     \
                            \
                            \
        BENCHMARK_TEMPLATE1(b4_3_set_union_cutoff_front_overhang,std::execution::sequenced_policy)->Name(BENCHMARK_NAME("b4_3_set_union_cutoff_front_overhang_seq"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(MAX_INPUT_SIZE, MAX_INPUT_SIZE); \
        BENCHMARK_TEMPLATE1(b4_3_set_union_cutoff_front_overhang,std::execution::parallel_policy)->Name(BENCHMARK_NAME("b4_3_set_union_cutoff_front_overhang_par"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(1 << 2, MAX_INPUT_SIZE);     \
                            \
                            \
                            \
                            \
        BENCHMARK_TEMPLATE1(b4_4_set_difference_cutoff_left_empty,std::execution::sequenced_policy)->Name(BENCHMARK_NAME("b4_4_set_difference_cutoff_left_empty_seq"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(MAX_INPUT_SIZE, MAX_INPUT_SIZE); \
        BENCHMARK_TEMPLATE1(b4_4_set_difference_cutoff_left_empty,std::execution::parallel_policy)->Name(BENCHMARK_NAME("b4_4_set_difference_cutoff_left_empty_par"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(1 << 2, MAX_INPUT_SIZE);     \
                            \
                            \
        BENCHMARK_TEMPLATE1(b4_4_set_difference_cutoff_right_empty,std::execution::sequenced_policy)->Name(BENCHMARK_NAME("b4_4_set_difference_cutoff_right_empty_seq"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(MAX_INPUT_SIZE, MAX_INPUT_SIZE); \
        BENCHMARK_TEMPLATE1(b4_4_set_difference_cutoff_right_empty,std::execution::parallel_policy)->Name(BENCHMARK_NAME("b4_4_set_difference_cutoff_right_empty_par"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(1 << 2, MAX_INPUT_SIZE);     \
                            \
                            \
        BENCHMARK_TEMPLATE1(b4_4_set_difference_cutoff_wholly_greater,std::execution::sequenced_policy)->Name(BENCHMARK_NAME("b4_4_set_difference_cutoff_wholly_greater_seq"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(MAX_INPUT_SIZE, MAX_INPUT_SIZE); \
        BENCHMARK_TEMPLATE1(b4_4_set_difference_cutoff_wholly_greater,std::execution::parallel_policy)->Name(BENCHMARK_NAME("b4_4_set_difference_cutoff_wholly_greater_par"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(1 << 2, MAX_INPUT_SIZE);     \
                            \
                            \
        BENCHMARK_TEMPLATE1(b4_4_set_difference_cutoff_intersected,std::execution::sequenced_policy)->Name(BENCHMARK_NAME("b4_4_set_difference_cutoff_intersected_seq"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(MAX_INPUT_SIZE, MAX_INPUT_SIZE); \
        BENCHMARK_TEMPLATE1(b4_4_set_difference_cutoff_intersected,std::execution::parallel_policy)->Name(BENCHMARK_NAME("b4_4_set_difference_cutoff_intersected_par"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(1 << 2, MAX_INPUT_SIZE);     \



#endif //MASTER_BENCHMARKS_B4_GROUP_H
