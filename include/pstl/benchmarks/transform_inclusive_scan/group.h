#ifndef PSTL_BENCH_TRANSFORM_INCLUSIVE_SCAN_GROUP_H
#define PSTL_BENCH_TRANSFORM_INCLUSIVE_SCAN_GROUP_H

#include "benchmark_prefix.h"

#include <benchmark/benchmark.h>

#include "transform_inclusive_scan_utils.h"

#include "transform_inclusive_scan_std.h"

#ifdef USE_HPX
#include "transform_inclusive_scan_hpx.h"
#endif

//region transform_inclusive_scan
template<class Policy>
static void transform_inclusive_scan_std_wrapper(benchmark::State & state)
{
	benchmark_transform_inclusive_scan::benchmark_transform_inclusive_scan_wrapper<Policy>(
	    state, benchmark_transform_inclusive_scan::transform_inclusive_scan_std);
}

#define TRANSFORM_INCLUSIVE_SCAN_SEQ_WRAPPER                                                    \
	BENCHMARK_TEMPLATE1(transform_inclusive_scan_std_wrapper, std::execution::sequenced_policy) \
	    ->Name(BENCHMARK_NAME_WITH_BACKEND("SEQ", "std::transform_inclusive_scan"))             \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                                 \
	    ->Range(MIN_INPUT_SIZE, MAX_INPUT_SIZE)                                                 \
	    ->UseManualTime();

#ifdef USE_PSTL
#define TRANSFORM_INCLUSIVE_SCAN_STD_WRAPPER                                                               \
	BENCHMARK_TEMPLATE1(transform_inclusive_scan_std_wrapper, std::execution::parallel_unsequenced_policy) \
	    ->Name(BENCHMARK_NAME("std::transform_inclusive_scan"))                                            \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                                            \
	    ->Range(MIN_INPUT_SIZE, MAX_INPUT_SIZE)                                                            \
	    ->UseManualTime();
#else
#define TRANSFORM_INCLUSIVE_SCAN_STD_WRAPPER
#endif
//endregion transform_inclusive_scan

//region transform_inclusive_scan_hpx
#ifdef USE_HPX
template<class Policy>
static void transform_inclusive_scan_hpx_wrapper(benchmark::State & state)
{
	benchmark_transform_inclusive_scan::benchmark_transform_inclusive_scan_wrapper<Policy>(
	    state, benchmark_transform_inclusive_scan::transform_inclusive_scan_hpx);
}

#define TRANSFORM_INCLUSIVE_SCAN_HPX_WRAPPER                                                               \
	BENCHMARK_TEMPLATE1(transform_inclusive_scan_hpx_wrapper, std::execution::parallel_unsequenced_policy) \
	    ->Name(BENCHMARK_NAME("hpx::transform_inclusive_scan"))                                            \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                                            \
	    ->Range(MIN_INPUT_SIZE, MAX_INPUT_SIZE)                                                            \
	    ->UseManualTime();
#else
#define TRANSFORM_INCLUSIVE_SCAN_HPX_WRAPPER
#endif

#define TRANSFORM_INCLUSIVE_SCAN_GROUP   \
	TRANSFORM_INCLUSIVE_SCAN_SEQ_WRAPPER \
	TRANSFORM_INCLUSIVE_SCAN_STD_WRAPPER \
	TRANSFORM_INCLUSIVE_SCAN_HPX_WRAPPER

#endif //PSTL_BENCH_TRANSFORM_INCLUSIVE_SCAN_GROUP_H
