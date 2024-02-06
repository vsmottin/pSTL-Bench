#ifndef PSTL_BENCH_TRANSFORM_EXCLUSIVE_SCAN_GROUP_H
#define PSTL_BENCH_TRANSFORM_EXCLUSIVE_SCAN_GROUP_H

#include "benchmark_prefix.h"

#include <benchmark/benchmark.h>

#include "transform_exclusive_scan_utils.h"

#include "transform_exclusive_scan_std.h"

#ifdef USE_HPX
#include "transform_exclusive_scan_hpx.h"
#endif

//region transform_exclusive_scan
template<class Policy>
static void transform_exclusive_scan_std_wrapper(benchmark::State & state)
{
	benchmark_transform_exclusive_scan::benchmark_transform_exclusive_scan_wrapper<Policy>(
	    state, benchmark_transform_exclusive_scan::transform_exclusive_scan_std);
}

#define TRANSFORM_EXCLUSIVE_SCAN_SEQ_WRAPPER                                                    \
	BENCHMARK_TEMPLATE1(transform_exclusive_scan_std_wrapper, std::execution::sequenced_policy) \
	    ->Name(BENCHMARK_NAME_WITH_BACKEND("SEQ", "std::transform_exclusive_scan"))             \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                                 \
	    ->Range(MIN_INPUT_SIZE, MAX_INPUT_SIZE);

#ifdef USE_PSTL
#define TRANSFORM_EXCLUSIVE_SCAN_STD_WRAPPER                                                               \
	BENCHMARK_TEMPLATE1(transform_exclusive_scan_std_wrapper, std::execution::parallel_unsequenced_policy) \
	    ->Name(BENCHMARK_NAME("std::transform_exclusive_scan"))                                            \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                                            \
	    ->Range(MIN_INPUT_SIZE, MAX_INPUT_SIZE);
#else
#define TRANSFORM_EXCLUSIVE_SCAN_STD_WRAPPER
#endif
//endregion transform_exclusive_scan

//region transform_exclusive_scan_hpx
#ifdef USE_HPX
template<class Policy>
static void transform_exclusive_scan_hpx_wrapper(benchmark::State & state)
{
	benchmark_transform_exclusive_scan::benchmark_transform_exclusive_scan_wrapper<Policy>(
	    state, benchmark_transform_exclusive_scan::transform_exclusive_scan_hpx);
}

#define TRANSFORM_EXCLUSIVE_SCAN_HPX_WRAPPER                                                               \
	BENCHMARK_TEMPLATE1(transform_exclusive_scan_hpx_wrapper, std::execution::parallel_unsequenced_policy) \
	    ->Name(BENCHMARK_NAME("hpx::transform_exclusive_scan"))                                            \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                                            \
	    ->Range(MIN_INPUT_SIZE, MAX_INPUT_SIZE);
#else
#define TRANSFORM_EXCLUSIVE_SCAN_HPX_WRAPPER
#endif

#define TRANSFORM_EXCLUSIVE_SCAN_GROUP   \
	TRANSFORM_EXCLUSIVE_SCAN_SEQ_WRAPPER \
	TRANSFORM_EXCLUSIVE_SCAN_STD_WRAPPER \
	TRANSFORM_EXCLUSIVE_SCAN_HPX_WRAPPER

#endif //PSTL_BENCH_TRANSFORM_EXCLUSIVE_SCAN_GROUP_H
