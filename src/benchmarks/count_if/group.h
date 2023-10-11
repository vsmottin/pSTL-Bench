#ifndef PSTL_BENCH_COUNT_IF_GROUP_H
#define PSTL_BENCH_COUNT_IF_GROUP_H

#include "count_if_utils.h"

#include "count_if_std.h"

#ifdef USE_OMP
#include "count_if_omp.h"
#endif

#ifdef USE_GNU_PSTL
#include "count_if_gnu.h"
#endif

//region count_if_std
template<class Policy>
static void count_if_std_wrapper(benchmark::State & state)
{
	benchmark_count_if::benchmark_wrapper<Policy>(state, benchmark_count_if::count_if_std);
}

#define COUNT_IF_STD_WRAPPER                                                    \
	BENCHMARK_TEMPLATE1(count_if_std_wrapper, std::execution::sequenced_policy) \
	    ->Name(BENCHMARK_NAME("std::count_if_seq"))                             \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                 \
	    ->Range(MAX_INPUT_SIZE, MAX_INPUT_SIZE);                                \
	BENCHMARK_TEMPLATE1(count_if_std_wrapper, std::execution::parallel_policy)  \
	    ->Name(BENCHMARK_NAME("std::count_if_par"))                             \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                 \
	    ->Range(1 << 2, MAX_INPUT_SIZE);
//endregion count_if_std

//region count_if_omp
#ifdef USE_OMP
template<class Policy>
static void count_if_omp_wrapper(benchmark::State & state)
{
	benchmark_count_if::benchmark_wrapper<Policy>(state, benchmark_count_if::count_if_omp);
}

#define COUNT_IF_OMP_WRAPPER                                                    \
	BENCHMARK_TEMPLATE1(count_if_omp_wrapper, std::execution::sequenced_policy) \
	    ->Name(BENCHMARK_NAME("omp::count_if_seq"))                             \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                 \
	    ->Range(MAX_INPUT_SIZE, MAX_INPUT_SIZE);                                \
	BENCHMARK_TEMPLATE1(count_if_omp_wrapper, std::execution::parallel_policy)  \
	    ->Name(BENCHMARK_NAME("omp::count_if_par"))                             \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                 \
	    ->Range(1 << 2, MAX_INPUT_SIZE);
#else
#define COUNT_IF_OMP_WRAPPER
#endif
//endregion count_if_omp

//region count_if_gnu
#ifdef USE_GNU_PSTL
template<class Policy>
static void count_if_gnu_wrapper(benchmark::State & state)
{
	benchmark_count_if::benchmark_wrapper<Policy>(state, benchmark_count_if::count_if_gnu);
}

#define COUNT_IF_GNU_WRAPPER                                                    \
	BENCHMARK_TEMPLATE1(count_if_gnu_wrapper, std::execution::sequenced_policy) \
	    ->Name(BENCHMARK_NAME("gnu::count_if_seq"))                             \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                 \
	    ->Range(MAX_INPUT_SIZE, MAX_INPUT_SIZE);                                \
	BENCHMARK_TEMPLATE1(count_if_gnu_wrapper, std::execution::parallel_policy)  \
	    ->Name(BENCHMARK_NAME("gnu::count_if_par"))                             \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                 \
	    ->Range(1 << 2, MAX_INPUT_SIZE);
#else
#define COUNT_IF_GNU_WRAPPER
#endif


#define COUNT_IF_GROUP   \
	COUNT_IF_STD_WRAPPER \
	COUNT_IF_OMP_WRAPPER \
	COUNT_IF_GNU_WRAPPER

#endif //PSTL_BENCH_COUNT_IF_GROUP_H
