
#ifndef MASTER_BENCHMARKS_B5_GROUP_H
#define MASTER_BENCHMARKS_B5_GROUP_H

#include <chrono>
#include <benchmark/benchmark.h>
#include <execution>
#include <vector>
#include <cassert>
#include <iostream>
#include <list>
#include <deque>

#include <benchmark_prefix.h>
#include <benchmark_utils.h>

#include "b5_1_find.h"
#include "b5_2_partition.h"
#include "b5_3_unique_copy.h"
#include "b5_4_minmax_element.h"

//region b5_1_find

template<class Policy>
static void b5_1_find_first_entry(benchmark::State &state) {
    constexpr auto execution_policy = Policy{};

    const auto &size = state.range(0);

    // vector with values [0,size)
    const auto vec1 = suite::generate_increment<Policy>(execution_policy, size, 1);


    for (auto _: state) {
        WRAP_TIMING(auto find_location = B5::b5_1_find(execution_policy, vec1, 0);)

        // make sure the val is really found
        assert(find_location != vec1.end());
    }

    // https://ccfd.github.io/courses/hpc_lab01.html
    const int64_t actual_size_in_bytes = sizeof(int) *
                                         (int64_t(vec1.size()));

    state.SetBytesProcessed(int64_t(state.iterations()) * actual_size_in_bytes);
}

template<class Policy>
static void b5_1_find_last_entry(benchmark::State &state) {
    constexpr auto execution_policy = Policy{};

    const auto &size = state.range(0);

    // vector with values [0,size)
    const auto vec1 = suite::generate_increment<Policy>(execution_policy, size, 1);

    for (auto _: state) {
        WRAP_TIMING(auto find_location = B5::b5_1_find(execution_policy, vec1, size - 1);)

        // make sure the val is really found
        assert(find_location != vec1.end());
    }

    // https://ccfd.github.io/courses/hpc_lab01.html
    const int64_t actual_size_in_bytes = sizeof(int) *
                                         (int64_t(vec1.size()));

    state.SetBytesProcessed(int64_t(state.iterations()) * actual_size_in_bytes);
}

template<class Policy>
static void b5_1_find_non_existing_entry(benchmark::State &state) {
    constexpr auto execution_policy = Policy{};

    const auto &size = state.range(0);

    // vector with values [0,size)
    const auto vec1 = suite::generate_increment<Policy>(execution_policy, size, 1);

    for (auto _: state) {
        WRAP_TIMING(auto find_location = B5::b5_1_find(execution_policy, vec1, -10);)

        // make sure the val is really found
        assert(find_location == vec1.end());
    }

    // https://ccfd.github.io/courses/hpc_lab01.html
    const int64_t actual_size_in_bytes = sizeof(int) *
                                         (int64_t(vec1.size()));

    state.SetBytesProcessed(int64_t(state.iterations()) * actual_size_in_bytes);
}

#define B5_1_FIND_WRAPPER \
                                    \
        BENCHMARK_TEMPLATE1(b5_1_find_first_entry,std::execution::sequenced_policy)->Name(BENCHMARK_NAME("b5_1_find_std::vector<int>_first_entry_seq"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(MAX_INPUT_SIZE, MAX_INPUT_SIZE); \
        BENCHMARK_TEMPLATE1(b5_1_find_first_entry,std::execution::parallel_policy)->Name(BENCHMARK_NAME("b5_1_find_std::vector<int>_first_entry_par"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(1 << 2, MAX_INPUT_SIZE);     \
                            \
                            \
        BENCHMARK_TEMPLATE1(b5_1_find_last_entry,std::execution::sequenced_policy)->Name(BENCHMARK_NAME("b5_1_find_std::vector<int>_last_entry_seq"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(MAX_INPUT_SIZE, MAX_INPUT_SIZE); \
        BENCHMARK_TEMPLATE1(b5_1_find_last_entry,std::execution::parallel_policy)->Name(BENCHMARK_NAME("b5_1_find_std::vector<int>_last_entry_par"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(1 << 2, MAX_INPUT_SIZE);     \
                            \
                            \
        BENCHMARK_TEMPLATE1(b5_1_find_non_existing_entry,std::execution::sequenced_policy)->Name(BENCHMARK_NAME("b5_1_find_std::vector<int>_non_existing_entry_seq"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(MAX_INPUT_SIZE, MAX_INPUT_SIZE); \
        BENCHMARK_TEMPLATE1(b5_1_find_non_existing_entry,std::execution::parallel_policy)->Name(BENCHMARK_NAME("b5_1_find_std::vector<int>_non_existing_entry_par"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(1 << 2, MAX_INPUT_SIZE);     \

//endregion b5_1_find

//region b5_2_partition

template<class Policy>
static void b5_2_partition_wrapper(benchmark::State &state) {
    constexpr auto execution_policy = Policy{};

    const auto &size = state.range(0);

    // vector with values [0,size)
    auto vec1 = suite::generate_increment<Policy>(execution_policy, size, 1);

    for (auto _: state) {
        WRAP_TIMING(auto find_location = B5::b5_2_partition(execution_policy, vec1);)

        // simple check so the val will not be optimized aways
        assert(*find_location >= 0);
    }

    // https://ccfd.github.io/courses/hpc_lab01.html
    const int64_t actual_size_in_bytes = sizeof(int) *
                                         (int64_t(vec1.size()));

    state.SetBytesProcessed(int64_t(state.iterations()) * actual_size_in_bytes);
}

//endregion b5_2_partition

//region b5_3_unique_copy

template<class Policy>
static void b5_3_unique_copy_default_wrapper(benchmark::State &state) {
    constexpr auto execution_policy = Policy{};

    const auto &size = state.range(0);

    // vector with value 1 of length size
    auto vec1 = suite::get_vec<Policy>(size);
    suite::fill_init<Policy>(vec1, 1);

    auto result = suite::get_vec<Policy>(1);
    suite::fill_init<Policy>(result, 0);

    for (auto _: state) {
        WRAP_TIMING(B5::b5_3_unique_copy_default(execution_policy, vec1, result);)

        // simple check so the val will not be optimized aways
        assert(result.size() == 1 && result[0] == 1);
    }

    // https://ccfd.github.io/courses/hpc_lab01.html
    const int64_t actual_size_in_bytes = sizeof(int) *
                                         (int64_t(vec1.size()) + int64_t(result.size()));

    state.SetBytesProcessed(int64_t(state.iterations()) * actual_size_in_bytes);
}

//endregion b5_3_unique_copy

//region b5_4_minmax_element

template<class Policy>
static void b5_4_minmax_element_all_equal(benchmark::State &state) {
    constexpr auto execution_policy = Policy{};

    const auto &size = state.range(0);

    // vector with value 1
    auto vec1 = suite::generate_increment<Policy>(execution_policy, size, 1, 0);

    for (auto _: state) {
        WRAP_TIMING(const auto res = B5::b5_4_minmax_element(execution_policy, vec1);)

        // min = max = 1 because all elements are 1
        assert(*(res.first) == 1 && *(res.second) == 1);
    }

    // https://ccfd.github.io/courses/hpc_lab01.html
    const int64_t actual_size_in_bytes = sizeof(int) *
                                         (int64_t(vec1.size()));

    state.SetBytesProcessed(int64_t(state.iterations()) * actual_size_in_bytes);
}

template<class Policy>
static void b5_4_minmax_element_increasing(benchmark::State &state) {
    constexpr auto execution_policy = Policy{};

    const auto &size = state.range(0);

    // vector with value 1
    auto vec1 = suite::generate_increment(execution_policy, size, 1);

    for (auto _: state) {
        WRAP_TIMING(const auto res = B5::b5_4_minmax_element(execution_policy, vec1);)

        // min = max = 1 because all elements are 1
        assert(*(res.first) == 0 && *(res.second) == size - 1);
    }

    // https://ccfd.github.io/courses/hpc_lab01.html
    const int64_t actual_size_in_bytes = sizeof(int) *
                                         (int64_t(vec1.size()));

    state.SetBytesProcessed(int64_t(state.iterations()) * actual_size_in_bytes);
}


//endregion b5_4_minmax_element

#ifdef ONLY_GPU

#define SPECIALIZED_TECHNIQUES_GROUP

#else

// Register the function as a benchmark
#define SPECIALIZED_TECHNIQUES_GROUP \
                            \
        B5_1_FIND_WRAPPER   \
                            \
                            \
        BENCHMARK_TEMPLATE1(b5_2_partition_wrapper,std::execution::sequenced_policy)->Name(BENCHMARK_NAME("b5_2_partition_seq"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(MAX_INPUT_SIZE, MAX_INPUT_SIZE); \
        BENCHMARK_TEMPLATE1(b5_2_partition_wrapper,std::execution::parallel_policy)->Name(BENCHMARK_NAME("b5_2_partition_par"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(1 << 2, MAX_INPUT_SIZE);     \
                            \
                            \
        BENCHMARK_TEMPLATE1(b5_3_unique_copy_default_wrapper,std::execution::sequenced_policy)->Name(BENCHMARK_NAME("b5_3_unique_copy_default_seq"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(MAX_INPUT_SIZE, MAX_INPUT_SIZE); \
        BENCHMARK_TEMPLATE1(b5_3_unique_copy_default_wrapper,std::execution::parallel_policy)->Name(BENCHMARK_NAME("b5_3_unique_copy_default_par"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(1 << 2, MAX_INPUT_SIZE);     \
                            \
                            \
        BENCHMARK_TEMPLATE1(b5_4_minmax_element_all_equal,std::execution::sequenced_policy)->Name(BENCHMARK_NAME("b5_4_minmax_element_all_equal_seq"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(MAX_INPUT_SIZE, MAX_INPUT_SIZE); \
        BENCHMARK_TEMPLATE1(b5_4_minmax_element_all_equal,std::execution::parallel_policy)->Name(BENCHMARK_NAME("b5_4_minmax_element_all_equal_par"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(1 << 2, MAX_INPUT_SIZE);     \
                            \
                            \
        BENCHMARK_TEMPLATE1(b5_4_minmax_element_increasing,std::execution::sequenced_policy)->Name(BENCHMARK_NAME("b5_4_minmax_element_increasing_seq"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(MAX_INPUT_SIZE, MAX_INPUT_SIZE); \
        BENCHMARK_TEMPLATE1(b5_4_minmax_element_increasing,std::execution::parallel_policy)->Name(BENCHMARK_NAME("b5_4_minmax_element_increasing_par"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(1 << 2, MAX_INPUT_SIZE);     \


#endif

#endif //MASTER_BENCHMARKS_B5_GROUP_H
