#ifndef PSTL_BENCH_EQUAL_GROUP_H
#define PSTL_BENCH_EQUAL_GROUP_H

#include "benchmark_prefix.h"

#include "equal_utils.h"

#include "equal_std.h"

#ifdef USE_GNU
#include "equal_gnu.h"
#endif

#ifdef USE_HPX
#include "equal_hpx.h"
#endif

//region equal_std
template<class Policy>
static void equal_std_wrapper(benchmark::State & state)
{
	benchmark_equal::benchmark_wrapper<Policy>(state, benchmark_equal::equal_std);
}

#define EQUAL_SEQ_WRAPPER                                                    \
	BENCHMARK_TEMPLATE1(equal_std_wrapper, std::execution::sequenced_policy) \
	    ->Name(BENCHMARK_NAME_WITH_BACKEND("SEQ", "std::equal"))             \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                              \
	    ->Range(MIN_INPUT_SIZE, MAX_INPUT_SIZE)                              \
	    ->UseManualTime();

#ifdef USE_PSTL
#define EQUAL_STD_WRAPPER                                                               \
	BENCHMARK_TEMPLATE1(equal_std_wrapper, std::execution::parallel_unsequenced_policy) \
	    ->Name(BENCHMARK_NAME("std::equal"))                                            \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                         \
	    ->Range(MIN_INPUT_SIZE, MAX_INPUT_SIZE)                                         \
	    ->UseManualTime();
#else
#define EQUAL_STD_WRAPPER
#endif
//endregion equal_std

//region equal_gnu
#ifdef USE_GNU
template<class Policy>
static void equal_gnu_wrapper(benchmark::State & state)
{
	benchmark_equal::benchmark_wrapper<Policy>(state, benchmark_equal::equal_gnu);
}

#define EQUAL_GNU_WRAPPER                                                               \
	BENCHMARK_TEMPLATE1(equal_gnu_wrapper, std::execution::parallel_unsequenced_policy) \
	    ->Name(BENCHMARK_NAME("gnu::equal"))                                            \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                         \
	    ->Range(MIN_INPUT_SIZE, MAX_INPUT_SIZE)                                         \
	    ->UseManualTime();
#else
#define EQUAL_GNU_WRAPPER
#endif

//region equal_hpx
#ifdef USE_HPX
template<class Policy>
static void equal_hpx_wrapper(benchmark::State & state)
{
	benchmark_equal::benchmark_wrapper<Policy>(state, benchmark_equal::equal_hpx);
}

#define EQUAL_HPX_WRAPPER                                                               \
	BENCHMARK_TEMPLATE1(equal_hpx_wrapper, std::execution::parallel_unsequenced_policy) \
	    ->Name(BENCHMARK_NAME("hpx::equal"))                                            \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                         \
	    ->Range(MIN_INPUT_SIZE, MAX_INPUT_SIZE)                                         \
	    ->UseManualTime();
#else
#define EQUAL_HPX_WRAPPER
#endif

#define EQUAL_GROUP   \
	EQUAL_SEQ_WRAPPER \
	EQUAL_STD_WRAPPER \
	EQUAL_GNU_WRAPPER \
	EQUAL_HPX_WRAPPER

#endif //PSTL_BENCH_EQUAL_GROUP_H
