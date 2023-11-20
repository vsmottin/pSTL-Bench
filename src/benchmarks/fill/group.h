#ifndef PSTL_BENCH_FILL_GROUP_H
#define PSTL_BENCH_FILL_GROUP_H

#include "benchmark_prefix.h"

#include "fill_utils.h"

#include "fill_std.h"

#ifdef USE_HPX
#include "fill_hpx.h"
#endif

//region fill_std
template<class Policy>
static void fill_std_wrapper(benchmark::State & state)
{
	benchmark_fill::benchmark_wrapper<Policy>(state, benchmark_fill::fill_std);
}

#define FILL_SEQ_WRAPPER                                                    \
	BENCHMARK_TEMPLATE1(fill_std_wrapper, std::execution::sequenced_policy) \
	    ->Name(BENCHMARK_NAME_WITH_BACKEND("SEQ", "std::fill"))             \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                             \
	    ->Range(MIN_INPUT_SIZE, MAX_INPUT_SIZE);

#ifdef USE_PSTL
#define FILL_STD_WRAPPER                                                               \
	BENCHMARK_TEMPLATE1(fill_std_wrapper, std::execution::parallel_unsequenced_policy) \
	    ->Name(BENCHMARK_NAME("std::fill"))                                            \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                        \
	    ->Range(MIN_INPUT_SIZE, MAX_INPUT_SIZE);
#else
#define FILL_STD_WRAPPER
#endif
//endregion fill_std

#ifdef USE_HPX
template<class Policy>
static void fill_hpx_wrapper(benchmark::State & state)
{
	benchmark_fill::benchmark_wrapper<Policy>(state, benchmark_fill::fill_hpx);
}

#define FILL_HPX_WRAPPER                                                               \
	BENCHMARK_TEMPLATE1(fill_hpx_wrapper, std::execution::parallel_unsequenced_policy) \
	    ->Name(BENCHMARK_NAME("hpx::fill"))                                            \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                        \
	    ->Range(MIN_INPUT_SIZE, MAX_INPUT_SIZE);
#else
#define FILL_HPX_WRAPPER
#endif

#define FILL_GROUP   \
	FILL_SEQ_WRAPPER \
	FILL_STD_WRAPPER \
	FILL_HPX_WRAPPER

#endif //PSTL_BENCH_FILL_GROUP_H
