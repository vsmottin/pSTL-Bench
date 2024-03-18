#ifndef PSTL_BENCH_TRANSFORM_REDUCE_GROUP_H
#define PSTL_BENCH_TRANSFORM_REDUCE_GROUP_H

#include "benchmark_prefix.h"

#include <benchmark/benchmark.h>

#include "transform_reduce_utils.h"

#include "transform_reduce_std.h"

#ifdef USE_HPX
#include "transform_reduce_hpx.h"
#endif

//region transform_reduce
template<class Policy>
static void transform_reduce_std_wrapper(benchmark::State & state)
{
	benchmark_transform_reduce::benchmark_wrapper<Policy>(state, benchmark_transform_reduce::transform_reduce_std);
}

#define TRANSFORM_REDUCE_SEQ_WRAPPER                                                    \
	BENCHMARK_TEMPLATE1(transform_reduce_std_wrapper, std::execution::sequenced_policy) \
	    ->Name(BENCHMARK_NAME_WITH_BACKEND("SEQ", "std::transform_reduce"))             \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                         \
	    ->Range(MIN_INPUT_SIZE, MAX_INPUT_SIZE)                                         \
	    ->UseManualTime();

#ifdef USE_PSTL
#define TRANSFORM_REDUCE_STD_WRAPPER                                                               \
	BENCHMARK_TEMPLATE1(transform_reduce_std_wrapper, std::execution::parallel_unsequenced_policy) \
	    ->Name(BENCHMARK_NAME("std::transform_reduce"))                                            \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                                    \
	    ->Range(MIN_INPUT_SIZE, MAX_INPUT_SIZE)                                                    \
	    ->UseManualTime();
#else
#define TRANSFORM_REDUCE_STD_WRAPPER
#endif
//endregion transform_reduce

//region transform_reduce_hpx
#ifdef USE_HPX
template<class Policy>
static void transform_reduce_hpx_wrapper(benchmark::State & state)
{
	benchmark_transform_reduce::benchmark_wrapper<Policy>(state, benchmark_transform_reduce::transform_reduce_hpx);
}

#define TRANSFORM_REDUCE_HPX_WRAPPER                                                               \
	BENCHMARK_TEMPLATE1(transform_reduce_hpx_wrapper, std::execution::parallel_unsequenced_policy) \
	    ->Name(BENCHMARK_NAME("hpx::transform_reduce"))                                            \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                                    \
	    ->Range(MIN_INPUT_SIZE, MAX_INPUT_SIZE)                                                    \
	    ->UseManualTime();
#else
#define TRANSFORM_REDUCE_HPX_WRAPPER
#endif

#define TRANSFORM_REDUCE_GROUP   \
	TRANSFORM_REDUCE_SEQ_WRAPPER \
	TRANSFORM_REDUCE_STD_WRAPPER \
	TRANSFORM_REDUCE_HPX_WRAPPER

#endif //PSTL_BENCH_TRANSFORM_REDUCE_GROUP_H
