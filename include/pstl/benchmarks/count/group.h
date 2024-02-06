#ifndef PSTL_BENCH_COUNT_GROUP_H
#define PSTL_BENCH_COUNT_GROUP_H

#include "benchmark_prefix.h"

#include "count_utils.h"

#include "count_std.h"

#ifdef USE_GNU
#include "count_gnu.h"
#endif

#ifdef USE_HPX
#include "count_hpx.h"
#endif

//region count_std
template<class Policy>
static void count_std_wrapper(benchmark::State & state)
{
	benchmark_count::benchmark_wrapper<Policy>(state, benchmark_count::count_std);
}

#define COUNT_SEQ_WRAPPER                                                    \
	BENCHMARK_TEMPLATE1(count_std_wrapper, std::execution::sequenced_policy) \
	    ->Name(BENCHMARK_NAME_WITH_BACKEND("SEQ", "std::count"))             \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                              \
	    ->Range(MIN_INPUT_SIZE, MAX_INPUT_SIZE);

#ifdef USE_PSTL
#define COUNT_STD_WRAPPER                                                               \
	BENCHMARK_TEMPLATE1(count_std_wrapper, std::execution::parallel_unsequenced_policy) \
	    ->Name(BENCHMARK_NAME("std::count"))                                            \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                         \
	    ->Range(MIN_INPUT_SIZE, MAX_INPUT_SIZE);
#else
#define COUNT_STD_WRAPPER
#endif
//endregion count_std

//region count_gnu
#ifdef USE_GNU
template<class Policy>
static void count_gnu_wrapper(benchmark::State & state)
{
	benchmark_count::benchmark_wrapper<Policy>(state, benchmark_count::count_gnu);
}

#define COUNT_GNU_WRAPPER                                                               \
	BENCHMARK_TEMPLATE1(count_gnu_wrapper, std::execution::parallel_unsequenced_policy) \
	    ->Name(BENCHMARK_NAME("gnu::count"))                                            \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                         \
	    ->Range(MIN_INPUT_SIZE, MAX_INPUT_SIZE);
#else
#define COUNT_GNU_WRAPPER
#endif
//endregion count_gnu

#ifdef USE_HPX
template<class Policy>
static void count_hpx_wrapper(benchmark::State & state)
{
	benchmark_count::benchmark_wrapper<Policy>(state, benchmark_count::count_hpx);
}

#define COUNT_HPX_WRAPPER                                                               \
	BENCHMARK_TEMPLATE1(count_hpx_wrapper, std::execution::parallel_unsequenced_policy) \
	    ->Name(BENCHMARK_NAME("hpx::count"))                                            \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                         \
	    ->Range(MIN_INPUT_SIZE, MAX_INPUT_SIZE);
#else
#define COUNT_HPX_WRAPPER
#endif

#define COUNT_GROUP   \
	COUNT_SEQ_WRAPPER \
	COUNT_STD_WRAPPER \
	COUNT_GNU_WRAPPER \
	COUNT_HPX_WRAPPER

#endif //PSTL_BENCH_COUNT_GROUP_H
