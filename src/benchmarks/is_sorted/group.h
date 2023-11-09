#ifndef PSTL_BENCH_IS_SORTED_GROUP_H
#define PSTL_BENCH_IS_SORTED_GROUP_H

#include "benchmark_prefix.h"

#include "is_sorted_utils.h"

#include "is_sorted_std.h"

#ifdef USE_HPX
#include "is_sorted_hpx.h"
#endif

//region is_sorted_std
template<class Policy>
static void is_sorted_std_wrapper(benchmark::State & state)
{
	benchmark_is_sorted::benchmark_wrapper<Policy>(state, benchmark_is_sorted::is_sorted_std);
}

#define IS_SORTED_SEQ_WRAPPER                                                    \
	BENCHMARK_TEMPLATE1(is_sorted_std_wrapper, std::execution::sequenced_policy) \
	    ->Name(BENCHMARK_NAME_WITH_BACKEND("SEQ", "std::is_sorted"))             \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                      \
	    ->Range(MIN_INPUT_SIZE, MAX_INPUT_SIZE);

#ifdef USE_PSTL
#define IS_SORTED_STD_WRAPPER                                                   \
	BENCHMARK_TEMPLATE1(is_sorted_std_wrapper, std::execution::parallel_policy) \
	    ->Name(BENCHMARK_NAME("std::is_sorted"))                                \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                     \
	    ->Range(MIN_INPUT_SIZE, MAX_INPUT_SIZE);
#else
#define IS_SORTED_STD_WRAPPER
#endif
//endregion is_sorted_std

//region is_sorted_hpx
#ifdef USE_HPX
template<class Policy>
static void is_sorted_hpx_wrapper(benchmark::State & state)
{
	benchmark_is_sorted::benchmark_wrapper<Policy>(state, benchmark_is_sorted::is_sorted_hpx);
}

#define IS_SORTED_HPX_WRAPPER                                                   \
	BENCHMARK_TEMPLATE1(is_sorted_hpx_wrapper, std::execution::parallel_policy) \
	    ->Name(BENCHMARK_NAME("hpx::is_sorted"))                                \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                     \
	    ->Range(MIN_INPUT_SIZE, MAX_INPUT_SIZE);
#else
#define IS_SORTED_HPX_WRAPPER
#endif

#define IS_SORTED_GROUP   \
	IS_SORTED_SEQ_WRAPPER \
	IS_SORTED_STD_WRAPPER \
	IS_SORTED_HPX_WRAPPER

#endif //PSTL_BENCH_IS_SORTED_GROUP_H
