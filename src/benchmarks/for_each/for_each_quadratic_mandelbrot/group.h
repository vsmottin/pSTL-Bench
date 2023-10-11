#ifndef PSTL_BENCH_FOR_EACH_QUADRATIC_MANDELBROT_GROUP_H
#define PSTL_BENCH_FOR_EACH_QUADRATIC_MANDELBROT_GROUP_H

#include <benchmark/benchmark.h>

#include "../for_each_utils.h"

#include "for_each_std_quadratic_mandelbrot.h"

#ifdef USE_OMP
#include "for_each_omp_quadratic_mandelbrot.h"
#endif

#ifdef USE_GNU_PSTL
#include "for_each_gnu_quadratic_mandelbrot.h"
#endif

//region for_each_quadratic_mandelbrot
template<class OuterPolicy, class InnerPolicy>
static void for_each_std_quadratic_mandelbrot_wrapper(benchmark::State & state)
{
	benchmark_for_each::benchmark_for_each_quadratic_mandelbrot_wrapper<OuterPolicy, InnerPolicy>(
	    state, benchmark_for_each::for_each_std_quadratic_mandelbrot);
}

#define FOR_EACH_QUADRATIC_MANDELBROT_WRAPPER(outer)                                                            \
	BENCHMARK_TEMPLATE2(for_each_std_quadratic_mandelbrot_wrapper, std::execution::sequenced_policy,            \
	                    std::execution::sequenced_policy)                                                       \
	    ->Name(BENCHMARK_NAME("std::for_each_quadratic_mandelbrot_outer_std::execution::sequenced_policy_seq")) \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                                                 \
	    ->Range(1 << 13, 1 << 13);                                                                              \
	BENCHMARK_TEMPLATE2(for_each_std_quadratic_mandelbrot_wrapper, outer, std::execution::parallel_policy)      \
	    ->Name(BENCHMARK_NAME("std::for_each_quadratic_mandelbrot_outer_" xstr(outer) "_par"))                  \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                                                 \
	    ->Range(1 << 5, 1 << 13);
//endregion for_each_quadratic_mandelbrot


//region for_each_quadratic_mandelbrot_omp
#ifdef USE_OMP
template<class OuterPolicy, class InnerPolicy>
static void for_each_omp_quadratic_mandelbrot_wrapper(benchmark::State & state)
{
	benchmark_for_each::benchmark_for_each_quadratic_mandelbrot_wrapper<OuterPolicy, InnerPolicy>(
	    state, benchmark_for_each::for_each_omp_quadratic_mandelbrot);
}

#define FOR_EACH_OMP_QUADRATIC_MANDELBROT_WRAPPER(outer)                                                        \
	BENCHMARK_TEMPLATE2(for_each_omp_quadratic_mandelbrot_wrapper, std::execution::sequenced_policy,            \
	                    std::execution::sequenced_policy)                                                       \
	    ->Name(BENCHMARK_NAME("omp::for_each_quadratic_mandelbrot_outer_std::execution::sequenced_policy_seq")) \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                                                 \
	    ->Range(1 << 13, 1 << 13);                                                                              \
	BENCHMARK_TEMPLATE2(for_each_omp_quadratic_mandelbrot_wrapper, outer, std::execution::parallel_policy)      \
	    ->Name(BENCHMARK_NAME("omp::for_each_quadratic_mandelbrot_outer_" xstr(outer) "_par"))                  \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                                                 \
	    ->Range(1 << 5, 1 << 13);
#else
#define FOR_EACH_OMP_QUADRATIC_MANDELBROT_WRAPPER(outer)
#endif
//endregion for_each_quadratic_mandelbrot_omp

//region for_each_quadratic_mandelbrot_gnu
#ifdef USE_GNU_PSTL
template<class OuterPolicy, class InnerPolicy>
static void for_each_gnu_quadratic_mandelbrot_wrapper(benchmark::State & state)
{
	benchmark_for_each::benchmark_for_each_quadratic_mandelbrot_wrapper<OuterPolicy, InnerPolicy>(
	    state, benchmark_for_each::for_each_gnu_quadratic_mandelbrot);
}

#define FOR_EACH_GNU_QUADRATIC_MANDELBROT_WRAPPER(outer)                                                        \
	BENCHMARK_TEMPLATE2(for_each_gnu_quadratic_mandelbrot_wrapper, std::execution::sequenced_policy,            \
	                    std::execution::sequenced_policy)                                                       \
	    ->Name(BENCHMARK_NAME("gnu::for_each_quadratic_mandelbrot_outer_std::execution::sequenced_policy_seq")) \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                                                 \
	    ->Range(1 << 13, 1 << 13);                                                                              \
	BENCHMARK_TEMPLATE2(for_each_gnu_quadratic_mandelbrot_wrapper, outer, std::execution::parallel_policy)      \
	    ->Name(BENCHMARK_NAME("gnu::for_each_quadratic_mandelbrot_outer_" xstr(outer) "_par"))                  \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                                                 \
	    ->Range(1 << 5, 1 << 13);
#else
#define FOR_EACH_GNU_QUADRATIC_MANDELBROT_WRAPPER(outer)
#endif
//endregion for_each_quadratic_mandelbrot_gnu


#define FOR_EACH_QUADRATIC_MANDELBROT_GROUP(outer)   \
	FOR_EACH_QUADRATIC_MANDELBROT_WRAPPER(outer)     \
	FOR_EACH_OMP_QUADRATIC_MANDELBROT_WRAPPER(outer) \
	FOR_EACH_GNU_QUADRATIC_MANDELBROT_WRAPPER(outer)

#endif //PSTL_BENCH_FOR_EACH_QUADRATIC_MANDELBROT_GROUP_H
