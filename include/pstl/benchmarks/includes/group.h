#ifndef PSTL_BENCH_INCLUDES_GROUP_H
#define PSTL_BENCH_INCLUDES_GROUP_H

#include "benchmark_prefix.h"

#include "includes_utils.h"

#include "includes_std.h"

#ifdef USE_HPX
#include "includes_hpx.h"
#endif

//region includes_std
template<class Policy>
static void includes_std_wrapper(benchmark::State & state)
{
	benchmark_includes::benchmark_wrapper<Policy>(state, benchmark_includes::includes_std);
}

#define INCLUDES_SEQ_WRAPPER                                                    \
	BENCHMARK_TEMPLATE1(includes_std_wrapper, std::execution::sequenced_policy) \
	    ->Name(BENCHMARK_NAME_WITH_BACKEND("SEQ", "std::includes"))             \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                 \
	    ->Range(MIN_INPUT_SIZE, MAX_INPUT_SIZE);

#ifdef USE_PSTL
#define INCLUDES_STD_WRAPPER                                                               \
	BENCHMARK_TEMPLATE1(includes_std_wrapper, std::execution::parallel_unsequenced_policy) \
	    ->Name(BENCHMARK_NAME("std::includes"))                                            \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                            \
	    ->Range(MIN_INPUT_SIZE, MAX_INPUT_SIZE);
#else
#define INCLUDES_STD_WRAPPER
#endif
//endregion includes_std

//region includes_hpx
#ifdef USE_HPX
template<class Policy>
static void includes_hpx_wrapper(benchmark::State & state)
{
	benchmark_includes::benchmark_wrapper<Policy>(state, benchmark_includes::includes_hpx);
}

#define INCLUDES_HPX_WRAPPER                                                               \
	BENCHMARK_TEMPLATE1(includes_hpx_wrapper, std::execution::parallel_unsequenced_policy) \
	    ->Name(BENCHMARK_NAME("hpx::includes"))                                            \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                            \
	    ->Range(MIN_INPUT_SIZE, MAX_INPUT_SIZE);
#else
#define INCLUDES_HPX_WRAPPER
#endif

#define INCLUDES_GROUP   \
	INCLUDES_SEQ_WRAPPER \
	INCLUDES_STD_WRAPPER \
	INCLUDES_HPX_WRAPPER

#endif //PSTL_BENCH_INCLUDES_GROUP_H
