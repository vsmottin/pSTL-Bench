#ifndef PSTL_BENCH_INPLACE_MERGE_GROUP_H
#define PSTL_BENCH_INPLACE_MERGE_GROUP_H

#include "benchmark_prefix.h"

#include "inplace_merge_utils.h"

#include "inplace_merge_std.h"

#ifdef USE_HPX
#include "inplace_merge_hpx.h"
#endif

//region inplace_merge_std
template<class Policy>
static void inplace_merge_std_wrapper(benchmark::State & state)
{
	benchmark_inplace_merge::benchmark_wrapper<Policy>(state, benchmark_inplace_merge::inplace_merge_std);
}

#define INPLACE_MERGE_SEQ_WRAPPER                                                    \
	BENCHMARK_TEMPLATE1(inplace_merge_std_wrapper, std::execution::sequenced_policy) \
	    ->Name(BENCHMARK_NAME_WITH_BACKEND("SEQ", "std::inplace_merge"))             \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                      \
	    ->Range(MIN_INPUT_SIZE, MAX_INPUT_SIZE);

#ifdef USE_PSTL
#define INPLACE_MERGE_STD_WRAPPER                                                               \
	BENCHMARK_TEMPLATE1(inplace_merge_std_wrapper, std::execution::parallel_unsequenced_policy) \
	    ->Name(BENCHMARK_NAME("std::inplace_merge"))                                            \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                                 \
	    ->Range(MIN_INPUT_SIZE, MAX_INPUT_SIZE);
#else
#define INPLACE_MERGE_STD_WRAPPER
#endif
//endregion inplace_merge_std

//region inplace_merge_hpx
#ifdef USE_HPX
template<class Policy>
static void inplace_merge_hpx_wrapper(benchmark::State & state)
{
	benchmark_inplace_merge::benchmark_wrapper<Policy>(state, benchmark_inplace_merge::inplace_merge_hpx);
}

#define INPLACE_MERGE_HPX_WRAPPER                                                               \
	BENCHMARK_TEMPLATE1(inplace_merge_hpx_wrapper, std::execution::parallel_unsequenced_policy) \
	    ->Name(BENCHMARK_NAME("hpx::inplace_merge"))                                            \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                                 \
	    ->Range(MIN_INPUT_SIZE, MAX_INPUT_SIZE);
#else
#define INPLACE_MERGE_HPX_WRAPPER
#endif

#define INPLACE_MERGE_GROUP   \
	INPLACE_MERGE_SEQ_WRAPPER \
	INPLACE_MERGE_STD_WRAPPER \
	INPLACE_MERGE_HPX_WRAPPER

#endif //PSTL_BENCH_INPLACE_MERGE_GROUP_H
