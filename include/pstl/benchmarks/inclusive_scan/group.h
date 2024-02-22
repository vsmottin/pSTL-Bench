#ifndef PSTL_BENCH_INCLUSIVE_SCAN_GROUP_H
#define PSTL_BENCH_INCLUSIVE_SCAN_GROUP_H

#include "benchmark_prefix.h"

#include "inclusive_scan_utils.h"

#include "inclusive_scan_std.h"

#ifdef USE_HPX
#include "inclusive_scan_hpx.h"
#endif

//region inclusive_scan_std
template<class Policy>
static void inclusive_scan_std_wrapper(benchmark::State & state)
{
	benchmark_inclusive_scan::benchmark_wrapper<Policy>(state, benchmark_inclusive_scan::inclusive_scan_std);
}

#define INCLUSIVE_SCAN_SEQ_WRAPPER                                                    \
	BENCHMARK_TEMPLATE1(inclusive_scan_std_wrapper, std::execution::sequenced_policy) \
	    ->Name(BENCHMARK_NAME_WITH_BACKEND("SEQ", "std::inclusive_scan"))             \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                       \
	    ->Range(MIN_INPUT_SIZE, MAX_INPUT_SIZE)                                       \
	    ->UseManualTime();

#ifdef USE_PSTL
#define INCLUSIVE_SCAN_STD_WRAPPER                                                               \
	BENCHMARK_TEMPLATE1(inclusive_scan_std_wrapper, std::execution::parallel_unsequenced_policy) \
	    ->Name(BENCHMARK_NAME("std::inclusive_scan"))                                            \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                                  \
	    ->Range(MIN_INPUT_SIZE, MAX_INPUT_SIZE)                                                  \
	    ->UseManualTime();
#else
#define INCLUSIVE_SCAN_STD_WRAPPER
#endif
//endregion inclusive_scan_std

//region inclusive_scan_hpx
#ifdef USE_HPX
template<class Policy>
static void inclusive_scan_hpx_wrapper(benchmark::State & state)
{
	benchmark_inclusive_scan::benchmark_wrapper<Policy>(state, benchmark_inclusive_scan::inclusive_scan_hpx);
}

#define INCLUSIVE_SCAN_HPX_WRAPPER                                                               \
	BENCHMARK_TEMPLATE1(inclusive_scan_hpx_wrapper, std::execution::parallel_unsequenced_policy) \
	    ->Name(BENCHMARK_NAME("hpx::inclusive_scan"))                                            \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                                  \
	    ->Range(MIN_INPUT_SIZE, MAX_INPUT_SIZE)                                                  \
	    ->UseManualTime();
#else
#define INCLUSIVE_SCAN_HPX_WRAPPER
#endif

#define INCLUSIVE_SCAN_GROUP   \
	INCLUSIVE_SCAN_SEQ_WRAPPER \
	INCLUSIVE_SCAN_STD_WRAPPER \
	INCLUSIVE_SCAN_HPX_WRAPPER

#endif //PSTL_BENCH_INCLUSIVE_SCAN_GROUP_H
