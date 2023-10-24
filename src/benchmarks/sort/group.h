#ifndef PSTL_BENCH_SORT_GROUP_H
#define PSTL_BENCH_SORT_GROUP_H

#include "benchmark_prefix.h"

#include "sort_utils.h"

#include "sort_std.h"

#ifdef USE_GNU_PSTL
#include "sort_gnu.h"
#endif //USE_GNU_PSTL

//region sort_std
template<class Policy>
static void sort_std_already_sorted_wrapper(benchmark::State & state)
{
	benchmark_sort::already_sorted_wrapper<Policy>(state, benchmark_sort::sort_std);
}

template<class Policy>
static void sort_std_random_wrapper(benchmark::State & state)
{
	benchmark_sort::random_wrapper<Policy>(state, benchmark_sort::sort_std);
}

#define SORT_SEQ_WRAPPER                                                                   \
	BENCHMARK_TEMPLATE1(sort_std_already_sorted_wrapper, std::execution::sequenced_policy) \
	    ->Name(BENCHMARK_NAME("std::sort_already_sorted_seq"))                             \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                            \
	    ->Range(MIN_INPUT_SIZE, MAX_INPUT_SIZE);                                           \
	BENCHMARK_TEMPLATE1(sort_std_random_wrapper, std::execution::sequenced_policy)         \
	    ->Name(BENCHMARK_NAME("std::sort_random_seq"))                                     \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                            \
	    ->Range(MIN_INPUT_SIZE, MAX_INPUT_SIZE);

#ifdef USE_PSTL
#define SORT_STD_WRAPPER                                                                  \
	BENCHMARK_TEMPLATE1(sort_std_already_sorted_wrapper, std::execution::parallel_policy) \
	    ->Name(BENCHMARK_NAME("std::sort_already_sorted_par"))                            \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                           \
	    ->Range(MIN_INPUT_SIZE, MAX_INPUT_SIZE);                                          \
	BENCHMARK_TEMPLATE1(sort_std_random_wrapper, std::execution::parallel_policy)         \
	    ->Name(BENCHMARK_NAME("std::sort_random_par"))                                    \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                           \
	    ->Range(MIN_INPUT_SIZE, MAX_INPUT_SIZE);
#else
#define SORT_STD_WRAPPER
#endif
//endregion sort_std

//region sort_gnu
#ifdef USE_GNU_PSTL
template<class Policy>
static void sort_gnu_already_sorted_wrapper(benchmark::State & state)
{
	benchmark_sort::already_sorted_wrapper<Policy>(state, benchmark_sort::sort_gnu);
}

template<class Policy>
static void sort_gnu_random_wrapper(benchmark::State & state)
{
	benchmark_sort::random_wrapper<Policy>(state, benchmark_sort::sort_gnu);
}

#define SORT_GNU_WRAPPER                                                                  \
	BENCHMARK_TEMPLATE1(sort_gnu_already_sorted_wrapper, std::execution::parallel_policy) \
	    ->Name(BENCHMARK_NAME("gnu::sort_already_sorted_par"))                            \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                           \
	    ->Range(MIN_INPUT_SIZE, MAX_INPUT_SIZE);                                          \
	BENCHMARK_TEMPLATE1(sort_gnu_random_wrapper, std::execution::parallel_policy)         \
	    ->Name(BENCHMARK_NAME("gnu::sort_random_par"))                                    \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                           \
	    ->Range(MIN_INPUT_SIZE, MAX_INPUT_SIZE);
#else
#define SORT_GNU_WRAPPER
#endif
//endregion sort_gnu

#define SORT_GROUP   \
	SORT_SEQ_WRAPPER \
	SORT_STD_WRAPPER \
	SORT_GNU_WRAPPER

#endif //PSTL_BENCH_SORT_GROUP_H
