
#ifndef MASTER_BENCHMARKS_B5_GROUP_H
#define MASTER_BENCHMARKS_B5_GROUP_H

#include <benchmark/benchmark.h>
#include <execution>
#include <vector>
#include <cassert>
#include <iostream>
#include <list>
#include <deque>

#include "../benchmark_prefix.h"
#include "../benchmark_utils.h"

#include "b5_1_find.h"
#include "b5_2_partition.h"

//region b5_1_find

template<class Policy, class Container>
static void b5_1_find_first_entry(benchmark::State &state) {
    constexpr auto execution_policy = Policy{};

    const auto &size = state.range(0);

    // vector with values [0,size)
    const Container vec1 = suite::generate_increment<Container>(size, 1);

    for (auto _: state) {
        auto find_location = b5_1_find(execution_policy, vec1, 0);

        state.PauseTiming();
        // make sure the val is really found
        assert(find_location != vec1.end());
        state.ResumeTiming();
    }
}

template<class Policy, class Container>
static void b5_1_find_last_entry(benchmark::State &state) {
    constexpr auto execution_policy = Policy{};

    const auto &size = state.range(0);

    // vector with values [0,size)
    const auto vec1 = suite::generate_increment<Container>(size, 1);

    for (auto _: state) {
        auto find_location = b5_1_find(execution_policy, vec1, size - 1);

        state.PauseTiming();
        // make sure the val is really found
        assert(find_location != vec1.end());
        state.ResumeTiming();
    }
}

template<class Policy, class Container>
static void b5_1_find_non_existing_entry(benchmark::State &state) {
    constexpr auto execution_policy = Policy{};

    const auto &size = state.range(0);

    // vector with values [0,size)
    const auto vec1 = suite::generate_increment<Container>(size, 1);

    for (auto _: state) {
        auto find_location = b5_1_find(execution_policy, vec1, -10);

        state.PauseTiming();
        // make sure the val is really found
        assert(find_location == vec1.end());
        state.ResumeTiming();
    }
}

#define B5_1_FIND_WRAPPER(datatype) \
                                    \
        BENCHMARK_TEMPLATE2(b5_1_find_first_entry,std::execution::sequenced_policy, datatype)->Name(BENCHMARK_NAME("b5_1_find_" xstr(datatype) "_first_entry_seq"))->RangeMultiplier(2)->Range(1 << 2, 1 << 20); \
        BENCHMARK_TEMPLATE2(b5_1_find_first_entry,std::execution::parallel_policy, datatype)->Name(BENCHMARK_NAME("b5_1_find_" xstr(datatype) "_first_entry_par"))->RangeMultiplier(2)->Range(1 << 2, 1 << 20);     \
        BENCHMARK_TEMPLATE2(b5_1_find_first_entry,std::execution::parallel_unsequenced_policy, datatype)->Name(BENCHMARK_NAME("b5_1_find_" xstr(datatype) "_first_entry_par_unseq"))->RangeMultiplier(2)->Range(1 << 2, 1 << 20); \
        BENCHMARK_TEMPLATE2(b5_1_find_first_entry,std::execution::unsequenced_policy, datatype)->Name(BENCHMARK_NAME("b5_1_find_" xstr(datatype) "_first_entry_unseq"))->RangeMultiplier(2)->Range(1 << 2, 1 << 20);\
                            \
                            \
        BENCHMARK_TEMPLATE2(b5_1_find_last_entry,std::execution::sequenced_policy,datatype)->Name(BENCHMARK_NAME("b5_1_find_" xstr(datatype) "_last_entry_seq"))->RangeMultiplier(2)->Range(1 << 2, 1 << 20); \
        BENCHMARK_TEMPLATE2(b5_1_find_last_entry,std::execution::parallel_policy,datatype)->Name(BENCHMARK_NAME("b5_1_find_" xstr(datatype) "_last_entry_par"))->RangeMultiplier(2)->Range(1 << 2, 1 << 20);     \
        BENCHMARK_TEMPLATE2(b5_1_find_last_entry,std::execution::parallel_unsequenced_policy,datatype)->Name(BENCHMARK_NAME("b5_1_find_" xstr(datatype) "_last_entry_par_unseq"))->RangeMultiplier(2)->Range(1 << 2, 1 << 20); \
        BENCHMARK_TEMPLATE2(b5_1_find_last_entry,std::execution::unsequenced_policy,datatype)->Name(BENCHMARK_NAME("b5_1_find_" xstr(datatype) "_last_entry_unseq"))->RangeMultiplier(2)->Range(1 << 2, 1 << 20);\
                            \
                            \
        BENCHMARK_TEMPLATE2(b5_1_find_non_existing_entry,std::execution::sequenced_policy,datatype)->Name(BENCHMARK_NAME("b5_1_find_" xstr(datatype) "_non_existing_entry_seq"))->RangeMultiplier(2)->Range(1 << 2, 1 << 20); \
        BENCHMARK_TEMPLATE2(b5_1_find_non_existing_entry,std::execution::parallel_policy,datatype)->Name(BENCHMARK_NAME("b5_1_find_" xstr(datatype) "_non_existing_entry_par"))->RangeMultiplier(2)->Range(1 << 2, 1 << 20);     \
        BENCHMARK_TEMPLATE2(b5_1_find_non_existing_entry,std::execution::parallel_unsequenced_policy,datatype)->Name(BENCHMARK_NAME("b5_1_find_" xstr(datatype) "_non_existing_entry_par_unseq"))->RangeMultiplier(2)->Range(1 << 2, 1 << 20); \
        BENCHMARK_TEMPLATE2(b5_1_find_non_existing_entry,std::execution::unsequenced_policy,datatype)->Name(BENCHMARK_NAME("b5_1_find_" xstr(datatype) "_non_existing_entry_unseq"))->RangeMultiplier(2)->Range(1 << 2, 1 << 20); \

//endregion b5_1_find

//region b5_2_partition

template<class Policy>
static void b5_2_partition_wrapper(benchmark::State &state) {
    constexpr auto execution_policy = Policy{};

    const auto &size = state.range(0);

    // vector with values [0,size)
    auto vec1 = suite::generate_increment<suite::int_vec>(size, 1);

    for (auto _: state) {
        auto find_location = b5_2_partition(execution_policy, vec1);

        state.PauseTiming();
        // simple check so the val will not be optimized aways
        assert(std::distance(find_location, vec1.cend()) >= 0);
        state.ResumeTiming();
    }
}

//endregion b5_2_partition


// Register the function as a benchmark
#define B5_GROUP_BENCHMARKS \
                            \
        /*B5_1_FIND_WRAPPER(std::vector<int>) \
        B5_1_FIND_WRAPPER(std::deque<int>)  \
                            */\
                            \
        BENCHMARK_TEMPLATE1(b5_2_partition_wrapper,std::execution::sequenced_policy)->Name(BENCHMARK_NAME("b5_2_partition_seq"))->RangeMultiplier(2)->Range(1 << 2, 1 << 20); \
        BENCHMARK_TEMPLATE1(b5_2_partition_wrapper,std::execution::parallel_policy)->Name(BENCHMARK_NAME("b5_2_partition_par"))->RangeMultiplier(2)->Range(1 << 2, 1 << 20);     \
        BENCHMARK_TEMPLATE1(b5_2_partition_wrapper,std::execution::parallel_unsequenced_policy)->Name(BENCHMARK_NAME("b5_2_partition_par_unseq"))->RangeMultiplier(2)->Range(1 << 2, 1 << 20); \
        BENCHMARK_TEMPLATE1(b5_2_partition_wrapper,std::execution::unsequenced_policy)->Name(BENCHMARK_NAME("b5_2_partition_unseq"))->RangeMultiplier(2)->Range(1 << 2, 1 << 20);          \



#endif //MASTER_BENCHMARKS_B5_GROUP_H
