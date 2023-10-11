#ifndef PSTL_BENCH_FOR_EACH_LINEAR_MANDELBROT_GROUP_H
#define PSTL_BENCH_FOR_EACH_LINEAR_MANDELBROT_GROUP_H

#include <benchmark/benchmark.h>

#include "../for_each_utils.h"

#include "for_each_std_linear_mandelbrot.h"

#ifdef USE_OMP
#include "for_each_omp_linear_mandelbrot.h"
#endif

#ifdef USE_GNU_PSTL
#include "for_each_gnu_linear_mandelbrot.h"
#endif

//region for_each_linear_mandelbrot
template<class Policy>
static void for_each_std_linear_mandelbrot_wrapper(benchmark::State & state)
{
	benchmark_for_each::benchmark_for_each_linear_mandelbrot_wrapper<Policy>(
	    state, benchmark_for_each::for_each_std_linear_mandelbrot);
}

#define FOR_EACH_STD_LINEAR_MANDELBROT_WRAPPER                                                    \
	BENCHMARK_TEMPLATE1(for_each_std_linear_mandelbrot_wrapper, std::execution::sequenced_policy) \
	    ->Name(BENCHMARK_NAME("std::for_each_linear_mandelbrot_seq"))                             \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                                   \
	    ->Range(MAX_INPUT_SIZE, MAX_INPUT_SIZE);                                                  \
	BENCHMARK_TEMPLATE1(for_each_std_linear_mandelbrot_wrapper, std::execution::parallel_policy)  \
	    ->Name(BENCHMARK_NAME("std::for_each_linear_mandelbrot_par"))                             \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                                   \
	    ->Range(1 << 5, MAX_INPUT_SIZE);
//endregion for_each_linear_mandelbrot

//region for_each_linear_mandelbrot_omp
#ifdef USE_OMP
template<class Policy>
static void for_each_omp_linear_mandelbrot_wrapper(benchmark::State & state)
{
	benchmark_for_each::benchmark_for_each_linear_mandelbrot_wrapper<Policy>(
	    state, benchmark_for_each::for_each_omp_linear_mandelbrot);
}

#define FOR_EACH_OMP_LINEAR_MANDELBROT_WRAPPER                                                    \
	BENCHMARK_TEMPLATE1(for_each_omp_linear_mandelbrot_wrapper, std::execution::sequenced_policy) \
	    ->Name(BENCHMARK_NAME("omp::for_each_linear_mandelbrot_seq"))                             \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                                   \
	    ->Range(MAX_INPUT_SIZE, MAX_INPUT_SIZE);                                                  \
	BENCHMARK_TEMPLATE1(for_each_omp_linear_mandelbrot_wrapper, std::execution::parallel_policy)  \
	    ->Name(BENCHMARK_NAME("omp::for_each_linear_mandelbrot_par"))                             \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                                   \
	    ->Range(1 << 5, MAX_INPUT_SIZE);
#else
#define FOR_EACH_OMP_LINEAR_MANDELBROT_WRAPPER
#endif
//endregion for_each_linear_mandelbrot_omp

//region for_each_linear_mandelbrot_gnu
#ifdef USE_GNU_PSTL
template<class Policy>
static void for_each_gnu_linear_mandelbrot_wrapper(benchmark::State & state)
{
	benchmark_for_each::benchmark_for_each_linear_mandelbrot_wrapper<Policy>(
	    state, benchmark_for_each::for_each_gnu_linear_mandelbrot);
}

#define FOR_EACH_GNU_LINEAR_MANDELBROT_WRAPPER                                                    \
	BENCHMARK_TEMPLATE1(for_each_gnu_linear_mandelbrot_wrapper, std::execution::sequenced_policy) \
	    ->Name(BENCHMARK_NAME("gnu::for_each_linear_mandelbrot_seq"))                             \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                                   \
	    ->Range(MAX_INPUT_SIZE, MAX_INPUT_SIZE);                                                  \
	BENCHMARK_TEMPLATE1(for_each_gnu_linear_mandelbrot_wrapper, std::execution::parallel_policy)  \
	    ->Name(BENCHMARK_NAME("gnu::for_each_linear_mandelbrot_par"))                             \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                                   \
	    ->Range(1 << 5, MAX_INPUT_SIZE);
#else
#define FOR_EACH_GNU_LINEAR_MANDELBROT_WRAPPER
#endif
//endregion for_each_linear_mandelbrot_gnu

#define FOR_EACH_LINEAR_MANDELBROT_GROUP   \
	FOR_EACH_STD_LINEAR_MANDELBROT_WRAPPER \
	FOR_EACH_OMP_LINEAR_MANDELBROT_WRAPPER \
	FOR_EACH_GNU_LINEAR_MANDELBROT_WRAPPER

#endif //PSTL_BENCH_FOR_EACH_LINEAR_MANDELBROT_GROUP_H
