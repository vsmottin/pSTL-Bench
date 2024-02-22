#ifndef PSTL_BENCH_ALL_OF_GROUP_H
#define PSTL_BENCH_ALL_OF_GROUP_H

#include "benchmark_prefix.h"

#include "all_of_utils.h"

#include "all_of_std.h"

#ifdef USE_HPX
#include "all_of_hpx.h"
#endif

//region all_of_std
template<class Policy>
static void all_of_std_wrapper(benchmark::State & state)
{
	benchmark_all_of::benchmark_wrapper<Policy>(state, benchmark_all_of::all_of_std);
}

#define ALL_OF_SEQ_WRAPPER                                                    \
	BENCHMARK_TEMPLATE1(all_of_std_wrapper, std::execution::sequenced_policy) \
	    ->Name(BENCHMARK_NAME_WITH_BACKEND("SEQ", "std::all_of"))             \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                               \
	    ->Range(MIN_INPUT_SIZE, MAX_INPUT_SIZE)                               \
	    ->UseManualTime();

#ifdef USE_PSTL
#define ALL_OF_STD_WRAPPER                                                               \
	BENCHMARK_TEMPLATE1(all_of_std_wrapper, std::execution::parallel_unsequenced_policy) \
	    ->Name(BENCHMARK_NAME("std::all_of"))                                            \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                          \
	    ->Range(MIN_INPUT_SIZE, MAX_INPUT_SIZE)                                          \
	    ->UseManualTime();
#else
#define ALL_OF_STD_WRAPPER
#endif
//endregion all_of_std

//region all_of_hpx
#ifdef USE_HPX
template<class Policy>
static void all_of_hpx_wrapper(benchmark::State & state)
{
	benchmark_all_of::benchmark_wrapper<Policy>(state, benchmark_all_of::all_of_hpx);
}

#define ALL_OF_HPX_WRAPPER                                                               \
	BENCHMARK_TEMPLATE1(all_of_hpx_wrapper, std::execution::parallel_unsequenced_policy) \
	    ->Name(BENCHMARK_NAME("hpx::all_of"))                                            \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                          \
	    ->Range(MIN_INPUT_SIZE, MAX_INPUT_SIZE)                                          \
	    ->UseManualTime();
#else
#define ALL_OF_HPX_WRAPPER
#endif

#define ALL_OF_GROUP   \
	ALL_OF_SEQ_WRAPPER \
	ALL_OF_STD_WRAPPER \
	ALL_OF_HPX_WRAPPER

#endif //PSTL_BENCH_ALL_OF_GROUP_H
