#ifndef PSTL_BENCH_SORT_GROUP_H
#define PSTL_BENCH_SORT_GROUP_H

#include "benchmark_prefix.h"

#include "sort_utils.h"

#include "sort_std.h"

#ifdef USE_GNU
#include "sort_gnu.h"
#endif //USE_GNU

#ifdef USE_HPX
#include "sort_hpx.h"
#endif //USE_HPX

//region sort_std
template<class Policy>
static void sort_std_wrapper(benchmark::State & state)
{
	benchmark_sort::benchmark_wrapper<Policy>(state, benchmark_sort::sort_std);
}

#define SORT_SEQ_WRAPPER                                                    \
	BENCHMARK_TEMPLATE1(sort_std_wrapper, std::execution::sequenced_policy) \
	    ->Name(BENCHMARK_NAME_WITH_BACKEND("SEQ", "std::sort"))             \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                             \
	    ->Range(MIN_INPUT_SIZE, MAX_INPUT_SIZE)                             \
	    ->UseManualTime();

#ifdef USE_PSTL
#define SORT_STD_WRAPPER                                                               \
	BENCHMARK_TEMPLATE1(sort_std_wrapper, std::execution::parallel_unsequenced_policy) \
	    ->Name(BENCHMARK_NAME("std::sort"))                                            \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                        \
	    ->Range(MIN_INPUT_SIZE, MAX_INPUT_SIZE)                                        \
	    ->UseManualTime();
#else
#define SORT_STD_WRAPPER
#endif
//endregion sort_std

//region sort_gnu
#ifdef USE_GNU
template<class Policy>
static void sort_gnu_wrapper(benchmark::State & state)
{
	benchmark_sort::benchmark_wrapper<Policy>(state, benchmark_sort::sort_gnu);
}

#define SORT_GNU_WRAPPER                                                               \
	BENCHMARK_TEMPLATE1(sort_gnu_wrapper, std::execution::parallel_unsequenced_policy) \
	    ->Name(BENCHMARK_NAME("gnu::sort"))                                            \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                        \
	    ->Range(MIN_INPUT_SIZE, MAX_INPUT_SIZE)                                        \
	    ->UseManualTime();
#else
#define SORT_GNU_WRAPPER
#endif
//endregion sort_gnu

//region sort_hpx
#ifdef USE_HPX
template<class Policy>
static void sort_hpx_wrapper(benchmark::State & state)
{
	benchmark_sort::benchmark_wrapper<Policy>(state, benchmark_sort::sort_hpx);
}

#define SORT_HPX_WRAPPER                                                               \
	BENCHMARK_TEMPLATE1(sort_hpx_wrapper, std::execution::parallel_unsequenced_policy) \
	    ->Name(BENCHMARK_NAME("hpx::sort"))                                            \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                        \
	    ->Range(MIN_INPUT_SIZE, MAX_INPUT_SIZE)                                        \
	    ->UseManualTime();
#else
#define SORT_HPX_WRAPPER
#endif

#define SORT_GROUP   \
	SORT_SEQ_WRAPPER \
	SORT_STD_WRAPPER \
	SORT_GNU_WRAPPER \
	SORT_HPX_WRAPPER

#endif //PSTL_BENCH_SORT_GROUP_H
