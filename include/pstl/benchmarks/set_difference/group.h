#ifndef PSTL_BENCH_SET_DIFFERENCE_GROUP_H
#define PSTL_BENCH_SET_DIFFERENCE_GROUP_H

#include "benchmark_prefix.h"

#include "set_difference_utils.h"

#include "set_difference_std.h"

#ifdef USE_GNU
#include "set_difference_gnu.h"
#endif

#ifdef USE_HPX
#include "set_difference_hpx.h"
#include <hpx/executors/parallel_executor.hpp>
#endif

//region set_difference_std
template<class Policy>
static void set_difference_std_wrapper(benchmark::State & state)
{
	benchmark_set_difference::benchmark_wrapper<Policy>(state, benchmark_set_difference::set_difference_std);
}

#define SET_DIFFERENCE_SEQ_WRAPPER                                                    \
	BENCHMARK_TEMPLATE1(set_difference_std_wrapper, std::execution::sequenced_policy) \
	    ->Name(BENCHMARK_NAME_WITH_BACKEND("SEQ", "std::set_difference"))             \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                       \
	    ->Range(MIN_INPUT_SIZE, MAX_INPUT_SIZE);

#ifdef USE_PSTL
#define SET_DIFFERENCE_STD_WRAPPER                                                               \
	BENCHMARK_TEMPLATE1(set_difference_std_wrapper, std::execution::parallel_unsequenced_policy) \
	    ->Name(BENCHMARK_NAME("std::set_difference"))                                            \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                                  \
	    ->Range(MIN_INPUT_SIZE, MAX_INPUT_SIZE);
#else
#define SET_DIFFERENCE_STD_WRAPPER
#endif
//endregion set_difference_std

//region set_difference_gnu
#ifdef USE_GNU
template<class Policy>
static void set_difference_gnu_wrapper(benchmark::State & state)
{
	benchmark_set_difference::benchmark_wrapper<Policy>(state, benchmark_set_difference::set_difference_gnu);
}

#define SET_DIFFERENCE_GNU_WRAPPER                                                               \
	BENCHMARK_TEMPLATE1(set_difference_gnu_wrapper, std::execution::parallel_unsequenced_policy) \
	    ->Name(BENCHMARK_NAME("gnu::set_difference"))                                            \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                                  \
	    ->Range(MIN_INPUT_SIZE, MAX_INPUT_SIZE);
#else
#define SET_DIFFERENCE_GNU_WRAPPER
#endif
//endregion set_difference_gnu

//region set_difference_hpx
#ifdef USE_HPX
template<class Policy>
static void set_difference_hpx_wrapper(benchmark::State & state)
{
	benchmark_set_difference::benchmark_wrapper<Policy>(state, benchmark_set_difference::set_difference_hpx);
}

#define SET_DIFFERENCE_HPX_WRAPPER                                                               \
	BENCHMARK_TEMPLATE1(set_difference_hpx_wrapper, hpx::execution::parallel_unsequenced_policy) \
	    ->Name(BENCHMARK_NAME("hpx::set_difference"))                                            \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                                  \
	    ->Range(MIN_INPUT_SIZE, MAX_INPUT_SIZE);
#else
#define SET_DIFFERENCE_HPX_WRAPPER
#endif

#define SET_DIFFERENCE_GROUP   \
	SET_DIFFERENCE_SEQ_WRAPPER \
	SET_DIFFERENCE_STD_WRAPPER \
	SET_DIFFERENCE_GNU_WRAPPER \
	SET_DIFFERENCE_HPX_WRAPPER

#endif //PSTL_BENCH_SET_DIFFERENCE_GROUP_H
