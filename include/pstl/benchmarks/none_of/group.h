#ifndef PSTL_BENCH_NONE_OF_GROUP_H
#define PSTL_BENCH_NONE_OF_GROUP_H

#include "benchmark_prefix.h"

#include "none_of_utils.h"

#include "none_of_std.h"

#ifdef USE_HPX
#include "none_of_hpx.h"
#endif

//region none_of_std
template<class Policy>
static void none_of_std_wrapper(benchmark::State & state)
{
	benchmark_none_of::benchmark_wrapper<Policy>(state, benchmark_none_of::none_of_std);
}

#define NONE_OF_SEQ_WRAPPER                                                    \
	BENCHMARK_TEMPLATE1(none_of_std_wrapper, std::execution::sequenced_policy) \
	    ->Name(BENCHMARK_NAME_WITH_BACKEND("SEQ", "std::none_of"))             \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                \
	    ->Range(MIN_INPUT_SIZE, MAX_INPUT_SIZE)                                \
	    ->UseManualTime();

#ifdef USE_PSTL
#define NONE_OF_STD_WRAPPER                                                               \
	BENCHMARK_TEMPLATE1(none_of_std_wrapper, std::execution::parallel_unsequenced_policy) \
	    ->Name(BENCHMARK_NAME("std::none_of"))                                            \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                           \
	    ->Range(MIN_INPUT_SIZE, MAX_INPUT_SIZE)                                           \
	    ->UseManualTime();
#else
#define NONE_OF_STD_WRAPPER
#endif
//endregion none_of_std

//region none_of_hpx
#ifdef USE_HPX
template<class Policy>
static void none_of_hpx_wrapper(benchmark::State & state)
{
	benchmark_none_of::benchmark_wrapper<Policy>(state, benchmark_none_of::none_of_hpx);
}

#define NONE_OF_HPX_WRAPPER                                                               \
	BENCHMARK_TEMPLATE1(none_of_hpx_wrapper, std::execution::parallel_unsequenced_policy) \
	    ->Name(BENCHMARK_NAME("hpx::none_of"))                                            \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                           \
	    ->Range(MIN_INPUT_SIZE, MAX_INPUT_SIZE)                                           \
	    ->UseManualTime();
#else
#define NONE_OF_HPX_WRAPPER
#endif

#define NONE_OF_GROUP   \
	NONE_OF_SEQ_WRAPPER \
	NONE_OF_STD_WRAPPER \
	NONE_OF_HPX_WRAPPER

#endif //PSTL_BENCH_NONE_OF_GROUP_H
