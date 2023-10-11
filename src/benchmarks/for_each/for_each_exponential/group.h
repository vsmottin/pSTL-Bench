#ifndef PSTL_BENCH_GROUP_H
#define PSTL_BENCH_GROUP_H

#include <benchmark/benchmark.h>

#include "../for_each_utils.h"

#include "for_each_std_exponential.h"

#ifdef USE_OMP
#include "for_each_omp_exponential.h"
#endif

#ifdef USE_GNU_PSTL
#include "for_each_gnu_exponential.h"
#endif

//region for_each_exponential
template<class Policy>
static void for_each_std_exponential_wrapper(benchmark::State & state)
{
	benchmark_for_each::benchmark_for_each_exponential_wrapper<Policy>(state,
	                                                                   benchmark_for_each::for_each_std_exponential);
}

#define FOR_EACH_STD_EXPONENTIAL_WRAPPER                                                    \
	BENCHMARK_TEMPLATE1(for_each_std_exponential_wrapper, std::execution::sequenced_policy) \
	    ->Name(BENCHMARK_NAME("std::for_each_exponential_seq"))                             \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                             \
	    ->Range(1 << 5, 1 << 5);                                                            \
	BENCHMARK_TEMPLATE1(for_each_std_exponential_wrapper, std::execution::parallel_policy)  \
	    ->Name(BENCHMARK_NAME("std::for_each_exponential_par"))                             \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                             \
	    ->Range(1 << 2, 1 << 5);
//endregion for_each_exponential

//region for_each_exponential_omp
#ifdef USE_OMP
template<class Policy>
static void for_each_omp_exponential_wrapper(benchmark::State & state)
{
	benchmark_for_each::benchmark_for_each_exponential_wrapper<Policy>(state,
	                                                                   benchmark_for_each::for_each_omp_exponential);
}

#define FOR_EACH_OMP_EXPONENTIAL_WRAPPER                                                    \
	BENCHMARK_TEMPLATE1(for_each_omp_exponential_wrapper, std::execution::sequenced_policy) \
	    ->Name(BENCHMARK_NAME("omp::for_each_exponential_seq"))                             \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                             \
	    ->Range(1 << 5, 1 << 5);                                                            \
	BENCHMARK_TEMPLATE1(for_each_omp_exponential_wrapper, std::execution::parallel_policy)  \
	    ->Name(BENCHMARK_NAME("omp::for_each_exponential_par"))                             \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                             \
	    ->Range(1 << 2, 1 << 5);
#else
#define FOR_EACH_OMP_EXPONENTIAL_WRAPPER
#endif
//endregion for_each_exponential_omp

//region for_each_exponential_gnu
#ifdef USE_GNU_PSTL
template<class Policy>
static void for_each_gnu_exponential_wrapper(benchmark::State & state)
{
	benchmark_for_each::benchmark_for_each_exponential_wrapper<Policy>(state,
	                                                                   benchmark_for_each::for_each_gnu_exponential);
}

#define FOR_EACH_GNU_EXPONENTIAL_WRAPPER                                                    \
	BENCHMARK_TEMPLATE1(for_each_gnu_exponential_wrapper, std::execution::sequenced_policy) \
	    ->Name(BENCHMARK_NAME("gnu::for_each_exponential_seq"))                             \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                             \
	    ->Range(1 << 5, 1 << 5);                                                            \
	BENCHMARK_TEMPLATE1(for_each_gnu_exponential_wrapper, std::execution::parallel_policy)  \
	    ->Name(BENCHMARK_NAME("gnu::for_each_exponential_par"))                             \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                             \
	    ->Range(1 << 2, 1 << 5);
#else
#define FOR_EACH_GNU_EXPONENTIAL_WRAPPER
#endif
//endregion for_each_exponential_gnu


#define FOR_EACH_EXPONENTIAL_GROUP   \
	FOR_EACH_STD_EXPONENTIAL_WRAPPER \
	FOR_EACH_OMP_EXPONENTIAL_WRAPPER \
	FOR_EACH_GNU_EXPONENTIAL_WRAPPER

#endif //PSTL_BENCH_GROUP_H
