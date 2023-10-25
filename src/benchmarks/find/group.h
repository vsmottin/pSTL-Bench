
#ifndef PSTL_BENCH_FIND_GROUP_H
#define PSTL_BENCH_FIND_GROUP_H

#include "benchmark_prefix.h"

#include "find_utils.h"

#include "find_std.h"

#ifdef USE_GNU
#include "find_gnu.h"
#endif

#ifdef USE_HPX
#include "find_hpx.h"
#endif

//region find
template<class Policy>
static void find_random_entry(benchmark::State & state)
{
	benchmark_find::benchmark_find_random_wrapper<Policy>(state, benchmark_find::find_std);
}

template<class Policy>
static void find_first_entry(benchmark::State & state)
{
	benchmark_find::benchmark_find_first_wrapper<Policy>(state, benchmark_find::find_std);
}

template<class Policy>
static void find_last_entry(benchmark::State & state)
{
	benchmark_find::benchmark_find_last_wrapper<Policy>(state, benchmark_find::find_std);
}

template<class Policy>
static void find_non_existing_entry(benchmark::State & state)
{
	benchmark_find::benchmark_find_non_existing_wrapper<Policy>(state, benchmark_find::find_std);
}

#define FIND_SEQ_WRAPPER                                                           \
	BENCHMARK_TEMPLATE1(find_random_entry, std::execution::sequenced_policy)       \
	    ->Name(BENCHMARK_NAME_WITH_BACKEND("SEQ", "std::find_random_entry"))       \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                    \
	    ->Range(MIN_INPUT_SIZE, MAX_INPUT_SIZE);                                   \
	BENCHMARK_TEMPLATE1(find_first_entry, std::execution::sequenced_policy)        \
	    ->Name(BENCHMARK_NAME_WITH_BACKEND("SEQ", "std::find_first_entry"))        \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                    \
	    ->Range(MIN_INPUT_SIZE, MAX_INPUT_SIZE);                                   \
	BENCHMARK_TEMPLATE1(find_last_entry, std::execution::sequenced_policy)         \
	    ->Name(BENCHMARK_NAME_WITH_BACKEND("SEQ", "std::find_last_entry"))         \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                    \
	    ->Range(MIN_INPUT_SIZE, MAX_INPUT_SIZE);                                   \
	BENCHMARK_TEMPLATE1(find_non_existing_entry, std::execution::sequenced_policy) \
	    ->Name(BENCHMARK_NAME_WITH_BACKEND("SEQ", "std::find_non_existing_entry")) \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                    \
	    ->Range(MIN_INPUT_SIZE, MAX_INPUT_SIZE);

#ifdef USE_PSTL
#define FIND_STD_WRAPPER                                                          \
	BENCHMARK_TEMPLATE1(find_random_entry, std::execution::parallel_policy)       \
	    ->Name(BENCHMARK_NAME("std::find_random_entry"))                          \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                   \
	    ->Range(MIN_INPUT_SIZE, MAX_INPUT_SIZE);                                  \
	BENCHMARK_TEMPLATE1(find_first_entry, std::execution::parallel_policy)        \
	    ->Name(BENCHMARK_NAME("std::find_first_entry"))                           \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                   \
	    ->Range(MIN_INPUT_SIZE, MAX_INPUT_SIZE);                                  \
	BENCHMARK_TEMPLATE1(find_last_entry, std::execution::parallel_policy)         \
	    ->Name(BENCHMARK_NAME("std::find_last_entry"))                            \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                   \
	    ->Range(MIN_INPUT_SIZE, MAX_INPUT_SIZE);                                  \
	BENCHMARK_TEMPLATE1(find_non_existing_entry, std::execution::parallel_policy) \
	    ->Name(BENCHMARK_NAME("std::find_non_existing_entry"))                    \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                   \
	    ->Range(MIN_INPUT_SIZE, MAX_INPUT_SIZE);
#else
#define FIND_STD_WRAPPER
#endif
//endregion find

//region find_gnu
#ifdef USE_GNU
template<class Policy>
static void find_gnu_random_entry(benchmark::State & state)
{
	benchmark_find::benchmark_find_random_wrapper<Policy>(state, benchmark_find::find_gnu);
}

template<class Policy>
static void find_gnu_first_entry(benchmark::State & state)
{
	benchmark_find::benchmark_find_first_wrapper<Policy>(state, benchmark_find::find_gnu);
}

template<class Policy>
static void find_gnu_last_entry(benchmark::State & state)
{
	benchmark_find::benchmark_find_last_wrapper<Policy>(state, benchmark_find::find_gnu);
}

template<class Policy>
static void find_gnu_non_existing_entry(benchmark::State & state)
{
	benchmark_find::benchmark_find_non_existing_wrapper<Policy>(state, benchmark_find::find_gnu);
}

#define FIND_GNU_WRAPPER                                                                           \
	BENCHMARK_TEMPLATE1(find_gnu_random_entry, std::execution::parallel_policy)                    \
	    ->Name(BENCHMARK_NAME("gnu::find_random_entry"))       \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                                    \
	    ->Range(MIN_INPUT_SIZE, MAX_INPUT_SIZE);                                                   \
	BENCHMARK_TEMPLATE1(find_gnu_first_entry, std::execution::parallel_policy)                     \
	    ->Name(BENCHMARK_NAME("gnu::find_first_entry"))        \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                                    \
	    ->Range(MIN_INPUT_SIZE, MAX_INPUT_SIZE);                                                   \
	BENCHMARK_TEMPLATE1(find_gnu_last_entry, std::execution::parallel_policy)                      \
	    ->Name(BENCHMARK_NAME("gnu::find_last_entry"))         \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                                    \
	    ->Range(MIN_INPUT_SIZE, MAX_INPUT_SIZE);                                                   \
	BENCHMARK_TEMPLATE1(find_gnu_non_existing_entry, std::execution::parallel_policy)              \
	    ->Name(BENCHMARK_NAME("gnu::find_non_existing_entry")) \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                                    \
	    ->Range(MIN_INPUT_SIZE, MAX_INPUT_SIZE);
#else
#define FIND_GNU_WRAPPER
#endif
//endregion find_gnu

//region find_hpx
#ifdef USE_HPX
template<class Policy>
static void find_hpx_random_entry(benchmark::State & state)
{
	benchmark_find::benchmark_find_random_wrapper<Policy>(state, benchmark_find::find_hpx);
}

template<class Policy>
static void find_hpx_first_entry(benchmark::State & state)
{
	benchmark_find::benchmark_find_first_wrapper<Policy>(state, benchmark_find::find_hpx);
}

template<class Policy>
static void find_hpx_last_entry(benchmark::State & state)
{
	benchmark_find::benchmark_find_last_wrapper<Policy>(state, benchmark_find::find_hpx);
}

template<class Policy>
static void find_hpx_non_existing_entry(benchmark::State & state)
{
	benchmark_find::benchmark_find_non_existing_wrapper<Policy>(state, benchmark_find::find_hpx);
}

#define FIND_HPX_WRAPPER                                                                           \
	BENCHMARK_TEMPLATE1(find_hpx_random_entry, std::execution::parallel_policy)                    \
	    ->Name(BENCHMARK_NAME("hpx::find_random_entry"))       \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                                    \
	    ->Range(MIN_INPUT_SIZE, MAX_INPUT_SIZE);                                                   \
	BENCHMARK_TEMPLATE1(find_hpx_first_entry, std::execution::parallel_policy)                     \
	    ->Name(BENCHMARK_NAME("hpx::find_first_entry"))        \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                                    \
	    ->Range(MIN_INPUT_SIZE, MAX_INPUT_SIZE);                                                   \
	BENCHMARK_TEMPLATE1(find_hpx_last_entry, std::execution::parallel_policy)                      \
	    ->Name(BENCHMARK_NAME("hpx::find_last_entry"))         \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                                    \
	    ->Range(MIN_INPUT_SIZE, MAX_INPUT_SIZE);                                                   \
	BENCHMARK_TEMPLATE1(find_hpx_non_existing_entry, std::execution::parallel_policy)              \
	    ->Name(BENCHMARK_NAME("hpx::find_non_existing_entry")) \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                                    \
	    ->Range(MIN_INPUT_SIZE, MAX_INPUT_SIZE);
#else
#define FIND_HPX_WRAPPER
#endif
//endregion find_hpx


// Register the function as a benchmark
#define FIND_GROUP   \
	FIND_SEQ_WRAPPER \
	FIND_STD_WRAPPER \
	FIND_GNU_WRAPPER \
	FIND_HPX_WRAPPER


#endif //PSTL_BENCH_FIND_GROUP_H
