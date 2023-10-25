#ifndef PSTL_BENCH_COUNT_IF_GROUP_H
#define PSTL_BENCH_COUNT_IF_GROUP_H

#include "benchmark_prefix.h"

#include "count_if_utils.h"

#include "count_if_std.h"

#ifdef USE_GNU
#include "count_if_gnu.h"
#endif

#ifdef USE_HPX
#include "count_if_hpx.h"
#endif

//region count_if_std
template<class Policy>
static void count_if_std_wrapper(benchmark::State & state)
{
	benchmark_count_if::benchmark_wrapper<Policy>(state, benchmark_count_if::count_if_std);
}

#define COUNT_IF_SEQ_WRAPPER                                                    \
	BENCHMARK_TEMPLATE1(count_if_std_wrapper, std::execution::sequenced_policy) \
	    ->Name(BENCHMARK_NAME_WITH_BACKEND("SEQ", "std::count_if"))             \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                 \
	    ->Range(MIN_INPUT_SIZE, MAX_INPUT_SIZE);

#ifdef USE_PSTL
#define COUNT_IF_STD_WRAPPER                                                   \
	BENCHMARK_TEMPLATE1(count_if_std_wrapper, std::execution::parallel_policy) \
	    ->Name(BENCHMARK_NAME("std::count_if"))                                \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                \
	    ->Range(MIN_INPUT_SIZE, MAX_INPUT_SIZE);
#else
#define COUNT_IF_STD_WRAPPER
#endif
//endregion count_if_std

//region count_if_gnu
#ifdef USE_GNU
template<class Policy>
static void count_if_gnu_wrapper(benchmark::State & state)
{
	benchmark_count_if::benchmark_wrapper<Policy>(state, benchmark_count_if::count_if_gnu);
}

#define COUNT_IF_GNU_WRAPPER                                                        \
	BENCHMARK_TEMPLATE1(count_if_gnu_wrapper, std::execution::parallel_policy)      \
	    ->Name(BENCHMARK_NAME("gnu::count_if")) \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                     \
	    ->Range(MIN_INPUT_SIZE, MAX_INPUT_SIZE);
#else
#define COUNT_IF_GNU_WRAPPER
#endif
//endregion count_if_gnu

#ifdef USE_HPX
template<class Policy>
static void count_if_hpx_wrapper(benchmark::State & state)
{
	benchmark_count_if::benchmark_wrapper<Policy>(state, benchmark_count_if::count_if_hpx);
}

#define COUNT_IF_HPX_WRAPPER                                                        \
	BENCHMARK_TEMPLATE1(count_if_hpx_wrapper, std::execution::parallel_policy)      \
	    ->Name(BENCHMARK_NAME("hpx::count_if")) \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                     \
	    ->Range(MIN_INPUT_SIZE, MAX_INPUT_SIZE);
#else
#define COUNT_IF_HPX_WRAPPER
#endif

#define COUNT_IF_GROUP   \
	COUNT_IF_SEQ_WRAPPER \
	COUNT_IF_STD_WRAPPER \
	COUNT_IF_GNU_WRAPPER \
	COUNT_IF_HPX_WRAPPER

#endif //PSTL_BENCH_COUNT_IF_GROUP_H
