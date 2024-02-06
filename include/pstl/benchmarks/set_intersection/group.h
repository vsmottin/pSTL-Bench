#ifndef PSTL_BENCH_SET_INTERSECTION_GROUP_H
#define PSTL_BENCH_SET_INTERSECTION_GROUP_H

#include "benchmark_prefix.h"

#include "set_intersection_utils.h"

#include "set_intersection_std.h"

#ifdef USE_GNU
#include "set_intersection_gnu.h"
#endif

#ifdef USE_HPX
#include "set_intersection_hpx.h"
#include <hpx/executors/parallel_executor.hpp>
#endif

//region set_intersection_std
template<class Policy>
static void set_intersection_std_wrapper(benchmark::State & state)
{
	benchmark_set_intersection::benchmark_wrapper<Policy>(state, benchmark_set_intersection::set_intersection_std);
}

#define SET_INTERSECTION_SEQ_WRAPPER                                                    \
	BENCHMARK_TEMPLATE1(set_intersection_std_wrapper, std::execution::sequenced_policy) \
	    ->Name(BENCHMARK_NAME_WITH_BACKEND("SEQ", "std::set_intersection"))             \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                         \
	    ->Range(MIN_INPUT_SIZE, MAX_INPUT_SIZE);

#ifdef USE_PSTL
#define SET_INTERSECTION_STD_WRAPPER                                                               \
	BENCHMARK_TEMPLATE1(set_intersection_std_wrapper, std::execution::parallel_unsequenced_policy) \
	    ->Name(BENCHMARK_NAME("std::set_intersection"))                                            \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                                    \
	    ->Range(MIN_INPUT_SIZE, MAX_INPUT_SIZE);
#else
#define SET_INTERSECTION_STD_WRAPPER
#endif
//endregion set_intersection_std

//region set_intersection_gnu
#ifdef USE_GNU
template<class Policy>
static void set_intersection_gnu_wrapper(benchmark::State & state)
{
	benchmark_set_intersection::benchmark_wrapper<Policy>(state, benchmark_set_intersection::set_intersection_gnu);
}

#define SET_INTERSECTION_GNU_WRAPPER                                                               \
	BENCHMARK_TEMPLATE1(set_intersection_gnu_wrapper, std::execution::parallel_unsequenced_policy) \
	    ->Name(BENCHMARK_NAME("gnu::set_intersection"))                                            \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                                    \
	    ->Range(MIN_INPUT_SIZE, MAX_INPUT_SIZE);
#else
#define SET_INTERSECTION_GNU_WRAPPER
#endif
//endregion set_intersection_gnu

//region set_intersection_hpx
#ifdef USE_HPX
template<class Policy>
static void set_intersection_hpx_wrapper(benchmark::State & state)
{
	benchmark_set_intersection::benchmark_wrapper<Policy>(state, benchmark_set_intersection::set_intersection_hpx);
}

#define SET_INTERSECTION_HPX_WRAPPER                                                               \
	BENCHMARK_TEMPLATE1(set_intersection_hpx_wrapper, hpx::execution::parallel_unsequenced_policy) \
	    ->Name(BENCHMARK_NAME("hpx::set_intersection"))                                            \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                                    \
	    ->Range(MIN_INPUT_SIZE, MAX_INPUT_SIZE);
#else
#define SET_INTERSECTION_HPX_WRAPPER
#endif

#define SET_INTERSECTION_GROUP   \
	SET_INTERSECTION_SEQ_WRAPPER \
	SET_INTERSECTION_STD_WRAPPER \
	SET_INTERSECTION_GNU_WRAPPER \
	SET_INTERSECTION_HPX_WRAPPER

#endif //PSTL_BENCH_SET_INTERSECTION_GROUP_H
