
#ifndef PSTL_BENCH_FIND_GROUP_H
#define PSTL_BENCH_FIND_GROUP_H

#include "benchmark_prefix.h"

#include "find_utils.h"

#include "find_std.h"

#ifdef USE_GNU
#include "find_gnu.h"
#endif

#ifdef USE_HPX
#include "find_hpx.h"
#endif

//region find
template<class Policy>
static void find_std_wrapper(benchmark::State & state)
{
	benchmark_find::benchmark_wrapper<Policy>(state, benchmark_find::find_std);
}

#define FIND_SEQ_WRAPPER                                                    \
	BENCHMARK_TEMPLATE1(find_std_wrapper, std::execution::sequenced_policy) \
	    ->Name(BENCHMARK_NAME_WITH_BACKEND("SEQ", "std::find"))             \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                             \
	    ->Range(MIN_INPUT_SIZE, MAX_INPUT_SIZE);

#ifdef USE_PSTL
#define FIND_STD_WRAPPER                                                   \
	BENCHMARK_TEMPLATE1(find_std_wrapper, std::execution::parallel_policy) \
	    ->Name(BENCHMARK_NAME("std::find"))                                \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                            \
	    ->Range(MIN_INPUT_SIZE, MAX_INPUT_SIZE);
#else
#define FIND_STD_WRAPPER
#endif
//endregion find

//region find_gnu
#ifdef USE_GNU
template<class Policy>
static void find_gnu_wrapper(benchmark::State & state)
{
	benchmark_find::benchmark_wrapper<Policy>(state, benchmark_find::find_gnu);
}

#define FIND_GNU_WRAPPER                                                   \
	BENCHMARK_TEMPLATE1(find_gnu_wrapper, std::execution::parallel_policy) \
	    ->Name(BENCHMARK_NAME("gnu::find"))                                \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                            \
	    ->Range(MIN_INPUT_SIZE, MAX_INPUT_SIZE);
#else
#define FIND_GNU_WRAPPER
#endif
//endregion find_gnu

//region find_hpx
#ifdef USE_HPX
template<class Policy>
static void find_hpx_wrapper(benchmark::State & state)
{
	benchmark_find::benchmark_wrapper<Policy>(state, benchmark_find::find_hpx);
}

#define FIND_HPX_WRAPPER                                                   \
	BENCHMARK_TEMPLATE1(find_hpx_wrapper, std::execution::parallel_policy) \
	    ->Name(BENCHMARK_NAME("hpx::find"))                                \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                            \
	    ->Range(MIN_INPUT_SIZE, MAX_INPUT_SIZE);
#else
#define FIND_HPX_WRAPPER
#endif
//endregion find_hpx


// Register the function as a benchmark
#define FIND_GROUP   \
	FIND_SEQ_WRAPPER \
	FIND_STD_WRAPPER \
	FIND_GNU_WRAPPER \
	FIND_HPX_WRAPPER


#endif //PSTL_BENCH_FIND_GROUP_H
