#ifndef PSTL_BENCH_LEXICOGRAPHICAL_COMPARE_GROUP_H
#define PSTL_BENCH_LEXICOGRAPHICAL_COMPARE_GROUP_H

#include "benchmark_prefix.h"

#include "lexicographical_compare_utils.h"

#include "lexicographical_compare_std.h"

#ifdef USE_GNU
#include "lexicographical_compare_gnu.h"
#endif

#ifdef USE_HPX
#include "lexicographical_compare_hpx.h"
#endif

//region lexicographical_compare_std
template<class Policy>
static void lexicographical_compare_std_wrapper(benchmark::State & state)
{
	benchmark_lexicographical_compare::benchmark_wrapper<Policy>(
	    state, benchmark_lexicographical_compare::lexicographical_compare_std);
}

#define LEXICOGRAPHICAL_COMPARE_SEQ_WRAPPER                                                    \
	BENCHMARK_TEMPLATE1(lexicographical_compare_std_wrapper, std::execution::sequenced_policy) \
	    ->Name(BENCHMARK_NAME_WITH_BACKEND("SEQ", "std::lexicographical_compare"))             \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                                \
	    ->Range(MIN_INPUT_SIZE, MAX_INPUT_SIZE);

#ifdef USE_PSTL
#define LEXICOGRAPHICAL_COMPARE_STD_WRAPPER                                                   \
	BENCHMARK_TEMPLATE1(lexicographical_compare_std_wrapper, std::execution::parallel_policy) \
	    ->Name(BENCHMARK_NAME("std::lexicographical_compare"))                                \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                               \
	    ->Range(MIN_INPUT_SIZE, MAX_INPUT_SIZE);
#else
#define LEXICOGRAPHICAL_COMPARE_STD_WRAPPER
#endif
//endregion lexicographical_compare_std

//region lexicographical_compare_gnu
#ifdef USE_GNU
template<class Policy>
static void lexicographical_compare_gnu_wrapper(benchmark::State & state)
{
	benchmark_lexicographical_compare::benchmark_wrapper<Policy>(
	    state, benchmark_lexicographical_compare::lexicographical_compare_gnu);
}

#define LEXICOGRAPHICAL_COMPARE_GNU_WRAPPER                                                   \
	BENCHMARK_TEMPLATE1(lexicographical_compare_gnu_wrapper, std::execution::parallel_policy) \
	    ->Name(BENCHMARK_NAME("gnu::lexicographical_compare"))                                \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                               \
	    ->Range(MIN_INPUT_SIZE, MAX_INPUT_SIZE);
#else
#define LEXICOGRAPHICAL_COMPARE_GNU_WRAPPER
#endif
//endregion lexicographical_compare_gnu

//region lexicographical_compare_hpx
#ifdef USE_HPX
template<class Policy>
static void lexicographical_compare_hpx_wrapper(benchmark::State & state)
{
	benchmark_lexicographical_compare::benchmark_wrapper<Policy>(
	    state, benchmark_lexicographical_compare::lexicographical_compare_hpx);
}

#define LEXICOGRAPHICAL_COMPARE_HPX_WRAPPER                                                   \
	BENCHMARK_TEMPLATE1(lexicographical_compare_hpx_wrapper, std::execution::parallel_policy) \
	    ->Name(BENCHMARK_NAME("hpx::lexicographical_compare"))                                \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                               \
	    ->Range(MIN_INPUT_SIZE, MAX_INPUT_SIZE);
#else
#define LEXICOGRAPHICAL_COMPARE_HPX_WRAPPER
#endif

#define LEXICOGRAPHICAL_COMPARE_GROUP   \
	LEXICOGRAPHICAL_COMPARE_SEQ_WRAPPER \
	LEXICOGRAPHICAL_COMPARE_STD_WRAPPER \
	LEXICOGRAPHICAL_COMPARE_GNU_WRAPPER \
	LEXICOGRAPHICAL_COMPARE_HPX_WRAPPER

#endif //PSTL_BENCH_LEXICOGRAPHICAL_COMPARE_GROUP_H
