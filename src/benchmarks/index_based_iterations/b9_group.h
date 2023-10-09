
#ifndef PSTL_BENCH_B9_GROUP_H
#define PSTL_BENCH_B9_GROUP_H

#include <benchmark/benchmark.h>
#include <chrono>

#include <execution>
#include <vector>

#include <benchmark_prefix.h>
#include <benchmark_utils.h>

#include <parallel/algorithm>

#include "b9_1_transform_baseline.h"
#include "b9_2_transform_old_iota.h"
#include "b9_3_transform_views_iota.h"
#include "b9_5_transform_custom_iterator.h"

#ifdef USE_BOOST
#include "b9_6_transform_boost.h"
#endif

#ifdef USE_OMP
#include "b9_7_transform_omp.h"
#endif

#ifdef USE_GNU_PSTL
#include "b9_8_transform_gnu.h"
#endif

#include "b9_utils.h"

//region b9_1_transform_baseline
template<class Policy>
static void b9_1_transform_baseline_wrapper(benchmark::State & state)
{
	B9::benchmark_wrapper<Policy>(state, B9::b9_1_transform_baseline);
}

#define B9_1_TRANSFORM_BASELINE_WRAPPER                                                    \
	BENCHMARK_TEMPLATE1(b9_1_transform_baseline_wrapper, std::execution::sequenced_policy) \
	    ->Name(BENCHMARK_NAME("b9_1_transform_baseline_seq"))                              \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                            \
	    ->Range(MAX_INPUT_SIZE, MAX_INPUT_SIZE);                                           \
	BENCHMARK_TEMPLATE1(b9_1_transform_baseline_wrapper, std::execution::parallel_policy)  \
	    ->Name(BENCHMARK_NAME("b9_1_transform_baseline_par"))                              \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                            \
	    ->Range(1 << 2, MAX_INPUT_SIZE);
//endregion b9_1_transform_baseline

//region b9_1_transform_baseline
template<class Policy>
static void b9_1_gnu_transform_wrapper(benchmark::State & state)
{
	const auto gnu_transform = [](const auto & container, auto & result) {
		__gnu_parallel::transform(container.begin(), container.end(), result.begin(), B9::lambda);
	};
	B9::benchmark_wrapper<Policy>(state, B9::b9_1_transform_baseline);
}

#define B9_1_GNU_TRANSFORM_WRAPPER                                                    \
	BENCHMARK_TEMPLATE1(b9_1_gnu_transform_wrapper, std::execution::sequenced_policy) \
	    ->Name(BENCHMARK_NAME("b9_1_gnu_transform_seq"))                              \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                       \
	    ->Range(MAX_INPUT_SIZE, MAX_INPUT_SIZE);                                      \
	BENCHMARK_TEMPLATE1(b9_1_gnu_transform_wrapper, std::execution::parallel_policy)  \
	    ->Name(BENCHMARK_NAME("b9_1_gnu_transform_par"))                              \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                       \
	    ->Range(1 << 2, MAX_INPUT_SIZE);
//endregion b9_1_transform_baseline

//region b9_2_transform_old_iota
template<class Policy>
static void b9_2_transform_old_iota_wrapper(benchmark::State & state)
{
	B9::benchmark_wrapper<Policy>(state, B9::b9_2_transform_old_iota);
}

#define B9_2_TRANSFORM_OLD_IOTA_WRAPPER                                                    \
	BENCHMARK_TEMPLATE1(b9_2_transform_old_iota_wrapper, std::execution::sequenced_policy) \
	    ->Name(BENCHMARK_NAME("b9_2_transform_old_iota_seq"))                              \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                            \
	    ->Range(MAX_INPUT_SIZE, MAX_INPUT_SIZE);                                           \
	BENCHMARK_TEMPLATE1(b9_2_transform_old_iota_wrapper, std::execution::parallel_policy)  \
	    ->Name(BENCHMARK_NAME("b9_2_transform_old_iota_par"))                              \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                            \
	    ->Range(1 << 2, MAX_INPUT_SIZE);
//endregion b9_2_transform_old_iota

//region b9_3_transform_views_iota
template<class Policy>
static void b9_3_transform_views_iota_wrapper(benchmark::State & state)
{
	B9::benchmark_wrapper<Policy>(state, B9::b9_3_transform_views_iota);
}

#define B9_3_TRANSFORM_VIEWS_IOTA_WRAPPER                                                    \
	BENCHMARK_TEMPLATE1(b9_3_transform_views_iota_wrapper, std::execution::sequenced_policy) \
	    ->Name(BENCHMARK_NAME("b9_3_transform_views_iota_seq"))                              \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                              \
	    ->Range(MAX_INPUT_SIZE, MAX_INPUT_SIZE);                                             \
	BENCHMARK_TEMPLATE1(b9_3_transform_views_iota_wrapper, std::execution::parallel_policy)  \
	    ->Name(BENCHMARK_NAME("b9_3_transform_views_iota_par"))                              \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                              \
	    ->Range(1 << 2, MAX_INPUT_SIZE);
//endregion b9_3_transform_views_iota

//region b9_5_transform_custom_iterator
template<class Policy>
static void b9_5_transform_custom_iterator_wrapper(benchmark::State & state)
{
	B9::benchmark_wrapper<Policy>(state, B9::b9_5_transform_custom_iterator);
}

#define B9_5_TRANSFORM_CUSTOM_ITERATOR_WRAPPER                                                    \
	BENCHMARK_TEMPLATE1(b9_5_transform_custom_iterator_wrapper, std::execution::sequenced_policy) \
	    ->Name(BENCHMARK_NAME("b9_5_transform_custom_iterator_seq"))                              \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                                   \
	    ->Range(MAX_INPUT_SIZE, MAX_INPUT_SIZE);                                                  \
	BENCHMARK_TEMPLATE1(b9_5_transform_custom_iterator_wrapper, std::execution::parallel_policy)  \
	    ->Name(BENCHMARK_NAME("b9_5_transform_custom_iterator_par"))                              \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                                   \
	    ->Range(1 << 2, MAX_INPUT_SIZE);
//endregion b9_5_transform_custom_iterator

//region b9_6_transform_boost
#ifdef USE_BOOST
template<class Policy>
static void b9_6_transform_boost_wrapper(benchmark::State & state)
{
	B9::benchmark_wrapper<Policy>(state, B9::b9_6_transform_boost);
}

#define B9_6_TRANSFORM_BOOST_WRAPPER                                                    \
	BENCHMARK_TEMPLATE1(b9_6_transform_boost_wrapper, std::execution::sequenced_policy) \
	    ->Name(BENCHMARK_NAME("b9_6_transform_boost_seq"))                              \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                         \
	    ->Range(MAX_INPUT_SIZE, MAX_INPUT_SIZE);                                        \
	BENCHMARK_TEMPLATE1(b9_6_transform_boost_wrapper, std::execution::parallel_policy)  \
	    ->Name(BENCHMARK_NAME("b9_6_transform_boost_par"))                              \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                         \
	    ->Range(1 << 2, MAX_INPUT_SIZE);
#else
#define B9_6_TRANSFORM_BOOST_WRAPPER
#endif
//endregion b9_6_transform_boost

//region b9_7_transform_omp
#ifdef USE_OMP
template<class Policy>
static void b9_7_transform_omp_wrapper(benchmark::State & state)
{
	B9::benchmark_wrapper<Policy>(state, B9::b9_7_transform_omp);
}

#define B9_7_TRANSFORM_OMP_WRAPPER                                                    \
	BENCHMARK_TEMPLATE1(b9_7_transform_omp_wrapper, std::execution::sequenced_policy) \
	    ->Name(BENCHMARK_NAME("b9_7_transform_omp_seq"))                              \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                       \
	    ->Range(MAX_INPUT_SIZE, MAX_INPUT_SIZE);                                      \
	BENCHMARK_TEMPLATE1(b9_7_transform_omp_wrapper, std::execution::parallel_policy)  \
	    ->Name(BENCHMARK_NAME("b9_7_transform_omp_par"))                              \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                       \
	    ->Range(1 << 2, MAX_INPUT_SIZE);
#else
#define B9_7_TRANSFORM_OMP_WRAPPER
#endif

//endregion b9_7_transform_omp


//region b9_8_transform_gnu
#ifdef USE_GNU_PSTL
template<class Policy>
static void b9_8_transform_gnu_wrapper(benchmark::State & state)
{
	B9::benchmark_wrapper<Policy>(state, B9::b9_8_transform_gnu);
}

#define B9_8_TRANSFORM_GNU_WRAPPER                                                    \
	BENCHMARK_TEMPLATE1(b9_8_transform_gnu_wrapper, std::execution::sequenced_policy) \
	    ->Name(BENCHMARK_NAME("b9_8_transform_gnu_seq"))                              \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                       \
	    ->Range(MAX_INPUT_SIZE, MAX_INPUT_SIZE);                                      \
	BENCHMARK_TEMPLATE1(b9_8_transform_gnu_wrapper, std::execution::parallel_policy)  \
	    ->Name(BENCHMARK_NAME("b9_8_transform_gnu_par"))                              \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                       \
	    ->Range(1 << 2, MAX_INPUT_SIZE);
#else
#define B9_8_TRANSFORM_GNU_WRAPPER
#endif
//endregion b9_8_transform_gnu

#ifdef ONLY_GPU

#define INDEX_BASED_ITERATIONS_GROUP B9_1_TRANSFORM_BASELINE_WRAPPER

#else

#define INDEX_BASED_ITERATIONS_GROUP       \
	B9_1_TRANSFORM_BASELINE_WRAPPER        \
	B9_2_TRANSFORM_OLD_IOTA_WRAPPER        \
	B9_3_TRANSFORM_VIEWS_IOTA_WRAPPER      \
	B9_5_TRANSFORM_CUSTOM_ITERATOR_WRAPPER \
	B9_6_TRANSFORM_BOOST_WRAPPER           \
	B9_7_TRANSFORM_OMP_WRAPPER             \
	B9_8_TRANSFORM_GNU_WRAPPER
#endif

#endif //PSTL_BENCH_B9_GROUP_H
