#pragma once

#include "pstl/utils/benchmark_naming.h"

#include "partial_sort_utils.h"

#include "partial_sort_std.h"

#ifdef USE_GNU
#include "partial_sort_gnu.h"
#endif

#ifdef USE_HPX
#include "partial_sort_hpx.h"
#endif

//region partial_sort_std
template<class Policy>
static void partial_sort_std_wrapper(benchmark::State & state)
{
	benchmark_partial_sort::benchmark_wrapper<Policy>(state, benchmark_partial_sort::partial_sort_std);
}

#define PARTIAL_SORT_SEQ_WRAPPER                                                    \
	BENCHMARK_TEMPLATE1(partial_sort_std_wrapper, std::execution::sequenced_policy) \
	    ->Name(BENCHMARK_NAME_WITH_BACKEND("SEQ", "std::partial_sort"))             \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                     \
	    ->Range(MIN_INPUT_SIZE, MAX_INPUT_SIZE)                                     \
	    ->UseManualTime();

#ifdef USE_PSTL
#define PARTIAL_SORT_STD_WRAPPER                                                               \
	BENCHMARK_TEMPLATE1(partial_sort_std_wrapper, std::execution::parallel_unsequenced_policy) \
	    ->Name(BENCHMARK_NAME("std::partial_sort"))                                            \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                                \
	    ->Range(MIN_INPUT_SIZE, MAX_INPUT_SIZE)                                                \
	    ->UseManualTime();
#else
#define PARTIAL_SORT_STD_WRAPPER
#endif
//endregion partial_sort_std

//region partial_sort_gnu
#ifdef USE_GNU
template<class Policy>
static void partial_sort_gnu_wrapper(benchmark::State & state)
{
	benchmark_partial_sort::benchmark_wrapper<Policy>(state, benchmark_partial_sort::partial_sort_gnu);
}

#define PARTIAL_SORT_GNU_WRAPPER                                                               \
	BENCHMARK_TEMPLATE1(partial_sort_gnu_wrapper, std::execution::parallel_unsequenced_policy) \
	    ->Name(BENCHMARK_NAME("gnu::partial_sort"))                                            \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                                \
	    ->Range(MIN_INPUT_SIZE, MAX_INPUT_SIZE)                                                \
	    ->UseManualTime();
#else
#define PARTIAL_SORT_GNU_WRAPPER
#endif
//endregion partial_sort_gnu

//region partial_sort_hpx
#ifdef USE_HPX
template<class Policy>
static void partial_sort_hpx_wrapper(benchmark::State & state)
{
	benchmark_partial_sort::benchmark_wrapper<Policy>(state, benchmark_partial_sort::partial_sort_hpx);
}

#define PARTIAL_SORT_HPX_WRAPPER                                                               \
	BENCHMARK_TEMPLATE1(partial_sort_hpx_wrapper, std::execution::parallel_unsequenced_policy) \
	    ->Name(BENCHMARK_NAME("hpx::partial_sort"))                                            \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                                \
	    ->Range(MIN_INPUT_SIZE, MAX_INPUT_SIZE)                                                \
	    ->UseManualTime();
#else
#define PARTIAL_SORT_HPX_WRAPPER
#endif

#define PARTIAL_SORT_GROUP   \
	PARTIAL_SORT_SEQ_WRAPPER \
	PARTIAL_SORT_STD_WRAPPER \
	PARTIAL_SORT_GNU_WRAPPER \
	PARTIAL_SORT_HPX_WRAPPER


