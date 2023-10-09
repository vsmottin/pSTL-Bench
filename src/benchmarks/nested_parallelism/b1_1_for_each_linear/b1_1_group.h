#ifndef PSTL_BENCH_B1_1_GROUP_H
#define PSTL_BENCH_B1_1_GROUP_H

#include <benchmark/benchmark.h>

#include "../b1_utils.h"

#include "b1_1_for_each_linear.h"

#ifdef USE_OMP
#include "b1_1_for_each_linear_omp.h"
#endif

#ifdef USE_GNU_PSTL
#include "b1_1_for_each_linear_gnu.h"
#endif

//region b1_1_for_each_linear
template<class Policy>
static void b1_1_for_each_linear_wrapper(benchmark::State & state)
{
	B1::benchmark_for_each_linear_wrapper<Policy>(state, B1::b1_1_for_each_linear);
}

#define B1_1_FOR_EACH_LINEAR_WRAPPER                                                    \
	BENCHMARK_TEMPLATE1(b1_1_for_each_linear_wrapper, std::execution::sequenced_policy) \
	    ->Name(BENCHMARK_NAME("b1_1_for_each_linear_seq"))                              \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                         \
	    ->Range(MAX_INPUT_SIZE, MAX_INPUT_SIZE);                                        \
	BENCHMARK_TEMPLATE1(b1_1_for_each_linear_wrapper, std::execution::parallel_policy)  \
	    ->Name(BENCHMARK_NAME("b1_1_for_each_linear_par"))                              \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                         \
	    ->Range(1 << 5, MAX_INPUT_SIZE);
//endregion b1_1_for_each_linear

//region b1_1_for_each_linear_omp
#ifdef USE_OMP
template<class Policy>
static void b1_1_for_each_linear_omp_wrapper(benchmark::State & state)
{
	B1::benchmark_for_each_linear_wrapper<Policy>(state, B1::b1_1_for_each_linear_omp);
}

#define B1_1_FOR_EACH_LINEAR_OMP_WRAPPER                                                    \
	BENCHMARK_TEMPLATE1(b1_1_for_each_linear_omp_wrapper, std::execution::sequenced_policy) \
	    ->Name(BENCHMARK_NAME("b1_1_for_each_linear_omp_seq"))                              \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                             \
	    ->Range(MAX_INPUT_SIZE, MAX_INPUT_SIZE);                                            \
	BENCHMARK_TEMPLATE1(b1_1_for_each_linear_omp_wrapper, std::execution::parallel_policy)  \
	    ->Name(BENCHMARK_NAME("b1_1_for_each_linear_omp_par"))                              \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                             \
	    ->Range(1 << 5, MAX_INPUT_SIZE);
#else
#define B1_1_FOR_EACH_LINEAR_OMP_WRAPPER
#endif
//endregion b1_1_for_each_linear_omp

//region b1_1_for_each_linear_gnu
#ifdef USE_GNU_PSTL
template<class Policy>
static void b1_1_for_each_linear_gnu_wrapper(benchmark::State & state)
{
	B1::benchmark_for_each_linear_wrapper<Policy>(state, B1::b1_1_for_each_linear_gnu);
}

#define B1_1_FOR_EACH_LINEAR_GNU_WRAPPER                                                    \
	BENCHMARK_TEMPLATE1(b1_1_for_each_linear_gnu_wrapper, std::execution::sequenced_policy) \
	    ->Name(BENCHMARK_NAME("b1_1_for_each_linear_gnu_seq"))                              \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                             \
	    ->Range(MAX_INPUT_SIZE, MAX_INPUT_SIZE);                                            \
	BENCHMARK_TEMPLATE1(b1_1_for_each_linear_gnu_wrapper, std::execution::parallel_policy)  \
	    ->Name(BENCHMARK_NAME("b1_1_for_each_linear_gnu_par"))                              \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                             \
	    ->Range(1 << 5, MAX_INPUT_SIZE);
#else
#define B1_1_FOR_EACH_LINEAR_GNU_WRAPPER
#endif
//endregion b1_1_for_each_linear_gnu


#define B1_1_FOR_EACH_LINEAR_GROUP   \
	B1_1_FOR_EACH_LINEAR_WRAPPER     \
	B1_1_FOR_EACH_LINEAR_OMP_WRAPPER \
	B1_1_FOR_EACH_LINEAR_GNU_WRAPPER

#endif //PSTL_BENCH_B1_1_GROUP_H
