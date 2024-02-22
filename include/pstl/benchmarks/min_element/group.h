#ifndef PSTL_BENCH_MIN_ELEMENT_GROUP_H
#define PSTL_BENCH_MIN_ELEMENT_GROUP_H

#include "benchmark_prefix.h"

#include "min_element_utils.h"

#include "min_element_std.h"

#ifdef USE_GNU
#include "min_element_gnu.h"
#endif

#ifdef USE_HPX
#include "min_element_hpx.h"
#endif

//region min_element_std
template<class Policy>
static void min_element_std_wrapper(benchmark::State & state)
{
	benchmark_min_element::benchmark_wrapper<Policy>(state, benchmark_min_element::min_element_std);
}

#define MIN_ELEMENT_SEQ_WRAPPER                                                    \
	BENCHMARK_TEMPLATE1(min_element_std_wrapper, std::execution::sequenced_policy) \
	    ->Name(BENCHMARK_NAME_WITH_BACKEND("SEQ", "std::min_element"))             \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                    \
	    ->Range(MIN_INPUT_SIZE, MAX_INPUT_SIZE)                                    \
	    ->UseManualTime();

#ifdef USE_PSTL
#define MIN_ELEMENT_STD_WRAPPER                                                               \
	BENCHMARK_TEMPLATE1(min_element_std_wrapper, std::execution::parallel_unsequenced_policy) \
	    ->Name(BENCHMARK_NAME("std::min_element"))                                            \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                               \
	    ->Range(MIN_INPUT_SIZE, MAX_INPUT_SIZE)                                               \
	    ->UseManualTime();
#else
#define MIN_ELEMENT_STD_WRAPPER
#endif
//endregion min_element_std

//region min_element_gnu
#ifdef USE_GNU
template<class Policy>
static void min_element_gnu_wrapper(benchmark::State & state)
{
	benchmark_min_element::benchmark_wrapper<Policy>(state, benchmark_min_element::min_element_gnu);
}

#define MIN_ELEMENT_GNU_WRAPPER                                                               \
	BENCHMARK_TEMPLATE1(min_element_gnu_wrapper, std::execution::parallel_unsequenced_policy) \
	    ->Name(BENCHMARK_NAME("gnu::min_element"))                                            \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                               \
	    ->Range(MIN_INPUT_SIZE, MAX_INPUT_SIZE)                                               \
	    ->UseManualTime();
#else
#define MIN_ELEMENT_GNU_WRAPPER
#endif
//endregion min_element_gnu

//region min_element_hpx
#ifdef USE_HPX
template<class Policy>
static void min_element_hpx_wrapper(benchmark::State & state)
{
	benchmark_min_element::benchmark_wrapper<Policy>(state, benchmark_min_element::min_element_hpx);
}

#define MIN_ELEMENT_HPX_WRAPPER                                                               \
	BENCHMARK_TEMPLATE1(min_element_hpx_wrapper, std::execution::parallel_unsequenced_policy) \
	    ->Name(BENCHMARK_NAME("hpx::min_element"))                                            \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                               \
	    ->Range(MIN_INPUT_SIZE, MAX_INPUT_SIZE)                                               \
	    ->UseManualTime();
#else
#define MIN_ELEMENT_HPX_WRAPPER
#endif

#define MIN_ELEMENT_GROUP   \
	MIN_ELEMENT_SEQ_WRAPPER \
	MIN_ELEMENT_STD_WRAPPER \
	MIN_ELEMENT_GNU_WRAPPER \
	MIN_ELEMENT_HPX_WRAPPER

#endif //PSTL_BENCH_MIN_ELEMENT_GROUP_H
