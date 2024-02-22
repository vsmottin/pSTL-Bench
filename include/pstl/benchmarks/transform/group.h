#ifndef PSTL_BENCH_TRANSFORM_GROUP_H
#define PSTL_BENCH_TRANSFORM_GROUP_H

#include "benchmark_prefix.h"

#include <benchmark/benchmark.h>

#include "transform_utils.h"

#include "transform_std.h"

#ifdef USE_GNU
#include "transform_gnu.h"
#endif

#ifdef USE_HPX
#include "transform_hpx.h"
#endif

//region transform
template<class Policy>
static void transform_std_wrapper(benchmark::State & state)
{
	benchmark_transform::benchmark_transform_wrapper<Policy>(state, benchmark_transform::transform_std);
}

#define TRANSFORM_SEQ_WRAPPER                                                    \
	BENCHMARK_TEMPLATE1(transform_std_wrapper, std::execution::sequenced_policy) \
	    ->Name(BENCHMARK_NAME_WITH_BACKEND("SEQ", "std::transform"))             \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                  \
	    ->Range(MIN_INPUT_SIZE, MAX_INPUT_SIZE)                                  \
	    ->UseManualTime();

#ifdef USE_PSTL
#define TRANSFORM_STD_WRAPPER                                                               \
	BENCHMARK_TEMPLATE1(transform_std_wrapper, std::execution::parallel_unsequenced_policy) \
	    ->Name(BENCHMARK_NAME("std::transform"))                                            \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                             \
	    ->Range(MIN_INPUT_SIZE, MAX_INPUT_SIZE)                                             \
	    ->UseManualTime();
#else
#define TRANSFORM_STD_WRAPPER
#endif
//endregion transform

//region transform_gnu
#ifdef USE_GNU
template<class Policy>
static void transform_gnu_wrapper(benchmark::State & state)
{
	benchmark_transform::benchmark_transform_wrapper<Policy>(state, benchmark_transform::transform_gnu);
}

#define TRANSFORM_GNU_WRAPPER                                                               \
	BENCHMARK_TEMPLATE1(transform_gnu_wrapper, std::execution::parallel_unsequenced_policy) \
	    ->Name(BENCHMARK_NAME("gnu::transform"))                                            \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                             \
	    ->Range(MIN_INPUT_SIZE, MAX_INPUT_SIZE)                                             \
	    ->UseManualTime();
#else
#define TRANSFORM_GNU_WRAPPER
#endif
//endregion transform_gnu

//region transform_hpx
#ifdef USE_HPX
template<class Policy>
static void transform_hpx_wrapper(benchmark::State & state)
{
	benchmark_transform::benchmark_transform_wrapper<Policy>(state, benchmark_transform::transform_hpx);
}

#define TRANSFORM_HPX_WRAPPER                                                               \
	BENCHMARK_TEMPLATE1(transform_hpx_wrapper, std::execution::parallel_unsequenced_policy) \
	    ->Name(BENCHMARK_NAME("hpx::transform"))                                            \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                             \
	    ->Range(MIN_INPUT_SIZE, MAX_INPUT_SIZE)                                             \
	    ->UseManualTime();
#else
#define TRANSFORM_HPX_WRAPPER
#endif

#define TRANSFORM_GROUP   \
	TRANSFORM_SEQ_WRAPPER \
	TRANSFORM_STD_WRAPPER \
	TRANSFORM_GNU_WRAPPER \
	TRANSFORM_HPX_WRAPPER

#endif //PSTL_BENCH_TRANSFORM_GROUP_H
