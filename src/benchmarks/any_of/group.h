#ifndef PSTL_BENCH_ANY_OF_GROUP_H
#define PSTL_BENCH_ANY_OF_GROUP_H

#include "benchmark_prefix.h"

#include "any_of_utils.h"

#include "any_of_std.h"

#ifdef USE_HPX
#include "any_of_hpx.h"
#endif

//region any_of_std
template<class Policy>
static void any_of_std_wrapper(benchmark::State & state)
{
	benchmark_any_of::benchmark_wrapper<Policy>(state, benchmark_any_of::any_of_std);
}

#define ANY_OF_SEQ_WRAPPER                                                    \
	BENCHMARK_TEMPLATE1(any_of_std_wrapper, std::execution::sequenced_policy) \
	    ->Name(BENCHMARK_NAME_WITH_BACKEND("SEQ", "std::any_of"))             \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                               \
	    ->Range(MIN_INPUT_SIZE, MAX_INPUT_SIZE);

#ifdef USE_PSTL
#define ANY_OF_STD_WRAPPER                                                   \
	BENCHMARK_TEMPLATE1(any_of_std_wrapper, std::execution::parallel_policy) \
	    ->Name(BENCHMARK_NAME("std::any_of"))                                \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                              \
	    ->Range(MIN_INPUT_SIZE, MAX_INPUT_SIZE);
#else
#define ANY_OF_STD_WRAPPER
#endif
//endregion any_of_std

//region any_of_hpx
#ifdef USE_HPX
template<class Policy>
static void any_of_hpx_wrapper(benchmark::State & state)
{
	benchmark_any_of::benchmark_wrapper<Policy>(state, benchmark_any_of::any_of_hpx);
}

#define ANY_OF_HPX_WRAPPER                                                   \
	BENCHMARK_TEMPLATE1(any_of_hpx_wrapper, std::execution::parallel_policy) \
	    ->Name(BENCHMARK_NAME("hpx::any_of"))                                \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                              \
	    ->Range(MIN_INPUT_SIZE, MAX_INPUT_SIZE);
#else
#define ANY_OF_HPX_WRAPPER
#endif

#define ANY_OF_GROUP   \
	ANY_OF_SEQ_WRAPPER \
	ANY_OF_STD_WRAPPER \
	ANY_OF_HPX_WRAPPER

#endif //PSTL_BENCH_ANY_OF_GROUP_H
