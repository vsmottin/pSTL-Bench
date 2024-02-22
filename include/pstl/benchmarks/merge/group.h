#ifndef PSTL_BENCH_MERGE_GROUP_H
#define PSTL_BENCH_MERGE_GROUP_H

#include "benchmark_prefix.h"

#include "merge_utils.h"

#include "merge_std.h"

#ifdef USE_GNU
#include "merge_gnu.h"
#endif

#ifdef USE_HPX
#include "merge_hpx.h"
#endif

//region merge_std
template<class Policy>
static void merge_std_wrapper(benchmark::State & state)
{
	benchmark_merge::benchmark_wrapper<Policy>(state, benchmark_merge::merge_std);
}

#define MERGE_SEQ_WRAPPER                                                    \
	BENCHMARK_TEMPLATE1(merge_std_wrapper, std::execution::sequenced_policy) \
	    ->Name(BENCHMARK_NAME_WITH_BACKEND("SEQ", "std::merge"))             \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                              \
	    ->Range(MIN_INPUT_SIZE, MAX_INPUT_SIZE)                              \
	    ->UseManualTime();

#ifdef USE_PSTL
#define MERGE_STD_WRAPPER                                                               \
	BENCHMARK_TEMPLATE1(merge_std_wrapper, std::execution::parallel_unsequenced_policy) \
	    ->Name(BENCHMARK_NAME("std::merge"))                                            \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                         \
	    ->Range(MIN_INPUT_SIZE, MAX_INPUT_SIZE)                                         \
	    ->UseManualTime();
#else
#define MERGE_STD_WRAPPER
#endif
//endregion merge_std

//region merge_gnu
#ifdef USE_GNU
template<class Policy>
static void merge_gnu_wrapper(benchmark::State & state)
{
	benchmark_merge::benchmark_wrapper<Policy>(state, benchmark_merge::merge_gnu);
}

#define MERGE_GNU_WRAPPER                                                               \
	BENCHMARK_TEMPLATE1(merge_gnu_wrapper, std::execution::parallel_unsequenced_policy) \
	    ->Name(BENCHMARK_NAME("gnu::merge"))                                            \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                         \
	    ->Range(MIN_INPUT_SIZE, MAX_INPUT_SIZE)                                         \
	    ->UseManualTime();
#else
#define MERGE_GNU_WRAPPER
#endif
//endregion merge_gnu

//region merge_hpx
#ifdef USE_HPX
template<class Policy>
static void merge_hpx_wrapper(benchmark::State & state)
{
	benchmark_merge::benchmark_wrapper<Policy>(state, benchmark_merge::merge_hpx);
}

#define MERGE_HPX_WRAPPER                                                               \
	BENCHMARK_TEMPLATE1(merge_hpx_wrapper, std::execution::parallel_unsequenced_policy) \
	    ->Name(BENCHMARK_NAME("hpx::merge"))                                            \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                         \
	    ->Range(MIN_INPUT_SIZE, MAX_INPUT_SIZE)                                         \
	    ->UseManualTime();
#else
#define MERGE_HPX_WRAPPER
#endif

#define MERGE_GROUP   \
	MERGE_SEQ_WRAPPER \
	MERGE_STD_WRAPPER \
	MERGE_GNU_WRAPPER \
	MERGE_HPX_WRAPPER

#endif //PSTL_BENCH_MERGE_GROUP_H
