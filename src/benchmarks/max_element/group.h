#ifndef PSTL_BENCH_MAX_ELEMENT_GROUP_H
#define PSTL_BENCH_MAX_ELEMENT_GROUP_H

#include "benchmark_prefix.h"

#include "max_element_utils.h"

#include "max_element_std.h"

#ifdef USE_GNU
#include "max_element_gnu.h"
#endif

#ifdef USE_HPX
#include "max_element_hpx.h"
#endif

//region max_element_std
template<class Policy>
static void max_element_std_wrapper(benchmark::State & state)
{
	benchmark_max_element::benchmark_wrapper<Policy>(state, benchmark_max_element::max_element_std);
}

#define MAX_ELEMENT_SEQ_WRAPPER                                                    \
	BENCHMARK_TEMPLATE1(max_element_std_wrapper, std::execution::sequenced_policy) \
	    ->Name(BENCHMARK_NAME_WITH_BACKEND("SEQ", "std::max_element"))             \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                    \
	    ->Range(MIN_INPUT_SIZE, MAX_INPUT_SIZE);

#ifdef USE_PSTL
#define MAX_ELEMENT_STD_WRAPPER                                                               \
	BENCHMARK_TEMPLATE1(max_element_std_wrapper, std::execution::parallel_unsequenced_policy) \
	    ->Name(BENCHMARK_NAME("std::max_element"))                                            \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                               \
	    ->Range(MIN_INPUT_SIZE, MAX_INPUT_SIZE);
#else
#define MAX_ELEMENT_STD_WRAPPER
#endif
//endregion max_element_std

//region max_element_gnu
#ifdef USE_GNU
template<class Policy>
static void max_element_gnu_wrapper(benchmark::State & state)
{
	benchmark_max_element::benchmark_wrapper<Policy>(state, benchmark_max_element::max_element_gnu);
}

#define MAX_ELEMENT_GNU_WRAPPER                                                               \
	BENCHMARK_TEMPLATE1(max_element_gnu_wrapper, std::execution::parallel_unsequenced_policy) \
	    ->Name(BENCHMARK_NAME("gnu::max_element"))                                            \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                               \
	    ->Range(MIN_INPUT_SIZE, MAX_INPUT_SIZE);
#else
#define MAX_ELEMENT_GNU_WRAPPER
#endif
//endregion max_element_gnu

//region max_element_hpx
#ifdef USE_HPX
template<class Policy>
static void max_element_hpx_wrapper(benchmark::State & state)
{
	benchmark_max_element::benchmark_wrapper<Policy>(state, benchmark_max_element::max_element_hpx);
}

#define MAX_ELEMENT_HPX_WRAPPER                                                               \
	BENCHMARK_TEMPLATE1(max_element_hpx_wrapper, std::execution::parallel_unsequenced_policy) \
	    ->Name(BENCHMARK_NAME("hpx::max_element"))                                            \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                               \
	    ->Range(MIN_INPUT_SIZE, MAX_INPUT_SIZE);
#else
#define MAX_ELEMENT_HPX_WRAPPER
#endif

#define MAX_ELEMENT_GROUP   \
	MAX_ELEMENT_SEQ_WRAPPER \
	MAX_ELEMENT_STD_WRAPPER \
	MAX_ELEMENT_GNU_WRAPPER \
	MAX_ELEMENT_HPX_WRAPPER

#endif //PSTL_BENCH_MAX_ELEMENT_GROUP_H
