
#ifndef PSTL_BENCH_B9_GROUP_H
#define PSTL_BENCH_B9_GROUP_H

#include <chrono>
#include <benchmark/benchmark.h>

#include <execution>
#include <vector>

#include <benchmark_prefix.h>
#include <benchmark_utils.h>

#include "b9_1_transform_baseline.h"
#include "b9_2_transform_old_iota.h"
#include "b9_3_transform_views_iota.h"
#include "b9_5_transform_custom_iterator.h"
#include "b9_6_transform_boost.h"

#include "b9_utils.hpp"

//region b9_1_transform_baseline
template<class Policy>
static void b9_1_transform_baseline_wrapper (benchmark::State & state) {
	B9::benchmark_wrapper<Policy>(state, B9::b9_1_transform_baseline);
}

#define B9_1_TRANSFORM_BASELINE_WRAPPER \
                                        \
        BENCHMARK_TEMPLATE1(b9_1_transform_baseline_wrapper,std::execution::sequenced_policy)->Name(BENCHMARK_NAME("b9_1_transform_baseline_seq"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(MAX_INPUT_SIZE, MAX_INPUT_SIZE); \
        BENCHMARK_TEMPLATE1(b9_1_transform_baseline_wrapper,std::execution::parallel_policy)->Name(BENCHMARK_NAME("b9_1_transform_baseline_par"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(1 << 2, MAX_INPUT_SIZE);     \
//endregion b9_1_transform_baseline

//region b9_2_transform_old_iota
template<class Policy>
static void b9_2_transform_old_iota_wrapper (benchmark::State & state) {
	B9::benchmark_wrapper<Policy>(state, B9::b9_2_transform_old_iota);
}

#define B9_2_TRANSFORM_OLD_IOTA_WRAPPER \
                                        \
        BENCHMARK_TEMPLATE1(b9_2_transform_old_iota_wrapper,std::execution::sequenced_policy)->Name(BENCHMARK_NAME("b9_2_transform_old_iota_seq"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(MAX_INPUT_SIZE, MAX_INPUT_SIZE); \
        BENCHMARK_TEMPLATE1(b9_2_transform_old_iota_wrapper,std::execution::parallel_policy)->Name(BENCHMARK_NAME("b9_2_transform_old_iota_par"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(1 << 2, MAX_INPUT_SIZE);     \
//endregion b9_2_transform_old_iota

//region b9_3_transform_views_iota
template<class Policy>
static void b9_3_transform_views_iota_wrapper (benchmark::State & state) {
	B9::benchmark_wrapper<Policy>(state, B9::b9_3_transform_views_iota);
}

#define B9_3_TRANSFORM_VIEWS_IOTA_WRAPPER \
                                        \
        BENCHMARK_TEMPLATE1(b9_3_transform_views_iota_wrapper,std::execution::sequenced_policy)->Name(BENCHMARK_NAME("b9_3_transform_views_iota_seq"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(MAX_INPUT_SIZE, MAX_INPUT_SIZE); \
        BENCHMARK_TEMPLATE1(b9_3_transform_views_iota_wrapper,std::execution::parallel_policy)->Name(BENCHMARK_NAME("b9_3_transform_views_iota_par"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(1 << 2, MAX_INPUT_SIZE);     \
//endregion b9_3_transform_views_iota

//region b9_5_transform_custom_iterator
template<class Policy>
static void b9_5_transform_custom_iterator_wrapper (benchmark::State & state) {
	B9::benchmark_wrapper<Policy>(state, B9::b9_5_transform_custom_iterator);
}

#define B9_5_TRANSFORM_CUSTOM_ITERATOR_WRAPPER \
                                        \
        BENCHMARK_TEMPLATE1(b9_5_transform_custom_iterator_wrapper,std::execution::sequenced_policy)->Name(BENCHMARK_NAME("b9_5_transform_custom_iterator_seq"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(MAX_INPUT_SIZE, MAX_INPUT_SIZE); \
        BENCHMARK_TEMPLATE1(b9_5_transform_custom_iterator_wrapper,std::execution::parallel_policy)->Name(BENCHMARK_NAME("b9_5_transform_custom_iterator_par"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(1 << 2, MAX_INPUT_SIZE);     \
//endregion b9_5_transform_custom_iterator

//region b9_6_transform_boost

#ifndef SKIP_BOOST

template<class Policy>
static void b9_6_transform_boost_wrapper (benchmark::State & state) {
	B9::benchmark_wrapper<Policy>(state, B9::b9_6_transform_boost);
}

#define B9_6_TRANSFORM_BOOST_WRAPPER \
                                        \
        BENCHMARK_TEMPLATE1(b9_6_transform_boost_wrapper,std::execution::sequenced_policy)->Name(BENCHMARK_NAME("b9_6_transform_boost_seq"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(MAX_INPUT_SIZE, MAX_INPUT_SIZE); \
        BENCHMARK_TEMPLATE1(b9_6_transform_boost_wrapper,std::execution::parallel_policy)->Name(BENCHMARK_NAME("b9_6_transform_boost_par"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(1 << 2, MAX_INPUT_SIZE);     \

#else

#define B9_6_TRANSFORM_BOOST_WRAPPER

#endif

//endregion b9_6_transform_boost

#ifdef ONLY_GPU

#define INDEX_BASED_ITERATIONS_GROUP \
                            \
            B9_1_TRANSFORM_BASELINE_WRAPPER

#else

#define INDEX_BASED_ITERATIONS_GROUP \
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
            B9_5_TRANSFORM_CUSTOM_ITERATOR_WRAPPER \
                            \
                            \
            B9_6_TRANSFORM_BOOST_WRAPPER

#endif

#endif //PSTL_BENCH_B9_GROUP_H
