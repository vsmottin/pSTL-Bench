#ifndef PSTL_BENCH_EXCLUSIVE_SCAN_GROUP_H
#define PSTL_BENCH_EXCLUSIVE_SCAN_GROUP_H

#include "benchmark_prefix.h"

#include "exclusive_scan_utils.h"

#include "exclusive_scan_std.h"

#ifdef USE_HPX
#include "exclusive_scan_hpx.h"
#endif

//region exclusive_scan_std
template<class Policy>
static void exclusive_scan_std_wrapper(benchmark::State & state)
{
	benchmark_exclusive_scan::benchmark_wrapper<Policy>(state, benchmark_exclusive_scan::exclusive_scan_std);
}

#define EXCLUSIVE_SCAN_SEQ_WRAPPER                                                    \
	BENCHMARK_TEMPLATE1(exclusive_scan_std_wrapper, std::execution::sequenced_policy) \
	    ->Name(BENCHMARK_NAME_WITH_BACKEND("SEQ", "std::exclusive_scan"))             \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                       \
	    ->Range(MIN_INPUT_SIZE, MAX_INPUT_SIZE);

#ifdef USE_PSTL
#define EXCLUSIVE_SCAN_STD_WRAPPER                                                               \
	BENCHMARK_TEMPLATE1(exclusive_scan_std_wrapper, std::execution::parallel_unsequenced_policy) \
	    ->Name(BENCHMARK_NAME("std::exclusive_scan"))                                            \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                                  \
	    ->Range(MIN_INPUT_SIZE, MAX_INPUT_SIZE);
#else
#define EXCLUSIVE_SCAN_STD_WRAPPER
#endif
//endregion exclusive_scan_std

//region exclusive_scan_hpx
#ifdef USE_HPX
template<class Policy>
static void exclusive_scan_hpx_wrapper(benchmark::State & state)
{
	benchmark_exclusive_scan::benchmark_wrapper<Policy>(state, benchmark_exclusive_scan::exclusive_scan_hpx);
}

#define EXCLUSIVE_SCAN_HPX_WRAPPER                                                               \
	BENCHMARK_TEMPLATE1(exclusive_scan_hpx_wrapper, std::execution::parallel_unsequenced_policy) \
	    ->Name(BENCHMARK_NAME("hpx::exclusive_scan"))                                            \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                                  \
	    ->Range(MIN_INPUT_SIZE, MAX_INPUT_SIZE);
#else
#define EXCLUSIVE_SCAN_HPX_WRAPPER
#endif

#define EXCLUSIVE_SCAN_GROUP   \
	EXCLUSIVE_SCAN_SEQ_WRAPPER \
	EXCLUSIVE_SCAN_STD_WRAPPER \
	EXCLUSIVE_SCAN_HPX_WRAPPER

#endif //PSTL_BENCH_EXCLUSIVE_SCAN_GROUP_H
