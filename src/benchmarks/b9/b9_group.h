
#ifndef MASTER_BENCHMARKS_B9_GROUP_H
#define MASTER_BENCHMARKS_B9_GROUP_H

#include <benchmark/benchmark.h>

#include <execution>
#include <vector>

#include "../benchmark_prefix.h"
#include "../benchmark_utils.h"

#include "b9_1_transform_baseline.h"
#include "b9_2_transform_old_iota.h"
#include "b9_3_transform_views_iota.h"
#include "b9_4_transform_views_iota_common.h"
#include "b9_5_transform_custom_iterator.h"
#include "b9_6_transform_boost.h"

//region b9_1_transform_baseline

template<class Policy>
static void b9_1_transform_baseline_wrapper(benchmark::State &state) {
    constexpr auto execution_policy = Policy{};

    const auto &size = state.range(0);
    const auto last_element = size - 1;

    const auto input_data = suite::generate_uniform_dist_vec<int>(size, 0, 10);

    std::vector<int> res(size);

    for (auto _: state) {
        B9::b9_1_transform_baseline(execution_policy, input_data, res);

        state.PauseTiming();
        assert((res[0] == input_data[0] + 10));
        assert((res[last_element] == input_data[last_element] + 10));
        state.ResumeTiming();
    }
}

#define B9_1_TRANSFORM_BASELINE_WRAPPER \
                                        \
        BENCHMARK_TEMPLATE1(b9_1_transform_baseline_wrapper,std::execution::sequenced_policy)->Name(BENCHMARK_NAME("b9_1_transform_baseline_seq"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(1 << 2, 1 << 20); \
        BENCHMARK_TEMPLATE1(b9_1_transform_baseline_wrapper,std::execution::parallel_policy)->Name(BENCHMARK_NAME("b9_1_transform_baseline_par"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(1 << 2, 1 << 20);     \
        BENCHMARK_TEMPLATE1(b9_1_transform_baseline_wrapper,std::execution::parallel_unsequenced_policy)->Name(BENCHMARK_NAME("b9_1_transform_baseline_par_unseq"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(1 << 2, 1 << 20); \
        BENCHMARK_TEMPLATE1(b9_1_transform_baseline_wrapper,std::execution::unsequenced_policy)->Name(BENCHMARK_NAME("b9_1_transform_baseline_unseq"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(1 << 2, 1 << 20);\


//endregion b9_1_transform_baseline

//region b9_2_transform_old_iota

template<class Policy>
static void b9_2_transform_old_iota_wrapper(benchmark::State &state) {
    constexpr auto execution_policy = Policy{};

    const auto &size = state.range(0);
    const auto last_element = size - 1;

    const auto input_data = suite::generate_uniform_dist_vec<int>(size, 0, 10);

    std::vector<int> res(size);

    for (auto _: state) {
        B9::b9_2_transform_old_iota(execution_policy, input_data, res);

        state.PauseTiming();
        assert((res[0] == input_data[0] + 10));
        assert((res[last_element] == input_data[last_element] + 10));
        state.ResumeTiming();
    }
}

#define B9_2_TRANSFORM_OLD_IOTA_WRAPPER \
                                        \
        BENCHMARK_TEMPLATE1(b9_2_transform_old_iota_wrapper,std::execution::sequenced_policy)->Name(BENCHMARK_NAME("b9_2_transform_old_iota_seq"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(1 << 2, 1 << 20); \
        BENCHMARK_TEMPLATE1(b9_2_transform_old_iota_wrapper,std::execution::parallel_policy)->Name(BENCHMARK_NAME("b9_2_transform_old_iota_par"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(1 << 2, 1 << 20);     \
        BENCHMARK_TEMPLATE1(b9_2_transform_old_iota_wrapper,std::execution::parallel_unsequenced_policy)->Name(BENCHMARK_NAME("b9_2_transform_old_iota_par_unseq"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(1 << 2, 1 << 20); \
        BENCHMARK_TEMPLATE1(b9_2_transform_old_iota_wrapper,std::execution::unsequenced_policy)->Name(BENCHMARK_NAME("b9_2_transform_old_iota_unseq"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(1 << 2, 1 << 20);\


//endregion b9_2_transform_old_iota

//region b9_3_transform_views_iota

template<class Policy>
static void b9_3_transform_views_iota_wrapper(benchmark::State &state) {
    constexpr auto execution_policy = Policy{};

    const auto &size = state.range(0);
    const auto last_element = size - 1;

    const auto input_data = suite::generate_uniform_dist_vec<int>(size, 0, 10);

    std::vector<int> res(size);

    for (auto _: state) {
        B9::b9_3_transform_views_iota(execution_policy, input_data, res);

        state.PauseTiming();
        assert((res[0] == input_data[0] + 10));
        assert((res[last_element] == input_data[last_element] + 10));
        state.ResumeTiming();
    }
}

#define B9_3_TRANSFORM_VIEWS_IOTA_WRAPPER \
                                        \
        BENCHMARK_TEMPLATE1(b9_3_transform_views_iota_wrapper,std::execution::sequenced_policy)->Name(BENCHMARK_NAME("b9_3_transform_views_iota_seq"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(1 << 2, 1 << 20); \
        BENCHMARK_TEMPLATE1(b9_3_transform_views_iota_wrapper,std::execution::parallel_policy)->Name(BENCHMARK_NAME("b9_3_transform_views_iota_par"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(1 << 2, 1 << 20);     \
        BENCHMARK_TEMPLATE1(b9_3_transform_views_iota_wrapper,std::execution::parallel_unsequenced_policy)->Name(BENCHMARK_NAME("b9_3_transform_views_iota_par_unseq"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(1 << 2, 1 << 20); \
        BENCHMARK_TEMPLATE1(b9_3_transform_views_iota_wrapper,std::execution::unsequenced_policy)->Name(BENCHMARK_NAME("b9_3_transform_views_iota_unseq"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(1 << 2, 1 << 20);\


//endregion b9_3_transform_views_iota

//region b9_4_transform_views_iota_common

template<class Policy>
static void b9_4_transform_views_iota_common_wrapper(benchmark::State &state) {
    constexpr auto execution_policy = Policy{};

    const auto &size = state.range(0);
    const auto last_element = size - 1;

    const auto input_data = suite::generate_uniform_dist_vec<int>(size, 0, 10);

    std::vector<int> res(size);

    for (auto _: state) {
        B9::b9_4_transform_views_iota_common(execution_policy, input_data, res);

        state.PauseTiming();
        assert((res[0] == input_data[0] + 10));
        assert((res[last_element] == input_data[last_element] + 10));
        state.ResumeTiming();
    }
}

#define B9_4_TRANSFORM_VIEWS_IOTA_COMMON_WRAPPER \
                                        \
        BENCHMARK_TEMPLATE1(b9_4_transform_views_iota_common_wrapper,std::execution::sequenced_policy)->Name(BENCHMARK_NAME("b9_4_transform_views_iota_common_seq"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(1 << 2, 1 << 20); \
        BENCHMARK_TEMPLATE1(b9_4_transform_views_iota_common_wrapper,std::execution::parallel_policy)->Name(BENCHMARK_NAME("b9_4_transform_views_iota_common_par"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(1 << 2, 1 << 20);     \
        BENCHMARK_TEMPLATE1(b9_4_transform_views_iota_common_wrapper,std::execution::parallel_unsequenced_policy)->Name(BENCHMARK_NAME("b9_4_transform_views_iota_common_par_unseq"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(1 << 2, 1 << 20); \
        BENCHMARK_TEMPLATE1(b9_4_transform_views_iota_common_wrapper,std::execution::unsequenced_policy)->Name(BENCHMARK_NAME("b9_4_transform_views_iota_common_unseq"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(1 << 2, 1 << 20);\


//endregion b9_4_transform_views_iota_common

//region b9_5_transform_custom_iterator

template<class Policy>
static void b9_5_transform_custom_iterator_wrapper(benchmark::State &state) {
    constexpr auto execution_policy = Policy{};

    const auto &size = state.range(0);
    const auto last_element = size - 1;

    const auto input_data = suite::generate_uniform_dist_vec<int>(size, 0, 10);

    std::vector<int> res(size);

    for (auto _: state) {
        B9::b9_5_transform_custom_iterator(execution_policy, input_data, res);

        state.PauseTiming();
        assert((res[0] == input_data[0] + 10));
        assert((res[last_element] == input_data[last_element] + 10));
        state.ResumeTiming();
    }
}

#define B9_5_TRANSFORM_CUSTOM_ITERATOR_WRAPPER \
                                        \
        BENCHMARK_TEMPLATE1(b9_5_transform_custom_iterator_wrapper,std::execution::sequenced_policy)->Name(BENCHMARK_NAME("b9_5_transform_custom_iterator_seq"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(1 << 2, 1 << 20); \
        BENCHMARK_TEMPLATE1(b9_5_transform_custom_iterator_wrapper,std::execution::parallel_policy)->Name(BENCHMARK_NAME("b9_5_transform_custom_iterator_par"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(1 << 2, 1 << 20);     \
        BENCHMARK_TEMPLATE1(b9_5_transform_custom_iterator_wrapper,std::execution::parallel_unsequenced_policy)->Name(BENCHMARK_NAME("b9_5_transform_custom_iterator_par_unseq"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(1 << 2, 1 << 20); \
        BENCHMARK_TEMPLATE1(b9_5_transform_custom_iterator_wrapper,std::execution::unsequenced_policy)->Name(BENCHMARK_NAME("b9_5_transform_custom_iterator_unseq"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(1 << 2, 1 << 20);\


//endregion b9_5_transform_custom_iterator

//region b9_6_transform_boost

template<class Policy>
static void b9_6_transform_boost_wrapper(benchmark::State &state) {
    constexpr auto execution_policy = Policy{};

    const auto &size = state.range(0);
    const auto last_element = size - 1;

    const auto input_data = suite::generate_uniform_dist_vec<int>(size, 0, 10);

    std::vector<int> res(size);

    for (auto _: state) {
        B9::b9_6_transform_boost(execution_policy, input_data, res);

        state.PauseTiming();
        assert((res[0] == input_data[0] + 10));
        assert((res[last_element] == input_data[last_element] + 10));
        state.ResumeTiming();
    }
}

#define B9_6_TRANSFORM_BOOST_WRAPPER \
                                        \
        BENCHMARK_TEMPLATE1(b9_6_transform_boost_wrapper,std::execution::sequenced_policy)->Name(BENCHMARK_NAME("b9_6_transform_boost_seq"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(1 << 2, 1 << 20); \
        BENCHMARK_TEMPLATE1(b9_6_transform_boost_wrapper,std::execution::parallel_policy)->Name(BENCHMARK_NAME("b9_6_transform_boost_par"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(1 << 2, 1 << 20);     \
        BENCHMARK_TEMPLATE1(b9_6_transform_boost_wrapper,std::execution::parallel_unsequenced_policy)->Name(BENCHMARK_NAME("b9_6_transform_boost_par_unseq"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(1 << 2, 1 << 20); \
        BENCHMARK_TEMPLATE1(b9_6_transform_boost_wrapper,std::execution::unsequenced_policy)->Name(BENCHMARK_NAME("b9_6_transform_boost_unseq"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(1 << 2, 1 << 20);\


//endregion b9_6_transform_boost


#define B9_GROUP_BENCHMARKS \
                            \
            B9_1_TRANSFORM_BASELINE_WRAPPER \
                            \
                            \
            B9_2_TRANSFORM_OLD_IOTA_WRAPPER \
                            \
                            \
            B9_3_TRANSFORM_VIEWS_IOTA_WRAPPER \
                            \
                            \
            B9_4_TRANSFORM_VIEWS_IOTA_COMMON_WRAPPER \
                            \
                            \
            B9_5_TRANSFORM_CUSTOM_ITERATOR_WRAPPER \
                            \
                            \
            B9_6_TRANSFORM_BOOST_WRAPPER


#endif //MASTER_BENCHMARKS_B9_GROUP_H
