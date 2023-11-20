#ifndef PSTL_BENCH_SEARCH_GROUP_H
#define PSTL_BENCH_SEARCH_GROUP_H

#include "benchmark_prefix.h"

#include "search_utils.h"

#include "search_std.h"

#ifdef USE_GNU
#include "search_gnu.h"
#endif

#ifdef USE_HPX
#include "search_hpx.h"
#endif

//region search_std
template<class Policy>
static void search_std_wrapper(benchmark::State & state)
{
	benchmark_search::benchmark_wrapper<Policy>(state, benchmark_search::search_std);
}

#define SEARCH_SEQ_WRAPPER                                                    \
	BENCHMARK_TEMPLATE1(search_std_wrapper, std::execution::sequenced_policy) \
	    ->Name(BENCHMARK_NAME_WITH_BACKEND("SEQ", "std::search"))             \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                               \
	    ->Range(MIN_INPUT_SIZE, MAX_INPUT_SIZE);

#ifdef USE_PSTL
#define SEARCH_STD_WRAPPER                                                               \
	BENCHMARK_TEMPLATE1(search_std_wrapper, std::execution::parallel_unsequenced_policy) \
	    ->Name(BENCHMARK_NAME("std::search"))                                            \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                          \
	    ->Range(MIN_INPUT_SIZE, MAX_INPUT_SIZE);
#else
#define SEARCH_STD_WRAPPER
#endif
//endregion search_std

//region search_gnu
#ifdef USE_GNU
template<class Policy>
static void search_gnu_wrapper(benchmark::State & state)
{
	benchmark_search::benchmark_wrapper<Policy>(state, benchmark_search::search_gnu);
}

#define SEARCH_GNU_WRAPPER                                                               \
	BENCHMARK_TEMPLATE1(search_gnu_wrapper, std::execution::parallel_unsequenced_policy) \
	    ->Name(BENCHMARK_NAME("gnu::search"))                                            \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                          \
	    ->Range(MIN_INPUT_SIZE, MAX_INPUT_SIZE);
#else
#define SEARCH_GNU_WRAPPER
#endif
//endregion search_gnu

//region search_hpx
#ifdef USE_HPX
template<class Policy>
static void search_hpx_wrapper(benchmark::State & state)
{
	benchmark_search::benchmark_wrapper<Policy>(state, benchmark_search::search_hpx);
}

#define SEARCH_HPX_WRAPPER                                                               \
	BENCHMARK_TEMPLATE1(search_hpx_wrapper, std::execution::parallel_unsequenced_policy) \
	    ->Name(BENCHMARK_NAME("hpx::search"))                                            \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                          \
	    ->Range(MIN_INPUT_SIZE, MAX_INPUT_SIZE);
#else
#define SEARCH_HPX_WRAPPER
#endif

#define SEARCH_GROUP   \
	SEARCH_SEQ_WRAPPER \
	SEARCH_STD_WRAPPER \
	SEARCH_GNU_WRAPPER \
	SEARCH_HPX_WRAPPER

#endif //PSTL_BENCH_SEARCH_GROUP_H
