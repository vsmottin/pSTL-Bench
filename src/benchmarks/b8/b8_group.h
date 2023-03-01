
#ifndef MASTER_BENCHMARKS_B8_GROUP_H
#define MASTER_BENCHMARKS_B8_GROUP_H

#include <benchmark/benchmark.h>
#include <vector>
#include <execution>
#include <iostream>

#include "../benchmark_utils.h"
#include "../benchmark_prefix.h"

#include "b8_1_reference_vs_copy.h"
#include "b8_2_reference_vs_copy_large_objects.h"

//region b8_1_reference_vs_copy

template<class Policy>
static void b8_1_reference_capture_simple_var(benchmark::State &state) {
    constexpr auto execution_policy = Policy{};

    const auto &size = state.range(0);

    // vector with values [0,size)
    std::vector<int> input_data(size, 0);

    const auto rand_int = (int) std::abs(10 + std::rand() * 100);

    for (auto _: state) {
        const auto res = B8::b8_1_lambda_reference_capture_simple_var(execution_policy, input_data, rand_int);

        state.PauseTiming();
        assert((res == true));
        state.ResumeTiming();
    }
}

template<class Policy>
static void b8_1_copy_capture_simple_var(benchmark::State &state) {
    constexpr auto execution_policy = Policy{};

    const auto &size = state.range(0);

    // vector with values [0,size)
    std::vector<int> input_data(size, 0);

    const auto rand_int = (int) std::abs(10 + std::rand() * 100);

    for (auto _: state) {
        const auto res = B8::b8_1_lambda_copy_capture_simple_var(execution_policy, input_data, rand_int);

        state.PauseTiming();
        assert((res == true));
        state.ResumeTiming();
    }
}

//endregion b8_1_reference_vs_copy


//region b8_2_reference_vs_copy_large_objects

template<class Policy>
static void b8_2_reference_capture_object_var(benchmark::State &state) {
    constexpr auto execution_policy = Policy{};

    const auto &size = state.range(0);

    // vector with values [0,size)
    std::vector<int> input_data(size, 0);

    const auto rand_int = suite::generate_uniform_dist_vec<int>(1, 10, 100)[0];
    const B8::LargeObject &largeObject = B8::LargeObject{rand_int, rand_int, rand_int};

    for (auto _: state) {
        const auto res = B8::b8_2_lambda_reference_capture_object_var(execution_policy, input_data, largeObject);

        state.PauseTiming();
        assert((res == true));
        state.ResumeTiming();
    }
}

template<class Policy>
static void b8_2_copy_capture_object_var(benchmark::State &state) {
    constexpr auto execution_policy = Policy{};

    const auto &size = state.range(0);

    // vector with values [0,size)
    std::vector<int> input_data(size, 0);

    const auto rand_int = suite::generate_uniform_dist_vec<int>(1, 10, 100)[0];
    const B8::LargeObject &largeObject = B8::LargeObject{rand_int, rand_int, rand_int};

    for (auto _: state) {
        const auto res = B8::b8_2_lambda_copy_capture_object_var(execution_policy, input_data, largeObject);

        state.PauseTiming();
        assert((res == true));
        state.ResumeTiming();
    }
}

//endregion b8_2_reference_vs_copy_large_objects

#define B8_GROUP_BENCHMARKS \
                            \
                            \
        BENCHMARK_TEMPLATE1(b8_1_reference_capture_simple_var,std::execution::sequenced_policy)->Name(BENCHMARK_NAME("b8_1_reference_capture_simple_var_seq"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(1 << 2, 1 << 20); \
        BENCHMARK_TEMPLATE1(b8_1_reference_capture_simple_var,std::execution::parallel_policy)->Name(BENCHMARK_NAME("b8_1_reference_capture_simple_var_par"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(1 << 2, 1 << 20);     \
        BENCHMARK_TEMPLATE1(b8_1_reference_capture_simple_var,std::execution::parallel_unsequenced_policy)->Name(BENCHMARK_NAME("b8_1_reference_capture_simple_var_par_unseq"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(1 << 2, 1 << 20); \
        BENCHMARK_TEMPLATE1(b8_1_reference_capture_simple_var,std::execution::unsequenced_policy)->Name(BENCHMARK_NAME("b8_1_reference_capture_simple_var_unseq"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(1 << 2, 1 << 20);\
                            \
                            \
        BENCHMARK_TEMPLATE1(b8_1_copy_capture_simple_var,std::execution::sequenced_policy)->Name(BENCHMARK_NAME("b8_1_copy_capture_simple_var_seq"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(1 << 2, 1 << 20); \
        BENCHMARK_TEMPLATE1(b8_1_copy_capture_simple_var,std::execution::parallel_policy)->Name(BENCHMARK_NAME("b8_1_copy_capture_simple_var_par"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(1 << 2, 1 << 20);     \
        BENCHMARK_TEMPLATE1(b8_1_copy_capture_simple_var,std::execution::parallel_unsequenced_policy)->Name(BENCHMARK_NAME("b8_1_copy_capture_simple_var_par_unseq"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(1 << 2, 1 << 20); \
        BENCHMARK_TEMPLATE1(b8_1_copy_capture_simple_var,std::execution::unsequenced_policy)->Name(BENCHMARK_NAME("b8_1_copy_capture_simple_var_unseq"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(1 << 2, 1 << 20);\
                            \
                            \
                            \
        BENCHMARK_TEMPLATE1(b8_2_reference_capture_object_var,std::execution::sequenced_policy)->Name(BENCHMARK_NAME("b8_2_reference_capture_object_var_seq"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(1 << 2, 1 << 20); \
        BENCHMARK_TEMPLATE1(b8_2_reference_capture_object_var,std::execution::parallel_policy)->Name(BENCHMARK_NAME("b8_2_reference_capture_object_var_par"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(1 << 2, 1 << 20);     \
        BENCHMARK_TEMPLATE1(b8_2_reference_capture_object_var,std::execution::parallel_unsequenced_policy)->Name(BENCHMARK_NAME("b8_2_reference_capture_object_var_par_unseq"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(1 << 2, 1 << 20); \
        BENCHMARK_TEMPLATE1(b8_2_reference_capture_object_var,std::execution::unsequenced_policy)->Name(BENCHMARK_NAME("b8_2_reference_capture_object_var_unseq"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(1 << 2, 1 << 20);\
                            \
                            \
        BENCHMARK_TEMPLATE1(b8_2_copy_capture_object_var,std::execution::sequenced_policy)->Name(BENCHMARK_NAME("b8_2_copy_capture_object_var_seq"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(1 << 2, 1 << 20); \
        BENCHMARK_TEMPLATE1(b8_2_copy_capture_object_var,std::execution::parallel_policy)->Name(BENCHMARK_NAME("b8_2_copy_capture_object_var_par"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(1 << 2, 1 << 20);     \
        BENCHMARK_TEMPLATE1(b8_2_copy_capture_object_var,std::execution::parallel_unsequenced_policy)->Name(BENCHMARK_NAME("b8_2_copy_capture_object_var_par_unseq"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(1 << 2, 1 << 20); \
        BENCHMARK_TEMPLATE1(b8_2_copy_capture_object_var,std::execution::unsequenced_policy)->Name(BENCHMARK_NAME("b8_2_copy_capture_object_var_unseq"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(1 << 2, 1 << 20);\



#endif //MASTER_BENCHMARKS_B8_GROUP_H
