#ifndef PSTL_BENCH_B1_2_GROUP_H
#define PSTL_BENCH_B1_2_GROUP_H

#include <benchmark/benchmark.h>

#include "../b1_utils.h"

#include "b1_2_for_each_linear_mandelbrot.h"

#ifdef USE_OMP
#include "b1_2_for_each_linear_mandelbrot_omp.h"
#endif

#ifdef USE_GNU_PSTL
#include "b1_2_for_each_linear_mandelbrot_gnu.h"
#endif

//region b1_2_for_each_linear_mandelbrot
template<class Policy>
static void b1_2_for_each_linear_mandelbrot_wrapper(benchmark::State & state)
{
	B1::benchmark_for_each_linear_mandelbrot_wrapper<Policy>(state, B1::b1_2_for_each_linear_mandelbrot);
}

#define B1_2_FOR_EACH_LINEAR_MANDELBROT_WRAPPER                                                    \
	BENCHMARK_TEMPLATE1(b1_2_for_each_linear_mandelbrot_wrapper, std::execution::sequenced_policy) \
	    ->Name(BENCHMARK_NAME("b1_2_for_each_linear_mandelbrot_seq"))                              \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                                    \
	    ->Range(MAX_INPUT_SIZE, MAX_INPUT_SIZE);                                                   \
	BENCHMARK_TEMPLATE1(b1_2_for_each_linear_mandelbrot_wrapper, std::execution::parallel_policy)  \
	    ->Name(BENCHMARK_NAME("b1_2_for_each_linear_mandelbrot_par"))                              \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                                    \
	    ->Range(1 << 5, MAX_INPUT_SIZE);
//endregion b1_2_for_each_linear_mandelbrot

//region b1_2_for_each_linear_mandelbrot_omp
#ifdef USE_OMP
template<class Policy>
static void b1_2_for_each_linear_mandelbrot_omp_wrapper(benchmark::State & state)
{
	B1::benchmark_for_each_linear_mandelbrot_wrapper<Policy>(state, B1::b1_2_for_each_linear_mandelbrot_omp);
}

#define B1_2_FOR_EACH_LINEAR_MANDELBROT_OMP_WRAPPER                                                    \
	BENCHMARK_TEMPLATE1(b1_2_for_each_linear_mandelbrot_omp_wrapper, std::execution::sequenced_policy) \
	    ->Name(BENCHMARK_NAME("b1_2_for_each_linear_mandelbrot_omp_seq"))                              \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                                        \
	    ->Range(MAX_INPUT_SIZE, MAX_INPUT_SIZE);                                                       \
	BENCHMARK_TEMPLATE1(b1_2_for_each_linear_mandelbrot_omp_wrapper, std::execution::parallel_policy)  \
	    ->Name(BENCHMARK_NAME("b1_2_for_each_linear_mandelbrot_omp_par"))                              \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                                        \
	    ->Range(1 << 5, MAX_INPUT_SIZE);
#else
#define B1_2_FOR_EACH_LINEAR_MANDELBROT_OMP_WRAPPER
#endif
//endregion b1_2_for_each_linear_mandelbrot_omp

//region b1_2_for_each_linear_mandelbrot_gnu
#ifdef USE_GNU_PSTL
template<class Policy>
static void b1_2_for_each_linear_mandelbrot_gnu_wrapper(benchmark::State & state)
{
	B1::benchmark_for_each_linear_mandelbrot_wrapper<Policy>(state, B1::b1_2_for_each_linear_mandelbrot_gnu);
}

#define B1_2_FOR_EACH_LINEAR_MANDELBROT_GNU_WRAPPER                                                    \
	BENCHMARK_TEMPLATE1(b1_2_for_each_linear_mandelbrot_gnu_wrapper, std::execution::sequenced_policy) \
	    ->Name(BENCHMARK_NAME("b1_2_for_each_linear_mandelbrot_gnu_seq"))                              \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                                        \
	    ->Range(MAX_INPUT_SIZE, MAX_INPUT_SIZE);                                                       \
	BENCHMARK_TEMPLATE1(b1_2_for_each_linear_mandelbrot_gnu_wrapper, std::execution::parallel_policy)  \
	    ->Name(BENCHMARK_NAME("b1_2_for_each_linear_mandelbrot_gnu_par"))                              \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                                        \
	    ->Range(1 << 5, MAX_INPUT_SIZE);
#else
#define B1_2_FOR_EACH_LINEAR_MANDELBROT_GNU_WRAPPER
#endif
//endregion b1_2_for_each_linear_mandelbrot_gnu

#define B1_2_FOR_EACH_LINEAR_MANDELBROT_GROUP   \
	B1_2_FOR_EACH_LINEAR_MANDELBROT_WRAPPER     \
	B1_2_FOR_EACH_LINEAR_MANDELBROT_OMP_WRAPPER \
	B1_2_FOR_EACH_LINEAR_MANDELBROT_GNU_WRAPPER

#endif //PSTL_BENCH_B1_2_GROUP_H
