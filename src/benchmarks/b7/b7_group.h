
#ifndef MASTER_BENCHMARKS_B7_GROUP_H
#define MASTER_BENCHMARKS_B7_GROUP_H

#include <benchmark/benchmark.h>
#include <vector>
#include <execution>
#include <cassert>

#include "../benchmark_prefix.h"
#include "../benchmark_utils.h"

#include "b7_copy_vs_for_each.h"

//region b7_copy_vs_for_each

template<class Policy>
static void b7_1_copy(benchmark::State &state) {
    constexpr auto execution_policy = Policy{};

    const auto &size = state.range(0);

    // vector with values [0,size)
    const auto vec1 = suite::generate_increment<suite::int_vec>(size, 1);
    std::vector res(size, -1);


    for (auto _: state) {
        B7::b7_1_copy(execution_policy, vec1, res);

        state.PauseTiming();
        assert(std::equal(vec1.begin(), vec1.end(), res.begin()));
        state.ResumeTiming();
    }
}

template<class Policy>
static void b7_custom_copy_with_foreach(benchmark::State &state) {
    constexpr auto execution_policy = Policy{};

    const auto &size = state.range(0);

    // vector with values [0,size)
    const auto vec1 = suite::generate_increment<suite::int_vec>(size, 1);
    std::vector res(size, -1);


    for (auto _: state) {
        B7::b7_custom_copy_with_foreach(execution_policy, vec1, res);

        state.PauseTiming();
        assert(std::equal(vec1.begin(), vec1.end(), res.begin()));
        state.ResumeTiming();
    }
}

//endregion b7_copy_vs_for_each



#define B7_GROUP_BENCHMARKS \
                            \
        BENCHMARK_TEMPLATE1(b7_1_copy,std::execution::sequenced_policy)->Name(BENCHMARK_NAME("b7_1_copy_seq"))->RangeMultiplier(2)->Range(1 << 2, 1 << 20); \
        BENCHMARK_TEMPLATE1(b7_1_copy,std::execution::parallel_policy)->Name(BENCHMARK_NAME("b7_1_copy_par"))->RangeMultiplier(2)->Range(1 << 2, 1 << 20);     \
        BENCHMARK_TEMPLATE1(b7_1_copy,std::execution::parallel_unsequenced_policy)->Name(BENCHMARK_NAME("b7_1_copy_par_unseq"))->RangeMultiplier(2)->Range(1 << 2, 1 << 20); \
        BENCHMARK_TEMPLATE1(b7_1_copy,std::execution::unsequenced_policy)->Name(BENCHMARK_NAME("b7_1_copy_unseq"))->RangeMultiplier(2)->Range(1 << 2, 1 << 20);\
                            \
                            \
        BENCHMARK_TEMPLATE1(b7_custom_copy_with_foreach,std::execution::sequenced_policy)->Name(BENCHMARK_NAME("b7_custom_copy_with_foreach_seq"))->RangeMultiplier(2)->Range(1 << 2, 1 << 20); \
        BENCHMARK_TEMPLATE1(b7_custom_copy_with_foreach,std::execution::parallel_policy)->Name(BENCHMARK_NAME("b7_custom_copy_with_foreach_par"))->RangeMultiplier(2)->Range(1 << 2, 1 << 20);     \
        BENCHMARK_TEMPLATE1(b7_custom_copy_with_foreach,std::execution::parallel_unsequenced_policy)->Name(BENCHMARK_NAME("b7_custom_copy_with_foreach_par_unseq"))->RangeMultiplier(2)->Range(1 << 2, 1 << 20); \
        BENCHMARK_TEMPLATE1(b7_custom_copy_with_foreach,std::execution::unsequenced_policy)->Name(BENCHMARK_NAME("b7_custom_copy_with_foreach_unseq"))->RangeMultiplier(2)->Range(1 << 2, 1 << 20);          \



#endif //MASTER_BENCHMARKS_B7_GROUP_H
